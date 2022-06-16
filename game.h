#pragma once
#include <vector>
#include <iostream>
#include <ncurses.h>
WINDOW *win1;
WINDOW *win2;
WINDOW *win3;

bool fail;
int stage;
char dir;
int movetimer;

int g_itemx, g_itemy, g_timer;
int p_itemx, p_itemy, p_timer;
int gate1_x, gate1_y;
int gate2_x, gate2_y;
int gatecount;
int chplus_count, chminus_count, chgate_count, chlength_count;
int winx, winy;

bool clearall;

int input();
int snake();
int colorsetting();
int start();
int game_show();


int timer();
int setstage(int n);

int check_target();
