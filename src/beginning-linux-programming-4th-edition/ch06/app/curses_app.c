/*
   CD Database Application

   Beginning Linux Programming

   Version: Terminals

   Copyright (c) 1996,2007 Wrox Press

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Fee Software Foundation; either version 2 of the License, or (at
   your option) any later version.

   This program is distributed in the hopes that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc. 675 Mass Ave, Cambridge, MA 02139, USA.

 */

/*
   Notes

   This version of the CD database application has been written
   using the information presented in the Terminals chapter.

   It is derived from the shell script presented in the Shell
   Programming chapter. It has not been redesigned for the C
   implementation, so many features of the shell original can
   still be seen in this version.

   There are some problems with this implementation that will
   be resolved in later revisions:

   It does not deal with commas in titles.
   It has a practical limit on tracks per CD to keep them on screen.

   The program deliberately uses the standard input and output
   file streams. It does not deal with re-directed input or
   output explicitly.  */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <curses.h>


#define MAX_STRING (80)		/* Longest allowed response       */
#define MAX_ENTRY (1024)	/* Longest allowed database entry */

#define MESSAGE_LINE 6		/* Misc. messages go here         */
#define ERROR_LINE   22		/* The line to use for errors     */
#define Q_LINE       20		/* Line for Questions             */
#define PROMPT_LINE  18		/* Line for prompting on          */

/*
   The variable current_cd is used to store the CD title we are
   working with. It is initialized so that the first character is NUL
   to indicate 'no CD selected'. The \0 is strictly unnecessary, but
   serves to emphasize the point.

   The variable current_cat will be used to record the catalog number
   of the current CD.
 */

static char current_cd[MAX_STRING] = "\0";
static char current_cat[MAX_STRING];

/*
   File names.

   These files are fixed in this version to keep things simple.
   The temporary file name is also fixed, this would cause a
   problem if this program is run by two users in the same directory.

   A better way to obtain data base file names would be either by
   program arguments, or from environment variables.

   We need a better way to generate a unique a temporary file name.

   Many of these issues will be addresed in later versions.
 */

const char *title_file = "title.cdb";
const char *tracks_file = "tracks.cdb";
const char *temp_file = "cdb.tmp";


/* Prototypes for local functions */
void clear_all_screen(void);
void get_return(void);
int get_confirm(void);
int getchoice(char *greet, char *choices[]);
void draw_menu(char *options[], int highlight, int start_row, int start_col);
void insert_title(char *cdtitle);
void get_string(char *string);
void add_record(void);
void count_cds(void);
void find_cd(void);
void list_tracks(void);
void remove_tracks(void);
void remove_cd(void);
void update_cd(void);


/*
   Menu structures.
   The first character is the character to return when the
   chice is selected, the remaining text is to be displayed.
 */
char *main_menu[] =
{
    "aadd new CD",
    "ffind CD",
    "ccount CDs and tracks in the catalog",
    "qquit",
    0,
};

/*
   The extended menu is displayed when a CD is currently selected
 */
char *extended_menu[] =
{
    "aadd new CD",
    "ffind CD",
    "ccount CDs and tracks in the catalog",
    "llist tracks on current CD",
    "rremove current CD",
    "uupdate track information",
    "qquit",
    0,
};

int main()
{
    int choice;

    initscr();

    do {

	choice = getchoice("Options:", current_cd[0] ? extended_menu : main_menu);

	switch (choice) {
	case 'q':
	    break;

	case 'a':
	    add_record();
	    break;

	case 'c':
	    count_cds();
	    break;

	case 'f':
	    find_cd();
	    break;

	case 'l':
	    list_tracks();
	    break;

	case 'r':
	    remove_cd();
	    break;

	case 'u':
	    update_cd();
	    break;
	}
    } while (choice != 'q');

    endwin();
    exit(EXIT_SUCCESS);

}				/* main */

/*
   getchoice - ask the user to choose
   passed: greet, an introduction
   choices, an array of strings, NULL at end
 */
int getchoice(char *greet, char *choices[])
{
    static int selected_row = 0;
    int max_row = 0;
    int start_screenrow = MESSAGE_LINE, start_screencol = 10;
    char **option;
    int selected;
    int key = 0;

    option = choices;
    while (*option) {
	max_row++;
	option++;
    }

    /* protect against menu getting shorted when CD deleted */
    if (selected_row >= max_row)
	selected_row = 0;

    clear_all_screen();
    mvprintw(start_screenrow - 2, start_screencol, greet);

    keypad(stdscr, TRUE);
    cbreak();
    noecho();

    key = 0;
    while (key != 'q' && key != KEY_ENTER && key != '\n') {
	if (key == KEY_UP) {
	    if (selected_row == 0)
		selected_row = max_row - 1;
	    else
		selected_row--;
	}
	if (key == KEY_DOWN) {
	    if (selected_row == (max_row - 1))
		selected_row = 0;
	    else
		selected_row++;
	}
	selected = *choices[selected_row];
	draw_menu(choices, selected_row, start_screenrow, start_screencol);
	key = getch();
    }

    keypad(stdscr, FALSE);
    nocbreak();
    echo();

    if (key == 'q')
	selected = 'q';

    return (selected);

}

void draw_menu(char *options[], int current_highlight, int start_row, int start_col)
{
    int current_row = 0;
    char **option_ptr;
    char *txt_ptr;

    option_ptr = options;
    while (*option_ptr) {
	if (current_row == current_highlight) attron(A_STANDOUT);
	txt_ptr = options[current_row];
	txt_ptr++;
	mvprintw(start_row + current_row, start_col, "%s", txt_ptr);
	if (current_row == current_highlight) attroff(A_STANDOUT);
	current_row++;
	option_ptr++;
    }

    mvprintw(start_row + current_row + 3, start_col, "Move highlight then press Return ");

    refresh();
}

/*
   clear_all_screen

   Clear the screen and re-write the title.
   If a CD is selected then display the information.
 */
void clear_all_screen()
{
    clear();
    mvprintw(2, Q_LINE, "%s", "CD Database Application");
    if (current_cd[0]) {
	mvprintw(ERROR_LINE, 0, "Current CD: %s: %s\n", current_cat, current_cd);
    }
    refresh();
}


/*
   get_return

   Prompt for and read a carriage return.
   Ignore other characters.
 */
void get_return()
{
    int ch;
    mvprintw(23, 0, "%s", " Press return ");
    refresh();
    while ((ch = getchar()) != '\n' && ch != EOF);
}

/*
   get_confirm

   Prompt for and read confirmation.
   Read a string and check first character for Y or y.
   On error or other character return no confirmation.
 */
int get_confirm()
{
    int confirmed = 0;
    char first_char = 'N';

    mvprintw(Q_LINE, 5, "Are you sure? ");
    clrtoeol();
    refresh();

    cbreak();
    first_char = getch();
    if (first_char == 'Y' || first_char == 'y') {
	confirmed = 1;
    }
    nocbreak();

    if (!confirmed) {
	mvprintw(Q_LINE, 1, "    Cancelled");
	clrtoeol();
	refresh();
	sleep(1);
    }
    return confirmed;
}


/*
   Database File Manipulation Functions
 */

/*
   insert_title

   Add a title to the CD database
   Simply add the title string to the end of the titles file

 */
void insert_title(char *cdtitle)
{
    FILE *fp = fopen(title_file, "a");
    if (!fp) {
	mvprintw(ERROR_LINE, 0, "cannot open CD titles database");
    } else {
	fprintf(fp, "%s\n", cdtitle);
	fclose(fp);
    }
}


/*
   get_string

   At the current screen position prompt for and read a string
   Delete any trailing newline.
 */
void get_string(char *string)
{
    int len;

    wgetnstr(stdscr, string, MAX_STRING);
    len = strlen(string);
    if (len > 0 && string[len - 1] == '\n')
	string[len - 1] = '\0';
}

/*
   add_record

   Add a new CD to the collection
 */

void add_record()
{
    char catalog_number[MAX_STRING];
    char cd_title[MAX_STRING];
    char cd_type[MAX_STRING];
    char cd_artist[MAX_STRING];
    char cd_entry[MAX_STRING];

    int screenrow = MESSAGE_LINE;
    int screencol = 10;

    clear_all_screen();
    mvprintw(screenrow, screencol, "Enter new CD details");
    screenrow += 2;

    mvprintw(screenrow, screencol, "Catalog Number: ");
    get_string(catalog_number);
    screenrow++;

    mvprintw(screenrow, screencol, "      CD Title: ");
    get_string(cd_title);
    screenrow++;

    mvprintw(screenrow, screencol, "       CD Type: ");
    get_string(cd_type);
    screenrow++;

    mvprintw(screenrow, screencol, "        Artist: ");
    get_string(cd_artist);
    screenrow++;

    mvprintw(15, 5, "About to add this new entry:");
    sprintf(cd_entry, "%s,%s,%s,%s", catalog_number, cd_title, cd_type, cd_artist);
    mvprintw(17, 5, "%s", cd_entry);
    refresh();

    move(PROMPT_LINE, 0);
    if (get_confirm()) {
	insert_title(cd_entry);
	strcpy(current_cd, cd_title);
	strcpy(current_cat, catalog_number);
    }
}

/*
   count_cds - scan the database and count titles and tracks
 */
void count_cds()
{
    FILE *titles_fp, *tracks_fp;
    char entry[MAX_ENTRY];
    int titles = 0;
    int tracks = 0;

    titles_fp = fopen(title_file, "r");
    if (titles_fp) {
	while (fgets(entry, MAX_ENTRY, titles_fp))
	    titles++;
	fclose(titles_fp);
    }
    tracks_fp = fopen(tracks_file, "r");
    if (tracks_fp) {
	while (fgets(entry, MAX_ENTRY, tracks_fp))
	    tracks++;
	fclose(tracks_fp);
    }
    mvprintw(ERROR_LINE, 0, "Database contains %d titles, with a total of %d tracks.", titles, tracks);
    get_return();
}

/*
   find_cd - locate a CD in the database

   prompt for a substring to match in the database
   set current_cd to the CD title

 */
void find_cd()
{
    char match[MAX_STRING], entry[MAX_ENTRY];
    FILE *titles_fp;
    int count = 0;
    char *found, *title, *catalog;

    mvprintw(Q_LINE, 0, "Enter a string to search for in CD titles: ");
    get_string(match);

    titles_fp = fopen(title_file, "r");
    if (titles_fp) {
	while (fgets(entry, MAX_ENTRY, titles_fp)) {

	    /* Skip past catalog number */
	    catalog = entry;
	    if (found = strstr(catalog, ",")) {
		*found = 0;
		title = found + 1;

		/* Zap the next comma in the entry to reduce it to title only */
		if (found = strstr(title, ",")) {
		    *found = '\0';

		    /* Now see if the match substring is present */
		    if (found = strstr(title, match)) {
			count++;
			strcpy(current_cd, title);
			strcpy(current_cat, catalog);
		    }
		}
	    }
	}
	fclose(titles_fp);
    }
    if (count != 1) {
	if (count == 0)
	    mvprintw(ERROR_LINE, 0, "Sorry, no matching CD found. ");
	if (count > 1)
	    mvprintw(ERROR_LINE, 0, "Sorry, match is ambiguous: %d CDs found. ", count);
	current_cd[0] = '\0';
	get_return();
    }
}


/*
   remove_tracks - delete tracks from the current CD
 */
void remove_tracks()
{
    FILE *tracks_fp, *temp_fp;
    char entry[MAX_ENTRY + 1];
    int cat_length;

    if (current_cd[0] == '\0')
	return;

    cat_length = strlen(current_cat);

    tracks_fp = fopen(tracks_file, "r");
    if (tracks_fp == (FILE *)NULL) return;
    temp_fp = fopen(temp_file, "w");

    

    while (fgets(entry, MAX_ENTRY, tracks_fp)) {
	/* Compare catalog number and copy entry if no match */
	if (strncmp(current_cat, entry, cat_length) != 0)
	    fputs(entry, temp_fp);
    }
    fclose(tracks_fp);
    fclose(temp_fp);

    unlink(tracks_file);
    rename(temp_file, tracks_file);
}

/*
   remove_cd - delete the current CD from the database
 */
void remove_cd()
{
    FILE *titles_fp, *temp_fp;
    char entry[MAX_ENTRY];
    int cat_length;

    if (current_cd[0] == '\0')
	return;

    clear_all_screen();
    mvprintw(PROMPT_LINE, 0, "About to remove CD %s: %s. ", current_cat, current_cd);
    if (!get_confirm())
	return;

    cat_length = strlen(current_cat);

    /* Copy the titles file to a temporary, ignoring this CD */
    titles_fp = fopen(title_file, "r");
    temp_fp = fopen(temp_file, "w");

    while (fgets(entry, MAX_ENTRY, titles_fp)) {
	/* Compare catalog number and copy entry if no match */
	if (strncmp(current_cat, entry, cat_length) != 0)
	    fputs(entry, temp_fp);
    }
    fclose(titles_fp);
    fclose(temp_fp);

    /* Delete the titles file, and rename the temporary file */
    unlink(title_file);
    rename(temp_file, title_file);

    /* Now do the same for the tracks file */
    remove_tracks();

    /* Reset current CD to 'None' */
    current_cd[0] = '\0';
}


/*
   Some defines we use only for showing or entering the track information
 */
#define BOXED_LINES    11
#define BOXED_ROWS     60
#define BOX_LINE_POS   8
#define BOX_ROW_POS    2
/*
   list_tracks - list the tracks for the current CD
 */
void list_tracks()
{
    FILE *tracks_fp;
    char entry[MAX_ENTRY];
    int cat_length;
    int lines_op = 0;
    WINDOW *track_pad_ptr;
    int tracks = 0;
    int key;
    int first_line = 0;

    if (current_cd[0] == '\0') {
	mvprintw(ERROR_LINE, 0, "You must select a CD first. ", stdout);
	get_return();
	return;
    }
    clear_all_screen();
    cat_length = strlen(current_cat);

    /* First count the number of tracks for the current CD */
    tracks_fp = fopen(tracks_file, "r");
    if (!tracks_fp)
	return;
    while (fgets(entry, MAX_ENTRY, tracks_fp)) {
	if (strncmp(current_cat, entry, cat_length) == 0)
	    tracks++;
    }
    fclose(tracks_fp);


    /* Make a new pad, ensure that even if there is only a single
       track the PAD is large enough so the later prefresh() is always
       valid.
     */
    track_pad_ptr = newpad(tracks + 1 + BOXED_LINES, BOXED_ROWS + 1);
    if (!track_pad_ptr)
	return;

    tracks_fp = fopen(tracks_file, "r");
    if (!tracks_fp)
	return;

    mvprintw(4, 0, "CD Track Listing\n");

    /* write the track information into the pad */
    while (fgets(entry, MAX_ENTRY, tracks_fp)) {
	/* Compare catalog number and output rest of entry */
	if (strncmp(current_cat, entry, cat_length) == 0) {
	    mvwprintw(track_pad_ptr, lines_op++, 0, "%s", entry + cat_length + 1);
	}
    }
    fclose(tracks_fp);

    if (lines_op > BOXED_LINES) {
	mvprintw(MESSAGE_LINE, 0, "Cursor keys to scroll, RETURN or q to exit");
    } else {
	mvprintw(MESSAGE_LINE, 0, "RETURN or q to exit");
    }
    wrefresh(stdscr);
    keypad(stdscr, TRUE);
    cbreak();
    noecho();

    key = 0;
    while (key != 'q' && key != KEY_ENTER && key != '\n') {
	if (key == KEY_UP) {
	    if (first_line > 0)
		first_line--;
	}
	if (key == KEY_DOWN) {
	    if (first_line + BOXED_LINES + 1 < tracks)
		first_line++;
	}
	/* now draw the appropriate part of the pad on the screen */
	prefresh(track_pad_ptr, first_line, 0,
		 BOX_LINE_POS, BOX_ROW_POS,
		 BOX_LINE_POS + BOXED_LINES, BOX_ROW_POS + BOXED_ROWS);
/*	wrefresh(stdscr); */
	key = getch();
    }

    delwin(track_pad_ptr);
    keypad(stdscr, FALSE);
    nocbreak();
    echo();
}

/*
   update_cd - re-enter tracks for current CD

   deletes all tracks for the current CD in the database
   and then prompts for new ones.
 */
void update_cd()
{
    FILE *tracks_fp;
    char track_name[MAX_STRING];
    int len;
    int track = 1;
    int screen_line = 1;
    WINDOW *box_window_ptr;
    WINDOW *sub_window_ptr;

    clear_all_screen();
    mvprintw(PROMPT_LINE, 0, "Re-entering tracks for CD. ");
    if (!get_confirm())
	return;
    move(PROMPT_LINE, 0);
    clrtoeol();

    remove_tracks();

    mvprintw(MESSAGE_LINE, 0, "Enter a blank line to finish");

    tracks_fp = fopen(tracks_file, "a");

    /* Just to show how, enter the information in a scrolling, boxed,
       window. The trick is to set-up a sub-window, draw a box around the
       edge, then add a new, scrolling, sub-window just inside the boxed
       sub-window. */
    box_window_ptr = subwin(stdscr, BOXED_LINES + 2, BOXED_ROWS + 2,
			    BOX_LINE_POS - 1, BOX_ROW_POS - 1);
    if (!box_window_ptr)
	return;
    box(box_window_ptr, ACS_VLINE, ACS_HLINE);

    sub_window_ptr = subwin(stdscr, BOXED_LINES, BOXED_ROWS,
			    BOX_LINE_POS, BOX_ROW_POS);
    if (!sub_window_ptr)
	return;
    scrollok(sub_window_ptr, TRUE);
    werase(sub_window_ptr);
    touchwin(stdscr);

    do {

	mvwprintw(sub_window_ptr, screen_line++, BOX_ROW_POS + 2, "Track %d: ", track);
	clrtoeol();
	refresh();
	wgetnstr(sub_window_ptr, track_name, MAX_STRING);
	len = strlen(track_name);
	if (len > 0 && track_name[len - 1] == '\n')
	    track_name[len - 1] = '\0';

	if (*track_name)
	    fprintf(tracks_fp, "%s,%d,%s\n", current_cat, track, track_name);
	track++;
	if (screen_line > BOXED_LINES - 1) {
	    /* time to start scrolling */
	    scroll(sub_window_ptr);
	    screen_line--;
	}
    } while (*track_name);
    delwin(sub_window_ptr);

    fclose(tracks_fp);
}
