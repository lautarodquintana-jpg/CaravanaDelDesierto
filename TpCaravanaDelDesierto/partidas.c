#include "partidas.h"

<<<<<<< HEAD
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
=======
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
>>>>>>> test
}

