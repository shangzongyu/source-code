/*  This code, useupper.c, accepts a file name as an argument
    and will respond with an error if called incorrectly.  */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    char *filename;

    if(argc != 2) {
        fprintf(stderr, "usage: useupper file\n");
        exit(1);
    }

    filename = argv[1];

/*  That done, we reopen the standard input, again checking for any errors as we do so,
    and then use execl to call upper.  */

    if(!freopen(filename, "r", stdin)) {
        fprintf(stderr, "could not redirect stdin to file %s\n", filename);
        exit(2);
    }

    execl("./upper", "upper", 0);

/*  Don't forget that execl replaces the current process;
    provided there is no error, the remaining lines are not executed.  */

    perror("could not exec ./upper");
    exit(3);
}
