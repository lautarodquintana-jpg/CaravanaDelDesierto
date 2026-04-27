#include <stdio.h>
#include <stdlib.h>

#include "TDA_Pila_Din.h"


int main()
{
    TDAPila pila;
    crearPila(&pila);

    for(int i = 0; i < 10; i++)
    {
        apilarPilaCir(&pila, &i, sizeof(int));
    }
    int num;
    verTopeDePilaCir(&pila, &num, sizeof(int));

    printf("----%2d------\n", num);

    printf("Hello world!\n");

    for(int i = 0; i < 5;i++)
    {
        desapilarPilaCir(&pila, &num, sizeof(num));
         printf("----%2d------\n", num);
    }

    verTopeDePilaCir(&pila, &num, sizeof(int));

    printf("tope nuevo----%2d------\n", num);

    vaciarPilaCir(&pila);



    for(int i = 0; i < 10; i++)
    {
        apilar(&pila, &i, sizeof(int));
    }
    verTopeDePila(&pila, &num, sizeof(int));

    printf("----%2d------\n", num);

    printf("Hello world!\n");

    for(int i = 0; i < 5;i++)
    {
        desapilar(&pila, &num, sizeof(num));
         printf("----%2d------\n", num);
    }

    verTopeDePila(&pila, &num, sizeof(int));

    printf("tope nuevo----%2d------\n", num);

    vaciarPila(&pila);

    return 0;
}
