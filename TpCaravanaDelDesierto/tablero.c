
#include "tablero.h"

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


    ret=cargarCategoria(tab, PREMIO, conf->premios, conf->cantPos);
    if(ret!=TODO_OK)
    {
        return ret;
    }
    ret=cargarCategoria(tab, VIDA_EXTRA, conf->vidasExtra, conf->cantPos);
    if(ret!=TODO_OK)
    {
        return ret;
    }

    ret=cargarCategoria(tab, OASIS, conf->oasis, conf->cantPos);
    if(ret!=TODO_OK)
    {
        return ret;
    }

    ret=cargarCategoria(tab, TORMENTA, conf->tormentas, conf->cantPos);
    if(ret!=TODO_OK)
    {
        return ret;
    }
    ret=cargarBandidos(tab, conf->bandidos, conf->cantPos);
    if(ret!=TODO_OK)
    {
        return ret;
    }

    mostrarLista(tab, mostrarCasillero);
    return TODO_OK;
}
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
    cas.numero++;
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
int cargarBandidos(tLista* tab, unsigned cant, unsigned tamTab)
{
    int ret;
    unsigned pos;

    while(cant > 0)
    {
        pos = (rand() % (tamTab - 2)) + 1; // 1 a (tamTab - 2) (inicio y salida incluidos)
//        rand() % 10 - 2 = (0 a 7) + 1 = 1 a 8
//        0 a 9 --> 1 a 8

        ret = actualizarNPos(tab, NULL, pos, actualizarBandido);
        if(ret != TODO_OK)
        {
            return ret;
        }
        cant--;
    }

    return TODO_OK;
}
void eliminarTablero(tLista* tab)
{
    vaciarLista(tab);
}

int tirarDado()
{
    return rand() % 6 + 1 ;
}
void mostrarCasillero(void *elem)
{
    tCasillero *cas=elem;
    char cat[]={ '.' , 'I' , 'S' , 'P' , 'V', 'O' , 'T'};

    printf("\n%-2d: Cat: %-1c, Bandidos: %-1d. Jugador: %d", cas->numero, cat[cas->categoria], cas->cantBandidos, cas->tieneJugador);
}
void actualizarCat(void *actualizado, const void *actualizador)
{
    tCasillero *elemActualizado=actualizado;
    const unsigned *elemActualizador=actualizador;

    elemActualizado->categoria=*elemActualizador;
}
void actualizarBandido(void *actualizado, const void *actualizador)
{
    tCasillero *elemActualizado=actualizado;

    elemActualizado->cantBandidos++;

    //Actualizador siempre recibe NULL porque solo incrementamos 1 bandido
}
