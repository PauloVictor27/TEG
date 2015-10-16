#include "Interface.h"

//0 = Fracasso/Nao, 1 = Sucesso/Sim.

int cria(ppLDSE pp, int tamInfo) {
    int ret = 0;
    if (((*pp) = (pLDSE) malloc(sizeof (LDSE))) == NULL)
        ret = 0;
    else {
        (*pp)->primeiro = NULL;
        (*pp)->tamInfo = tamInfo;
        (*pp)->tamLista = 0;
        ret = 1;
    }
    return ret;
}

int reinicia(pLDSE p) {
    pNoLDSE aux = NULL;

    if (p->primeiro != NULL) {
        aux = p->primeiro->proximo;

        while (aux != NULL) {
            free(p->primeiro->dados);
            free(p->primeiro);
            p->primeiro = aux;
            aux = p->primeiro->proximo;
        }
        free(p->primeiro->dados);
        free(p->primeiro);
        p->primeiro = NULL;
        p->tamLista = 0;
    }
}

void destroi(ppLDSE pp) {
    reinicia(*pp);
    free(*pp);
    (*pp) = NULL;
}

int testaSeVazia(pLDSE p) {
    if (p->primeiro != NULL)
        return 0;
    else
        return 1;
}

/*int tamanho (pLDSE p)
{
    int cont = 0;
    pLDSE aux = p->primeiro;
    if (aux != NULL)
    {
        while (aux != NULL)
        {
            cont += 1;
            aux = aux->proximo;
        }
    }
    return cont;
}*/

int insereNovoPrimeiro(pLDSE p, void *novo) {
    pNoLDSE temp;
    int ret = 0;
    if ((temp = (NoLDSE *) malloc(sizeof (NoLDSE))) != NULL) {
        if ((temp->dados = (void *) malloc(p->tamInfo)) != NULL) {
            memcpy(temp->dados, novo, p->tamInfo);
            temp->proximo = p->primeiro;
            p->primeiro = temp;
            p->tamLista += 1;
            ret = 1;
        } else
            free(temp);
    }
    return ret;
}

int buscaPrimeiro(pLDSE p, void *reg) {
    int ret = 0;
    if (p->primeiro != NULL) {
        memcpy(reg, p->primeiro->dados, p->tamInfo);
        ret = 1;
    }
    return ret;
}

int removePrimeiro(pLDSE p, void *reg) {
    int ret = 0;
    pNoLDSE aux = NULL;
    if (p->primeiro != NULL) {
        aux = p->primeiro->proximo;
        memcpy(reg, p->primeiro->dados, p->tamInfo);
        free(p->primeiro->dados);
        free(p->primeiro);
        p->primeiro = aux;
        ret = 1;
    }
    return ret;
}

int insereNovoUltimo(pLDSE p, void *novo) {
    pNoLDSE temp, aux;
    int ret = 0;
    if (p->tamLista != 0) {
        if ((temp = (NoLDSE *) malloc(sizeof (NoLDSE))) != NULL) {
            if ((temp->dados = (void *) malloc(p->tamInfo)) != NULL) {
                memcpy(temp->dados, novo, p->tamInfo);
                aux = p->primeiro;
                while (aux->proximo != NULL) {
                    aux = aux->proximo;
                }
                aux->proximo = temp;
                temp->proximo = NULL;
                p->tamLista += 1;
                ret = 1;
            } else
                free(temp);
        }
    } else {
        if ((temp = (NoLDSE *) malloc(sizeof (NoLDSE))) != NULL) {
            if ((temp->dados = (void *) malloc(p->tamInfo)) != NULL) {
                memcpy(temp->dados, novo, p->tamInfo);
                temp->proximo = NULL;
                p->primeiro = temp;
                p->tamLista += 1;
                ret = 1;
            } else
                free(temp);
        }
    }
    return ret;
}

int buscaUltimo(pLDSE p, void *reg) {
    pNoLDSE aux = p->primeiro;
    int ret;
    if (p->tamLista == 0) {
        ret = 0;
    } else {
        while (aux->proximo != NULL) {
            aux = aux->proximo;
        }
        memcpy(reg, aux->dados, p->tamInfo);
        ret = 1;
    }
    return ret;
}

int removeUltimo(pLDSE p) {
    pNoLDSE aux1, aux2;
    int ret;
    if (p->tamLista == 0) {
        ret = 0;
    } else {
        aux1 = p->primeiro;
        aux2 = aux1->proximo;
        if (aux2 == NULL) {
            free(p->primeiro->dados);
            free(p->primeiro);
            p->primeiro = NULL;
            p->tamLista--;
            ret = 1;
        } else {
            while (aux2->proximo != NULL) {
                aux1 = aux2;
                aux2 = aux2->proximo;
            }
            free(aux2->dados);
            free(aux2);
            aux1->proximo = NULL;
            p->tamLista--;
            ret = 1;
        }
    }
    return ret;
}

int insereNovoPosLog(pLDSE p, void *novo, unsigned int posLog) {
    pNoLDSE aux1, aux2;
    int ret = 0;
    int cont;
    if (posLog > 0 && p->tamLista != 0) {
        if (posLog == 1) {
            return insereNovoPrimeiro(p, novo);
        } else {
            cont = 2;
            aux1 = p->primeiro;
            aux2 = aux1->proximo;
            while (aux2 != NULL && cont < posLog) {
                aux1 = aux2;
                aux2 = aux2-> proximo;
                cont += 1;
            }
            if (aux2 != NULL && cont < posLog) {
                aux1->proximo = (NoLDSE *) malloc(sizeof (p->tamInfo));
                aux1->proximo ->proximo = aux2;
                memcpy(aux1->proximo->dados, novo, p->tamInfo);
                ret = 1;
            }
        }
    } else {
        ret = 0;
    }
    return ret;
}

int buscaNaPosLog(pLDSE p, void *reg, unsigned int posLog) {
    pNoLDSE aux;
    int ret, cont;
    if (p->tamLista != 0 && posLog > 0) {
        if (posLog == 1) {
            memcpy(reg, p->primeiro->dados, p->tamInfo);
            ret = 1;
        } else {
            cont = 2;
            aux = p->primeiro->proximo;
            while (aux != NULL && cont < posLog) {
                aux = aux-> proximo;
                cont += 1;
            }
            if (aux != NULL && cont == posLog) {
                memcpy(reg, aux->dados, p->tamInfo);
                ret = 1;
            }

        }
    } else {
        ret = 0;
    }
    return ret;
}

int removeDaPosLog(pLDSE p, unsigned int posLog, void *reg) {
    pNoLDSE aux1, aux2;
    int ret = 0, cont;
    if (posLog > 0 && p->tamLista != 0) {
        if (posLog == 1) {
            return removePrimeiro(p,reg);
        } else {
            cont = 2;
            aux1 = p->primeiro;
            aux2 = aux1->proximo;
            while (aux2 != NULL && cont < posLog) {
                aux1 = aux2;
                aux2 = aux2-> proximo;
                cont += 1;
            }
            if (aux2 != NULL && cont < posLog) {
                aux1->proximo = aux2->proximo;
                free(aux2->dados);
                free(aux2);
                p->tamLista--;
                ret = 1;
            }
        }
    } else {
        ret = 0;
    }
    return ret;
}







