#include "Nodo.h"

nodo* crearNodo(const void* elem, size_t tamElem)
{
    nodo* nue = malloc(sizeof(nodo));
    void* elemNodo = malloc(tamElem);

    if(nue == NULL || elemNodo == NULL)
    {
        free(elemNodo);
        free(nue);
        return NULL;
    }

    memcpy(elemNodo, elem, tamElem);

    nue->elem = elemNodo;
    nue->tamElem = tamElem;
    nue->sig = NULL;

    return nue;
}
void destruirNodo(nodo* nae, void* elem, size_t tamElem)
{
    memcpy(elem, nae->elem, MIN(nae->tamElem, tamElem));
    free(nae->elem);
    free(nae);
}
