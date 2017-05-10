syntax on
set ai si nu et ts=4 sts=4 sw=4 tm=300 cin cinw+=forn spr
set bs=indent,eol,start

imap jk <esc>:w<cr>
imap jj <esc>
map <c-j> 5j
map <c-k> 5k
map gc ^i//<esc>
map gu ^xx
map H ^
map L $
imap {<cr> {<cr>}<esc>O

map <f9> :w<cr>:!g++ -O2 -DLOCAL -Wno-unused-result -std=c++11 -Wall -Wextra -o %< %<cr>
map <f5> :w<cr>:!%<<cr>

set guifont=Consolas:cRUSSIAN
