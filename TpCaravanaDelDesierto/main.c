#include "config.h"

int main()
{
    tConfig miConf;

    printf ("%d\n", crearConfig(&miConf));
    leerConfig(&miConf, "config.txt");

    printf ("pos: %u\n", miConf.cantPos);
    printf ("bandidos: %u\n", miConf.bandidos);
    printf ("oasis: %u\n", miConf.oasis);
    printf ("premios: %u\n", miConf.premios);

    return 0;
}
