#ifndef TIPOS_H_INCLUDED
#define TIPOS_H_INCLUDED

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "config.h"

#define TAM_NOMBRE 11

typedef enum
{
    VACIO,      // 0
    INICIO,     // 1
    SALIDA,     // 2
    PREMIO,     // 3
    VIDA_EXTRA, // 4
    OASIS,      // 5
    TORMENTA    // 6
} tCategoria;

typedef struct
{
    int   numero;           // posicion 1..N
    tCategoria categoria;   // lo que hay fijo en esa casilla
    int   cantBandidos;     // cuantos bandidos estan parados ahi
    int   tieneJugador;     // 0 o 1
} tCasillero;

typedef struct
{
    char nombre[TAM_NOMBRE];
    int  vidas;
    int  puntosAcum;
    int  protegido;     // efecto oasis activo
    int  pierdeTurno;   // cayo en tormenta
    int  posicion;      // numero de casillero donde esta (1..N)
} tJugador;

typedef struct
{
    int id;
    int posicion;       // numero de casillero donde esta
} tBandido;




#endif // TIPOS_H_INCLUDED


