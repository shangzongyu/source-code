augroup configure_projects
  autocmd!
  autocmd User ProjectionistActivate call s:linters()
augroup END

function! s:linters() abort
  let l:linters = projectionist#query('linters')
  if len(l:linters) > 0
    let b:ale_linters = {&filetype: l:linters[0][1]}
  endif
endfunction
