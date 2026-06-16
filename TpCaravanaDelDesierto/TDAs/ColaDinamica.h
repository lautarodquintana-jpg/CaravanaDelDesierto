#ifndef COLADINAMICA_H_INCLUDED
#define COLADINAMICA_H_INCLUDED

#include <string.h>
#include <stdlib.h>
#define minimo(x,y)(x<=y? x:y)

#define TODO_OK 0
#define COLA_VACIA 2
#define SIN_MEM 1
typedef struct sNodoC
{
    void *info;
    unsigned tamElem;
    struct sNodoC *sig;
}tNodoC;
typedef struct
{
    tNodoC *pri;
    tNodoC *ult;
}tCola;

void crearCola(tCola *c);
void vaciarCola(tCola *c);
int ponerEnCola(tCola *c, const void *elem, unsigned tamElem);
int verPrimero(const tCola *c, void *elem, unsigned tamElem);
int sacarDeCola(tCola *c, void *elem, unsigned tamElem);
int colaVacia(const tCola *c);
int colaLlena(const tCola *c);

#endif // COLADINAMICA_H_INCLUDED
