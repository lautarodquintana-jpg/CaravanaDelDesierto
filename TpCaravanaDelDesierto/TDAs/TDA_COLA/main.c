#include <stdio.h>
#include <stdlib.h>

#include "TDA_Cola_Imp_Din.h"

int main()
{
    TDAcolaCir cola;
    crearColaCir(&cola);

    for(int i = 10; i < 20; i++)
    {
        encolarCir(&cola, &i, sizeof(int));
    }

    int num;
    verFrenteDeColaCir(&cola, &num, sizeof(int));
    printf("-----%2d-----\n",num);


    for(int i = 0 ; i < 5; i++)
    {
        desencolarCir(&cola, &num, sizeof(int));
        printf("-----%2d-----\n",num);

    }

    verFrenteDeColaCir(&cola, &num, sizeof(int));
    printf("\n-----%2d-----\n",num);
    if(!colaCirLlena(&cola, sizeof(int)))
        printf("tda_cola no esta llena\n");



    if(colaCirVacia(&cola))
        printf("tda_cola vacia\n");

    vaciarColaCir(&cola);

    return 0;
}
