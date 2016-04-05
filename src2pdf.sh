#!/usr/bin/env bash

# Origin: http://superuser.com/questions/601198/how-can-i-automatically-convert-all-source-code-files-in-a-folder-recursively

tex_file=$(mktemp) ## Random temp file name

cat<<EOF >$tex_file   ## Print the tex file header
\documentclass{article}
\usepackage{libertine}
\usepackage{listings}
\usepackage{listingsutf8}
\usepackage[usenames,dvipsnames]{color}  %% Allow color names
\usepackage[utf8]{inputenc}
\usepackage[english,russian]{babel}
\lstdefinestyle{stylevim}{
  belowcaptionskip=1\baselineskip,
  xleftmargin=\parindent,
  language=C++,   %% Change this to whatever you write in
  breaklines=true, %% Wrap long lines
  basicstyle=\footnotesize\ttfamily,
  stringstyle=\color{Black},
  keywordstyle=\bfseries\color{OliveGreen},
  identifierstyle=\color{blue},
  xleftmargin=-8em,
}        
\lstdefinestyle{styletxt}{
  belowcaptionskip=1\baselineskip,
  xleftmargin=\parindent,
  breaklines=true, %% Wrap long lines
  basicstyle=\footnotesize\ttfamily,
  stringstyle=\color{Black},
  xleftmargin=-8em,
  keepspaces=true,
  extendedchars=false
}        
\lstdefinestyle{stylecpp}{
  belowcaptionskip=1\baselineskip,
  xleftmargin=\parindent,
  language=C++,   %% Change this to whatever you write in
  breaklines=true, %% Wrap long lines
  basicstyle=\footnotesize\ttfamily,
  commentstyle=\itshape\color{Gray},
  stringstyle=\color{Black},
  keywordstyle=\bfseries\color{OliveGreen},
  identifierstyle=\color{blue},
  xleftmargin=-8em,
}        
\usepackage[colorlinks=true,linkcolor=blue]{hyperref} 
\begin{document}
\tableofcontents

EOF

find . -type f -regex ".*\.\(cpp\|vim\|txt\)" ! -name ".*" ! -name "*~" |
sort |
sed 's/^\..//' |                 ## Change ./foo/bar.src to foo/bar.src

while read  i; do                ## Loop through each file
    echo "FOUND DOCUMENT $i"

    echo "\newpage" >> $tex_file   ## start each section on a new page
    echo "\section{${i//_/\\_}}" >> $tex_file  ## Create a section for each file

    ## This command will include the file in the PDF
    if [[ "$i" == *.cpp ]]; then
        echo "\lstinputlisting[style=stylecpp]{$i}" >>$tex_file
    elif [[ "$i" == *.vim ]]; then
        echo "\lstinputlisting[style=stylevim]{$i}" >>$tex_file
    else
        echo "\lstinputlisting[style=styletxt]{$i}" >>$tex_file
    fi
done &&
echo "\end{document}" >> $tex_file &&
# cp $tex_file teambook.tex && 
pdflatex $tex_file -output-directory . && 
pdflatex $tex_file -output-directory .  ## This needs to be run twice 
                                           ## for the TOC to be generated    

rm tmp.{aux,log,out,toc}
mv tmp.pdf teambook.pdf
