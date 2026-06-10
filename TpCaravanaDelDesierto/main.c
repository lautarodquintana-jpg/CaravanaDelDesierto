#include "config.h"
#include "TDAs/listaSimplementeEnlazada.h"
#include "tablero.h"
#include "TDAs/arbol.h"
#include "juego.h"
#include "partidas.h"
#include "usuarios.h"

int ejecutarMenu();
int ejecutarJuego(const tConfig *config, const char *nomUsuario);
int main()
{
    int num, ret, bandInicioSesion=0;
    char opcion;
    tConfig miConf;
    tArbol arbol;
    tRegistroDeUsuario usuario;

    crearArbol(&arbol);

    srand(time(NULL));

    //printf ("%d\n", crearConfig(&miConf));
    leerConfig(&miConf, "config.txt");

    printf ("Configuracion de juego: \n");
    printf ("-----------------------------------------\n");
    printf ("Cantidad de casillas: %u\n", miConf.cantPos);
    printf ("Cantidad de tormentas: %u\n", miConf.tormentas);
    printf ("Cantidad de bandidos: %u\n", miConf.bandidos);
    printf ("Cantidad de oasis: %u\n", miConf.oasis);
    printf ("Cantidad de premios: %u\n", miConf.premios);
    printf ("Cantidad de vidas extras en mapa: %u\n", miConf.vidasExtra);
    printf ("Cantidad de vidas del jugador: %u\n", miConf.vidas);
    printf ("-----------------------------------------\n");

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
                bandInicioSesion=1;
            }
            else//Ya inicio sesion
            {
                printf("\nDesea seguir jugando con el mismo usuario? (S o N): ");
                scanf(" %c", &opcion);
                opcion=toupper(opcion);
                while(opcion != 'S' && opcion !='N')//Valido
                {
                    printf("\nOpcion ingresada no valida...\n");
                    printf("\nDesea seguir jugando con el mismo usuario? (S o N): ");
                    scanf(" %c", &opcion);
                    opcion=toupper(opcion);
                }
                if(opcion=='N')//Debe volver a iniciar sesion
                {
                    ret = iniciarSesionORegistrar(&arbol, &usuario);
                    if(ret != TODO_OK)
                    {
                        destruirArbol(&arbol);
                        return ret;
                    }
                bandInicioSesion=1;
                }
            }
            printf("\nQue empiece el juego!!\n");
            ret = ejecutarJuego(&miConf, usuario.nombreUsuario);
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
            printf("\nEl ranking de jugadores es el siguiente: ");
            ret = cargarYMostrarRankingEnLista(ARCH_PARTIDAS);
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
int ejecutarJuego(const tConfig *config, const char *nomUsuario)
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


    ret=aJugar(&tab, &jugador, &bandidos, config, nomUsuario);
    if(ret!=TODO_OK)
        return ret;

    eliminarTablero(&tab);
    vectorDestruir(&bandidos);

    return TODO_OK;
}
