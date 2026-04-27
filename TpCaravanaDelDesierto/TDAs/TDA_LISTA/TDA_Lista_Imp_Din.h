#ifndef TDA_LISTA_IMP_DIN_H
#define TDA_LISTA_IMP_DIN_H

#include "./NODO/Nodo.h"

typedef nodo* TDAlista;

void crearLista(TDAlista* lista);

bool insertPrimLista(TDAlista* lista, const void* elem, size_t tamElem);
bool verPrimDeLista(TDAlista* lista, void* elem, size_t tamElem);
bool sacarPrimDeLista(TDAlista* lista, void* elem, size_t tamElem);

bool insertFinLista(TDAlista* lista, const void* elem, size_t tamElem);
bool verFinDeLista(TDAlista* lista, void* elem, size_t tamElem);
bool sacarFinDeLista(TDAlista* lista, void* elem, size_t tamElem);

bool insertPosLista(TDAlista* lista, const void* elem, size_t tamElem, size_t pos);
bool verPosDeLista(TDAlista* lista, void* elem, size_t tamElem, size_t pos);
bool sacarPosDeLista(TDAlista* lista, void* elem, size_t tamElem, size_t pos);

int insertOrdListaSinDuplicado(TDAlista* lista, const void* elem, size_t tamElem, Cmp cmp);
int eliminarDuplicadosLista(TDAlista* lista, Cmp cmp);

int invertirLista(TDAlista* lista);
int ordInsercionLista(TDAlista* lista, Cmp cmp);
int ordSeleccionLista(TDAlista* lista, Cmp cmp);



#endif // TDA_LISTA_IMP_DIN_H
