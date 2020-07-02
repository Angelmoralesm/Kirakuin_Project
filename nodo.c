#include "nodo.h"
#include "funciones.h"
#include <stdio.h>
#include <stdlib.h>


typedef struct level
{
    level* arriba;
    level* abajo;
    level* derecha;
    level* izquierda;

    int recorrido = 0;
    int enemigo = 0;
    int cofre = 0;
    int id;

}level;


typedef struct mapa

    level * root;

}Mapa;

typedef struct jugador

    int id;
    int def;
    int atk;
    char * nombre;

}jugador;

typedef struct enemigo

    int prt;
    int atk;
    char * nombre;

}enemigo;