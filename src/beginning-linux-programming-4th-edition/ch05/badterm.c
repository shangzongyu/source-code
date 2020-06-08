#include <stdio.h>
#include <term.h>
#include <curses.h>
#include <stdlib.h>

int main()
{
    setupterm("unlisted", fileno(stdout), (int *)0);
    printf("Done.\n");
    exit(0);
}
