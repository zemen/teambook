#!/usr/bin/env bash

# Origin: http://superuser.com/questions/601198/how-can-i-automatically-convert-all-source-code-files-in-a-folder-recursively

tex_file=$(mktemp) ## Random temp file name

cat<<EOF >$tex_file   ## Print the tex file header
\documentclass[twocolumn]{article}                                               %% two-column document
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

# find . -type f -regex ".*\.\(cpp\|vim\|txt\)" ! -name ".*" ! -name "*~" |
find . -type f -regex "./algo.*\.cpp\|.*.txt" |
LC_ALL=C sort |
sed 's/^\..//' |                 ## Change ./foo/bar.src to foo/bar.src

while read  i; do                ## Loop through each file
    echo "FOUND DOCUMENT $i"

    echo "\newpage" >> $tex_file   ## start each section on a new page
    echo "\section{${i//_/\\_}}" >> $tex_file  ## Create a section for each file

    ## This command will include the file in the PDF
    if [[ "$i" == *.cpp ]]; then
        echo "\inputminted[linenos,breaklines,fontsize=\scriptsize]{c++}{$i}" >>$tex_file
        # echo "\lstinputlisting[style=stylecpp]{$i}" >>$tex_file
    elif [[ "$i" == *.vim ]]; then
        echo "\inputminted[linenos,breaklines]{vim}{$i}" >>$tex_file
    else    
        echo "\inputminted[breaklines]{html}{$i}" >>$tex_file
    fi
done &&
echo "\end{document}" >> $tex_file &&
# cp $tex_file teambook.tex && 
pdflatex -shell-escape $tex_file -output-directory . && 
pdflatex -shell-escape $tex_file -output-directory .  ## This needs to be run twice 
                                           ## for the TOC to be generated    

rm tmp.{aux,log,out,toc}
rm -rf _minted-tmp
mv tmp.pdf teambook.pdf
