#ifndef NODO_H_
#define NODO_H_

#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>

#define TODO_OK 0
#define ERR_ARCH 1
#define ERR_SIN_MEM 2
#define ERR_NO_ENCONTRADO -1
#define ERR_ARGS 3
#define ERR_ARCH_A_MEM 4
#define DUPLICADO 5
#define ERR_SIN_ELEM 1

#define MIN(X,Y) X > Y ? Y : X


typedef int (*Cmp)(const void* a, const void* b);

typedef struct sNodo
{
    void* elem;
    size_t tamElem;
    struct sNodo* sig;
}nodo;

nodo* crearNodo(const void* elem, size_t tamElem);
void destruirNodo(nodo* nae, void* elem, size_t tamElem);

#endif // NODO_H_
