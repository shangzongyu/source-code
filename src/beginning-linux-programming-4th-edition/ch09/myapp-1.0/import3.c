/*
   This is an important file for managing the project.
   It implements the canoncial "Hello World" program.

   Filename: $RCSfile$
*/

#include <stdlib.h>
#include <stdio.h>

static char *RCSinfo = "$Id$";

int main()
{
    printf("Hello World\n");
    printf("This is an extra line added later\n");
    printf("This file is under RCS control.  Its ID is \n%s\n", RCSinfo);
    exit(EXIT_SUCCESS);
}
 
