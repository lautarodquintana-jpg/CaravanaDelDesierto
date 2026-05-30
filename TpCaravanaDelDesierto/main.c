#include "config.h"
#include "TDAs/listaSimplementeEnlazada.h"
#include "tablero.h"
int ejecutarMenu();
int comenzarJuego(tListaCD *tab, const tConfig *config);
int main()
{
    int num, ret;
    tConfig miConf;
    tListaCD tab;
    //printf ("%d\n", crearConfig(&miConf));
    leerConfig(&miConf, "config.txt");

    printf ("pos: %u\n", miConf.cantPos);
    printf ("bandidos: %u\n", miConf.bandidos);
    printf ("oasis: %u\n", miConf.oasis);
    printf ("premios: %u\n", miConf.premios);

    printf("\nBienvenido a Caravana Del Desierto!\n");
    num=ejecutarMenu();
    while(num!=3)
    {
        if(num==1)
        {
            printf("\nQue empiece el juego!!\n");
            ret=comenzarJuego(&tab, &miConf);
            eliminarTablero(&tab);
            if(ret!=TODO_OK)
            {

                return ret;
            }
            printf("\nPartida finalizada..\n");
            system("pause");
        }
        if(num==2)
        {
            printf("\nEl ranking de jugadores es el siguiente: ");
            //Funcion MostrarRaking()
            system("pause");
        }
        system("cls");
        num=ejecutarMenu();
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
int comenzarJuego(tListaCD *tab, const tConfig *config)
{
    int ret;

    ret=crearTablero(tab, config);
    if(ret!=TODO_OK)
    {
        return ret;
    }

    //Cooming soon: ret=aJugar();
    return TODO_OK;
}
