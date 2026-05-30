#include "ListaCircularDoblementeEnlazada.h"
void crearListaCD(tListaCD *pl)
{
    *pl = NULL;
}

int reservarMemoriaParaNodoYAsignarCD(const void *elem, unsigned tam, tNodo **nuevo)
{
    *nuevo = malloc(sizeof(tNodo));
    if(!(*nuevo))
        return SIN_MEM;

    (*nuevo)->info = malloc(tam);
    if(!(*nuevo)->info)
    {
        free(*nuevo);
        return SIN_MEM;
    }

    memcpy((*nuevo)->info, elem, tam);
    (*nuevo)->tamElem = tam;
    return TODO_OK;
}

void vaciarListaCD(tListaCD *pl)
{
    tNodo *primero, *elim;

    if(*pl == NULL)
        return;

    primero = (*pl)->sig;


    (*pl)->sig = NULL;

    elim = primero;
    while(elim)
    {
        primero = elim->sig;
        free(elim->info);
        free(elim);
        elim = primero;
    }

    *pl = NULL;
}

int insertarAlComienzoDeListaCD(tListaCD *pl, const void *elem, unsigned tam)
{
    tNodo *nue, *primero;

    if(reservarMemoriaParaNodoYAsignarCD(elem, tam, &nue) != TODO_OK)
        return SIN_MEM;

    if(*pl == NULL)
    {

        nue->sig = nue;
        nue->ant = nue;
        *pl = nue;
    }
    else
    {
        primero = (*pl)->sig;


        nue->sig      = primero;
        nue->ant      = *pl;
        (*pl)->sig    = nue;
        primero->ant  = nue;

    }

    return TODO_OK;
}


int insertarAlFinalDeListaCD(tListaCD *pl, const void *elem, unsigned tam)
{
    tNodo *nue, *primero;

    if(reservarMemoriaParaNodoYAsignarCD(elem, tam, &nue) != TODO_OK)
        return SIN_MEM;

    if(*pl == NULL)
    {
        nue->sig = nue;
        nue->ant = nue;
        *pl = nue;
    }
    else
    {
        primero = (*pl)->sig;

        nue->sig      = primero;
        nue->ant      = *pl;
        (*pl)->sig    = nue;
        primero->ant  = nue;

        *pl = nue;
    }

    return TODO_OK;
}

void recorrerDeIzquierdaADerechaCD(const tListaCD *pl, void(*mostrar)(const void *elem))
{
    tNodo *actual, *primero;

    if(*pl == NULL)
        return;

    primero = (*pl)->sig;
    actual  = primero;

    do
    {
        mostrar(actual->info);
        actual = actual->sig;
    }
    while(actual != primero);
}



void recorrerDeDerechaAIzquierdaCD(const tListaCD *pl, void(*mostrar)(const void *elem))
{
    tNodo *actual, *ultimo;

    if(*pl == NULL)
        return;

    ultimo = *pl;
    actual = ultimo;

    do
    {
        mostrar(actual->info);
        actual = actual->ant;
    }
    while(actual != ultimo);
}
int verNElemCD(const tListaCD *pl, unsigned pos, void *elem, unsigned tam)
{
    tNodo   *actual, *primero;
    unsigned i = 0;

    if(*pl == NULL)
        return LISTA_VACIA;

    primero = (*pl)->sig;
    actual  = primero;

    while(i < pos)
    {
        actual = actual->sig;
        i++;


        if(actual == primero)
            return POS_INVALIDA;
    }

    memcpy(elem, actual->info, MINIMO(tam, actual->tamElem));
    return TODO_OK;
}
int actualizarNPosCD(tListaCD *pl, unsigned pos, const void *elem, void(*actualizar)(void *actualizado, const void *actualizador))
{
    tNodo   *actual, *primero;
    unsigned i = 0;

    if(*pl == NULL)
        return LISTA_VACIA;

    primero = (*pl)->sig;
    actual  = primero;

    while(i < pos)
    {
        actual = actual->sig;
        i++;

        if(actual == primero)
            return POS_INVALIDA;
    }

    actualizar(actual->info, elem);
    return TODO_OK;
}
