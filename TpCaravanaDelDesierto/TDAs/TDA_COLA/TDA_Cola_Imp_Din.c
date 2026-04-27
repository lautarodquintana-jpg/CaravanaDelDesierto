#include "TDA_Cola_Imp_Din.h"


void crearCola(TDACola* cola)
{
    cola->ini = NULL;
    cola->ult = NULL;
}
bool encolar(TDACola* cola, const void* elem, size_t tamElem)
{
    nodo* nue = crearNodo(elem, tamElem);


    cola->ult ? (cola->ult->sig = nue) : (cola->ini = nue);

    cola->ult = nue;

    return true;
}
bool desencolar(TDACola* cola, void* elem, size_t tamElem)
{
    nodo* nae = cola->ini;

    if(!nae)
        return false;

    cola->ini = nae->sig;

    destruirNodo(nae,elem, tamElem);

    if(!cola->ini)
        cola->ult = NULL;

    return true;
}
bool verFrenteDeCola(TDACola* cola, void* elem, size_t tamElem)
{
    nodo* aux = cola->ini;

    if(!aux)
        return false;

    memcpy(elem, aux->elem, MIN(tamElem, aux->tamElem));

    return true;
}
bool colaVacia(const TDACola* cola)
{
    return !cola->ini;
}
bool colaLlena(const TDACola* cola, size_t tamElem)
{
    void* auxNodo = malloc(sizeof(nodo));
    void* auxElem = malloc(tamElem);
    free(auxNodo);
    free(auxElem);

    return !auxElem || !auxNodo;
}
void vaciarCola(TDACola* cola)
{
    while (cola->ini)
    {
        nodo* nae = cola->ini;
        cola->ini = nae->sig;
        free(nae->elem);
        free(nae);
    }
    cola->ult = NULL;
}



void crearColaCir(TDAcolaCir* cola)
{
    *cola = NULL;
}
bool encolarCir(TDAcolaCir* cola, const void* elem, size_t tamElem)
{
    
    nodo* nue = crearNodo(elem, tamElem);

    if(!nue)
        return false;

    if(*cola)
    {
        nue->sig = (*cola)->sig;
        (*cola)->sig = nue;
    }
    else
        nue->sig = nue;

    *cola = nue;

    return true;
}
bool desencolarCir(TDAcolaCir* cola, void* elem, size_t tamElem)
{
    if(!*cola)
        return false;

    nodo* nae = (*cola)->sig;

    destruirNodo(nae, elem, MIN(tamElem,nae->tamElem));

    if(nae == *cola)
        return false;
    else
        (*cola)->sig = nae->sig;

    return true;
}
bool verFrenteDeColaCir(TDAcolaCir* cola, void* elem, size_t tamElem)
{
    if(!*cola)
        return false;

    nodo* nae = (*cola)->sig;

    memcpy(elem, nae->elem, MIN(tamElem, nae->tamElem));
    return true;
}
bool colaCirVacia(const TDAcolaCir* cola)
{
    return !*cola;
}
bool colaCirLlena(const TDAcolaCir* cola, size_t tamElem)
{
    void* nodoAux = malloc(sizeof(nodo));
    void* elemAux = malloc(tamElem);
    free(nodoAux);
    free(elemAux);

    return !nodoAux || !elemAux;
}
void vaciarColaCir(TDAcolaCir* cola)
{
    nodo* nae;
    while (*cola)
    {
        nae = (*cola)->sig;
        if(nae == *cola)
            *cola = NULL;
        else
            (*cola)->sig = nae->sig;

        free(nae->elem);
        free(nae);
    }

}
