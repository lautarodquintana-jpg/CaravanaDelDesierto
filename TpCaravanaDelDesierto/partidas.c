#include "partidas.h"

int iniciarSesionORegistrar(tArbol* pa, tRegistrodeUsuario* usuarioAct, FILE* pf)
{
    char opcion;
    tRegistrodeUsuario registroAnterior;
    int ret;

    printf("¿Tiene una cuenta? (S o N): ");
    scanf(" %c", &opcion);
    opcion = toupper(opcion);


    if(opcion == 'S')
    {
        do
        {
            printf("Ingrese su nombre de usuario (sin espacios): ");
            scanf("%s", usuarioAct->nombreUsuario);

            ret = buscarElemArbol(pa, usuarioAct, sizeof(tRegistrodeUsuario), cmpNombreJugador);

            if(ret == ERROR_NO_ENCONTRADO)
                printf("Usuario inexistente, vuelva a escribir el nombre.\n");

        } while(ret == ERROR_NO_ENCONTRADO);
    }
    else
        printf("Ingrese su nombre de usuario (sin espacios): ");
        scanf("%s", usuarioAct->nombreUsuario);

        fseek(pf, 0, SEEK_END);

        if(ftell(pf) == 0)
        {
            usuarioAct->idJugador = 1;
        }
        else
        {
            fseek(pf, -(long long)sizeof(tRegistrodeUsuario), SEEK_END);
            fread(&registroAnterior, sizeof(tRegistrodeUsuario), 1, pf);

            usuarioAct->idJugador = registroAnterior.idJugador + 1;
        }
    }
    return TODO_OK;
}

int cmpNombreJugador(const void* a, const void* b)
{
    const tRegistrodeUsuario* x = (const tRegistrodeUsuario*)a;
    const tRegistroIdx* y = (const tRegistroIdx*)b;

    return strcmp(x->nombreUsuario, y->nombreUsuario);
}


int cmpPuntaje(const void* e1, const void* e2)
{
    const tRegistroDePartida* x = (const tRegistroDePartida*)e1;
    const tRegistroDePartida* y = (const tRegistroDePartida*)e2;

    return x->puntaje - y->puntaje;
}
void actualizarRegistroPuntaje(void* actualizado, const void* actualizador)
{
    tRegistroDePartida* x = (tRegistroDePartida*)actualizado;
    const tRegistroDePartida* y =(const tRegistroDePartida*)actualizador;
    x->puntaje += y->puntaje;
}

int cmpIdJugador(const void* e1, const void* e2)
{
    const tRegistroDePartida* x = (const tRegistroDePartida*)e1;
    const tRegistroDePartida* y = (const tRegistroDePartida*)e2;

    return x->idJugador - y->idJugador;
}


int grabarRegistrosDePartida(tRegistroDePartida* partidaAct, const char* archRegistros)
{
    tRegistroDePartida registroAnterior;

    FILE* arch = fopen(archRegistros, "r+b");

    if(!arch)
        return ERROR_ARCHIVO;

    fseek(arch, 0, SEEK_END);

    if(ftell(arch) == 0)
    {
        partidaAct->idPartida = 1;
    }
    else
    {
        fseek(arch, - (long long)sizeof(tRegistroDePartida), SEEK_END);
        fread(&registroAnterior, sizeof(tRegistroDePartida), 1, arch);

        partidaAct->idPartida = registroAnterior.idPartida + 1;
    }

    fwrite(partidaAct, sizeof(tRegistroDePartida), 1, arch);

    fclose(arch);
    return TODO_OK;
}
int cargarYMostrarRankingEnLista(const char* nomArchJugadores, const char* nomArchRegistros)
{
    tLista lRanking;
    crearLista(&lRanking);

    cargarOrdenadoListaSinDupDeArchivo(&lRanking, sizeof(tRegistroDePartida), cmpIdJugador, actualizarRegistroPuntaje, nomArchRegistros);
    ordenarLista(&lRanking,cmpPuntaje);


    vaciarLista(&lRanking);
    return TODO_OK;
}



