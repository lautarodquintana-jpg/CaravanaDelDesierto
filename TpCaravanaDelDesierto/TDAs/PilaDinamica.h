#ifndef PILADINAMICA_H_INCLUDED
#define PILADINAMICA_H_INCLUDED
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct sNodo
{
    void *info;
    unsigned tam;
    struct sNodo *sig;
}TNodo;//Esto queda asi ya que si omitiese sNodo, el compilador no sabría a que estructura apunta, debido a que no conoce el alias todavia.

typedef TNodo* TPila;

void crearPila(TPila *p);
int pilaLlena(const TPila *p, unsigned tam);
int pilaVacia(const TPila *p);
void vaciarPila(TPila *p);
int apilar(TPila *p, const void *elem, unsigned tam);
int desapilar(TPila *p, void *elem, unsigned tam);
int verTope(const TPila *p, void *dato, unsigned tam);
unsigned MinimoEntre2(unsigned a, unsigned b);

#endif // PILADINAMICA_H_INCLUDED
