#include "partidas.h"

int grabarRegistrosDePartida(tResgistrosDeJugador* partidaAct, const char* archRegistros)
{
    tResgistrosDeJugador registroAnterior;

    FILE* arch = fopen(archRegistros, "r+b");

    if(!arch)
        return ERROR_ARCHIVO;

    fseek(arch, 0, SEEK_END);

    if(ftell(arch) == 0)
    {
        partidaAct->idPartida = 1;
    }
    else
    {
        fseek(arch, -sizeof(tResgistrosDeJugador), SEEK_END);
        fread(&registroAnterior, sizeof(tResgistrosDeJugador), 1, arch);

        partidaAct->idPartida = registroAnterior.idPartida + 1;
    }

    fwrite(partidaAct, sizeof(tResgistrosDeJugador), 1, arch);
    
    fclose(arch);
    return TODO_OK;
}
int cargarYMostrarRankingEnLista(const char* nomArchJugadores, const char* nomArchRegistros)
{
    tLista lRanking;
    crearLista(&lRanking);

    cargarOrdenadoListaSinDupDeArchivo(&lRanking, sizeof(tResgistrosDeJugador), cmpPuntaje, actualizarRegistroPuntajes, nomArchRegistros);

    ordenarLista(&lRanking, cmpPuntaje);


    return TODO_OK;
}

