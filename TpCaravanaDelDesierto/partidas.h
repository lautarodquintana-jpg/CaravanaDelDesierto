#ifndef PARTIDAS_H_INCLUDED
#define PARTIDAS_H_INCLUDED


#include "tipos.h"

#include "TDAs/listaSimplementeEnlazada.h"
#include "TDAs/ListaCircularDoblementeEnlazada.h"

#include "TDAs/ListaCircularDoblementeEnlazada.h"
#include <stdlib.h>


#define ATRAS 1
#define ADELANTE 0


int cmpPuntaje(const void* e1, const void* e2);
void actualizarRegistroPuntaje(void* actualizado, const void* actualizador);
int cmpIdJugador(const void* e1, const void* e2);
void imprimirRanking(const void* elem);

int grabarRegistrosDePartida(tRegistroDeJugador* partidaAct, const char* archRegistros);
int cargarYMostrarRankingEnLista(const char* nomArchJugadores, const char* nomArchRegistros);


#endif // PARTIDAS_H_INCLUDED

