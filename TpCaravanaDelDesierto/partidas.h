#ifndef PARTIDAS_H_INCLUDED
#define PARTIDAS_H_INCLUDED

#include "tipos.h"
#include "TDAs/ListaCircularDoblementeEnlazada.h"
#include <stdlib.h>

#define ATRAS 1
#define ADELANTE 0

void moverJugador (tListaCD *tab, unsigned cant_mov, int sentido, int tam_tablero, int pos_jugador);
void actualizarEstadoJugCasillero (void *actualizado, const void *actualizador);
void moverBandido (tListaCD *tab, tJugador* jugador, tBandido* bandido, int tam_tablero);
#endif // PARTIDAS_H_INCLUDED
