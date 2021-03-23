augroup demo
  autocmd!
  autocmd BufNewFile,BufReadPost vimrc,*.vim
        \ echo 'Editing Vim script: ' . expand('<afile>')
augroup END
