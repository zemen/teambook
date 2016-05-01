#!/usr/bin/env bash

# Origin: http://superuser.com/questions/601198/how-can-i-automatically-convert-all-source-code-files-in-a-folder-recursively

# tex_file=$(mktemp) ## Random temp file name
tex_file=teambook.tex ## Not random temp file name

cat<<EOF >$tex_file   ## Print the tex file header
\documentclass[twocolumn,a4paper]{article}                                       %% two-column document
\usepackage{minted}                                                              %% color code listings
\usepackage[utf8]{inputenc}                                                      %% UTF-8 support
\usepackage[english,russian]{babel}                                              %% Cyrillic support
\usepackage[colorlinks=true,linkcolor=blue]{hyperref}                            %% HTML table of contents
\usepackage[margin=0.4in,footskip=0in]{geometry}                                 %% page bounds
\usepackage{tocloft}                                                             %% dotted table of contents
\renewcommand\cftsecleader{\cftdotfill{\cftdotsep}}                              %% dotted table of contents
\renewcommand{\theFancyVerbLine}{\sffamily {\scriptsize \arabic{FancyVerbLine}}} %% numbers font size
\begin{document}
\tableofcontents

EOF

truncate_script='\
/END_CODE/ { code = 0 } ;\
{ if (code) print $0 } ;\
/BEGIN_CODE/ { code = 1 };'

processed_code_dir=$(mktemp -d -p $(pwd))

# find . -type f -regex ".*\.\(cpp\|vim\|txt\)" ! -name ".*" ! -name "*~" |
find . -type f -regex "./algo.*\.cpp\|.*.txt" |
LC_ALL=C sort |
sed 's/^\..//' |                 ## Change ./foo/bar.src to foo/bar.src

while read filename; do                ## Loop through each file
    echo "FOUND DOCUMENT $filename"

    if grep -q 'NO_TEAMBOOK' $filename; then
        continue
    fi

    if grep -q 'BEGIN_CODE' $filename; then
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
        echo "\inputminted[numbersep=1pt,linenos,breaklines,fontsize=\scriptsize]{c++}{$src}" >>$tex_file
        # echo "\lstinputlisting[style=stylecpp]{$filename}" >>$tex_file
    elif [[ "$filename" == *.vim ]]; then
        echo "\inputminted[linenos,breaklines]{vim}{$src}" >>$tex_file
    else    
        echo "\inputminted[breaklines]{html}{$src}" >>$tex_file
    fi
done &&
echo "\end{document}" >> $tex_file &&
# cp $tex_file teambook.tex && 
pdflatex -shell-escape $tex_file -output-directory . && 
pdflatex -shell-escape $tex_file -output-directory .  ## This needs to be run twice 
                                           ## for the TOC to be generated    

rm -f teambook.{aux,log,out,toc}
rm teambook.tex
rm -rf $processed_code_dir
rm -rf _minted-teambook
