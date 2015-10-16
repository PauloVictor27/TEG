#include "Descritor.h"

typedef struct LDSE *pLDSE, **ppLDSE;

int cria(ppLDSE pp, int tamInfo);
int insereNovoPrimeiro(pLDSE p, void *novo);
int insereNovoUltimo(pLDSE p, void *novo);
int insereNovoPosLog(pLDSE p, void *novo,unsigned int poLog);
int buscaPrimeiro(pLDSE p, void *reg);
int buscaUltimo(pLDSE p, void *reg);
int buscaNaPosLog(pLDSE p, void *reg, unsigned int posLog);
int removePrimeiro(pLDSE p, void *reg);
int removeUltimo(pLDSE p);
int removeDaPosLog(pLDSE p, unsigned int posLog, void *reg);
int reinicia(pLDSE p);
int testaSeVazia(pLDSE p);
void destroi(ppLDSE pp);
//int tamanho (pLDSE P);
