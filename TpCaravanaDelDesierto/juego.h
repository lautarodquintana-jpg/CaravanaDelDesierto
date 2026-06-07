#ifndef JUEGO_H_INCLUDED
#define JUEGO_H_INCLUDED

#define MUERTE -1
#define NO_MUERTE 231
#include "tipos.h"
#include "TDAs/ListaCircularDoblementeEnlazada.h"
#include "TDAs/ColaDinamica.h"
#include "tablero.h"
#include <ctype.h>
#include <time.h>

void moverJugador (unsigned desplazamiento, char sentido, int tam_tablero, tJugador *jugador);
void ponerCatEnVacio (void *actualizado, const void *actualizador);
void calcularDespBandido (tMovimiento *mov, int posJ, int posB, int tam_tablero);
void actualizarBandido (void *actualizado, const void *actualizador);
int aJugar(tListaCD *tab, tJugador *jugador, tVector *bandidos, const tConfig *config);
char validarSentido();
int aplicarEfectosDelCasillero(tListaCD *tab, tJugador* jugador, unsigned *catAct);
int validarMuerte(tJugador *jugador, tVector *bandidos, unsigned catAnt);


#endif // JUEGO_H_INCLUDED
