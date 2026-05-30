
// HAY 2 EJERCICIOS EN MIEL PARA PRACTICAR ESTO!!!

#include "listaSimplementeEnlazada.h"

void crearLista(tLista* p)
{
    *p = NULL;
}

int listaVacia(const tLista* p)
{
    return *p == NULL;
}

int listaLlena(const tLista* p, unsigned cantBytes)
{
    return 0;
}

void vaciarLista(tLista* p)
{
    while(*p)
    {
        tNodo* aux = *p;

        *p = aux->sig;
        free(aux->info);
        free(aux);
    }
}

int insertarAlComienzo(tLista* p, const void* d, unsigned cantBytes)
{
    tNodo* nue = (tNodo*)malloc(sizeof(tNodo));
    if(nue == NULL)
    {
        return SIN_MEM;
    }

    nue->info = malloc(cantBytes);
    if(nue->info == NULL)
    {
        free(nue);
        return SIN_MEM;
    }

    memcpy(nue->info, d, cantBytes);
    nue->tamInfo = cantBytes;
    nue->sig = *p;

    *p = nue;

    return TODO_OK;
}

int sacarPrimeroLista(tLista* p, void* d, unsigned cantBytes)
{
    if(*p == NULL)
    {
        return LISTA_VACIA;
    }
    memcpy(d, (*p)->info, MINIMO(cantBytes, (*p)->tamInfo));

    tNodo* aux = *p;

    *p = aux->sig;

    free(aux->info);
    free(aux);

    return TODO_OK;
}

int verPrimeroLista(const tLista* p, void* d, unsigned cantBytes)
{
    if(*p == NULL)
    {
        return LISTA_VACIA;
    }
    memcpy(d, (*p)->info, MINIMO(cantBytes, (*p)->tamInfo));

    return TODO_OK;
}

int insertarAlFinal(tLista* p, const void* d, unsigned cantBytes)
{
    tNodo* nue = (tNodo*)malloc(sizeof(tNodo));
    if(nue == NULL)
    {
        return SIN_MEM;
    }

    nue->info = malloc(cantBytes);
    if(nue->info == NULL)
    {
        free(nue);
        return SIN_MEM;
    }

    memcpy(nue->info, d, cantBytes);
    nue->tamInfo = cantBytes;
    nue->sig = NULL;

    while(*p != NULL)
    {
        p = &((*p)->sig);
    }

    *p = nue;

    return TODO_OK;
}

int sacarUltimoLista(tLista* p, void* d, unsigned cantBytes)
{
    if(*p == NULL)
    {
        return LISTA_VACIA;
    }

    while((*p)->sig != NULL)
    {
        p = &((*p)->sig);
    }
    memcpy(d, (*p)->info, MINIMO(cantBytes, (*p)->tamInfo));

    free((*p)->info);
    free(*p);
    *p = NULL;

    return TODO_OK;
}

int verUltimoLista(const tLista* p, void* d, unsigned cantBytes)
{
    if(*p == NULL)
    {
        return LISTA_VACIA;
    }

    while((*p)->sig != NULL)
    {
        p = &((*p)->sig);
    }
    memcpy(d, (*p)->info, MINIMO(cantBytes, (*p)->tamInfo));

    return TODO_OK;
}
void mostrarLista(const tLista *p, Accion accion)
{
    while(*p)
    {
        accion((*p)->info);
        p=&(*p)->sig;
    }
}
int eliminarDeLista(tLista* p, void* d, unsigned cantBytes, Cmp cmp)
{
    tNodo* elim;

    if(*p == NULL)
    {
        return LISTA_VACIA;
    }

    while(*p != NULL && cmp((*p)->info, d) != 0)
    {
        p = &((*p)->sig);
    }

    if(*p == NULL)
    {
        return ELEM_NO_ENCONTRADO;
    }

    memcpy(d, (*p)->info, MINIMO(cantBytes, (*p)->tamInfo));

    elim = *p;
    *p = elim->sig;

    free(elim->info);
    free(elim);

    return TODO_OK;
}

int insertarOrdenadoListaSinD(tLista* p, const void* d, unsigned cantBytes, Cmp cmp, Actualizar actualizar)
{
    while(*p && cmp((*p)->info, d) < 0)
    {
        p = &((*p)->sig);
    }

    if(*p && cmp((*p)->info, d) == 0)
    {
        if(actualizar)
        {
            actualizar((*p)->info, d);
        }
        return DUPLICADO;
    }

    tNodo* nue = (tNodo*)malloc(sizeof(tNodo));
    if(!nue)
    {
        return SIN_MEM;
    }

    nue->info = malloc(cantBytes);
    if(!nue->info)
    {
        free(nue);
        return SIN_MEM;
    }

    memcpy(nue->info, d, cantBytes);
    nue->tamInfo = cantBytes;

    nue->sig = *p;
    *p = nue;

    return TODO_OK;
}

int insertarOrdenadoListaConD(tLista* p, const void* d, unsigned cantBytes, Cmp cmp)
{
    while(*p && cmp((*p)->info, d) < 0)
    {
        p = &((*p)->sig);
    }

    tNodo* nue = (tNodo*)malloc(sizeof(tNodo));
    if(!nue)
    {
        return SIN_MEM;
    }

    nue->info = malloc(cantBytes);
    if(!nue->info)
    {
        free(nue);
        return SIN_MEM;
    }

    memcpy(nue->info, d, cantBytes);
    nue->tamInfo = cantBytes;

    nue->sig = *p;
    *p = nue;

    return TODO_OK;
}

void ordenarLista(tLista* p, Cmp cmp)
{
    tLista* pri = p;

    if(!*p)
    {
        return;
    }

    while((*p)->sig)
    {
        if(cmp((*p)->info, (*p)->sig->info) > 0)
        {
            tLista* q = pri;
            tNodo* aux = (*p)->sig;

            (*p)->sig = aux->sig;

            while(cmp((*q)->info, aux->info) < 0)
            {
                q = &((*q)->sig);
            }
            aux->sig = *q;
            *q = aux;
        }
        else
        {
            p = &((*p)->sig);
        }
    }
}

int actualizarNPos(tLista* p, const void* d, unsigned pos, Actualizar actualizar)
{
    int i = 0;

    while(i < pos && *p != NULL)
    {
        p = &((*p)->sig);
        i++;
    }

    if(*p == NULL)
    {
        return POS_INVALIDA;
    }

    actualizar((*p)->info, d);

    return TODO_OK;
}

int verNElem(tLista *p, unsigned pos, void *elem, unsigned tam)
{
    unsigned i = 0;

    while(*p && i < pos)
    {
        p = &(*p)->sig;
        i++;
    }

    if(*p)
    {
        memcpy(elem, (*p)->info, MINIMO(tam, (*p)->tamInfo));
        return TODO_OK;
    }

    return POS_INVALIDA;
}

int cargarOrdenadoListaSinDupDeArchivo(tLista* p, unsigned cantBytes, Cmp cmp, Actualizar actualizar, const char* nomArch)
{
    void* reg;
    tNodo* nue;
    tLista* ini = p;

    FILE* arch = fopen(nomArch,"rb");

    if(!arch)
        return ERR_ARCH;

    reg = malloc(cantBytes);

    if(!reg)
    {
        fclose(arch);
        return SIN_MEM;
    }

    while(fread(reg, cantBytes, 1, arch) == 1)
    {
        p = ini;

        while(*p && cmp((*p)->info, reg) < 0)
        {
            p = &((*p)->sig);
        }

        if(*p && cmp((*p)->info, reg) == 0)
        {
            if(actualizar)
            {
                actualizar((*p)->info, reg);
            }
        }

        nue = (tNodo*)malloc(sizeof(tNodo));

        if(!nue)
        {
            free(reg);
            fclose(arch);
            return SIN_MEM;
        }

        nue->info = malloc(cantBytes);

        if(!nue->info)
        {
            free(nue);
            free(reg);
            fclose(arch);
            return SIN_MEM;
        }

        memcpy(nue->info, reg, cantBytes);

        nue->tamInfo = cantBytes;

        nue->sig = *p;

        *p = nue;
    }

    free(reg);

    fclose(arch);

    return TODO_OK;
}


