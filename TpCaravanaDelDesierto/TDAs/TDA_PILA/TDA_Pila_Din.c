#include "TDA_Pila_Din.h"


void crearPila(TDAPila* pila)
{
    *pila = NULL;
}
bool apilar(TDAPila* pila, const void* elem, size_t tamElem)
{
    nodo* nue = crearNodo(elem, tamElem);

    if(!nue)
        return false;

    nue->sig = *pila;
    *pila = nue;

    return true;
}
bool desapilar(TDAPila* pila, void* elem, size_t tamElem)
{
    if(!pila)
        return false;

    nodo* nae = *pila;
    *pila = nae->sig;

    destruirNodo(nae,elem, tamElem);

    return true;
}
bool verTopeDePila(TDAPila* pila, void* elem, size_t tamElem)
{
    if(!pila)
        return false;

    nodo* tope = *pila;

    memcpy(elem, tope->elem, MIN(tamElem, tope->tamElem));

    return true;
}
bool pilaVacia(const TDAPila* pila)
{
    return !*pila;
}
bool pilaLlena(const TDAPila* pila, size_t tamElem)
{
    void* auxNodo = malloc(sizeof(nodo));
    void* auxElem = malloc(tamElem);

    free(auxNodo);
    free(auxElem);

    return !auxNodo || !auxElem;
}
void vaciarPila(TDAPila* pila)
{
    nodo* nae;

    while (*pila)
    {
        nae = *pila;
        *pila = nae->sig;
        free(nae->elem);
        free(nae);
    }
}

bool apilarPilaCir(TDAPila* pila, const void* elem, size_t tamElem)
{
    nodo* nue = crearNodo(elem, tamElem);

    if(!nue)
        return false;
    
    if(*pila)
    {
        nue->sig = (*pila)->sig;
        (*pila)->sig = nue;
    }
    else
    {
        nue->sig = nue;
        *pila = nue;
    }
    return true;
}
bool verTopeDePilaCir(TDAPila* pila, void* elem, size_t tamElem)
{
    if(!*pila)
        return false;
    
    nodo* tope = (*pila)->sig;

    memcpy(elem, tope->elem, MIN(tamElem, tope->tamElem));

    return true;

}
bool desapilarPilaCir(TDAPila* pila, void* elem, size_t tamElem)
{
    if (!*pila)
        return false;

    nodo* nae = (*pila)->sig;
    
    destruirNodo(nae, elem, tamElem);

    if(nae == *pila)
        *pila = NULL;
    else
        (*pila)->sig = nae->sig;

    return true;
}
void vaciarPilaCir(TDAPila* pila)
{
    nodo* nae;

    while (*pila)
    {
        nae = (*pila)->sig;

        if(nae == *pila)
            *pila = NULL;
        else
            (*pila)->sig = nae->sig;
        
        free(nae->elem);
        free(nae);
    }
}


