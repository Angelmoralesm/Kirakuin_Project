#include <ncurses.h>
#include <string.h>
#include <stdio.h>
#include "nodo.h"
#include <stdlib.h>
#include "funciones.h"
#define ENTER 10
#define MAXIMO 99999999
#define MINIMO 11111111

int main(int argc, char ** argv){
    initscr();

    noecho();
    cbreak();
    start_color();
    init_pair(2,COLOR_WHITE,COLOR_RED);
    init_pair(5,COLOR_WHITE,COLOR_BLACK);
    init_pair(3,COLOR_WHITE,COLOR_BLUE);
    bkgd(COLOR_PAIR(5));
    int yMax , xMax;
    getmaxyx(stdscr, yMax , xMax);

    WINDOW * menuwin = newwin(6, xMax-12,yMax-6, 5);
    WINDOW * gamewin = newwin(20,45,3,47);//y,x,mover arriba,mover derecha
    wbkgd(gamewin,COLOR_PAIR(2));
    wbkgd(menuwin,COLOR_PAIR(3));
    box(menuwin,0,0);
    box(gamewin,0,0);
    refresh();
    wrefresh(menuwin);
    wrefresh(gamewin);
    
    keypad(menuwin,true);
    
    getch();
    
    endwin();

    return 0;
}