#ifndef BANDIDO_H_INCLUDED
#define BANDIDO_H_INCLUDED

#include "tipos.h"
#include "TDAs/vector.h"

#define TODO_OK 0
#define SIN_MEM 1

/*
typedef struct
{
    int id;
    int posicion;
} tBandido;
*/

int cargarBandidos(tVector *bandidos, int cantBand, int tamTab);
int cantBandidoEnPos(tVector *bandidos, int posTablero);

#endif // BANDIDO_H_INCLUDED
