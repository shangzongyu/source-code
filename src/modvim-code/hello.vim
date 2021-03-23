function! SayHello()
  echo 'Hello, world!'
endfunction

command! Hello call SayHello()

nnoremap Q :Hello<CR>
