#ifndef LISTACIRCULARDOBLEMENTEENLAZADA_H_INCLUDED
#define LISTACIRCULARDOBLEMENTEENLAZADA_H_INCLUDED

#include <string.h>
#include <stdlib.h>

#define MINIMO(X,Y) ((X) <= (Y) ? (X) : (Y))
#define TODO_OK 0
#define SIN_MEM 1
#define LISTA_VACIA 3
#define ELEM_NO_ENCONTRADO 4
#define DUPLICADO 5
#define POS_INVALIDA 6

typedef struct sNodo
{
    struct sNodo *ant;
    void         *info;
    unsigned      tamElem;
    struct sNodo *sig;
} tNodo;

typedef tNodo* tListaCD;

//Inicializacion y liberacion
void crearListaCD(tListaCD *pl);
void vaciarListaCD(tListaCD *pl);

//Insercion
int  reservarMemoriaParaNodoYAsignarCD(const void *elem, unsigned tam, tNodo **nuevo);
int  insertarAlComienzoDeListaCD(tListaCD *pl, const void *elem, unsigned tam);
int  insertarAlFinalDeListaCD(tListaCD *pl, const void *elem, unsigned tam);


//Recorrido
void recorrerDeIzquierdaADerechaCD(const tListaCD *pl, void(*mostrar)(const void *elem));
void recorrerDeDerechaAIzquierdaCD(const tListaCD *pl, void(*mostrar)(const void *elem));

//Otros
int verNElemCD(const tListaCD *pl, unsigned pos, void *elem, unsigned tam);
int actualizarNPosCD(tListaCD *pl, unsigned pos, const void *elem, void(*actualizar)(void *actualizado, const void *actualizador));

#endif // LISTACIRCULARDOBLEMENTEENLAZADA_H_INCLUDED
