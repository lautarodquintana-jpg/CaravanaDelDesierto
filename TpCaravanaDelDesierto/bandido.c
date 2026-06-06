
#include "bandido.h"

int cargarBandidos(tVector *bandidos, int cantBand, int tamTab)
{
    int ret;
    tBandido band;

    for(int i = 0; i < cantBand; i++)
    {
        band.id = i + 1;
        band.posicion = (rand() % (tamTab - 2)) + 1;

        ret = vectorInsertarAlFinal(bandidos, &band);
        if(ret != TODO_OK)
        {
            return ret;
        }
    }
    return TODO_OK;
}

int cantBandidoEnPos(tVector *bandidos, int posTablero)
{
    int contador = 0;
    tBandido band;

    for(int i = 0; i < bandidos->ce; i++)
    {
        vectorObtenerElem(bandidos, i, &band);
        if(band.posicion == posTablero)
        {
            contador++;
        }
    }
    return contador;
}
