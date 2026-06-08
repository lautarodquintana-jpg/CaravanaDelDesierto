#ifndef PARTIDAS_H_INCLUDED
#define PARTIDAS_H_INCLUDED


#include "tipos.h"
#include "TDAs/listaSimplementeEnlazada.h"
#include "TDAs/ListaCircularDoblementeEnlazada.h"
#include "TDAs/arbol.h"

#include <stdlib.h>



int cmpIndiceJugador(const void* a, const void* b);
int cmpPuntaje(const void* e1, const void* e2);
void actualizarRegistroPuntaje(void* actualizado, const void* actualizador);
void imprimirRanking(const void* elem);

int cmpNombreJugador(const void* e1, const void* e2);
int cmpNombre(const void *a, const void *b);
void extraerNombreUsuario(void *clave, const void *dato);
void extraerClaveUsuario(const void* reg, void* clave);

int grabarRegistroDePartida(tRegistroDePartida* partidaAct, const char* nomArchRegistros);
int cargarYMostrarRankingEnLista(const char* nomArchRegistros);

int iniciarSesionORegistrar(tArbol* pa, tRegistroDeUsuario* usuarioAct, const char* nomArchUsuario, const char* nomArchIdx);
void leerYValidarNombre(char *nom, int tam);

int crearArchIndJugadores(tArbol* pa, unsigned tamElem, Cmp cmp, Extraer extraerClave,char *nombArchOriginal, char *nombArchInd);
int insNueJugadorEnArchivo(tIndJugadores* indAct, const char* archJugadores);
int insJugadorEnArchivoIdx(const tIndJugadores* ind, const char* nomArchIdx);


#endif // PARTIDAS_H_INCLUDED

