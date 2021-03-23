function! CurrentTime()
  let l:time = "00:00"
  if exists("*strftime")
    let l:time = strftime("%H:%M")
  endif
  return l:time
endfunction
