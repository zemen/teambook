#!/usr/bin/env bash

# Origin: http://superuser.com/questions/601198/how-can-i-automatically-convert-all-source-code-files-in-a-folder-recursively

# tex_file=$(mktemp) ## Random temp file name
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

cat tex_header.tex >$tex_file

find . -type f -regex "./algo.*\.cpp\|.*.txt" |
LC_ALL=C sort |
sed 's/^\..//' |                 ## Change ./foo/bar.src to foo/bar.src

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

    echo "\newpage" >> $tex_file   ## start each section on a new page
    echo "\section{${filename//_/\\_}}" >> $tex_file  ## Create a section for each file

    ## This command will include the file in the PDF
    if [[ "$filename" == *.cpp ]]; then
        echo $(renew_font $CODE_FONT) >>$tex_file
        echo "\inputminted[numbersep=1pt,linenos,breaklines]{c++}{$src}" >>$tex_file
    elif [[ "$filename" == *.vim ]]; then
        echo "\inputminted[linenos,breaklines]{vim}{$src}" >>$tex_file
    else    
        echo $(renew_font $TEXT_FONT) >>$tex_file
        echo "\inputminted[breaklines]{html}{$src}" >>$tex_file
    fi
done &&

echo "\label{LastPage}" >> $tex_file &&
echo "\end{document}" >> $tex_file &&
# cp $tex_file teambook.tex && 
pdflatex -shell-escape $tex_file -output-directory . && 
pdflatex -shell-escape $tex_file -output-directory .  ## This needs to be run twice 

rm -f teambook.{fls,aux,log,out,toc,dvi}
rm teambook.tex
rm -rf $processed_code_dir
rm -rf _minted-teambook
