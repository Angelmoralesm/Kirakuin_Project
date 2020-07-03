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
    level * root;
    level  * current;
}Mapa;

typedef struct jugador{
    int dfs;
    int atk;
    char * nombre;
    int level;
}jugador;

typedef struct enemigo{
    int prt;
    int atk;
    char *nombre;
}enemigo;

jugador *crear_jugador (int level ,char *nombre, int atak,int dfs){
    jugador *p = malloc(sizeof(jugador));
    p->level = level;
    p->nombre = nombre;
    p->atk = atak;
    p->dfs = dfs;
    return p;
}

void typewriter(int x, int y, int velocidad, WINDOW* ventana, char* text){
    int i;
    for(i=0;i<strlen(text);i++){
        mvprintw(x,y+i,"%c",text[i]);
        wrefresh(ventana);
        napms(velocidad);
    }
}

void showtitle(int x, int y, int velocidad){
    typewriter(y,x,velocidad,stdscr,"==================================================================================");
    typewriter(y+1,x,velocidad,stdscr,"-@@@---@@@@-@@@@@@-@@@@@@@-------@@@@----@@@---@@@@-@@@@----@@@@-@@@@@@-@@-----@@-");
    typewriter(y+2,x,velocidad,stdscr,"--@@--@@@-----@@----@@---@@-----@@--@@----@@--@@@----@@------@@----@@---@@@@---@@-");
    typewriter(y+3,x,velocidad,stdscr,"--@@-@@@------@@----@@---@@----@@----@@---@@-@@@-----@@------@@----@@---@@-@@--@@-");
    typewriter(y+4,x,velocidad,stdscr,"--@@@@@-------@@----@@@@@@-----@@@@@@@@---@@@@@------@@------@@----@@---@@--@@-@@-");
    typewriter(y+5,x,velocidad,stdscr,"--@@-@@@------@@----@@--@@-----@@----@@---@@-@@@-----@@------@@----@@---@@---@@@@-");
    typewriter(y+6,x,velocidad,stdscr,"--@@--@@@-----@@----@@---@@----@@----@@---@@--@@@----@@@----@@@----@@---@@----@@@-");
    typewriter(y+7,x,velocidad,stdscr,"-@@@---@@@@-@@@@@@--@@----@@@-@@------@@-@@@---@@@@----@@@@@@----@@@@@@-@@-----@@-");
    typewriter(y+8,x,velocidad,stdscr,"==================================================================================");
}

int menu_principal(){
    int key;
    
    noecho();
    cbreak();

    int yMax , xMax;
    getmaxyx(stdscr, yMax , xMax);

    WINDOW * menuwin = newwin(6, xMax-12,yMax-8, 5);
    int yMac, xMac;
    getmaxyx(menuwin,yMac,xMac);
    showtitle(1,5,1);

    box(menuwin,0,0);
    refresh();
    wrefresh(menuwin);

    keypad(menuwin,true);
    int y =1; 

    if (has_colors()){
        
        int beep(void);
        
        start_color();
        init_pair(1,COLOR_WHITE,COLOR_GREEN);
        init_pair(2,COLOR_WHITE,COLOR_BLUE);
        attron(COLOR_PAIR(1));
        wmove(menuwin,1,1);
        wprintw(menuwin," Nueva partida");
        wmove(menuwin,2,1);
        wprintw(menuwin," Cargar Partida");
        wmove(menuwin,3,1);
        wprintw(menuwin," Ingresar cheats");
        attroff(COLOR_PAIR(1));
        wrefresh(menuwin);
        wmove(menuwin,1,20);
        noecho();
        curs_set(0); 
        
        do{
        	key = wgetch(menuwin);
        	wrefresh(menuwin);


        	if(key == KEY_UP){
                mvwprintw(menuwin,y,1," ");
                y--;
        		if(y==0)y=3;
                if(y==4)y=1;
                
                wmove(menuwin,y,1);
                mvwprintw(menuwin,y,1,">");
                
                
                continue;
        	}
        	
        	if(key == KEY_DOWN){
        	  mvwprintw(menuwin,y,1," ");
                 y++;
                 if(y==0)y=3;
                 if(y==4)y=1;
                 wmove(menuwin,y,1);
                 mvwprintw(menuwin,y,1,">");
                 continue;
        	}

        }while(key != ENTER);
        
	refresh();
    }

    return y;

}

void ingresar(char *nombre){
    char *name=nombre;
    FILE *nuevoJugador = fopen("jugadores.txt", "a");
    fputs(nombre,nuevoJugador);
    fputc(',', nuevoJugador);
    fputs("100", nuevoJugador);
    fputc(',', nuevoJugador);
    fputs("100", nuevoJugador);
    fputc(',', nuevoJugador);
    fputs("1", nuevoJugador);
    fputs("\n", nuevoJugador);
    fclose(nuevoJugador);
}

void nueva_partida(){
    
    echo();
    char cadena[128];
    typewriter(9,23,50,stdscr,"¿Cual es tu nombre? ");
    move(10,23);
    scanw("%[^\n]s",cadena);
    typewriter(11,23,50,stdscr,"tu nombre es: ");
    typewriter(11,37,50,stdscr,cadena);
    typewriter(12,23,50,stdscr,"estas seguro?");
    typewriter(14,23,50,stdscr,"SI");
    typewriter(14,26,50,stdscr,"NO");
    refresh();
    int key;
    int x=1;
    noecho();

    do{
            
        key = getch();
        refresh();
        	
        if(key == KEY_LEFT){
          
            if(x==1)continue;
            
            x=1;
            mvwprintw(stdscr,15,23,"^");
            continue;
        }
        	
        if(key == KEY_RIGHT){
           
            if(x==3)continue;
            
            x=3;
            mvwprintw(stdscr,15,26,"a");
            continue;
        }

    }while(key != ENTER);
	
    if(x==3)return nueva_partida();

    ingresar(cadena);
    jugador *player = crear_jugador(1,cadena,100,100);
}

int main(int argc, char ** argv){
    
    initscr();
    
    int option=menu_principal();
    
    
    init_pair(4,COLOR_WHITE,COLOR_MAGENTA);
    clear();
    bkgd(COLOR_PAIR(4));
    switch (option)
    
    {
    case 1:
        nueva_partida();
        //typewriter(10,10,50,stdscr,"Nueva Partida");
        /* code */
        break;
    case 2:
        typewriter(10,10,50,stdscr,"Cargar partida");
        break;
    case 3:
        typewriter(10,10,50,stdscr,"CHEATS");
        break;
    default:
        return 0;
    }
    
    napms(2000);
   
    refresh();
    getch();
   
    endwin();

    return 0;

}
