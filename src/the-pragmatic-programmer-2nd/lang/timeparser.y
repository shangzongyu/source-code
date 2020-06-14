%{
/**
  * From "Domain Languages", a yacc specification for 
  * time input.
  */
#include <stdio.h>
#include <ctype.h>
int yylex(void);
#define YYDEBUG 1

enum {AM_MINS=0, PM_MINS=12*60};
%}
 
%token END_TOKEN DIGIT AM PM
%start time
 
%%
time:	  spec END_TOKEN
          { if ($1 >= 24*60) yyerror("Time is too large");
            printf("%d minutes past midnight\n", $1);
	    exit(0);
          }
        ;

spec:     hour ':' minute
          { $$ = $1 + $3;
          }
        | hour ':' minute ampm 
          { if ($1 > 11*60) yyerror("Hour out of range");
	    $$ = $1 + $3 + $4; 
	  }
        | hour ampm            
          { if ($1 > 11*60) yyerror("Hour out of range");
            $$ = $1 + $2; 
          }
        ;

hour:     hour_num
          { if ($1 > 23) yyerror("Hour out of range");
	    $$ = $1 * 60;
          };

minute:   DIGIT DIGIT 
          { $$ = $1*10 + $2;
            if ($$ > 59) yyerror("minute out of range"); 
          };

ampm:     AM                  { $$ = AM_MINS; }
        | PM                  { $$ = PM_MINS; }
        ;

hour_num: DIGIT               { $$ = $1; }
        | DIGIT DIGIT         { $$ = $1*10 + $2; }
        ;
%%

const char *cp;

int yylex() {
  char ch = *cp;

  if (!ch)
    return END_TOKEN;

  cp++;
  if (isdigit(ch)) {
    yylval = ch - '0';
    return DIGIT;
  }

  if (((ch == 'a') || (ch == 'p')) && (*cp == 'm')) {
    cp++;
    return (ch == 'a') ? AM : PM;
  }
  
  return ch;
}

int yyerror(char *str) {
  printf("Error: %s\n", str);
  exit(-1);
}
int main(int argc, char **argv) {
  if (argc > 1) {
    cp = argv[1];
    yyparse();	
  }
  return 0; /* never get here */
}
