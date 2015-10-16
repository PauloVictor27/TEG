#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Funcoes.c"

typedef struct Lista *pLista, **ppLista;

//Funções Iniciais
void inicializa_lista(Lista *l, int t);
Elemento *aloca_elemento(void *info, int tam);

//Funções de Inserção
int insere_inicio(Lista *l, void *info);
int insere_fim(Lista *l, void *info);
int insere_posicao(Lista *l, void *info, int posicao);

//Funções de Remoção
int remove_inicio(Lista *l, void *saiu);
int remove_fim(Lista *l, void *info);
int remove_posicao(Lista *l, int posicao, void *info);
void *info_posicao(Lista *l, int posicao);

