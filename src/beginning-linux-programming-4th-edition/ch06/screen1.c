/* A simple program to show basic use of the curses library */

#include <unistd.h>
#include <stdlib.h>
#include <curses.h>

int main() {
    initscr();

/*  We move the cursor to the point (5,15) on the logical screen,
    print "Hello World" and refresh the actual screen.
    Lastly, we use the call sleep(2) to suspend the program for two seconds,
    so we can see the output before the program ends.  */

    move(5, 15);
    printw("%s", "Hello World");
    refresh();

    sleep(2);

    endwin();
    exit(EXIT_SUCCESS);
}

