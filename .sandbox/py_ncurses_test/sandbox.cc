#include <cstdlib>
#include <ncurses.h>

using namespace std;

int main(){
    initscr();
    cbreak();
    noecho();

    clear();

    refresh();
    getch();
    endwin();
}
