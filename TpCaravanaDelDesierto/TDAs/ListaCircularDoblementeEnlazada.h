#ifndef LISTACIRCULARDOBLEMENTEENLAZADA_H_INCLUDED
#define LISTACIRCULARDOBLEMENTEENLAZADA_H_INCLUDED

#include <string.h>
#include <stdlib.h>

#define MINIMO(X,Y) ((X) <= (Y) ? (X) : (Y))
#define TODO_OK 0
#define SIN_MEM 1
#define ERR_ARCH 2
#define LISTA_VACIA 3
#define ELEM_NO_ENCONTRADO 4
#define DUPLICADO 5
#define POS_INVALIDA 6

typedef struct sNodoCD
{
    struct sNodoCD *ant;
    void         *info;
    unsigned      tamElem;
    struct sNodoCD *sig;
} tNodoCD;

typedef tNodoCD* tListaCD;

//Inicializacion y liberacion
void crearListaCD(tListaCD *pl);
void vaciarListaCD(tListaCD *pl);

//Insercion
int  reservarMemoriaParaNodoYAsignarCD(const void *elem, unsigned tam, tNodoCD **nuevo);
int  insertarAlComienzoDeListaCD(tListaCD *pl, const void *elem, unsigned tam);
int  insertarAlFinalDeListaCD(tListaCD *pl, const void *elem, unsigned tam);


//Recorrido
void recorrerDeIzquierdaADerechaCD(const tListaCD *pl, void(*mostrar)(const void *elem));
void recorrerDeDerechaAIzquierdaCD(const tListaCD *pl, void(*mostrar)(const void *elem));

//Otros
int verNElemCD(const tListaCD *pl, unsigned pos, void *elem, unsigned tam);
int actualizarNPosCD(tListaCD *pl, const void *elem, unsigned pos, void(*actualizar)(void *actualizado, const void *actualizador));


#endif // LISTACIRCULARDOBLEMENTEENLAZADA_H_INCLUDED
