#ifndef TIPOS_H_INCLUDED
#define TIPOS_H_INCLUDED

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#include "config.h"

#define TAM_MAX_NOM 61

#define VACIO 0
#define INICIO 1
#define SALIDA 2
#define PREMIO 3
#define VIDA_EXTRA 4
#define OASIS 5
#define TORMENTA 6

typedef struct
{
    int   numero;           // posicion 1..N
    unsigned categoria;   // lo que hay fijo en esa casilla
} tCasillero;

typedef struct
{
    int  vidas;
    int  puntosAcum;
    int  posicion;      // numero de casillero donde esta (1..N)
} tJugador;

typedef struct
{
    int id;
    int posicion;       // numero de casillero donde esta
} tBandido;

typedef struct
{
    unsigned int idPartida;
    unsigned int idJugador;
    unsigned int puntaje;
    unsigned int nroJugadas;
}tRegistroDePartida;

typedef struct
{
    unsigned int idJugador;
    char nombreUsuario [TAM_MAX_NOM];
    unsigned int partdiasJugadas;
}tRegistrodeUsuario;

typedef struct
{
    char tipo;//'J' O 'B'
    char sentido;//'F' o 'B'
    int desplazamiento;
}tMovimiento;


typedef struct
{
    unsigned int idClave;
    char nombreUsuario [TAM_MAX_NOM];
}tRegistroIdx;

#endif // TIPOS_H_INCLUDED


