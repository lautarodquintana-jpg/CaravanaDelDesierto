#ifndef PARTIDAS_H_INCLUDED
#define PARTIDAS_H_INCLUDED

#include "usuarios.h"

typedef struct 
{
    unsigned int idPartida;
    unsigned int idJugador;
    unsigned int puntajes;
    unsigned int nroJugadas;
}tArchivoPartidas;

void grabarRegistrosDePartida(tArchivoPartidas* partidaAct, FILE* archRegistros);
int cargarYMostrarRankingEnLista(const char* nomArchJugadores, const char* nomArchRegistros);


#endif // PARTIDAS_H_INCLUDED