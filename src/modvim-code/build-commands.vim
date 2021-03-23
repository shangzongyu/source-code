" Anti-pattern demonstration (with side-effects)
command! Build :compiler tsconfig | make
command! Lint :compiler tslint | make
