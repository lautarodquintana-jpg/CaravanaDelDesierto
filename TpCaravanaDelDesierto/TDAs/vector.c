
#include "vector.h"

bool redimensionarVector(tVector* v, float factor); //pongo header aca porque no es una primitiva

bool redimensionarVector(tVector* v, float factor)
{
    size_t nuevaCap = v->cap * factor;

    if(nuevaCap < CAP_INI)
    {
        return true; //para no hacerlo tan chico al vector
    }

    void* nuevoVec = realloc(v->vec, nuevaCap * v->tamElem);

    if(nuevoVec == NULL)
    {
        return false;
    }

    // %zu -> size unsigned, %lld -> long long decimal. Ambas sirven para size_t, pero %zu mejor
    printf("\nRedimension de %zu a %zu exitosa.\n", v->cap, nuevaCap);

    v->vec = nuevoVec;
    v->cap = nuevaCap;

    return true;
}

//////////////////  FUNCIONES PRIMITIVAS  /////////////////////////////////////////////////////////
int vectorCrear(tVector* v, size_t tamE)
{
    v->ce = 0;

    if(tamE == 0)
    {
        v->vec = NULL;
        v->cap = 0;
        v->tamElem = 0;
        return ERR_TAM_ELEM;
    }

    v->vec = malloc(CAP_INI * tamE);
    if(v->vec == NULL)
    {
        v->cap = 0;
        v->tamElem = 0;
        return SIN_MEM;
    }

    v->tamElem = tamE;
    v->cap = CAP_INI;

    return TODO_OK;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
void vectorRecorrer(tVector* v, Accion acc)
{
    void* ult = v->vec + (v->ce - 1) * v->tamElem;

    for(void* i = v->vec; i <= ult; i += v->tamElem)
    {
        acc(i);
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////
int vectorInsertarAlFinal(tVector* v, const void* elem)
{
    if(v->ce == v->cap)
    {
        if(!redimensionarVector(v, FACTOR_INCR))
        {
            return SIN_MEM;
        }
    }

    void* dest = v->vec + v->ce * v->tamElem;
    memcpy(dest, elem, v->tamElem);
    v->ce++;

    return TODO_OK;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
int vectorOrdInsertar(tVector* v, const void* elem, Cmp cmp)
{
    if(v->ce == v->cap)
    {
        if(!redimensionarVector(v,FACTOR_INCR))
        {
            return SIN_MEM;
        }
    }

    void* ult = v->vec + (v->ce - 1)* v->tamElem;
    void* i = v->vec;

    while(i <= ult && cmp(elem,i) > 0)
    {
        i += v->tamElem;
    }

    if(i <= ult && cmp(elem,i) == 0)
    {
        printf("\nElemento duplicado. Finalizando...\n");
        return DUPLICADO;
    }

//    for(void* j = ult; j >= i; j -= v->tamElem)
//    {
//        memcpy(j + v->tamElem, j, v->tamElem);
//    } // o hago el for este o el memmove de abajo, el q me acuerde, pero el de abajo mas prime

    memmove(i + v->tamElem, i, ult - i + v->tamElem);

    memcpy(i, elem, v->tamElem);

    v->ce++;

    return TODO_OK;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
bool vectorEliminarDePos(tVector* v, int pos)
{
    if(pos < 0 || pos >= v->ce)
    {
        return false;
    }

    void* ult = v->vec + (v->ce - 1) * v->tamElem;

    for(void* i = v->vec + pos * v->tamElem; i < ult; i += v->tamElem)
    {
        memcpy(i, i + v->tamElem, v->tamElem);
    }

    v->ce--;

    if(((float)v->ce / v->cap) <= FACTOR_OCUP)
    {
        redimensionarVector(v, FACTOR_DECR);
    }

    return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
bool vectorEliminarElem(tVector* v, const void* elem, Cmp cmp)
{
    void* ult = v->vec + (v->ce - 1) * v->tamElem;
    void* i = v->vec;
    int pos = 0;
    int eliminado = 0;

    while(i <= ult && !eliminado)
    {
        if(cmp(elem, i) == 0)
        {
            vectorEliminarDePos(v, pos);
            eliminado = 1;
        }
        i += v->tamElem;
        pos++;
    }
    return eliminado;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
int vectorOrdBuscar(const tVector* v, void* elem, Cmp cmp)
{
    void* li = v->vec;
    void* ls = v->vec + (v->ce - 1) * v->tamElem;
    void* m;

    int pos = -1; // posicion del elemento encontrado o no
    int comp; // almacena el resultado de comparaciones
    bool encontrado = false;

    while(!encontrado && li <= ls)
    {
        m = li + (((ls - li) / v->tamElem) / 2) * v->tamElem; //aca Pan hace /tamelem y * tamelem para que siempre caiga en un byte de inicio de un tPersona, pq sino podria caer en el nombre por ej y se rompe todo.

        comp = cmp(elem,m);

        if(comp > 0)
        {
            li = m + v->tamElem;
        }
        else if(comp < 0)
        {
            ls = m - v->tamElem;
        }
        else
        {
            encontrado = true;
            memcpy(elem, m, v->tamElem); // si buscas una persona por su dni haciendo tPersona perBuscar y perBuscar.dni = 292, y luego envias esa perBuscar a la funcion, con esto copias los demas datos de esa persona.
            pos = (m - v->vec) / v->tamElem;
        }
    }

    return pos;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
int vectorOrdenar(tVector* v, Cmp cmp)
{
    void* ult = v->vec + (v->ce - 1) * v->tamElem;
    void* j;
    void* elemAIns = malloc(v->tamElem);

    if(elemAIns == NULL)
    {
        return SIN_MEM;
    }

    for(void* i = v->vec + v->tamElem; i <= ult; i += v->tamElem)
    {
        memcpy(elemAIns, i, v->tamElem);
        j = i - v->tamElem;

        while(j >= v->vec && cmp(elemAIns,j) < 0)
        {
            memcpy(j + v->tamElem, j, v->tamElem);
            j -= v->tamElem;
        }
        memcpy(j + v->tamElem, elemAIns, v->tamElem);
    }

    free(elemAIns);

    return TODO_OK;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
void vectorDestruir(tVector* v)
{
    if(v->vec != NULL)
    {
        free(v->vec);
        v->vec = NULL;
    }
    v->ce = 0;
    v->cap = 0;
    v->tamElem = 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
int vectorObtenerElem(tVector* v, int pos, void* elem)
{
    if(pos < 0 || pos >= v->ce)
    {
        return POS_INVALIDA;
    }

    memcpy(elem, v->vec + pos * v->tamElem, v->tamElem);
    return TODO_OK;
}
