let current_compiler = "tslint"
let s:cpo_save = &cpo
set cpo-=C
CompilerSet makeprg=tslint\ $*\ -t\ prose\ -c\ tslint.json\ 'src/**/*.ts'
CompilerSet errorformat=
    \%EERROR:\ %f[%l\\\,\ %c]:\ %m,
    \%WWARNING:\ %f[%l\\\,\ %c]:\ %m,
    \%E%f[%l\\\,\ %c]:\ %m
let &cpo = s:cpo_save
unlet s:cpo_save
