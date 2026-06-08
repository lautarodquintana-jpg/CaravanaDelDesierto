#include "partidas.h"
#include "usuarios.h"

int iniciarSesionORegistrar(tArbol* pa, tRegistroDeUsuario* usuarioAct)
{
    char opcion;
    int ret;
    tIndiceUsuario idxBuscar;

    printf("\nTiene una cuenta? (S o N): ");
    do
    {
        scanf(" %c", &opcion);
        while(getchar() != '\n');
        opcion = toupper(opcion);

        if(opcion != 'S' && opcion != 'N')
        printf("\nOpcion invalida. Ingrese S o N: ");

    }while(opcion != 'S' && opcion != 'N');


    printf("\nIngrese su nombre de usuario (sin espacios y no mas de 20 caracteres): ");
    leerYValidarNombre(idxBuscar.nombreUsuario, TAM_MAX_NOM);

    usuarioAct->partidasJugadas = 0; //solo para esta sesion

    if(opcion == 'S')
    {
        do
        {
            ret = buscarElemArbol(pa, &idxBuscar, sizeof(tIndiceUsuario), cmpNombre);

            if(ret == ERROR_NO_ENCONTRADO)
            {
                printf("\nUsuario inexistente, vuelva a escribir el nombre.");
                leerYValidarNombre(idxBuscar.nombreUsuario, TAM_MAX_NOM);
            }
        }while(ret == ERROR_NO_ENCONTRADO);
    }
    else
    {
        do
        {
            ret = buscarElemArbol(pa, &idxBuscar, sizeof(tIndiceUsuario), cmpNombre);

            if(ret != ERROR_NO_ENCONTRADO)
            {
                printf("\nEste usuario ya existe, ingrese otro por favor.");
                leerYValidarNombre(idxBuscar.nombreUsuario, TAM_MAX_NOM);
            }
        }while(ret != ERROR_NO_ENCONTRADO);
    }

    strcpy(usuarioAct->nombreUsuario, idxBuscar.nombreUsuario);

    if(opcion == 'N')
    {
        ret = registrarUsuario(pa, usuarioAct, ARCH_USUARIOS);
        if(ret != TODO_OK)
        {
            return ret;
        }
    }


    return TODO_OK;
}

void leerYValidarNombre(char *nom, int tam)
{
    int valido;
    do
    {
        valido = 1;
        fgets(nom, tam, stdin);
        char *pos = strchr(nom, '\n');
        if(pos)
            *pos = '\0';

        if(nom[0] == '\0')
        {
            valido = 0;
        }
        else
        {
            for(int i = 0; nom[i] != '\0' && valido; i++)
            {
                if(isspace(nom[i]))
                    valido = 0;
            }
        }

        if(!valido)
            printf("Nombre invalido. Ingrese una sola palabra sin espacios.\n");

    }
    while(!valido);
}


int cmpNombreUsuario(const void* a, const void* b)
{
    const tRegistroDePartida* x = (const tRegistroDePartida*)a;
    const tRegistroDePartida* y = (const tRegistroDePartida*)b;

    return strcmp(x->nombreUsuario, y->nombreUsuario);
}

int cmpNombre(const void *a, const void *b)
{
    return strcmp((const char*)a, (const char*)b);
}


void imprimirRanking(const void* elem)
{
    const tRegistroDePartida* imprimir = (const tRegistroDePartida*)elem;
    printf("%-20s %-10d %-12d\n", imprimir->nombreUsuario, imprimir->puntaje, imprimir->nroJugadas);
}

int cmpPuntajeAsc(const void* e1, const void* e2)
{
    const tRegistroDePartida* x = (const tRegistroDePartida*)e1;
    const tRegistroDePartida* y = (const tRegistroDePartida*)e2;

    return x->puntaje - y->puntaje;
}
int cmpPuntajeDesc(const void* e1, const void* e2)
{
    const tRegistroDePartida* x = (const tRegistroDePartida*)e1;
    const tRegistroDePartida* y = (const tRegistroDePartida*)e2;

    return y->puntaje - x->puntaje;
}
void actualizarRegistroPuntaje(void* actualizado, const void* actualizador)
{
    tRegistroDePartida* x = (tRegistroDePartida*)actualizado;
    const tRegistroDePartida* y =(const tRegistroDePartida*)actualizador;
    x->puntaje += y->puntaje;
    x->nroJugadas += y->nroJugadas;
}


int grabarRegistroDePartida(tRegistroDePartida* partidaAct, const char* archRegistros)
{
    tRegistroDePartida registroAnterior;

    FILE* arch = fopen(archRegistros, "r+b");
    if(!arch)
    {
        arch = fopen(archRegistros, "w+b");
        if(!arch)
        {
            return ERROR_ARCHIVO;
        }
    }

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
int cargarYMostrarRankingEnLista(const char* nomArchRegistros)
{
    tLista lRanking;
    crearLista(&lRanking);

    cargarOrdenadoListaSinDupDeArchivo(&lRanking, sizeof(tRegistroDePartida), cmpNombreUsuario, actualizarRegistroPuntaje, nomArchRegistros);
    ordenarLista(&lRanking,cmpPuntajeDesc);
    printf("\n%-20s %-10s %-12s\n",
           "Jugador",
           "Puntos",
           "Movimientos");

    printf("--------------------------------------------------------\n");
    mostrarLista(&lRanking, imprimirRanking);

    vaciarLista(&lRanking);
    return TODO_OK;
}
