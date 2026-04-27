#ifndef TDA_COLA_IMP_DIN_H
#define TDA_COLA_IMP_DIN_H

#include "../NODO/Nodo.h"

typedef struct
{
    nodo* ini;
    nodo* ult;
}TDACola;

typedef nodo* TDAcolaCir;

void crearCola(TDACola* cola);
bool encolar(TDACola* cola, const void* elem, size_t tamElem);
bool desencolar(TDACola* cola, void* elem, size_t tamElem);
bool verFrenteDeCola(TDACola* cola, void* elem, size_t tamElem);
bool colaVacia(const TDACola* cola);
bool colaLlena(const TDACola* cola, size_t tamElem);
void vaciarCola(TDACola* cola);


void crearColaCir(TDAcolaCir* cola);
bool encolarCir(TDAcolaCir* cola, const void* elem, size_t tamElem);
bool desencolarCir(TDAcolaCir* cola, void* elem, size_t tamElem);
bool verFrenteDeColaCir(TDAcolaCir* cola, void* elem, size_t tamElem);
bool colaCirVacia(const TDAcolaCir* cola);
bool colaCirLlena(const TDAcolaCir* cola, size_t tamElem);
void vaciarColaCir(TDAcolaCir* cola);

#endif // TDA_COLA_IMP_DIN_H
