/*  As usual let's get our definitions sorted first.  */

#include <unistd.h>
#include <stdlib.h>
#include <curses.h>

int main() 
{
    WINDOW *new_window_ptr;
    WINDOW *popup_window_ptr;
    int x_loop;
    int y_loop;
    char a_letter = 'a';

    initscr();

/*  Then we fill the base window with characters,
    refreshing the actual screen once the logical screen has been filled:
    move(5, 5);
    printw("%s", "Testing multiple windows");
    refresh();

    for (x_loop = 0; x_loop < COLS - 1; x_loop++) {
        for (y_loop = 0; y_loop < LINES - 1; y_loop++) {
            mvwaddch(stdscr, y_loop, x_loop, a_letter);
            a_letter++;
            if (a_letter > 'z') a_letter = 'a';
        }
    }

    refresh();
    sleep(2);

/*  Now we create a new 10x20 window
    and add some text to it before drawing it on the screen.  */

    new_window_ptr = newwin(10, 20, 5, 5);
    mvwprintw(new_window_ptr, 2, 2, "%s", "Hello World");
    mvwprintw(new_window_ptr, 5, 2, "%s", 
              "Notice how very long lines wrap inside the window");

    wrefresh(new_window_ptr);
    sleep(2);

/*  We now change the contents of the background window and, when we
refresh the screen, the window pointed to by new_window_ptr is obscured.  */

   a_letter = '0';
     for (x_loop = 0; x_loop < COLS - 1; x_loop++) {
        for (y_loop = 0; y_loop < LINES -1; y_loop++) {
            mvwaddch(stdscr, y_loop, x_loop, a_letter);
            a_letter++;
            if (a_letter > '9') a_letter = '0';
        }
    }

    refresh();
    sleep(2);

/*  If we make a call to refresh the new window, nothing will change,
    because we haven't changed the new window.  */

    wrefresh(new_window_ptr);
    sleep(2);

/*  But if we touch the window first
    and trick curses into thinking that the window has been changed.
    The next call to wrefresh will bring the new window to the front again.  */

    touchwin(new_window_ptr);
    wrefresh(new_window_ptr);
    sleep(2);

/*  Next, we add another overlapping window with a box around it.  */

    popup_window_ptr = newwin(10, 20, 8, 8);
    box(popup_window_ptr, '|', '-');
    mvwprintw(popup_window_ptr, 5, 2, "%s", "Pop Up Window!");
    wrefresh(popup_window_ptr);
    sleep(2);

/*  Then we fiddle with the new and pop-up windows before clearing and deleting them.  */

    touchwin(new_window_ptr);
    wrefresh(new_window_ptr);
    sleep(2);

    wclear(new_window_ptr);
    wrefresh(new_window_ptr);
    sleep(2);
    
    delwin(new_window_ptr);

    touchwin(popup_window_ptr);
    wrefresh(popup_window_ptr);
    sleep(2);
    
    delwin(popup_window_ptr);
    
    touchwin(stdscr);
    refresh();
    sleep(2);

    endwin();
    exit(EXIT_SUCCESS);
}

