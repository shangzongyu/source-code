augroup configure_projects
  autocmd!
  autocmd User ProjectionistActivate call s:hardwrap()
augroup END

function! s:hardwrap() abort
  for [root, value] in projectionist#query('hardwrap')
    let &l:textwidth = value
    break
  endfor
endfunction
