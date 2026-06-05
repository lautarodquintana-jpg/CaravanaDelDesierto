#ifndef PARTIDAS_H_INCLUDED
#define PARTIDAS_H_INCLUDED

#include "tipos.h"
<<<<<<< HEAD
#include "TDAs/listaSimplementeEnlazada.h"
#include "TDAs/ListaCircularDoblementeEnlazada.h"
=======
#include "TDAs/ListaCircularDoblementeEnlazada.h"
#include <stdlib.h>
>>>>>>> test

#define ATRAS 1
#define ADELANTE 0

<<<<<<< HEAD
int cmpPuntaje(const void* e1, const void* e2);
void actualizarRegistroPuntajes(void* actualizado, const void* actualizador);
int cmpIdJugador(const void* e1, const void* e2);

int grabarRegistrosDePartida(tResgistrosDeJugador* partidaAct, const char* archRegistros);
int cargarYMostrarRankingEnLista(const char* nomArchJugadores, const char* nomArchRegistros);



#endif // PARTIDAS_H_INCLUDED
=======
void moverJugador (tListaCD *tab, unsigned cant_mov, int sentido, int tam_tablero, int pos_jugador);
void actualizarEstadoJugCasillero (void *actualizado, const void *actualizador);
void moverBandido (tListaCD *tab, tJugador* jugador, tBandido* bandido, int tam_tablero);
#endif // PARTIDAS_H_INCLUDED
>>>>>>> test
