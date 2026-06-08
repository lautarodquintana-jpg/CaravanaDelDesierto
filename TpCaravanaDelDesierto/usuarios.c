#include "usuarios.h"

int cargarArbolUsuarios(tArbol *pa)
{
    int ret;

    ret = generarArbolBalanceadoAPartirDeArchivoBinarioOrdenado(pa, ARCH_IDX_USUARIOS, sizeof(tIndiceUsuario));

    if(ret == ERROR_ARCHIVO)
    {
        ret = generarIdxUsuariosEnArbolDesdeArch(pa, ARCH_USUARIOS);

        if(ret == ERROR_ARCHIVO)
        {
            return TODO_OK; // primera vez, no existen los archivos aun pero esta bien eso
        }
    }

    return ret;
}

int generarIdxUsuariosEnArbolDesdeArch(tArbol *pa, const char *nomArch)
{
    FILE *arch = fopen(nomArch, "rb");
    tRegistroDeUsuario reg;
    tIndiceUsuario idx;
    unsigned i = 0;
    int ret;

    if(!arch)
        return ERROR_ARCHIVO;

    crearArbol(pa); //siempre se llama con arbol vacio a esta funcion
    fread(&reg, sizeof(tRegistroDeUsuario), 1, arch);
    while(!feof(arch))
    {
        strcpy(idx.nombreUsuario, reg.nombreUsuario);
        idx.idx = i;
        ret = insertarOrdenadoConRecursividad(pa, &idx, sizeof(tIndiceUsuario), cmpNombre);
        if(ret == ERROR_MEMORIA)
        {
            fclose(arch);
            return ERROR_MEMORIA;
        }
        i++;
        fread(&reg, sizeof(tRegistroDeUsuario), 1, arch);
    }
    fclose(arch);
    return TODO_OK;
}

int registrarUsuario(tArbol *pa, tRegistroDeUsuario *usuario, const char *archUsuarios)
{
    FILE *arch = fopen(archUsuarios, "r+b");
    tIndiceUsuario idx;
    int ret;

    if(!arch)
    {
        arch = fopen(archUsuarios, "w+b");
        if(!arch)
        {
            return ERROR_ARCHIVO;
        }
    }

    fseek(arch, 0, SEEK_END);
    idx.idx = ftell(arch) / sizeof(tRegistroDeUsuario);
    strcpy(idx.nombreUsuario, usuario->nombreUsuario);

    fwrite(usuario, sizeof(tRegistroDeUsuario), 1, arch);
    fclose(arch);

    ret = insertarOrdenadoConRecursividad(pa, &idx, sizeof(tIndiceUsuario), cmpNombre);
    if(ret == ERROR_MEMORIA)
        return ret;

    return crearArchivoBinarioAPartirDeArbol(pa, ARCH_IDX_USUARIOS);
}

int actualizarUsuarioAlSalir(tArbol *pa, tRegistroDeUsuario *usuarioAct, const char *archUsuarios)
{
    tIndiceUsuario idxBuscar;
    tRegistroDeUsuario regFile;
    int ret;
    FILE *pf = fopen(archUsuarios, "r+b");
    if(!pf) return ERROR_ARCHIVO;

    strcpy(idxBuscar.nombreUsuario, usuarioAct->nombreUsuario);
    ret = buscarElemArbol(pa, &idxBuscar, sizeof(tIndiceUsuario), cmpNombre);
    if(ret != TODO_OK) { fclose(pf); return ret; }

    fseek(pf, idxBuscar.idx * sizeof(tRegistroDeUsuario), SEEK_SET);
    fread(&regFile, sizeof(tRegistroDeUsuario), 1, pf);

    regFile.partidasJugadas += usuarioAct->partidasJugadas;

    fseek(pf, idxBuscar.idx * sizeof(tRegistroDeUsuario), SEEK_SET);
    fwrite(&regFile, sizeof(tRegistroDeUsuario), 1, pf);

    fclose(pf);
    return TODO_OK;
}
