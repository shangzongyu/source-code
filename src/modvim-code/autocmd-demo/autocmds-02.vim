augroup demo
  autocmd!
  autocmd BufReadPost *.vim,vimrc
        \ echo 'Editing Vim script: ' . expand('<afile>')
augroup END
