#ifndef JUEGO_H_INCLUDED
#define JUEGO_H_INCLUDED

#define MUERTE -1
#define NO_MUERTE 0
#include "tipos.h"
#include "TDAs/ListaCircularDoblementeEnlazada.h"
#include "TDAs/ColaDinamica.h"
#include "tablero.h"
#include <ctype.h>

void moverJugador (unsigned desplazamiento, char sentido, int tam_tablero, tJugador *jugador);
void ponerCatEnVacio (void *actualizado, const void *actualizador);
void moverBandido (tListaCD *tab, tJugador* jugador, tBandido* bandido, int tam_tablero);
int aJugar(tListaCD *tab, tJugador *jugador, tVector *bandidos, const tConfig *config);
char validarSentido();
int aplicarEfectosDelCasillero(tListaCD *tab, tJugador* jugador, unsigned *catAct);
int validarMuerte(tJugador *jugador, tVector *bandidos, unsigned catAnt);


#endif // JUEGO_H_INCLUDED
