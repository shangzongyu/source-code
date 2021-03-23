let current_compiler = "tardyscript"
CompilerSet makeprg=sleep\ 5;tsc\ $*\ --outDir\ build\ %
CompilerSet errorformat=%+A\ %#%f\ %#(%l\\\,%c):\ %m,%C%m
