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
