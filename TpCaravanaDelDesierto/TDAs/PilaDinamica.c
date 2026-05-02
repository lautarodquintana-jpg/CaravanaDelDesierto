//Ahora al decir TPila en realidad estoy diciendo Tnodo*, o sea, un puntero a un nodo
#include "PilaDinamica.h"


void crearPila(TPila *p)//Esto quedaría asi: TNodo **p, o sea, puntero al puntero. Como queremos inicializar a lo que apunta p es la dir null
{
    *p=NULL;
}
int pilaLlena(const TPila *p, unsigned tam)
{
    return 0;
}
int pilaVacia(const TPila *p)
{//Si bien TPila *p en realidad es TNodo **p, Si TNodo *p apunta a nulo, no tiene nada
    if(*p==NULL)
        return 1;
    else
        return 0;
}
void vaciarPila(TPila *p)
{//Debo vaciar cada nodo, y la dir que posee info de cada nodo
/*  Pasos:Chequeo que *p no sea NULL
    Guardo aux=(*p)->sig
    Libero (*p)->info
    Libero el nodo
    *p=aux*/
    void *aux;
    while(*p!=NULL)
    {
        aux=(*p)->sig;
        free((*p)->info);
        free(*p);
        *p=aux;
    }
}
int apilar(TPila *p, const void *elem, unsigned tam)
{
    TPila nuevo; //TPila==TNodo *

    nuevo=malloc(sizeof(TNodo));
    if(!nuevo)
        return 0;
    nuevo->info=malloc(tam);
    if(!nuevo->info)
    {//DEBO VACIAR LA MEMORIA RESERVADA PARA EL NODO
        free(nuevo);
        return 0;
    }

    memcpy(nuevo->info, elem ,tam);
    nuevo->tam=tam;
    nuevo->sig=*p;//Antes hacia nuevo->sig=p, sin puntero. Que significaba eso? que le estaba pasando el contenido de p (la dir), no el contenido de lo que p apuntaba
    *p=nuevo;

    return 1;
}
int desapilar(TPila *p, void *elem, unsigned tam)
{
/*  Chequeo que *p no sea nulo
    Copio en elem lo que tiene (*p)->info la cantidad de bytes que sea menor entre tam y p->tam
    TPila elim=p
    *p=elim->sig
    free(elim->info)
    free(elim)
    retorno*/

    TPila elim;

    if(*p==NULL)
        return 0;

    memcpy(elem, (*p)->info, MinimoEntre2(tam, (*p)->tam));
    elim=*p; //Antes hacia elim=p;, esta mal debido a que copio la direccion de TNodo*, no de TNodo **
    *p=((*p)->sig);

    free(elim->info); //Antes hacia  free((*elim)->info), especificamente está mal (*elim) ya que eso dice: accede al campo info de lo que apunta elim, siendo que ya tengo la direccion
    free(elim);

    return 1;
}
int verTope(const TPila *p, void *dato, unsigned tam)
{
    if(*p==NULL)
        return 0;

    memcpy(dato, (*p)->info, MinimoEntre2(tam, (*p)->tam));

    return 1;
}
unsigned MinimoEntre2(unsigned a, unsigned b)
{
    return (a<=b? a:b);
}
