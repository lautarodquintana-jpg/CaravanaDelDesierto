#ifndef PARTIDAS_H_INCLUDED
#define PARTIDAS_H_INCLUDED


#include "tipos.h"
#include "TDAs/listaSimplementeEnlazada.h"
#include "TDAs/ListaCircularDoblementeEnlazada.h"
#include "TDAs/arbol.h"

#include <stdlib.h>




int cmpPuntajeAsc(const void* e1, const void* e2);
int cmpPuntajeDesc(const void* e1, const void* e2);
void actualizarRegistroPuntaje(void* actualizado, const void* actualizador);
void imprimirRanking(const void* elem);

int cmpNombreUsuario(const void* e1, const void* e2);
int cmpNombre(const void *a, const void *b);

int grabarRegistroDePartida(tRegistroDePartida* partidaAct, const char* nomArchRegistros);
int cargarYMostrarRankingEnLista(const char* nomArchRegistros);

int iniciarSesionORegistrar(tArbol* pa, tRegistroDeUsuario* usuarioAct);
void leerYValidarNombre(char *nom, int tam);
#endif // PARTIDAS_H_INCLUDED

