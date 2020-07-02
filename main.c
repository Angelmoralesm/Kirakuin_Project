#include <ncurses.h>
#include <string.h>
#include <stdio.h>
#include "nodo.h"
#include <stdlib.h>
#include "funciones.h"

typedef struct level level;

struct level{
    level *izq;
    level *der;
    level *up;
    level *dwn;
    int recorrido;
    int enemigo;
    int cofre;
    int id;
};


typedef struct mapa{
    level *root;
    level  *current;
}Mapa;

typedef struct jugador{

    int id;
    int def;
    int atk;
    char * nombre;

}jugador;

typedef struct enemigo{

    int prt;
    int atk;
    char *nombre;

}enemigo;

void menu_principal(){
    
    noecho();
    cbreak();

    int yMax , xMax;
    getmaxyx(stdscr, yMax , xMax);

    WINDOW * menuwin = newwin(6, xMax-12,yMax-8, 5);
    box(menuwin,0,0);
    refresh();
    wrefresh(menuwin);

    keypad(menuwin,true);
    
    
    echo();

    if (has_colors()){
        
        int beep(void);
        start_color();
        init_pair(1,COLOR_WHITE,COLOR_GREEN);
        init_pair(2,COLOR_WHITE,COLOR_BLUE);
        attron(COLOR_PAIR(1));
        wmove(menuwin,18,10);
        printw("Nueva partida");
        wmove(menuwin,19,10);
        printw("Cargar Partida");
        wmove(menuwin,20,10);
        printw("Ingresar Cheats");
        attroff(COLOR_PAIR(1));
        
        char cadena[128];
        scanw("%s",&cadena);
        
	printw("Has elegido %s\n",cadena);
	refresh();
    }


    getch();

}


int main(int argc, char ** argv){
    initscr();
    
    menu_principal();
    
    clear();
    
    refresh();
    int flash(void);
    
   napms (2000) ;
   flash();
   napms (2000) ;
   flash();
   napms (2000) ;
   flash();
   
   refresh();
    
    menu_principal();

    endwin();

    return 0;

}
