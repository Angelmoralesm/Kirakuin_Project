#include <ncurses.h>
#include <string.h>
#include <stdio.h>
#include "nodo.h"
#include <stdlib.h>
#include "funciones.h"
#define ENTER 10
#define MAXIMO 99999999
#define MINIMO 11111111

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


int menu_principal(){
    int key;
    
    noecho();
    cbreak();

    int yMax , xMax;
    getmaxyx(stdscr, yMax , xMax);

    WINDOW * menuwin = newwin(6, xMax-12,yMax-8, 5);
    WINDOW * submen = subwin(menuwin,1,1,1,1);
    box(menuwin,0,0);
    refresh();
    wrefresh(menuwin);

    keypad(menuwin,true);
    

    if (has_colors()){
        
        int beep(void);
        
        start_color();
        init_pair(1,COLOR_WHITE,COLOR_GREEN);
        init_pair(2,COLOR_WHITE,COLOR_BLUE);
        attron(COLOR_PAIR(1));
        wmove(menuwin,1,1);
        wprintw(menuwin,"Nueva partida");
        wmove(menuwin,2,1);
        wprintw(menuwin,"Cargar Partida");
        wmove(menuwin,3,1);
        wprintw(menuwin,"Ingresar cheats");
        
        attroff(COLOR_PAIR(1));
        wrefresh(menuwin);
        
        do{
        	key = wgetch(menuwin);
        	wrefresh(menuwin);
        	if(key == KEY_UP){
        		wprintw(menuwin,"arriba");
        	}
        	
        	if(key == KEY_DOWN){
        		wprintw(menuwin,"abajo");
        	}
        	
        }while(key != ENTER);
        
	refresh();
    }

    return 0;

}


int main(int argc, char ** argv){
    initscr();
    
    int option=menu_principal();
    
    bkgd(COLOR_PAIR(1));
    
    if(option=0);{
    
    	printw("xd");
    }
    
   napms(2000) ;
   
   refresh();
   getch();
   
   endwin();

    return 0;

}
