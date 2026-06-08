#include "partidas.h"
#include "usuarios.h"


int iniciarSesionORegistrar(tArbol* pa, tRegistroDeUsuario* usuarioAct)
{
    char opcion;
    int ret;
    tIndJugadores regAct;

    printf("\nTiene una cuenta? (S o N): ");
    do
    {
        scanf(" %c", &opcion);
        getchar();

        opcion = toupper(opcion);

        if(opcion != 'S' && opcion != 'N')
        printf("\nOpcion invalida. Ingrese S o N: ");

    } while(opcion != 'S' && opcion != 'N');


    printf("\nIngrese su nombre de usuario (sin espacios y no mas de 20 caracteres): ");
    leerYValidarNombre(regAct.clave, TAM_MAX_NOM);

    if(opcion == 'S')
    {
        do
        {
            ret = buscarElemArbol(pa, &regAct, sizeof(tIndJugadores), cmpIndiceJugador);

            if(ret == ERROR_NO_ENCONTRADO)
            {
                printf("\nUsuario inexistente, vuelva a escribir el nombre: ");
                leerYValidarNombre(regAct.clave, TAM_MAX_NOM);
            }
        }while(ret == ERROR_NO_ENCONTRADO);



        printf("\n=========================================");
        printf("\n%s ha iniciado sesion correctamente.", regAct.clave);
        printf("\n=========================================");
    }
    else
    {
        do
        {
            ret = buscarElemArbol(pa, &regAct, sizeof(tIndJugadores), cmpIndiceJugador);

            if(ret != ERROR_NO_ENCONTRADO)
            {
                printf("\nEste usuario ya existe, ingrese otro por favor: ");
                leerYValidarNombre(regAct.clave, TAM_MAX_NOM);
            }
        }while(ret != ERROR_NO_ENCONTRADO);

        insNueJugadorEnArchivo(&regAct, ARCH_USUARIOS);

        insertarOrdenadoConRecursividad(pa, &regAct, sizeof(tIndJugadores), cmpIndiceJugador);

        printf("\n=========================================");
        printf("\nRegistro exitoso.");
        printf("\nUsuario: %s", regAct.clave);
        printf("\n=========================================\n");
    }
    strcpy(usuarioAct->nombreUsuario, regAct.clave);
    usuarioAct->partidasJugadas = 0;

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
            printf("\nNombre invalido. Ingrese una sola palabra sin espacios: ");

    }
    while(!valido);
}


int cmpNombreJugador(const void* a, const void* b)
{
    const tRegistroDePartida* x = (const tRegistroDePartida*)a;
    const tRegistroDePartida* y = (const tRegistroDePartida*)b;

    return strcmp(x->nombreUsuario, y->nombreUsuario);
}

void extraerNombreUsuario(void *clave, const void *dato)
{
    const tRegistroDeUsuario *reg = dato;
    char *nom = clave;
    strcpy(nom, reg->nombreUsuario);
}


void imprimirRanking(const void* elem)
{
    const tRegistroDePartida* imprimir = (const tRegistroDePartida*)elem;
    printf("|%-20s |%-10d |%-12d|\n",
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

    cargarOrdenadoListaSinDupDeArchivo(&lRanking, sizeof(tRegistroDePartida), cmpNombreJugador, actualizarRegistroPuntaje, nomArchRegistros);
    ordenarListaDesc(&lRanking,cmpPuntaje);
    printf("\n|%-20s |%-10s |%-12s|\n",
           "Jugador",
           "Puntos",
           "Movimientos");

    printf("\n===================================================\n");
    mostrarLista(&lRanking, imprimirRanking);

    vaciarLista(&lRanking);
    return TODO_OK;
}

/*

ARCHIVO PARTIDAS:

username    id_partida   puntaje    cant_movimientos
pepito      1            1          10
pepito      5            3          22
santino     2            0          9



ARCHIVO JUGADORES:

username


tenes cuenta?
    si-> ingresa tu usuario y lo busco usando el indice
    no-> ingresa tu usuario y te creo una cuenta



usuario juega y por cada partida terminada guardas en archivo partidas un registro con el usuario, puntos,
ultimo id_partida + 1, puntos, cant_movimientos. (la idea seria poder insertar ordenado por username en este
                                                  archivo para luego usar una cola que lea el archivo y vaya
                                                  acumulando puntaje mientras sea el mismo jugador, luego se
                                                  desencola y se puede usar para mostrar el ranking, pero no
                                                  se si hace falta una lista simplemente enlazada o que para esto)


*/

void extraerClaveUsuario(const void* reg, void* clave)
{
    const tRegistroDeUsuario* x = (const tRegistroDeUsuario*)reg;
    tIndJugadores* y = (tIndJugadores*)clave;

    strcpy(y->clave, x->nombreUsuario);
}
int cmpIndiceJugador(const void* a, const void* b)
{
    const tIndJugadores* x = (tIndJugadores*)a;
    const tIndJugadores* y = (tIndJugadores*)b;

    return strcmp(x->clave, y->clave);
}




int crearArchIndJugadores(tArbol* pa, unsigned tamElem, Cmp cmp, Extraer extraerClave,char *nombArchOriginal, char *nombArchInd)
{

    void* reg;
    int ret;
    tIndJugadores ind;
    ind.pos = 0;

    FILE* archOriginal = fopen(nombArchOriginal,"rb");
    if(!archOriginal)
    {

        return ERROR_ARCHIVO;
    }

    reg = malloc(tamElem);
    if(!reg)
    {
        fclose(archOriginal);
        return ERROR_MEMORIA;
    }

    while(fread(reg, tamElem, 1, archOriginal))
    {
        extraerClave(reg, &ind);
        ret =insertarOrdenadoConRecursividad(pa, &ind, sizeof(ind), cmp);
        if (ret != TODO_OK)
        {
            free(reg);
            fclose(archOriginal);
            return ERROR_MEMORIA;
        }
        ind.pos++;
    }

    crearArchivoBinarioAPartirDeArbol(pa, nombArchInd);

    free(reg);
    fclose(archOriginal);
    return TODO_OK;
}

int insNueJugadorEnArchivo(tIndJugadores* indAct, const char* archJugadores)
{
    tRegistroDeUsuario reg;
    FILE* pf = fopen(archJugadores, "r+b");
    if(!pf)
        return ERROR_ARCHIVO;

    fseek(pf, 0L, SEEK_END);

    indAct->pos = ftell(pf) / sizeof(tRegistroDeUsuario);

    strcpy(reg.nombreUsuario, indAct->clave);
    reg.partidasJugadas = 0;

    fwrite(&reg,sizeof(tRegistroDeUsuario), 1, pf);

    fclose(pf);

    return TODO_OK;
}
