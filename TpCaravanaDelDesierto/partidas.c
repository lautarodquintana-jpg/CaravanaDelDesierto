#include "partidas.h"
#include "usuarios.h"

int iniciarSesionORegistrar(tArbol* pa, tRegistroDeUsuario* usuarioAct)
{
    char opcion;
    int ret;
    tIndiceUsuario idxBuscar;
    int flagAlta=0;
    int op;

    printf("\nTiene una cuenta? (S o N): ");
    do
    {
        scanf(" %c", &opcion);
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
                printf("\nUsuario inexistente, desea reingresar (ingrese 1) o crear usuario (ingrese 2):");
                scanf ("%d", &op);

                if (op==1)
                {
                    printf("\nIngrese su nombre de usuario (sin espacios y no mas de 20 caracteres): ");
                    leerYValidarNombre(idxBuscar.nombreUsuario, TAM_MAX_NOM);
                }
                else
                    flagAlta=1;
            }
        }while(ret == ERROR_NO_ENCONTRADO && !flagAlta);
    }
    else
    {
        do
        {
            ret = buscarElemArbol(pa, &idxBuscar, sizeof(tIndiceUsuario), cmpNombre);

            if(ret != ERROR_NO_ENCONTRADO)
            {
                printf("\nEste usuario ya existe. Desea ingresar otro (S) o usar %s (N): ", idxBuscar.nombreUsuario);
                fflush(stdin);
                scanf(" %c", &opcion);
                opcion=toupper(opcion);
                while(opcion != 'S' && opcion != 'N')
                {
                    printf("\nOpcion ingresada no valida..\n");
                    printf("Desea reutilizar este usuario (S o N): ");
                    fflush(stdin);
                    scanf(" %c", &opcion);
                    opcion=toupper(opcion);
                }
                if(opcion=='S')
                {
                    printf("\nIngrese su nombre de usuario (sin espacios y no mas de 20 caracteres): ");
                    leerYValidarNombre(idxBuscar.nombreUsuario, TAM_MAX_NOM);
                }

            }
        }while(ret != ERROR_NO_ENCONTRADO && opcion=='S');
    }

    strcpy(usuarioAct->nombreUsuario, idxBuscar.nombreUsuario);

    if(opcion == 'N' || flagAlta)
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
        getchar();
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


int cmpNombreUsuarioYDificultad(const void* a, const void* b)
{
    int cmp;
    const tRegistroDePartida* x = (const tRegistroDePartida*)a;
    const tRegistroDePartida* y = (const tRegistroDePartida*)b;

    cmp=strcmp(x->nombreUsuario, y->nombreUsuario);
    if(cmp!=0)
        return cmp;
    return x->dificultad-y->dificultad;
}

int cmpNombre(const void *a, const void *b)
{
    return strcmp((const char*)a, (const char*)b);
}


void imprimirRanking(const void* elem, void *param)
{
    const tRegistroDePartida* imprimir = (const tRegistroDePartida*)elem;
    char *opcion=param;
    if(*opcion==imprimir->dificultad)
        printf("%-20s %-10d %-12d\n", imprimir->nombreUsuario, imprimir->puntaje, imprimir->nroJugadas);
}

int cmpPuntajeDesc(const void* e1, const void* e2)
{
    const tRegistroDePartida* x = (const tRegistroDePartida*)e1;
    const tRegistroDePartida* y = (const tRegistroDePartida*)e2;
    int dif=y->puntaje - x->puntaje;

    if (dif == 0)
        dif= x->nroJugadas - y->nroJugadas;

    return dif;
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
int cargarYMostrarRankingEnLista(const char* nomArchRegistros, char dificultad)
{
    tLista lRanking;
    crearLista(&lRanking);

    cargarOrdenadoListaSinDupDeArchivo(&lRanking, sizeof(tRegistroDePartida), cmpNombreUsuarioYDificultad, actualizarRegistroPuntaje, nomArchRegistros);
    ordenarLista(&lRanking,cmpPuntajeDesc);
    printf("\n%-20s %-10s %-12s\n",
           "Jugador",
           "Puntos",
           "Turnos");

    printf("--------------------------------------------------------\n");
    mostrarListaYParametro(&lRanking, imprimirRanking, &dificultad);

    vaciarLista(&lRanking);
    return TODO_OK;
}
