
#include "partidas.h"


int cmpPuntaje(const void* e1, const void* e2)
{
    const tRegistroDeJugador* x = (const tRegistroDeJugador*)e1;
    const tRegistroDeJugador* y = (const tRegistroDeJugador*)e2;

    return x->puntaje - y->puntaje;
}
void actualizarRegistroPuntaje(void* actualizado, const void* actualizador)
{
    tRegistroDeJugador* x = (tRegistroDeJugador*)actualizado;
    const tRegistroDeJugador* y =(const tRegistroDeJugador*)actualizador;
    x->puntaje += y->puntaje;
}

int cmpIdJugador(const void* e1, const void* e2)
{
    const tRegistroDeJugador* x = (const tRegistroDeJugador*)e1;
    const tRegistroDeJugador* y = (const tRegistroDeJugador*)e2;

    return x->idJugador - y->idJugador;
}


int grabarRegistrosDePartida(tRegistroDeJugador* partidaAct, const char* archRegistros)
{
    tRegistroDeJugador registroAnterior;

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
        fseek(arch, - (long long)sizeof(tRegistroDeJugador), SEEK_END);
        fread(&registroAnterior, sizeof(tRegistroDeJugador), 1, arch);

        partidaAct->idPartida = registroAnterior.idPartida + 1;
    }

    fwrite(partidaAct, sizeof(tRegistroDeJugador), 1, arch);

    fclose(arch);
    return TODO_OK;
}
int cargarYMostrarRankingEnLista(const char* nomArchJugadores, const char* nomArchRegistros)
{
    tLista lRanking;
    crearLista(&lRanking);

    cargarOrdenadoListaSinDupDeArchivo(&lRanking, sizeof(tRegistroDeJugador), cmpIdJugador, actualizarRegistroPuntaje, nomArchRegistros);
    ordenarLista(&lRanking,cmpPuntaje);


    vaciarLista(&lRanking);
    return TODO_OK;
}



