#ifndef USUARIOS_H_INCLUDED
#define USUARIOS_H_INCLUDED
#include "tipos.h"
#include "partidas.h"
#include "TDAs/arbol.h"

int cargarArbolUsuarios(tArbol *pa);
int generarIdxUsuariosEnArbolDesdeArch(tArbol *pa, const char *nomArch);
int registrarUsuario(tArbol *pa, tRegistroDeUsuario *usuario, const char *archUsuarios);
int actualizarUsuarioAlSalir(tArbol *pa, tRegistroDeUsuario *usuarioAct, const char *archUsuarios);


#endif // USUARIOS_H_INCLUDED
