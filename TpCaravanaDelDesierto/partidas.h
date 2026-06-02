#ifndef PARTIDAS_H_INCLUDED
#define PARTIDAS_H_INCLUDED

#include "tipos.h"
#include "TDAs/listaSimplementeEnlazada.h"
#include "TDAs/ListaCircularDoblementeEnlazada.h"


int cmpPuntaje(const void* e1, const void* e2);
void actualizarRegistroPuntajes(void* actualizado, const void* actualizador);
int cmpIdJugador(const void* e1, const void* e2);

int grabarRegistrosDePartida(tResgistrosDeJugador* partidaAct, const char* archRegistros);
int cargarYMostrarRankingEnLista(const char* nomArchJugadores, const char* nomArchRegistros);



#endif // PARTIDAS_H_INCLUDED