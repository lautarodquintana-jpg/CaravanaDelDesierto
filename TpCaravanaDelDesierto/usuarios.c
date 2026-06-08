#include "usuarios.h"


int registrarUsuario(tRegistroDeUsuario* usuario, const char* archUsuarios)
{
    FILE* arch = fopen(archUsuarios, "r+b");
    if(!arch)
    {
        arch = fopen(archUsuarios, "w+b");
        if(!arch)
        {
            return ERROR_ARCHIVO;
        }
    }

    fseek(arch, 0, SEEK_END);

    fwrite(usuario, sizeof(tRegistroDeUsuario), 1, arch);

    fclose(arch);
    return TODO_OK;
}
int actualizarUsuarioAlSalir(tArbol* pa,tRegistroDeUsuario* usuarioAct, const char* archivoUsuarios)
{
    tRegistroDeUsuario usuarioALeer;
    tIndJugadores indAbuscar;
    int ret;
    FILE* pf = fopen(archivoUsuarios, "r+b");
    if(!pf)
        return ERROR_ARCHIVO;

    strcpy(indAbuscar.clave, usuarioAct->nombreUsuario);
    ret = buscarElemArbol(pa, &indAbuscar, sizeof(tIndJugadores), cmpIndiceJugador);
    if(ret == ERROR_NO_ENCONTRADO)
    {
        fclose(pf);
        return ret;
    }

    fseek(pf, indAbuscar.pos * sizeof(tRegistroDeUsuario), SEEK_SET);
    fread(&usuarioALeer, sizeof(tRegistroDeUsuario), 1, pf);

    usuarioAct->partidasJugadas += usuarioALeer.partidasJugadas;

    fseek(pf, indAbuscar.pos * sizeof(tRegistroDeUsuario), SEEK_SET);
    fwrite(usuarioAct, sizeof(tRegistroDeUsuario), 1, pf);

    fclose(pf);
    return TODO_OK;
}
