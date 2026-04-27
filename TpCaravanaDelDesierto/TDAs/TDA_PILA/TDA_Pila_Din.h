#ifndef TDA_PILA_DIN_H
#define TDA_PILA_DIN_H

#include "../NODO/Nodo.h"

typedef nodo* TDAPila;


void crearPila(TDAPila* pila);
bool apilar(TDAPila* pila, const void* elem, size_t tamElem);
bool desapilar(TDAPila* pila, void* elem, size_t tamElem);
bool verTopeDePila(TDAPila* pila, void* elem, size_t tamElem);
bool pilaVacia(const TDAPila* pila);
bool pilaLlena(const TDAPila* pila, size_t tamElem);
void vaciarPila(TDAPila* pila);
bool apilarPilaCir(TDAPila* pila, const void* elem, size_t tamElem);
bool verTopeDePilaCir(TDAPila* pila, void* elem, size_t tamElem);
bool desapilarPilaCir(TDAPila* pila, void* elem, size_t tamElem);
void vaciarPilaCir(TDAPila* pila);



#endif // TDA_PILA_DIN_H
