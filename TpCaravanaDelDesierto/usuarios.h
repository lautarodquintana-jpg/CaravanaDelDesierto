#ifndef USUARIOS_H_INCLUDED
#define USUARIOS_H_INCLUDED

#include "tipos.h"
#include "TDAs/arbol.h"
#include "partidas.h"

int registrarUsuario(tRegistroDeUsuario* usuario, const char* archUsuarios);
int actualizarUsuarioAlSalir(tArbol* pa,tRegistroDeUsuario* usuarioAct, const char* archivoUsuarios);


#endif // USUARIOS_H_INCLUDED
