augroup demo
  autocmd BufReadPost * echo 'Reading: ' . expand('<afile>')
  autocmd BufWritePost * echo 'Writing: ' . expand('<afile>')
augroup END
