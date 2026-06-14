#include "config.h"
#include "TDAs/listaSimplementeEnlazada.h"
#include "tablero.h"
#include "TDAs/arbol.h"
#include "juego.h"
#include "partidas.h"
#include "usuarios.h"

int ejecutarMenu();
int ejecutarJuego(const tConfig *config, const char *nomUsuario, int dificultad);
char leerYValidarChar(char paramA, char paramB);

int main()
{
    int num, ret, bandInicioSesion=0;
    char opcion, dificultad='N', nomConfig[13];
    tConfig miConf;
    tArbol arbol;
    tRegistroDeUsuario usuario;

    crearArbol(&arbol);

    srand(time(NULL));

    ret=crearDistintosConfigs();
    if(ret!=TODO_OK)
        return ret;


    ret = cargarArbolUsuarios(&arbol);
    if(ret != TODO_OK)
    {
        destruirArbol(&arbol);
        return ret;
    }

    printf("\nBienvenido a Caravana Del Desierto!\n");

    num = ejecutarMenu();

    while(num != 3)
    {
        if(num == 1)
        {
            if(bandInicioSesion==0)//Si no inicio sesion, debe hacerlo
            {
                ret = iniciarSesionORegistrar(&arbol, &usuario);
                if(ret != TODO_OK)
                {
                    destruirArbol(&arbol);
                    return ret;
                }
                dificultad=elegirDificultad(nomConfig);
                leerConfig(&miConf, nomConfig);
                bandInicioSesion=1;
            }
            else//Ya inicio sesion
            {
                printf("\nDesea seguir jugando con el mismo usuario: %s?", usuario.nombreUsuario);
                opcion=leerYValidarChar('S','N');
                if(opcion=='N')//Debe volver a iniciar sesion
                {
                    ret = iniciarSesionORegistrar(&arbol, &usuario);
                    if(ret != TODO_OK)
                    {
                        destruirArbol(&arbol);
                        return ret;
                    }
                }
                printf("\nDesea seguir jugando con la misma dificultad? %c", dificultad);
                opcion=leerYValidarChar('S','N');
                if(opcion=='N')
                {
                    dificultad=elegirDificultad(nomConfig);
                    leerConfig(&miConf, nomConfig);
                }
            }
            printf("\nQue empiece el juego!!\n");
            ret = ejecutarJuego(&miConf, usuario.nombreUsuario, dificultad);
            if(ret != TODO_OK)
            {
                destruirArbol(&arbol);
                return ret;
            }

            usuario.partidasJugadas++;

            actualizarUsuarioAlSalir(&arbol, &usuario, ARCH_USUARIOS);
            printf("\nPartida finalizada..\n");
            system("pause");
        }
        if(num == 2)
        {
            if(bandInicioSesion==1)//Ya hay dificultad ingresada
            {
                printf("\nDesea ver el ranking para la dificultad ");
                switch(dificultad)
                {
                    case 'F':printf("%s", "facil?");
                            break;
                    case 'I':printf("%s", "intermedia?");
                            break;
                    case 'D':printf("%s", "dificil?");
                            break;
                    case 'E':printf("%s", "extrema?");
                            break;
                }
                opcion=leerYValidarChar('S', 'N');
                if(opcion=='N')
                    dificultad=elegirDificultad(NULL);
            }
            else
                dificultad=elegirDificultad(NULL);
            printf("\nEl ranking de jugadores es el siguiente: ");
            ret = cargarYMostrarRankingEnLista(ARCH_PARTIDAS, dificultad);
            if(ret != TODO_OK)
            {
                destruirArbol(&arbol);
                return ret;
            }
            system("pause");
        }
        system("cls");
        num = ejecutarMenu();
    }

    destruirArbol(&arbol);

    printf("\nGracias por jugar Caravana del Desierto. Hasta pronto!\n");
    system("pause");

    return 0;
}
int ejecutarMenu()
{
    int num;

    printf("\nQue desea hacer?\n"
           "1 Para empezar una nueva partida\n"
           "2 Para ver el ranking\n"
           "3 Para salir");
    printf("\nIngrese la opcion: ");
    scanf("%d", &num);
    while(num<1 || num>3)
    {
        printf("\nOpcion ingresada invalida, le recordamos: \n");
        printf("1 Para empezar una nueva partida\n"
               "2 Para ver el ranking\n"
               "3 Para salir");
        printf("\nIngrese la opcion: ");
        scanf("%d", &num);
    }
    return num;
}
int ejecutarJuego(const tConfig *config, const char *nomUsuario, int dificultad)
{
    int ret;

    tListaCD tab;
    tVector bandidos;
    tJugador jugador;


    ret = crearTablero(&tab, config);
    if(ret != TODO_OK)
    {
        return ret;
    }

    ret = vectorCrear(&bandidos, sizeof(tBandido));
    if(ret != TODO_OK)
    {
        return ret;
    }

    ret = cargarBandidos(&bandidos, config->bandidos, config->cantPos);
    if(ret != TODO_OK)
    {
        return ret;
    }

    ret = crearCaravanaTxt(&tab, &bandidos);
    if(ret != TODO_OK)
    {
        return ret;
    }


    ret=aJugar(&tab, &jugador, &bandidos, config, nomUsuario, dificultad);
    if(ret!=TODO_OK)
        return ret;

    eliminarTablero(&tab);
    vectorDestruir(&bandidos);

    return TODO_OK;
}
char leerYValidarChar(char paramA, char paramB)
{
    char opcion;
    printf("(%c o %c):", paramA, paramB);
    scanf(" %c", &opcion);
    opcion=toupper(opcion);
    while(opcion != paramA && opcion != paramB)
    {
        printf("\nSolo puede elegir %c o %c. Ingrese nuevamente: ", paramA, paramB);
        scanf(" %c", &opcion);
        opcion=toupper(opcion);
    }
    return opcion;
}
