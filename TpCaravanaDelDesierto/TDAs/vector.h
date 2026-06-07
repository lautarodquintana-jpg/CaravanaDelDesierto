#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>


#define CAP_INI 8
#define FACTOR_INCR 1.5
#define FACTOR_DECR 0.5
#define FACTOR_OCUP 0.25

#define TODO_OK 0
#define SIN_MEM 1
#define ERR_TAM_ELEM 2
#define DUPLICADO 5
#define POS_INVALIDA 6


typedef struct
{
   void* vec;
   size_t ce;
   size_t cap;
   size_t tamElem;
} tVector;

typedef int (*Cmp)(const void* e1, const void* e2);
typedef void (*Accion)(void* e);
typedef void (*Actualizar)(void* actualizado, const void* actualizador);

int vectorCrear(tVector* v, size_t tamE);
void vectorRecorrer(tVector* v, Accion acc);
int vectorInsertarAlFinal(tVector* v, const void* elem);
int vectorOrdInsertar(tVector* v, const void* elem, Cmp cmp);
int vectorEliminarDePos(tVector* v, int pos);
int vectorOrdBuscar(const tVector* v, void* elem, Cmp cmp);
int vectorOrdenar(tVector* v, Cmp cmp);
void vectorDestruir(tVector* v);
int vectorObtenerElem(tVector* v, int pos, void* elem);
int vectorActualizarNPos(tVector* v, int pos, const void* elem, void(*actualizar)(void *actualizado, const void *actualizador));
int vectorCantElementos(tVector * v);
#endif // VECTOR_H_INCLUDED
