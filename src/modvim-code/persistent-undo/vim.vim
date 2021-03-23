set undofile
set undodir=~/.vim/undo
augroup vimrc
  autocmd!
  autocmd BufWritePre /tmp/* setlocal noundofile
augroup END
