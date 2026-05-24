#ifndef TABLERO_H_INCLUDED
#define TABLERO_H_INCLUDED

#include "tipos.h"
#include "TDAs/listaSimplementeEnlazada.h"



int inicializarTablero(tLista* tab, unsigned cantPos);
int cargarCategoria(tLista* tab, unsigned cat, unsigned cant, unsigned tamTab);
int crearTablero(tLista* tab, const tConfig* conf);
void eliminarTablero(tLista* tab);
int tirarDado();

#endif // TABLERO_H_INCLUDED
