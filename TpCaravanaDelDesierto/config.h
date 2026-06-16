#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

#include "tipos.h"

#define ERROR_ARCHIVO -2
#define FUERA_RANGO 33
#define TODO_OK 0

#define MIN_POS 10
#define MAX_POS 200
#define MIN_VIDAS 1
#define MIN_BANDIDOS 0
#define MAXPORC_BANDIDOS 0.2
#define MIN_VIDASEXT 0
#define MAXPORC_VIDASEXT 0.2
#define MIN_OASIS 0
#define MAXPORC_OASIS 0.2
#define MIN_TORMENTAS 0
#define MAXPORC_TORMENTAS 0.2
#define MIN_PREMIOS 0
#define MAXPORC_PREMIOS 0.2

typedef struct
{
    unsigned cantPos;
    unsigned vidas;
    unsigned bandidos;
    unsigned vidasExtra;
    unsigned oasis;
    unsigned tormentas;
    unsigned premios;
} tConfig;

int crearDistintosConfigs();
int crearConfig (const tConfig* conf, const char *nomArch);
int leerConfig (tConfig* conf, const char* nomArch);
char elegirDificultad(char *nomConfig);
void mostrarInfo();
#endif // CONFIG_H_INCLUDED
