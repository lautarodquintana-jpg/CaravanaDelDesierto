#include "partidas.h"

int iniciarSesionORegistrar(tArbol* pa, tRegistrodeUsuario* usuarioAct, FILE* pf)
{
    char opcion;
    int ret;

    printf("¿Tiene una cuenta? (S o N): ");
    scanf(" %c", &opcion);
    opcion = toupper(opcion);


    if(opcion == 'S')
    {
        do
        {
            printf("Ingrese su nombre de usuario (sin espacios y no mas de 60 caracteres): ");
            scanf("%s", usuarioAct->nombreUsuario);

            ret = buscarElemArbol(pa, usuarioAct, sizeof(tRegistrodeUsuario), cmpNombreJugador);

            if(ret == ERROR_NO_ENCONTRADO)
                printf("Usuario inexistente, vuelva a escribir el nombre.\n");

        } while(ret == ERROR_NO_ENCONTRADO);
    }
    else
    {
        printf("Ingrese su nombre de usuario (sin espacios y no mas de 60 caracteres): ");
        scanf("%s", usuarioAct->nombreUsuario);
    }
    return TODO_OK;
}

int cmpNombreJugadorConIdx(const void* a, const void* b)
{
    const tRegistrodeUsuario* x = (const tRegistrodeUsuario*)a;
    const tRegistroIdx* y = (const tRegistroIdx*)b;

    return strcmp(x->nombreUsuario, y->nombreUsuario);
}
int cmpNombreJugador(const void* a, const void* b)
{
    const tRegistroDePartida* x = (const tRegistroDePartida*)a;
    const tRegistroDePartida* y = (const tRegistroDePartida*)b;

    return strcmp(x->nombreUsuario, y->nombreUsuario);
}

void imprimirRanking(const void* elem)
{
    const tRegistroDePartida* imprimir = (const tRegistroDePartida*)elem;
    printf("%-10d %-20s %-10d %-12d\n",
           imprimir->idPartida,
           imprimir->nombreUsuario,
           imprimir->puntaje,
           imprimir->nroJugadas);
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

    cargarOrdenadoListaSinDupDeArchivo(&lRanking, sizeof(tRegistroDePartida), cmpNombreJugador, actualizarRegistroPuntaje, nomArchRegistros);
    ordenarLista(&lRanking,cmpPuntaje);
    printf("\n%-10s %-20s %-10s %-12s\n",
           "Partida",
           "Jugador",
           "Puntos",
           "Movimientos");

    printf("--------------------------------------------------------\n");
    mostrarLista(&lRanking, imprimirRanking);

    vaciarLista(&lRanking);
    return TODO_OK;
}



