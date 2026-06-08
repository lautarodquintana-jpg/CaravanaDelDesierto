#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TODO_OK 0
#define SIN_MEM 1
#define ERR_ARCH 2
#define LISTA_VACIA 3
#define ELEM_NO_ENCONTRADO 4
#define DUPLICADO 2
#define POS_INVALIDA 6

#define MINIMO(X,Y) ((X) <= (Y) ? (X) : (Y))

typedef struct sNodol
{
    void* info;
    unsigned tamInfo;
    struct sNodol* sig;
} tNodoL;

typedef tNodoL* tLista;

typedef int (*Cmp)(const void* e1, const void* e2);
typedef void (*Actualizar)(void* actualizado, const void* actualizador);
typedef void (*Accion)(const void* elem);

void crearLista(tLista* p);
int listaVacia(const tLista* p);
int listaLlena(const tLista* p, unsigned cantBytes);
void vaciarLista(tLista* p);
int insertarAlComienzo(tLista* p, const void* d, unsigned cantBytes);
int sacarPrimeroLista(tLista* p, void* d, unsigned cantBytes);
int verPrimeroLista(const tLista* p, void* d, unsigned cantBytes);
int insertarAlFinal(tLista* p, const void* d, unsigned cantBytes);
int sacarUltimoLista(tLista* p, void* d, unsigned cantBytes);
int verUltimoLista(const tLista* p, void* d, unsigned cantBytes);
void mostrarLista(const tLista *p, Accion accion);

int eliminarElemDeLista(tLista* p, void* d, unsigned cantBytes, Cmp cmp);

int insertarOrdenadoListaSinD(tLista* p, const void* d, unsigned cantBytes, Cmp cmp, Actualizar actualizar);
int insertarOrdenadoListaConD(tLista* p, const void* d, unsigned cantBytes, Cmp cmp);

void ordenarListaDesc(tLista* p, Cmp cmp);
void ordenarListaAsc(tLista* p, Cmp cmp);

int actualizarNPos(tLista* p, const void* d, unsigned pos, Actualizar actualizar);

int verNElem(tLista *p, unsigned pos, void *elem, unsigned tam);

int cargarOrdenadoListaSinDupDeArchivo(tLista* p, unsigned cantBytes, Cmp cmp, Actualizar actualizar, const char* nomArch);


#endif // LISTA_H_INCLUDED
