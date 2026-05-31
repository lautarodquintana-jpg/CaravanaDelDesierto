#ifndef TABLERO_H_INCLUDED
#define TABLERO_H_INCLUDED

#include "tipos.h"
#include "TDAs/ListaCircularDoblementeEnlazada.h"

int inicializarTablero(tListaCD* tab, unsigned cantPos);
int cargarCategoria(tListaCD* tab, unsigned cat, unsigned cant, unsigned tamTab);
int cargarBandidos(tListaCD* tab, unsigned cant, unsigned tamTab);
void actualizarCat(void *actualizado, const void *actualizador);
void actualizarBandido(void *actualizado, const void *actualizador);
int crearTablero(tListaCD* tab, const tConfig* conf);
void eliminarTablero(tListaCD* tab);
int tirarDado();
void mostrarCasillero(const void *elem);

int crearCaravanaTxt(tListaCD *tab);


#endif // TABLERO_H_INCLUDED
