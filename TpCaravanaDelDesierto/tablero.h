#ifndef TABLERO_H_INCLUDED
#define TABLERO_H_INCLUDED

#include "tipos.h"
#include "bandido.h"
#include "TDAs/ListaCircularDoblementeEnlazada.h"
#include "TDAs/vector.h"

int inicializarTablero(tListaCD* tab, unsigned cantPos);
int cargarCategoria(tListaCD* tab, unsigned cat, unsigned cant, unsigned tamTab);
void actualizarCat(void *actualizado, const void *actualizador);
int crearTablero(tListaCD* tab, const tConfig* conf);
void eliminarTablero(tListaCD* tab);
int tirarDado();
void mostrarTablero (const tListaCD *tab,tVector *bandidos, int posJ, int tamTablero);

int crearCaravanaTxt(tListaCD *tab, tVector *bandidos);


#endif // TABLERO_H_INCLUDED
