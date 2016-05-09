#!/usr/bin/env bash

# Origin: http://superuser.com/questions/601198/how-can-i-automatically-convert-all-source-code-files-in-a-folder-recursively

tex_file=teambook.tex ## Not random temp file name

CODE_FONT="7.9 8.5"
TEXT_FONT="10 12"

renew_font() {
    echo  "\fontsize{$1}{$2}\selectfont"
}

truncate_script='\
/END.CODE/ { code = 0 } ;\
{ if (code) print $0 } ;\
/BEGIN.CODE/ { code = 1 };'

processed_code_dir=$(mktemp -d -p $(pwd))

echo "\input{header}" >$tex_file

src2latex() {
    filename=$1
    src=$2

    echo "\newpage" ## start each section on a new page
    echo "\section{${filename//_/\\_}}"  ## Create a section for each file

    ## This command will include the file in the PDF
    if [[ "$filename" == *.cpp ]]; then
        echo $(renew_font $CODE_FONT)
        echo "\inputminted[numbersep=1pt,linenos,breaklines]{c++}{$src}"
    elif [[ "$filename" == *.vim ]]; then
        echo $(renew_font $CODE_FONT)
        echo "\inputminted[linenos,breaklines]{vim}{$src}"
    elif [[ "$filename" == *.tex ]]; then
        echo $(renew_font $TEXT_FONT)
        echo "\input{${src::-4}}" # remove .tex suffix
    else
        echo $(renew_font $TEXT_FONT)
        echo "\inputminted[breaklines]{html}{$src}"
    fi
}

pictures() {
    for paper in misc/*; do
        cat << EOF
\twocolumn[
\section{Сеточка}
\includegraphics{$paper}
]
EOF
    done
}

find . -type f -regex "./algo.*\.\(cpp\|tex\)\|.*.txt" |
LC_ALL=C sort |
sed 's/^\..//' |
while read filename; do                ## Loop through each file
    echo "FOUND DOCUMENT $filename"

    if grep -q 'NO.TEAMBOOK' $filename; then
        continue
    fi

    if grep -q 'BEGIN.CODE' $filename; then
        src=$(mktemp -p $processed_code_dir)
        cat $filename | awk "$truncate_script" >$src
    else
        src=$filename
    fi

    if [[ "$filename" == algo* ]]; then # remove algo/ prefix
        filename=${filename:5}
    fi

    src2latex "$filename" "$src" >>$tex_file
done

pictures >>$tex_file

echo "\end{document}" >> $tex_file

# TOC requires this to be run twice
for((i=0;i<2;++i)); do
    pdflatex -shell-escape $tex_file -output-directory
done

rm -f teambook.{fls,aux,log,out,toc,dvi}
rm -f teambook-pics.pdf
rm teambook.tex
rm -rf $processed_code_dir
rm -rf _minted-teambook
