#include <pdcurses/curses.h>

int main() {
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    curs_set(0);

    mvprintw(0, 0, "Press arrow keys or q to quit.");

    int ch;
    while ((ch = getch()) != 'q') {
        mvprintw(1, 0, "Key code: %d        ", ch);
        refresh();
    }

    endwin();
    return 0;
}
