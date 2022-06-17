#include <ncurses.h>
#include <unistd.h>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include "map.h"
#include "game.h"
#include "start.cpp"
#include "item.cpp"
using namespace std;

#define tick 100000
int colorsetting(){
  init_pair(1,COLOR_WHITE,COLOR_WHITE);
  init_pair(2,COLOR_GREEN,COLOR_GREEN);
  init_pair(3,COLOR_CYAN,COLOR_CYAN);
  init_pair(4,COLOR_YELLOW, COLOR_YELLOW);
  init_pair(5, COLOR_BLUE, COLOR_BLUE);
  init_pair(6, COLOR_RED, COLOR_RED);
  init_pair(7, COLOR_BLACK, COLOR_WHITE);
  init_pair(8,COLOR_MAGENTA,COLOR_GREEN);
  return 0;
}

vector<int> snakex;
vector<int> snakey;


int game_show(){

  clear();
  win1=newwin(25,25,3,10);
  int i = stage;
  for(int i=0; i<25; i++){
    printw("\n");
    for(int a=0; a<25; a++){
      if(map[stage][i][a]==1){
        wattron(win1,COLOR_PAIR(1));
        mvwprintw(win1, i, a, " ");
      }
      else if(map[stage][i][a]==2){
        wattron(win1,COLOR_PAIR(2));
        mvwprintw(win1, i, a, " ");
      }
      else if(map[stage][i][a]==3){
        wattron(win1,COLOR_PAIR(3));
        mvwprintw(win1, i, a, " ");
      }
      else if(map[stage][i][a]==4){
        wattron(win1,COLOR_PAIR(4));
        mvwprintw(win1, i, a, " ");
      }
      else if(map[stage][i][a]==5){
        wattron(win1,COLOR_PAIR(5));
        mvwprintw(win1, i, a, " ");
      }
      else if(map[stage][i][a]==6){
        wattron(win1,COLOR_PAIR(6));
        mvwprintw(win1, i, a, " ");
      }
      else if(map[stage][i][a]==7){
        wattron(win1,COLOR_PAIR(8));
        mvwprintw(win1, i, a, " ");
      }

    }
  }

  win2=newwin(8,20,5,73); //Score board
  wbkgd(win2,COLOR_PAIR(7));
  wattron(win2,COLOR_PAIR(7));

  wborder(win2,'*','*','*','*','*','*','*','*');
  mvwprintw(win2,1,5,"Score Board");
  mvwprintw(win2,2,2,"B :%d",chlength_count);
  mvwprintw(win2,3,2,"+ :%d",chplus_count);
  mvwprintw(win2,4,2,"- :%d",chminus_count);
  mvwprintw(win2,5,2,"G :%d",chgate_count);
  wrefresh(win2);


  wrefresh(win1);
  win3=newwin(8,20,20,73); //target board
  wbkgd(win3,COLOR_PAIR(7));
  wattron(win3,COLOR_PAIR(7));

  wborder(win3,'*','*','*','*','*','*','*','*');
  mvwprintw(win3,1,5,"Mission");
  mvwprintw(win3,2,2,"B : %d",target_score[stage][0]);
  mvwprintw(win3,3,2,"+ : %d",target_score[stage][1]);
  mvwprintw(win3,4,2,"- : %d",target_score[stage][2]);
  mvwprintw(win3,5,2,"G : %d",target_score[stage][3]);
  wrefresh(win3);

  return 0;
}

int main(){
    start();
    while (fail==false)
    {
        timer();
        input();
        game_show();

        usleep(tick);
        // endwin();
    }
    if(clearall == false)
    {
        delwin(win1);
        delwin(win2);
        delwin(win3);
        clear();
        mvprintw(winy/2, (winx-11)/2, "Failed...Try again!");
        refresh();
        usleep(1000000);
    }
    // endwin();
    return 0;
}



int input(){
    int click = getch();

    switch (click){
    case KEY_UP:
        if (dir == 'D')
        { fail = true;}
        else dir = 'U';
        break;
    case KEY_DOWN:
        if (dir == 'U')
        { fail = true;}
        else dir = 'D';
        break;
    case KEY_LEFT:
        if (dir == 'R')
        { fail = true;}
        else dir = 'L';
        break;
    case KEY_RIGHT:
        if (dir == 'L')
        { fail = true;}
        else dir = 'R';
        break;
    }
    return 0;
}

int snake(){
    if (gatecount > 0){
        if (gatecount == 1){
            map[stage][gate1_y][gate1_x] = 1;
            map[stage][gate2_y][gate2_x] = 1;
            chgate_count += 1;
            gate();
        }
        gatecount --;
    }
    int last = snakex.size();

    int lastx = snakex[last - 1];
    int lasty = snakey[last - 1];

    map[stage][snakey[last - 1]][snakex[last - 1]] = 0;
    for (int i = last - 1; i > 0; i--){
        snakex[i] = snakex[i - 1];
        snakey[i] = snakey[i - 1];
    }

    if(dir=='U'){
      snakey[0]--;
    }
    else if(dir=='D'){
      snakey[0]++;
    }
    else if(dir=='L'){
      snakex[0]--;
    }
    else if(dir=='R'){
      snakex[0]++;
    }


    if (map[stage][snakey[0]][snakex[0]] == 7){
        gatecount = last;

        int exitx, exity;
        if(snakex[0] == gate1_x && snakey[0] == gate1_y){
            exitx = gate2_x;
            exity = gate2_y;
        }
        else{
            exitx = gate1_x;
            exity = gate1_y;
        }

        if(exitx == 0){
            snakex[0] = exitx + 1;
            snakey[0] = exity;
            dir = 'R';
        }
        else if(exitx == 20){
            snakex[0] = exitx - 1;
            snakey[0] = exity;
            dir = 'L';
        }
        else if(exity == 0){
            snakex[0] = exitx;
            snakey[0] = exity + 1;
            dir = 'D';
        }
        else if(exity == 20){
            snakex[0] = exitx;
            snakey[0] = exity - 1;
            dir = 'U';
        }
        else {

          snakex[0] = exitx;
          snakey[0] = exity;
          char tempdir = dir;

          if(dir=='U'){
            snakey[0]=snakey[0]-1;
          }
          else if(dir=='D'){
            snakey[0]=snakey[0]+1;
          }
          else if(dir=='L'){
            snakex[0]=snakex[0]-1;
          }
          else if(dir=='R'){
            snakex[0]=snakex[0]+1;
          }



          if (map[stage][snakey[0]][snakex[0]] == 7 || map[stage][snakey[0]][snakex[0]] == 1 || map[stage][snakey[0]][snakex[0]] == 2){
              snakex[0] = exitx;
              snakey[0] = exity;

              if(dir=='U'){
                dir='R';
              }
              else if(dir=='D'){
                dir='L';
              }
              else if(dir=='L'){
                dir='U';
              }
              else if(dir=='R'){
                dir='D';
              }

              if(dir=='U'){
                snakey[0]=snakey[0]-1;
              }
              else if(dir=='D'){
                snakey[0]=snakey[0]+1;
              }
              else if(dir=='L'){
                snakex[0]=snakex[0]-1;
              }
              else if(dir=='R'){
                snakex[0]=snakex[0]+1;
              }


              if (map[stage][snakey[0]][snakex[0]] == 7 || map[stage][snakey[0]][snakex[0]] == 1 || map[stage][snakey[0]][snakex[0]] == 2){
                  snakex[0] = exitx;
                  snakey[0] = exity;

                  if(tempdir=='U'){
                    dir='L';
                  }
                  else if(tempdir='D'){
                    dir='R';
                  }
                  else if(tempdir='L'){
                    dir='D';
                  }
                  else if(tempdir='R'){
                    dir='U';
                  }

                  if(tempdir=='U'){
                    snakey[0]--;
                  }
                  else if(tempdir='D'){
                    snakey[0]++;
                  }
                  else if(tempdir='L'){
                      snakex[0]--;
                  }
                  else if(tempdir='R'){
                    snakex[0]++;
                  }


                  if (map[stage][snakey[0]][snakex[0]] == 7 || map[stage][snakey[0]][snakex[0]] == 1 || map[stage][snakey[0]][snakex[0]] == 2){
                      snakex[0] = exitx;
                      snakey[0] = exity;

                      if(tempdir=='U'){
                        dir='D';
                      }
                      else if(tempdir='D'){
                        dir='U';
                      }
                      else if(tempdir='L'){
                        dir='R';
                      }
                      else if(tempdir='R'){
                        dir='L';
                      }

                      if(dir=='U'){
                        snakey[0]--;
                      }
                      else if(dir='D'){
                        snakey[0]++;
                      }
                      else if(dir='L'){
                          snakex[0]--;
                      }
                      else if(dir='R'){
                        snakex[0]++;
                      }



                    }
                }
            }
        }
}

    int grown = 0, poisoned = 0;
    if (map[stage][snakey[0]][snakex[0]] == 4 || map[stage][snakey[0]][snakex[0]] == 1){
        fail = true;
    }
    else if (map[stage][snakey[0]][snakex[0]] == 5) {
        snakex.push_back(lastx);
        snakey.push_back(lasty);
        grown = 1;
        chplus_count += 1;

        if(chlength_count < snakex.size())
        {
            chlength_count = snakex.size();
        }
    }
    else if (map[stage][snakey[0]][snakex[0]] == 6) {
        if(last == 3){
            fail = true;
        }
        else{
            map[stage][snakey[last - 1]][snakex[last - 1]] = 0;
            snakex.pop_back();
            snakey.pop_back();
            poisoned = 1;
            chminus_count += 1;
        }
    }

    map[stage][snakey[0]][snakex[0]] = 3;
    for (int i = 1; i < snakex.size(); i++){
        map[stage][snakey[i]][snakex[i]] = 4;
    }
    if(poisoned == 1){
        poison();
        p_timer = 100;
    }
    if(grown == 1){
        growing();
        g_timer = 100;
    }
    check_target();

    return 0;
}





int timer(){
    g_timer --;
    p_timer --;
    movetimer --;

    if(g_timer == 0){
        map[stage][g_itemy][g_itemx] = 0;
        growing();
        g_timer = 100;
    }
    if(p_timer == 0){
        map[stage][p_itemy][p_itemx] = 0;
        poison();
        p_timer = 100;
    }
    if(movetimer == 0){
        snake();
        movetimer = 5;
    }
    return 0;
}
int setstage(int n){
    clear();
    if(stage==0){
        mvprintw(winy/2, (winx-20)/2, "Welcome to the C++ sname game", stage+1);
    }
    else{
    mvprintw(winy/2, (winx)/2, "Stage %d", stage+1);}
    refresh();
    usleep(1000000);

    movetimer = 3;
    g_timer = 80;
    p_timer = 80;
    gatecount = 0;

    chgate_count = 0;
    chplus_count = 0;
    chminus_count = 0;
    chlength_count= 3;

    vector<int>().swap(snakex);
    vector<int>().swap(snakey);

    if(stage==0){
        snakex.push_back(9);
        snakey.push_back(9);
        snakex.push_back(10);
        snakey.push_back(9);
        snakex.push_back(11);
        snakey.push_back(9);
        dir = 'L';}
      else if(stage==1){

        snakex.push_back(10);
        snakey.push_back(9);
        snakex.push_back(10);
        snakey.push_back(10);
        snakex.push_back(10);
        snakey.push_back(11);
        dir = 'U';}

    else if(stage==2){
        snakex.push_back(9);
        snakey.push_back(9);
        snakex.push_back(10);
        snakey.push_back(9);
        snakex.push_back(11);
        snakey.push_back(9);
        dir = 'L';
      }
    else if(stage==3){

        snakex.push_back(9);
        snakey.push_back(10);
        snakex.push_back(10);
        snakey.push_back(11);
        snakex.push_back(11);
        snakey.push_back(17);
        dir = 'L';}

    gate();
    growing();
    poison();

    return 0;
}


int check_target(){
    if( chplus_count >= target_score[stage][1] &&chgate_count >= target_score[stage][3] && chminus_count >= target_score[stage][2] && chlength_count >= target_score[stage][0])
    {
        if(stage < 3)
        {
            clear();
            mvprintw(winy/2, (winx-20)/2, "You clear  %d Stage!", stage+1);
            mvprintw(winy/2+1, (winx-31)/2, "Here comes the new stage");
            refresh();
            usleep(1000000);
            stage ++;
            setstage(stage);
        }
        else
        {
            clear();
            mvprintw(winy/2, (winx)/2, "Finally you clear all stage!");
            refresh();
            usleep(1000000);
            fail = true;
            clearall = true;
        }
    }
    return 0;
}
