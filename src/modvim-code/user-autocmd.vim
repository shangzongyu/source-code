function! s:UserFunction()
  echom "UserFunction() was called: "
  echom "<amatch>: ".expand('<amatch>')
  echom "<afile>: ".expand('<afile>')
  echom "<abuf>: ".expand('<abuf>')
endfunction

augroup user_au
  autocmd!
  autocmd User MyEvent call s:UserFunction()
augroup END

" After sourcing this file, call this by hand:
" :doautocmd User MyEvent
