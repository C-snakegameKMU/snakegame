
#include "game.h"
int start(){
    initscr();
    start_color();
    nodelay(stdscr, true);
    noecho();

    cbreak();
    keypad(stdscr, TRUE);
    getmaxyx(stdscr, winy, winx);

    fail = false;
    clearall = false;
    stage = 0;

    setstage(stage);


  colorsetting();
  return 0;
}
