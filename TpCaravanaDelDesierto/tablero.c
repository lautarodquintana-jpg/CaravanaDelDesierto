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

    ret = cargarCategoria(tab, PREMIO, conf->premios, conf->cantPos);
    if(ret != TODO_OK)
    {
        return ret;
    }

    ret = cargarCategoria(tab, VIDA_EXTRA, conf->vidasExtra, conf->cantPos);
    if(ret != TODO_OK)
    {
        return ret;
    }

    ret = cargarCategoria(tab, OASIS, conf->oasis, conf->cantPos);
    if(ret != TODO_OK)
    {
        return ret;
    }

    ret = cargarCategoria(tab, TORMENTA, conf->tormentas, conf->cantPos);
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
    cas.categoria = INICIO;
    cas.numero = i;

    ret = insertarAlComienzoDeListaCD(tab, &cas, sizeof(tCasillero));
    if(ret != TODO_OK)
    {
        return ret;
    }

    i++;
    cas.categoria = VACIO;

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

void eliminarTablero(tListaCD* tab)
{
    vaciarListaCD(tab);
}

int tirarDado()
{
    return rand() % 6 + 1 ;
}

void actualizarCat(void *actualizado, const void *actualizador)
{
    tCasillero *elemActualizado=actualizado;
    const unsigned *elemActualizador=actualizador;

    elemActualizado->categoria=*elemActualizador;
}

int crearCaravanaTxt(tListaCD *tab, tVector *bandidos)
{
    int i = 1;
    int cantBandidosEnCas;
    tCasillero cas;
    char cat[] = { '.', 'I', 'S', 'P', 'V', 'O', 'T'};

    FILE *pf = fopen("caravana.txt", "wt");
    if(pf == NULL)
    {
        return ERR_ARCH;
    }

    fprintf(pf, "01: [%c %c]\n", cat[1], 'J');

    while(verNElemCD(tab, i, &cas, sizeof(tCasillero)) == TODO_OK)
    {
        fprintf(pf, "%02d: [", cas.numero);

        cantBandidosEnCas = cantBandidoEnPos(bandidos, cas.numero);

        if(cas.categoria == VACIO && cantBandidosEnCas > 0)
        {
            if(cantBandidosEnCas == 1)
            {
                fprintf(pf, "B");
            }
            else
            {
                fprintf(pf, "%dB", cantBandidosEnCas);
            }
        }
        else if (cas.categoria != VACIO && cantBandidosEnCas > 0)
        {
            if(cantBandidosEnCas == 1)
            {
                fprintf(pf, "%c B", cat[cas.categoria]);
            }
            else
            {
                fprintf(pf, "%c %dB", cat[cas.categoria], cantBandidosEnCas);
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

void mostrarTablero(const tListaCD *tab, tVector *bandidos, int posJ, int tamTablero)
{
    int i = 0;
    tCasillero cas;
    char cat[] = { '.', 'I', 'S', 'P', 'V', 'O', 'T' };
    int cantBandidos;
    int hayJugador;
    int hayCategoria;
    int hayBandidos;
    int hayAlgoAntes;

    while (verNElemCD(tab, i, &cas, sizeof(tCasillero)) == TODO_OK)
    {
        cantBandidos = cantBandidoEnPos(bandidos, cas.numero);
        hayJugador   = (cas.numero == posJ);
        hayCategoria = (cas.categoria != VACIO);
        hayBandidos  = (cantBandidos > 0);

        printf("%02d: [", cas.numero);

        if (!hayJugador && !hayBandidos)
            printf("%c", cat[cas.categoria]);
        else
        {
            if (hayCategoria)
                printf("%c", cat[cas.categoria]);

            if (hayJugador)
                printf("%sJ", hayCategoria ? " " : "");

            if (hayBandidos)
            {
                hayAlgoAntes = hayCategoria || hayJugador;
                if (cantBandidos > 1)
                    printf("%s%dB", hayAlgoAntes ? " " : "", cantBandidos);
                else
                    printf("%sB", hayAlgoAntes ? " " : "");
            }
        }

        printf("]\n");
        i++;
    }
}
