#include "config.h"
#include "TDAs/listaSimplementeEnlazada.h"
#include "tablero.h"
#include "TDAs/arbol.h"
#include "juego.h"
int ejecutarMenu();
int ejecutarJuego(const tConfig *config);
int main()
{
    int num, ret;
    tConfig miConf;
    tArbol arbol;
    crearArbol(&arbol);

    srand(time(NULL));

    //printf ("%d\n", crearConfig(&miConf));
    leerConfig(&miConf, "config.txt");

    printf ("pos: %u\n", miConf.cantPos);
    printf ("bandidos: %u\n", miConf.bandidos);
    printf ("oasis: %u\n", miConf.oasis);
    printf ("premios: %u\n", miConf.premios);

    printf("\nBienvenido a Caravana Del Desierto!\n");

    num = ejecutarMenu();

    while(num != 3)
    {
        if(num == 1)
        {
            printf("\nQue empiece el juego!!\n");
            ret = ejecutarJuego(&miConf);
            if(ret != TODO_OK)
            {

                return ret;
            }
            printf("\nPartida finalizada..\n");
            system("pause");
        }
        if(num == 2)
        {
            printf("\nEl ranking de jugadores es el siguiente: ");
            //Funcion MostrarRaking()
            system("pause");
        }
        system("cls");
        num = ejecutarMenu();
    }
    printf("\nEl ranking ha quedado de la siguiente manera: \n");
    //Funcion MostrarRanking
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
int ejecutarJuego(const tConfig *config)
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


    ret=aJugar(&tab, &jugador, &bandidos, config);
    if(ret!=TODO_OK)
        return ret;

    eliminarTablero(&tab);
    vectorDestruir(&bandidos);

    return TODO_OK;
}
