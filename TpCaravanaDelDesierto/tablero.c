#include "tablero.h"

int crearTablero(tListaCD* tab, const tConfig* conf)
{
    int ret;

    crearListaCD(tab);

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

    recorrerDeIzquierdaADerechaCD(tab, mostrarCasillero);

    ret = crearCaravanaTxt(tab);
    if(ret != TODO_OK)
    {
        return ret;
    }

    return TODO_OK;
}

int inicializarTablero(tListaCD* tab, unsigned cantPos)
{
    int i = 1;
    int ret;

    tCasillero cas;
    cas.cantBandidos = 0;
    cas.categoria = INICIO;
    cas.numero = i;
    cas.tieneJugador = 1;

    ret = insertarAlComienzoDeListaCD(tab, &cas, sizeof(tCasillero));
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
        ret = insertarAlFinalDeListaCD(tab, &cas, sizeof(tCasillero));
        if(ret != TODO_OK)
        {
            return ret;
        }

        i++;
    }

    cas.categoria = SALIDA;
    cas.numero++;
    ret = insertarAlFinalDeListaCD(tab, &cas, sizeof(tCasillero));
    if(ret != TODO_OK)
    {
        return ret;
    }

    return TODO_OK;
}

int cargarCategoria(tListaCD* tab, unsigned cat, unsigned cant, unsigned tamTab)
{
    int ret;
    unsigned pos;
    tCasillero casilleroLeido;

    while(cant > 0)
    {
        pos = (rand() % (tamTab - 2)) + 1; // 1 a (tamTab - 2) (inicio y salida incluidos)
//        rand() % 10 - 2 = (0 a 7) + 1 = 1 a 8
//        0 a 9 --> 1 a 8

        ret = verNElemCD(tab, pos, &casilleroLeido, sizeof(tCasillero));
        if(ret != TODO_OK)
        {
            return ret;
        }

        if(casilleroLeido.categoria == VACIO)
        {
            ret = actualizarNPosCD(tab, &cat, pos, actualizarCat);
            if(ret != TODO_OK)
            {
                return ret;
            }

            cant--;
        }
    }

    return TODO_OK;
}

int cargarBandidos(tListaCD* tab, unsigned cant, unsigned tamTab)
{
    int ret;
    unsigned pos;

    while(cant > 0)
    {
        pos = (rand() % (tamTab - 2)) + 1; // 1 a (tamTab - 2) (inicio y salida incluidos)
//        rand() % 10 - 2 = (0 a 7) + 1 = 1 a 8
//        0 a 9 --> 1 a 8

        ret = actualizarNPosCD(tab, NULL, pos, actualizarBandido);
        if(ret != TODO_OK)
        {
            return ret;
        }
        cant--;
    }

    return TODO_OK;
}

void eliminarTablero(tListaCD* tab)
{
    vaciarListaCD(tab);
}

int tirarDado()
{
    return rand() % 6 + 1 ;
}

void mostrarCasillero(const void *elem)
{
    const tCasillero *cas = elem;
    char cat[] = { '.' , 'I' , 'S' , 'P' , 'V', 'O' , 'T'};

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

int crearCaravanaTxt(tListaCD *tab)
{
    int i = 1;
    tCasillero cas;
    char cat[] = { '.' , 'I' , 'S' , 'P' , 'V', 'O' , 'T'};

    FILE *pf = fopen("caravana.txt", "wt");
    if(pf == NULL)
    {
        return ERR_ARCH;
    }

    fprintf(pf, "01: [%c %c]\n", cat[1], 'J');

    while(verNElemCD(tab, i, &cas, sizeof(tCasillero)) == TODO_OK)
    {
        fprintf(pf, "%02d: [", cas.numero);

        if(cas.categoria == VACIO && cas.cantBandidos)
        {
            if(cas.cantBandidos == 1)
            {
                fprintf(pf, "%c", 'B');
            }
            else
            {
                fprintf(pf, "%d%c", cas.cantBandidos, 'B');
            }
        }
        else if (cas.categoria != VACIO && cas.cantBandidos)
        {
            if(cas.cantBandidos == 1)
            {
                fprintf(pf, "%c %c", cat[cas.categoria], 'B');
            }
            else
            {
                fprintf(pf, "%c %d%c", cat[cas.categoria], cas.cantBandidos, 'B');
            }
        }
        else
        {
            fprintf(pf, "%c", cat[cas.categoria]);
        }

        fprintf(pf, "]\n");

        i++;
    }

    fclose(pf);

    return TODO_OK;
}

















