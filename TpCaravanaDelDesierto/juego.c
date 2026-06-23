#include "juego.h"
#include "tipos.h"
#include "partidas.h"
#include "TDAs/ListaCircularDoblementeEnlazada.h"
#include "TDAs/vector.h"

void ponerCatEnVacio (void *actualizado, const void *actualizador)
{
    tCasillero *casActualizar=actualizado;

    casActualizar->categoria=VACIO;
}

void moverJugador(tListaCD *tab, tVector *bandidos, tJugador *jugador, unsigned desplazamiento, char sentido, int tam_tablero)
{
    int paso;
    int dir = (sentido == 'B') ? -1 : 1;
    int nuevaPos;

    for (paso = 0; paso < desplazamiento; paso++)
    {
        nuevaPos = jugador->posicion + dir;

        // rebote en el extremo superior
        if (nuevaPos > tam_tablero)
        {
            dir = -1;
            nuevaPos = tam_tablero - 1;
        }

        jugador->posicion = nuevaPos;
        system("cls");
        mostrarTablero(tab, bandidos, jugador->posicion, tam_tablero);
        system("timeout /t 1 /nobreak > nul");  // 1 segundo entre pasos, sin mostrar mensaje
    }
}

void calcularDespBandido(tMovimiento *mov, int posJ, int posB, int tam_tablero)
{
    int distAvance   = (posJ - posB + tam_tablero) % tam_tablero;
    int distRetroceso = (posB - posJ + tam_tablero) % tam_tablero;

    if(distAvance < distRetroceso)
    {
        mov->desplazamiento = (posB % tam_tablero) + 1;
        mov->sentido = 'F';
    }
    else
    {
        if(distAvance > distRetroceso)
        {
            mov->desplazamiento = ((posB - 2 + tam_tablero) % tam_tablero) + 1;
            mov->sentido = 'B';
        }
        else
        {
            mov->desplazamiento=posB;
        }
    }
}

void actualizarBandido (void *actualizado, const void *actualizador)
{
    memcpy(actualizado, actualizador, sizeof (tBandido));
}

int aJugar(tListaCD *tab, tJugador *jugador, tVector *bandidos, const tConfig *config, const char *nomUsuario, char dificultad)
{
    int dado, ret, desplazamientoEnCasillas, i;
    int desp;
    unsigned catAnt=VACIO, catAct=INICIO;
    char sentido;//del movimiento
    tMovimiento mov;//mov es el de bandidos y jugadores, regMov es el que muestro al final
    tBandido bandidoAux;

    tRegistroDePartida partida;

    tCola colaMovimientos, colaRegMovimientos;// Esto es para el registro de los movimientos

    partida.nroJugadas = 0;
    strcpy(partida.nombreUsuario, nomUsuario);
    partida.dificultad=dificultad;

    crearCola(&colaMovimientos);
    crearCola(&colaRegMovimientos);

    jugador->vidas=config->vidas;
    jugador->posicion=1;
    jugador->puntosAcum=0;
    system("cls");

    printf("Turno del jugador\n");
    mostrarTablero(tab, bandidos, jugador->posicion, config->cantPos);
    while(jugador->vidas>0 && catAct!=SALIDA)
    {
        partida.nroJugadas++;

        if(catAnt!=TORMENTA)//Si no esta afectado por tormenta, le permito moverse
        {
            //dado=tirarDado();
            scanf("%d", &dado);//Utilizado para casos de prueba
            printf("\nTiras el dado y sale el valor: %d", dado);
            if(jugador->posicion-dado <= 0)
            {
                printf("\nSolo puedes dirigirte hacia adelante\n");
                system("pause");//Le va a pedir una tecla cualquiera para continuar
                sentido='F';
            }
            else
            {
                sentido=validarSentido();//Devuelve 'F' de forward o 'B' de backward
            }

            //Esto lo voy desencolar al final, no durante la partida
            desplazamientoEnCasillas = ( sentido == 'B' ? -dado : dado );
            ret=ponerEnCola(&colaRegMovimientos, &desplazamientoEnCasillas, sizeof(int));
            if(ret!=TODO_OK)
            {
                vaciarCola(&colaRegMovimientos);
                vaciarCola(&colaMovimientos);
                return ret;
            }

            //Cargo el tMovimiento
            mov.desplazamiento=dado;
            mov.sentido=sentido;
            mov.tipo='J';

            ret=ponerEnCola(&colaMovimientos, &mov, sizeof(tMovimiento));
            if(ret!=TODO_OK)
            {
                vaciarCola(&colaRegMovimientos);
                vaciarCola(&colaMovimientos);
                return ret;
            }
        }
        else
        {
            printf("\nHas perdido el turno debido a que estas bajo el efecto de una tormenta\n");
            system("timeout /t 2 /nobreak > nul");

            dado = 0;
            mov.desplazamiento=0;
            mov.sentido='F';
            mov.tipo='J';
            ret=ponerEnCola(&colaMovimientos, &mov, sizeof(tMovimiento));
            if(ret!=TODO_OK)
            {
                vaciarCola(&colaMovimientos);
                vaciarCola(&colaRegMovimientos);
                return ret;
            }

            catAnt=VACIO;
            catAct=VACIO;
        }

        mov.tipo='B';
        i=0;
        while(i < vectorCantElementos(bandidos))
        {
            vectorObtenerElem(bandidos, i, &bandidoAux);
            calcularDespBandido(&mov, jugador->posicion, bandidoAux.posicion, config->cantPos);
            ret=ponerEnCola(&colaMovimientos, &mov, sizeof(tMovimiento));
            if(ret!=TODO_OK)
            {
                vaciarCola(&colaRegMovimientos);
                vaciarCola(&colaMovimientos);
                return ret;
            }
            i++;
        }

        //Desencolamos movimiento del jugador
        ret=sacarDeCola(&colaMovimientos, &mov, sizeof(tMovimiento));
        if(ret!=TODO_OK)
        {
            vaciarCola(&colaRegMovimientos);
            vaciarCola(&colaMovimientos);
            return ret;
        }

        moverJugador(tab, bandidos, jugador, mov.desplazamiento, mov.sentido, config->cantPos);

        if(mov.desplazamiento!=0)
        {
            ret=aplicarEfectosDelCasillero(tab, jugador, &catAct);
            if(ret!=TODO_OK)
            {
                vaciarCola(&colaRegMovimientos);
                vaciarCola(&colaMovimientos);
                return ret;
            }
        }

        ret=validarMuerte(jugador, bandidos, catAnt, catAct);
        if(ret==POS_INVALIDA)
        {
            vaciarCola(&colaRegMovimientos);
            vaciarCola(&colaMovimientos);
            return ret;
        }

        if(MUERTE==ret)//Valido si el jugador cae sobre un bandido
        {
            printf("\nTe ha interceptado un bandido y perdiste una vida, ahora te quedan: %d\n", jugador->vidas);
            system("timeout /t 2 /nobreak > nul");
            system ("cls");
            mostrarTablero(tab, bandidos, jugador->posicion, config->cantPos);
            catAct=INICIO;
            catAnt=VACIO;
        }
        else
        {
            i=0;
            while(ret!=MUERTE && !colaVacia(&colaMovimientos) && i < vectorCantElementos(bandidos))
            {
                sacarDeCola(&colaMovimientos, &mov, sizeof(tMovimiento));
                vectorObtenerElem(bandidos, i, &bandidoAux);
                bandidoAux.posicion=mov.desplazamiento;
                vectorActualizarNPos(bandidos, i, &bandidoAux, actualizarBandido);
                system("cls");
                mostrarTablero(tab, bandidos, jugador->posicion, config->cantPos);
                printf("\nMovimiento de bandidos...\n");
                system("timeout /t 2 /nobreak > nul");
                ret=validarMuerte(jugador, bandidos, catAnt, catAct);
                i++;
            }
            catAnt=catAct;
        }

        if(MUERTE == ret)////Valido si un bandido (al desplazarse) cayo sobre un jugador
        {
            printf("\nTe ha interceptado un bandido y perdiste una vida, ahora te quedan: %d\n", jugador->vidas);
            system("timeout /t 2 /nobreak > nul");
            system ("cls");
            mostrarTablero(tab, bandidos, jugador->posicion, config->cantPos);
            catAct=INICIO;
            catAnt=VACIO;
        }
        vaciarCola(&colaMovimientos);

    }

    if (catAct == SALIDA)
    {
        printf ("\nFelicidades has ganado, obtendras 3 puntos extra");
        jugador->puntosAcum+=3;
    }


    partida.puntaje = jugador->puntosAcum;

    ret = grabarRegistroDePartida(&partida, ARCH_PARTIDAS);
    if(ret != TODO_OK)
    {
        vaciarCola(&colaRegMovimientos);
        vaciarCola(&colaMovimientos);
    }


    printf("\n=== Registro de movimientos ===\n");
    printf("\nF= Movimiento hacia adelante");
    printf("\nB= Movimiento hacia atras\n");
    while (sacarDeCola(&colaRegMovimientos, &desp, sizeof(int)) == TODO_OK)
    {
        if (desp > 0)
            printf("F%d\n", desp);
        else
            printf("B%d\n", -desp);
    }

    vaciarCola(&colaRegMovimientos);
    vaciarCola(&colaMovimientos);

    return TODO_OK;
}
char validarSentido()
{
    char sentido;
    printf("\nIngrese 'F' para dirigirse hacia ADELANTE, 'B' para dirigirse hacia ATRAS: ");
    fflush(stdin);
    scanf(" %c", &sentido);
    sentido=toupper(sentido);
    while(sentido!='F' && sentido !='B')
    {
        printf("\nOpcion ingresada invalida...");
        printf("\nIngrese 'F' para dirigirse hacia ADELANTE, 'B' para dirigirse hacia ATRAS: ");
        fflush(stdin);
        scanf(" %c", &sentido);
        sentido=toupper(sentido);
    }
    return sentido;
}
int aplicarEfectosDelCasillero(tListaCD *tab, tJugador* jugador, unsigned *catAct)
{
    tCasillero casAct;
    int ret;

    ret=verNElemCD(tab, jugador->posicion-1, &casAct, sizeof(tCasillero));
    if(ret!=TODO_OK)
        return ret;
    switch(casAct.categoria)
    {
    case PREMIO:
        printf("\nHas ganado un premio!\n");
        jugador->puntosAcum++;
        printf("\nAhora posees: %d punto%c", jugador->puntosAcum, jugador->puntosAcum>1? 's': '\0');
        *catAct = PREMIO;
        ret=actualizarNPosCD(tab, NULL, casAct.numero - 1, ponerCatEnVacio);
        break;
    case VIDA_EXTRA:
        printf("\nHas obtenido una vida extra!\n");
        jugador->vidas++;
        printf("\nAhora posees: %d vida%c", jugador->vidas, jugador->vidas>1? 's': '\0');
        *catAct = VIDA_EXTRA;
        ret=actualizarNPosCD(tab, NULL, casAct.numero - 1, ponerCatEnVacio);
        break;
    case OASIS:
        printf("\nHas caido en un oasis! Tienes proteccion por este turno y el siguiente ante 1 solo bandido");
        *catAct = OASIS;
        break;
    case TORMENTA:
        if(*catAct == OASIS)
        {
            printf("\nHas caido en una tormenta, pero tienes proteccion de oasis del turno anterior!");
            *catAct = VACIO;
        }
        else
        {
            printf("\nMala suerte. Has caido en una tormenta");
            *catAct = TORMENTA;
        }
        break;
    case SALIDA:
        printf("\nHas llegado a la salida! Ganaras si no te intercepta un bandido...");
        *catAct = SALIDA;
        break;
    }
    system("timeout /t 3 /nobreak > nul");
    return ret;
}
int validarMuerte(tJugador *jugador, tVector *bandidos, unsigned catAnt, unsigned catAct)
{
    int cantBandidos = 0;
    int posBandidoVec;
    int ret;
    tBandido band;

    for(int i = 0; i < vectorCantElementos(bandidos); i++)
    {
        vectorObtenerElem(bandidos, i, &band);

        if(band.posicion == jugador->posicion)
        {
            cantBandidos++;
            posBandidoVec=i;
        }
    }//si el anterior es oasis y hay mas de 2 bandidos o (no importa la anterior= pero hay mas de un bandido. Y
    if(((catAnt==OASIS && cantBandidos>=2) || (catAnt!=OASIS && cantBandidos>=1)) && ((catAct==OASIS && cantBandidos>=2) || (catAct!=OASIS && cantBandidos>=1)))//Si hay bandidos en la posicion
    {
        jugador->vidas--;
        jugador->posicion = 1;
        ret=vectorEliminarDePos(bandidos, posBandidoVec);
        if(ret!=TODO_OK)
            return ret;

        return MUERTE;
    }

    return NO_MUERTE;
}
