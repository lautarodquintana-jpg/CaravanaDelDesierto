#ifndef PARTIDAS_H_INCLUDED
#define PARTIDAS_H_INCLUDED


#include "tipos.h"
#include "TDAs/listaSimplementeEnlazada.h"
#include "TDAs/ListaCircularDoblementeEnlazada.h"
#include "TDAs/arbol.h"

#include <stdlib.h>




int cmpPuntaje(const void* e1, const void* e2);
void actualizarRegistroPuntaje(void* actualizado, const void* actualizador);
int cmpIdJugador(const void* e1, const void* e2);
void imprimirRanking(const void* elem);
int cmpNombreJugador(const void* e1, const void* e2);

int grabarRegistrosDePartida(tRegistroDePartida* partidaAct, const char* nomArchRegistros);
int cargarYMostrarRankingEnLista(const char* nomArchJugadores, const char* nomArchRegistros);

int iniciarSesionORegistrar(tArbol* arbol, tRegistrodeUsuario* usuarioAct, FILE* pf);
#endif // PARTIDAS_H_INCLUDED

