
#include <curses.h>

#include "CursesWindow.h"


CursesWindow::CursesWindow(){
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
}
CursesWindow::~CursesWindow(){
    endwin();
}
