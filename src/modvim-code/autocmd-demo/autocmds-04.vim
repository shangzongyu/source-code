augroup demo
  autocmd!
  autocmd FileType vim
        \ echo 'Editing Vim script: ' . expand('<afile>') . '\n'
        \ . 'Filetype: '. expand('<amatch>')
augroup END
