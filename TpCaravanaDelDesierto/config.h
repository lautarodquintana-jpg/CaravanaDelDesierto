#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

#include <stdio.h>

#define TAM_LINEA 61
#define SOLICITADO 1
#define NO_SOLICITADO 0
#define ERR_ARCHIVO 1
#define TODO_OK 0

typedef struct
{
    const char* clave;
    int solicitado;
    const char* caracter;
    unsigned int cantCasillas; 
}MapaDeCasillas;
int procesarArchivoConfigTxt(const char* nomArchTxt);
void escribirEnArchivotxt(void* );
int procesarLinea()


#endif // CONFIG_H_INCLUDED
