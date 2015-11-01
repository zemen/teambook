syntax on
set ai
set si
set nu
set expandtab
set tabstop=4
set shiftwidth=4
cinwords+=forn,forab

imap jj <esc>
map <c-j> 5j
map <c-k> 5k
map gc ^i//<esc>
map gu ^xx

let $CPPFLAGS='-O2 -DLOCAL -Wall -Wextra -Wno-unused-result -std=c++11'
map <f9> :w<cr>:make %:r<cr>
map <f5> :!./%<<cr>

imap {<cr> {<cr>}<esc>kA<cr>
