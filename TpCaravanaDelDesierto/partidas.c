#include "partidas.h"

void moverJugador (tListaCD *tab, unsigned cant_mov, int sentido, int tam_tablero, int pos_jugador)
{
    tCasillero aux;
    int num_casillero;

    verNElemCD(tab, pos_jugador, &aux, sizeof (tCasillero));
    aux.tieneJugador=0;

    actualizarNPosCD(tab, &aux, aux.numero, actualizarEstadoJugCasillero);

    if (sentido == ATRAS)
    {
        num_casillero= aux.numero-cant_mov;
    }
    else
    {
        num_casillero= tam_tablero - abs (tam_tablero - (aux.numero + cant_mov));
    }

    verNElemCD(tab, num_casillero, &aux, sizeof (tCasillero));
    aux.tieneJugador=1;
    actualizarNPosCD(tab, &aux, aux.numero, actualizarEstadoJugCasillero);
}

void actualizarEstadoJugCasillero (void *actualizado, const void *actualizador)
{
    memcpy(actualizado, actualizador, sizeof (tCasillero));
}

void moverBandido (tListaCD *tab, tJugador* jugador, tBandido* bandido, int tam_tablero)
{
    int distAvance= ( jugador->posicion - bandido->posicion + tam_tablero) % tam_tablero;
    int distRetroceso= ( bandido->posicion - jugador->posicion + tam_tablero) % tam_tablero;

    if (distAvance <= distRetroceso )
        bandido->posicion= (bandido->posicion + 1) % tam_tablero;
    else
        bandido->posicion= (bandido->posicion - 1 + tam_tablero) % tam_tablero;
}

