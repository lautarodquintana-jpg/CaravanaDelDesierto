#include "ColaDinamica.h"
void crearCola(tCola *c)
{
    c->pri=NULL;
    c->ult=NULL;
}
void vaciarCola(tCola *c)
{//Voy vaciando del primero a ultimo
    tNodoC *sig;

    while(c->pri)
    {
        sig=c->pri->sig;
        free(c->pri->info);
        free(c->pri);
        c->pri=sig;
    }
    c->ult=NULL;//Es innecesario poner pri en NULL porque al borrar el ultimo, este adquirira la direccion de siguiente que es Null
}
int ponerEnCola(tCola *c, const void *elem, unsigned tamElem)
{
    tNodoC *nue;
    nue=malloc(sizeof(tNodoC));
    if(!nue)
    {
        return 0;
    }
    nue->info=malloc(tamElem);
    if(!nue->info)
    {
        free(nue);
        return 0;
    }

    memcpy(nue->info, elem, tamElem);
    nue->sig=NULL;
    nue->tamElem=tamElem;
    if(c->pri==NULL)
        c->pri=nue;
    else
    {
        c->ult->sig=nue;
    }
    c->ult=nue;
    return 1;
}
int verPrimero(const tCola *c, void *elem, unsigned tamElem)
{
    if(c->pri==NULL)
        return 0;
    memcpy(elem, c->pri->info, minimo(tamElem, c->pri->tamElem));
    return 1;
}
int sacarDeCola(tCola *c, void *elem, unsigned tamElem)
{//Para sacar de cola no debo perder el siguiente antes de liberar el nodo, chequear que la pila no esté vacia, que si el siguiente es nulo, poner en nulo a ult tambien
    tNodoC *sig;
    if(c->pri==NULL)
        return 0;

    memcpy(elem, c->pri->info, minimo(c->pri->tamElem, tamElem));
    sig=c->pri->sig;
    free(c->pri->info);
    free(c->pri);
    c->pri=sig;
    if(c->pri==NULL)
        c->ult=NULL;

    return 1;

}
int colaVacia(const tCola *c)
{
    return c->pri==NULL;
}
int colaLlena(const tCola *c)
{
    return 0;//Se mantiene por cuestiones de compatibilidad, pero no tiene uso real
}
