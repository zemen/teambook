syntax on
set ai
set si
set nu
set et
set ts=4
set sts=4
set sw=4
set tm=300
set cin
set cinw+=forn,forab

imap jk <esc>:w<cr>
imap jj <esc>
map <c-j> 5j
map <c-k> 5k
map gc ^i//<esc>
map gu ^xx
map H ^
map L $
imap {<cr> {<cr>}<esc>O

let $CPPFLAGS='-O2 -DLOCAL -Wall -Wextra -Wno-unused-result -std=c++11'
map <f9> :w<cr>:make %:r<cr>
map <f5> :w<cr>:!./%<<cr>
