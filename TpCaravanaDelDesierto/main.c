#include "config.h"
int EjecutarMenu();
int main()
{
    int num;
    tConfig miConf;

    //printf ("%d\n", crearConfig(&miConf));
    leerConfig(&miConf, "config.txt");

    printf ("pos: %u\n", miConf.cantPos);
    printf ("bandidos: %u\n", miConf.bandidos);
    printf ("oasis: %u\n", miConf.oasis);
    printf ("premios: %u\n", miConf.premios);

    printf("\nBienvenido a Caravana Del Desierto!\n");
    num=EjecutarMenu();
    while(num!=3)
    {
        if(num==1)
        {
            printf("\nQue empiece el juego!!\n");
            //Funcion EmpezarJuego()
            printf("\nPartida finalizada..          \n");
            system("pause");
        }
        if(num==2)
        {
            printf("\nEl ranking de jugadores es el siguiente: ");
            //Funcion MostrarRaking()
            system("pause");
        }
        system("cls");
        num=EjecutarMenu();
    }
    printf("\nEl ranking ha quedado de la siguiente manera: \n");
    //Funcion MostrarRanking
    printf("\nGracias por jugar Caravana del Desierto. Hasta pronto!\n");
    system("pause");

    return 0;
}
int EjecutarMenu()
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
