/*  Having initialized the program and the curses library, we set the Keypad mode TRUE.  */

#include <unistd.h>
#include <stdlib.h>
#include <curses.h>

#define LOCAL_ESCAPE_KEY    27

int main() 
{
    int key;

    initscr();
    crmode();
    keypad(stdscr, TRUE);

/*  Next, we must turn echo off
    to prevent the cursor being moved when some cursor keys are pressed.
    The screen is cleared and some text displayed.
    The program waits for each key stroke
    and, unless it's q, or produces an error, the key is printed.
    If the key strokes match one of the terminal's keypad sequences, 
    then that sequence is printed instead.  */

    noecho(); 

    clear();
    mvprintw(5, 5, "Key pad demonstration. Press 'q' to quit");
    move(7, 5);
    refresh();

    key = getch();
    while(key != ERR && key != 'q') {
        move(7, 5);
        clrtoeol();

        if ((key >= 'A' && key <= 'Z') ||
            (key >= 'a' && key <= 'z')) {
            printw("Key was %c", (char)key);
        }
        else {
            switch(key) {
            case LOCAL_ESCAPE_KEY: printw("%s", "Escape key"); break;
            case KEY_END: printw("%s", "END key"); break;
            case KEY_BEG: printw("%s", "BEGINNING key"); break;
            case KEY_RIGHT: printw("%s", "RIGHT key"); break;
            case KEY_LEFT: printw("%s", "LEFT key"); break;
            case KEY_UP: printw("%s", "UP key"); break;
            case KEY_DOWN: printw("%s", "DOWN key"); break;
            default: printw("Unmatched - %d", key); break;
            } /* switch */
        } /* else */

        refresh();
        key = getch();
    } /* while */

    endwin();
    exit(EXIT_SUCCESS);
}
