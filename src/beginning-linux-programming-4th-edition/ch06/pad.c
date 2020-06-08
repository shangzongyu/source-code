/*  At the start of this program, we initialize the pad structure
    and then create a pad, which returns a pointer to that pad.
    We add characters to fill the pad structure
    (which is 50 characters wider and longer than the terminal display.  */

#include <unistd.h>
#include <stdlib.h>
#include <curses.h>

int main() 
{
    WINDOW *pad_ptr;
    int x, y;
    int pad_lines;
    int pad_cols;
    char disp_char;

    initscr();

    pad_lines = LINES + 50;
    pad_cols = COLS + 50;

    pad_ptr = newpad(pad_lines, pad_cols);

    disp_char = 'a';
    for (x = 0; x < pad_lines; x++) {
        for (y = 0; y < pad_cols; y++) {
            mvwaddch(pad_ptr, x, y, disp_char);
            if (disp_char == 'z') disp_char = 'a';
            else disp_char++;
        }
    }

/*  We can now draw different areas of the pad on the screen at different locations
    before quitting.  */

    prefresh(pad_ptr, 5, 7, 2, 2, 9, 9);
    sleep(1);

    prefresh(pad_ptr, LINES + 5, COLS + 7, 5, 5, 21, 19);
    sleep(1);

    delwin(pad_ptr);

    endwin();
    exit(EXIT_SUCCESS);
}

