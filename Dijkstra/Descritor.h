#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Descritor da Lista
typedef struct elemento{
	void *info;
	struct elemento *proximo;
}Elemento;

typedef struct{
	int tamInfo;
	Elemento *cabeca;
}Lista; 
