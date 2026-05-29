#include "partidas.h"

void grabarRegistrosDePartida(tArchivoPartidas* partidaAct, FILE* archRegistros)
{
    fwrite(partidaAct,sizeof(tArchivoPartidas), 1, archRegistros);
}
int cargarYMostrarRankingEnLista(const char* nomArchJugadores, const char* nomArchRegistros)
{
    TDAlista lista;
    crearLista(lista);

    


    return TODO_OK;
}