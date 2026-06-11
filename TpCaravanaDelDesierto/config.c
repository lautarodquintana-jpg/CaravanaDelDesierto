#include "config.h"

void leerYValidar (unsigned *dest, int li, int ls)
{
    unsigned val;

    scanf ("%u", &val);

    while (li>val || ls<val)
    {
        printf ("Valor no valido, ingresar nuevamente entre %d y %d: ", li, ls);
        scanf ("%u", &val);
    }

    *dest=val;
}

int crearConfig (tConfig* conf)
{
    FILE *pf;

    pf= fopen ("config.txt", "wt");

    if (!pf)
    {
        printf ("Error al crear el archivo");
        return ERROR_ARCHIVO;
    }

    printf ("Ingresar cantidad de posiciones del tablero: ");
    leerYValidar(&conf->cantPos, MIN_POS, MAX_POS);

    printf ("\nIngresar cantidad de vidas: ");
    leerYValidar(&conf->vidas, MIN_VIDAS,conf->cantPos/2);

    printf ("\nIngresar cantidad maxima de bandidos: ");
    leerYValidar(&conf->bandidos,MIN_BANDIDOS,(conf->cantPos-2)*MAXPORC_BANDIDOS);

    printf ("\nIngresar cantidad maxima de vidas extras: ");
    leerYValidar(&conf->vidasExtra, MIN_VIDASEXT,(conf->cantPos-2)*MAXPORC_VIDASEXT);

    printf ("\nIngresar cantidad maxima de oasis: ");
    leerYValidar(&conf->oasis, MIN_OASIS, (conf->cantPos-2)*MAXPORC_OASIS);

    printf ("\nIngresar cantidad maxima de tormentas: ");
    leerYValidar(&conf->tormentas, MIN_TORMENTAS, (conf->cantPos-2)*MAXPORC_TORMENTAS);

    printf ("\nIngresar cantidad de premios: ");
    leerYValidar(&conf->premios, MIN_PREMIOS, (conf->cantPos-2)*MAXPORC_PREMIOS);

    fprintf (pf, "Posiciones:%u\n", conf->cantPos);
    fprintf (pf, "Vidas:%u\n", conf->vidas);
    fprintf (pf, "Bandidos:%u\n", conf->bandidos);
    fprintf (pf, "Vidas extras:%u\n", conf->vidasExtra);
    fprintf (pf, "Oasis:%u\n", conf->oasis);
    fprintf (pf, "Tormentas:%u\n", conf->tormentas);
    fprintf (pf, "Premios:%u\n", conf->premios);

    fclose (pf);
    return TODO_OK;
}

int leerConfig (tConfig* conf, const char* nomArch)
{
    FILE* pf= fopen (nomArch, "rt");
    char buffer[30];
    char *aux;

    if (!pf)
    {
        return ERROR_ARCHIVO;
    }

    fgets (buffer, sizeof (buffer), pf);
    aux= strchr (buffer, ':');
    sscanf(aux+1,"%d", &conf->cantPos);

    fgets (buffer, sizeof (buffer), pf);
    aux= strchr (buffer, ':');
    sscanf(aux+1,"%d", &conf->vidas);

    fgets (buffer, sizeof (buffer), pf);
    aux= strchr (buffer, ':');
    sscanf(aux+1,"%d", &conf->bandidos);

    fgets (buffer, sizeof (buffer), pf);
    aux= strchr (buffer, ':');
    sscanf(aux+1,"%d", &conf->vidasExtra);

    fgets (buffer, sizeof (buffer), pf);
    aux= strchr (buffer, ':');
    sscanf(aux+1,"%d", &conf->oasis);

    fgets (buffer, sizeof (buffer), pf);
    aux= strchr (buffer, ':');
    sscanf(aux+1,"%d", &conf->tormentas);

    fgets (buffer, sizeof (buffer), pf);
    aux= strchr (buffer, ':');
    sscanf(aux+1,"%d", &conf->premios);

    fclose (pf);
    return TODO_OK;
}
char elegirDificultad(char *nomConfig)
{
    char opcion;

    printf("\nIngrese la dificultad\n");
    printf("F=Facil, I=Intermedio, D=Dificil, E=Extremo, M=Mas informacion:");
    scanf(" %c", &opcion);
    opcion=toupper(opcion);
    while(opcion!='F' && opcion!='I' && opcion!='D' && opcion!='E')
    {
        if(opcion=='M')
        {
            mostrarInfo();
        }
        else
        {
            printf("\nOpcion no valida...\n");
        }
        printf("F=Facil, I=Intermedio, D=Dificil, E=Extremo, M=Mas informacion:");
        scanf(" %c", &opcion);
        system("cls");
        opcion=toupper(opcion);
    }
    if(nomConfig)
    {
        switch(opcion)
        {
            case 'F':strcpy(nomConfig, "configF.txt");
                    break;
            case 'I':strcpy(nomConfig, "configI.txt");
                    break;
            case 'D':strcpy(nomConfig, "configD.txt");
                    break;
            case 'E':strcpy(nomConfig, "configE.txt");
                    break;
        }
    }

    return opcion;
}
void mostrarInfo()
{
    printf("\nFactores fijos:");
    printf("\n2 Vidas extra, menos en extremo");
    printf("\n3 Oasis");
    printf("\n4 Tormentas");
    printf("\n4 Premios");
    printf("\n-------------------------------");


    printf("\nFacil:");
    printf("\n4 Vidas");
    printf("\n5 Bandidos");
    printf("\n-------------------------------");

    printf("\nIntermedio:");
    printf("\n2 Vidas");
    printf("\n6 Bandidos");
    printf("\n-------------------------------");

    printf("\nDificil:");
    printf("\n1 Vida");
    printf("\n7 Bandidos");
    printf("\n-------------------------------");

    printf("\nExtremo:");
    printf("\n1 Vida");
    printf("\n8 Bandidos");
    printf("\nSin vidas extra");
    printf("\n-------------------------------\n");
}
