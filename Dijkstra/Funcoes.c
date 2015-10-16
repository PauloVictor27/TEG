#include "Descritor.h"

//Funções Iniciais
void inicializa_lista(Lista *l, int t){
	l->tamInfo = t;
	l->cabeca = NULL;
}

int lista_vazia(Lista l){
	return l.cabeca == NULL;
}

Elemento *aloca_elemento(void *info, int tam){
	Elemento *p = (Elemento*)malloc(sizeof(Elemento)); //Elemento Novo
	if(p!=NULL){
		p->info = malloc(tam);
		if(p->info != NULL){
			memcpy(p->info, info, tam);
		}else{
			free(p);
		}
	}
	return p;
}

//Funções de Inserção
int insere_inicio(Lista *l, void *info){
	Elemento *p = aloca_elemento(info, l->tamInfo); //Elemento Novo
	if(p!=NULL){
		p->proximo = l->cabeca;
		l->cabeca = p;
		return 1; //Sucesso
	}else{
		return 0; //Fracasso
	}
}

int insere_fim(Lista *l, void *info){
	if(lista_vazia(*l)){
		insere_inicio(l, info);
	}else{
		Elemento *p = aloca_elemento(info, l->tamInfo); //Elemento Novo
		if(p!=NULL){
			Elemento *iterator = l->cabeca;
			while(iterator->proximo!=NULL){
				 iterator = iterator->proximo;
			}
			iterator->proximo = p;
			p->proximo = NULL;
		}else{
			return 0; //Fracasso
		}
	}
	return 1; //Sucesso
}

int insere_posicao(Lista *l, void *info, int posicao){
	if(posicao<0) return -2; //Posicão Invalida
	if(posicao==0) return insere_inicio(l, info);
	Elemento *p = l->cabeca; //Primeiro Elemento
	int i = 0;
	while(i<posicao-1 && p->proximo!=NULL){
		p = p->proximo;
		i++;
	}
	if(i!=posicao-1){
		return -2; //Posição Invalida
	}
	Elemento *novo = aloca_elemento(info, l->tamInfo);
	if(novo==NULL){
		return 0;
	}
	novo->proximo = p->proximo; 
	p->proximo = novo; 
	return 1;
}

//Funções de Remoção
int remove_inicio(Lista *l, void *saiu){
	if(lista_vazia(*l)){
		return -1; //Lista Vazia
		printf("Lista Vazia\n");
	}else{
		Elemento *p = l->cabeca;
		l->cabeca = l->cabeca->proximo;
		memcpy(saiu, p->info, l->tamInfo);
		free(p->info);
		free(p);
		return 1; //Sucesso
	}
}

int remove_fim(Lista *l, void *info){
	if(lista_vazia(*l)){
		return -1;
		printf("Lista Vazia\n");
	}
	if(l->cabeca->proximo==NULL){
		remove_inicio(l, info); //Elemento Unico
	}else{
		Elemento *iterator = l->cabeca;
		while(iterator->proximo->proximo!=NULL){ //Penultimo Elemento
			iterator = iterator->proximo;
		}
		Elemento *ultimo_elemento = iterator->proximo;
		memcpy(info, ultimo_elemento->info, l->tamInfo);
		free(ultimo_elemento->info);
		free(ultimo_elemento);
		iterator->proximo = NULL;
		return 1;
	}
	return 0;
}

int remove_posicao(Lista *l, int posicao, void *info){
	if(lista_vazia(*l)){
		return -1; //Lista Vazia
	}else{
		if(posicao<0) return -2; //Posição Invalida
		if(posicao==0) return remove_inicio(l, info);
		Elemento *p = l->cabeca; //Primeiro Elemento
		int i = 0;
		while(i<posicao-1 && p->proximo!=NULL){
			p=p->proximo;
			i++;
		}
		if(i!=posicao-1){
			return -2; //Posição Invalida
		}

		Elemento* removido = p->proximo;
		p->proximo = p->proximo->proximo;
		memcpy(info, removido->info, l->tamInfo);
		free(removido->info);
		free(removido);
		return 1;
	}
}

//Funções de Modificação
void *info_posicao(Lista *l, int posicao) {
    Elemento *p = l->cabeca;
	int iterator_pos = 0;
	while (p != NULL && iterator_pos<posicao) {
		p = p->proximo;
		iterator_pos++;
	}
	if(iterator_pos==posicao){
		return p->info;
	}
    return NULL;
}
