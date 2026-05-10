
#include "tablero.h"

int inicializarTablero(tLista* tab, unsigned cantPos)
{
    int i = 1;
    int ret;

    tCasillero cas;
    cas.cantBandidos = 0;
    cas.categoria = INICIO;
    cas.numero = i;
    cas.tieneJugador = 1;

    ret = insertarAlComienzo(tab, &cas, sizeof(tCasillero));
    if(ret != TODO_OK)
    {
        return ret;
    }

    i++;
    cas.categoria = VACIO;
    cas.tieneJugador = 0;

    while(i < cantPos)
    {
        cas.numero = i;
        ret = insertarAlFinal(tab, &cas, sizeof(tCasillero));
        if(ret != TODO_OK)
        {
            return ret;
        }

        i++;
    }

    cas.categoria = SALIDA;
    ret = insertarAlFinal(tab, &cas, sizeof(tCasillero));
    if(ret != TODO_OK)
    {
        return ret;
    }

    return TODO_OK;
}

int cargarCategoria(tLista* tab, unsigned cat, unsigned cant, unsigned tamTab)
{
    int ret;
    unsigned pos;
    tCasillero casilleroLeido;

    while(cant > 0)
    {
        pos = (rand() % (tamTab - 2)) + 1; // 1 a (tamTab - 2) (inicio y salida incluidos)
//        rand() % 10 - 2 = (0 a 7) + 1 = 1 a 8
//        0 a 9 --> 1 a 8

        ret = verNElem(tab, pos, &casilleroLeido, sizeof(tCasillero));
        if(ret != TODO_OK)
        {
            return ret;
        }

        if(casilleroLeido.categoria == VACIO)
        {
            ret = actualizarNPos(tab, &cat, pos, actualizarCat);
            if(ret != TODO_OK)
            {
                return ret;
            }

            cant--;
        }
    }

    return TODO_OK;
}

int crearTablero(tLista* tab, const tConfig* conf)
{
    int ret;

    crearLista(tab);

    // se insertan todas las posiciones en "blanco" (menos inicio y salida)
    ret = inicializarTablero(tab, conf->cantPos);
    if(ret != TODO_OK)
    {
        return ret;
    }


    cargarCategoria()



    return TODO_OK;
}

void eliminarTablero(tLista* tab)
{

}

int tirarDado()
{
    return 0;
}
