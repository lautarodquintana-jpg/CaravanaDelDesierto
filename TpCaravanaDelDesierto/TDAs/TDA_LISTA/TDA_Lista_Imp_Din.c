#include "TDA_Lista_Imp_Din.h"

void crearLista(TDAlista* lista)
{
    *lista = NULL;
}

bool insertPrimLista(TDAlista* lista, const void* elem, size_t tamElem)
{
    nodo* nue = crearNodo(elem, tamElem);
    if(!nue)
        return false;

    nue->sig = *lista;

    *lista = nue;

    return true;
}

bool verPrimDeLista(TDAlista* lista, void* elem, size_t tamElem)
{
    if(!*lista)
        return false;

    nodo* nae = *lista;

    memcpy(elem, nae->elem, MIN(tamElem, nae->tamElem));

    return true;
}
bool sacarPrimDeLista(TDAlista* lista, void* elem, size_t tamElem) 
{
    if(!*lista)
        false;

    nodo* nae = *lista;
    *lista = nae->sig;

    destruirNodo(nae, elem, MIN(tamElem, nae->tamElem));

    return true;
}

bool insertFinLista(TDAlista* lista, const void* elem, size_t tamElem)
{
    while(*lista)
        lista = &(*lista)->sig;

    return insertPrimLista(lista, elem, tamElem);
}
bool verFinDeLista(TDAlista* lista, void* elem, size_t tamElem)
{
    if(!*lista)
        return false;

    while ((*lista)->sig)
        lista = &(*lista)->sig;
    
    nodo* aux = *lista;

    memcpy(elem, aux->elem, MIN(tamElem, aux->tamElem));
    
    return true;
}
bool sacarFinDeLista(TDAlista* lista, void* elem, size_t tamElem)
{
    if(!*lista)
        return false;

    while ((*lista)->sig)
        lista = &(*lista)->sig;
    
    nodo* nae = *lista;

    destruirNodo(nae, elem, tamElem);
    *lista = NULL;

    return true;
}

bool insertPosLista(TDAlista* lista, const void* elem, size_t tamElem, size_t pos)
{
    while (*lista && pos)
    {
        lista = &(*lista)->sig;
        pos--;
    }

    if(pos)
        return false;

    return insertPrimLista(lista, elem, tamElem);
}
bool verPosDeLista(TDAlista* lista, void* elem, size_t tamElem, size_t pos)
{
    if(!*lista)
        return false;

    while ((*lista)->sig && pos)
    {
        lista = &(*lista)->sig;
        pos--;
    }
    if(!*lista || pos)
        return false;
    
    nodo* aux = *lista;

    memcpy(elem, aux->elem, MIN(tamElem, aux->tamElem));
    
    return true;
}
bool sacarPosDeLista(TDAlista* lista, void* elem, size_t tamElem, size_t pos)
{
    if(!*lista)
        return false;

    while ((*lista)->sig && pos)
    {
        lista = &(*lista)->sig;
        pos--;
    }

    if(!*lista || pos)
        return false;

    nodo* nae = *lista;
    *lista = nae->sig;

    destruirNodo(nae, elem, tamElem);

    return true;
}

int insertOrdListaSinDuplicado(TDAlista* lista, const void* elem, size_t tamElem, Cmp cmp)
{
    if(*lista && cmp(elem,(*lista)->elem) > 0)
        lista = &(*lista)->sig;
    
    if(*lista && cmp(elem, (*lista)->elem) == 0)
        return DUPLICADO;
    
    return insertPrimLista(lista, elem, tamElem);
}
int eliminarDuplicadosLista(TDAlista* lista, Cmp cmp)
{
    if(!*lista)
        return ERR_SIN_ELEM;

    nodo* anterior;
    nodo* actual;

    while(*lista)
    {
        anterior = *lista;
        actual = (*lista)->sig;

        while(actual)
        {
            if(cmp(anterior->elem, actual->elem) == 0)
            {
                anterior->sig = actual->sig;

                free(actual->elem);
                free(actual);

                actual = anterior->sig;
            }
            else
            {
                anterior = actual;
                actual = anterior->sig;
            }
        }
        lista = &(*lista)->sig;
    }

    return TODO_OK;
}


int invertirLista(TDAlista* lista)
{
    if(!*lista)
        return ERR_SIN_ELEM;

    nodo* actual = *lista;
    nodo* siguiente = NULL;
    nodo* anterior = NULL;

    while (actual)
    {
        siguiente = actual->sig;

        actual->sig = anterior;

        anterior = actual;
        actual = siguiente;
    }
    *lista = anterior;
    
    return TODO_OK
}

int ordInsercionLista(TDAlista* lista, Cmp cmp)
{

    return TODO_OK;
}
int ordSeleccionLista(TDAlista* lista, Cmp cmp)
{
    
    return TODO_OK;
}
