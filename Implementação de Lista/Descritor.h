#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


typedef struct noLDSE
{
    void *dados;
    struct noLDSE *proximo;
}NoLDSE,*pNoLDSE;

typedef struct LDSE
{
    int tamInfo;
    int tamLista;
    pNoLDSE primeiro;
}LDSE, *pLDSE, **ppLDSE;
