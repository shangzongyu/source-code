/*  We include the following header files,
    define some character arrays and a pointer to those arrays
    and then initialize the curses structures.  */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>

int main() 
{
    const char witch_one[] = " First Witch  ";
    const char witch_two[] = " Second Witch ";
    const char *scan_ptr;

    initscr();

/*  Now for the three initial sets of text that appear at intervals on the screen.
    Note the on and off flagging of text attributes.  */

    move(5, 15);
    attron(A_BOLD);
    printw("%s", "Macbeth");
    attroff(A_BOLD);
    refresh();
    sleep(1);

    move(8, 15);
    attron(A_STANDOUT);
    printw("%s", "Thunder and Lightning");
    attroff(A_STANDOUT);
    refresh();
    sleep(1);

    move(10, 10);
    printw("%s", "When shall we three meet again");
    move(11, 23);
    printw("%s", "In thunder, lightning, or in rain ?");
    move(13, 10);
    printw("%s", "When the hurlyburly's done,");
    move(14,23);
    printw("%s", "When the battle's lost and won.");
    refresh();
    sleep(1);


/*  Lastly, the actors are identified and their names are inserted a character
    at the time.
We also add the reset function at the end of the main function.  */

    attron(A_DIM);
    scan_ptr = witch_one + strlen(witch_one) - 1;
    while(scan_ptr != witch_one) {
        move(10,10);
        insch(*scan_ptr--);
    }

    scan_ptr = witch_two + strlen(witch_two) - 1;
    while (scan_ptr != witch_two) {
        move(13, 10);
        insch(*scan_ptr--);
    }
    attroff(A_DIM);

    refresh();
    sleep(1); 

    move(LINES - 1, COLS - 1);
    refresh();
    sleep(1);

    endwin();
    exit(EXIT_SUCCESS);
}

