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

//Matriz
typedef struct{
	Lista linhas; //Lista de elementos das linhas
	int tamInfoMatriz;
	int numLinhas;
	int numColunas;
}MatrizEsparsa;

typedef struct{
	int indice;
	void *info;
}EntradaMatriz;

int inserir_linha(Lista *linhas) {
	Lista *ele = (Lista*)malloc(sizeof(Lista));
    inicializa_lista(ele, sizeof(EntradaMatriz));
    return insere_fim(linhas, ele);
}

MatrizEsparsa *aloca_matriz(int linhas, int colunas, int tamInfo) {
    MatrizEsparsa *matriz = (MatrizEsparsa*) malloc(sizeof(MatrizEsparsa));
    int i;
    if (matriz != NULL) {
        inicializa_lista(&matriz->linhas, sizeof(Lista));
        matriz->numLinhas = linhas;
        matriz->numColunas = colunas;
        matriz->tamInfoMatriz = tamInfo;
        for (i = 0; i < linhas; i++) {
            inserir_linha(&matriz->linhas);
        }
    }
    return matriz;
}

EntradaMatriz *aloca_etMatriz(int *coluna, void *info) {
    EntradaMatriz *p = (EntradaMatriz *)malloc(sizeof(EntradaMatriz)); //nova Entrada de Matriz
    if (p != NULL) {
        p->info = malloc(sizeof(int));
        if (p->info != NULL) {
            memcpy(&p->indice, coluna, sizeof (int));
            memcpy(p->info, info, sizeof (int));
        } else {
            free(p);
        }
    }
    return p;
}

int inclui_valor_matriz(MatrizEsparsa *me, int *linha, int *coluna, void *info) {
    if ((*linha < 0 || (*linha) > me->numLinhas)&&(*coluna < 0 || *coluna > me->numColunas)) {
        return 0;
    } else {
        Lista *infosLinha = (Lista*) info_posicao(&me->linhas, *linha); //Pega a lista que é a linha da matriz
        Elemento *encontrar = infosLinha->cabeca; //Primeiro Elemento
        int posicao = 0;
        //Encontra aonde deve ser inserido
        while (encontrar != NULL && (((EntradaMatriz*) encontrar->info)->indice)<(*coluna)) {
            encontrar = encontrar->proximo;
            posicao++;
        }
        //Se já existe um elemento e este está no indice de inserção, remove ele para inserir o novo
        if(encontrar!=NULL && (((EntradaMatriz*) encontrar->info)->indice)==(*coluna)){
			EntradaMatriz entrada_removida;
			remove_posicao(infosLinha, posicao, &entrada_removida);
			free(entrada_removida.info);
		}
		if(*(int*)info!=0){ //Insere um novo elemento se ele não for nulo
			EntradaMatriz *etMatriz = aloca_etMatriz(coluna, info);
			//Agora cria um elemento que vai ser o elemento a ser inserido, ele irá conter a informacao da célula
			insere_posicao(infosLinha, etMatriz, posicao);
		}
        return 1;
    }
    return 1;
}

void *pega_valor_matriz(MatrizEsparsa *me, int *linha, int *coluna) {
    if ((*linha < 0 || (*linha) > me->numLinhas)&&(*coluna < 0 || *coluna > me->numColunas)) {
        return NULL;
    } else {
        Lista *linha_matriz = (Lista*)info_posicao(&me->linhas, *linha);

        Elemento *elementoCelula = linha_matriz->cabeca;
        while(elementoCelula!=NULL && (((EntradaMatriz*)elementoCelula->info)->indice)<*coluna){
			elementoCelula = elementoCelula->proximo;
		}
		if(elementoCelula!=NULL && (((EntradaMatriz*)elementoCelula->info)->indice)==*coluna){
			return ((EntradaMatriz*)elementoCelula->info)->info;
		}
    }
    return NULL;
}

void mostra_matriz(MatrizEsparsa *matriz) {
    printf("Matriz:\n");
    Lista lines = matriz->linhas;
    Elemento *walkOnLines = lines.cabeca; //Linhas da matriz
    while (walkOnLines != NULL) {
        Lista *dentroLinha = (Lista*) walkOnLines->info; //Listas de celulas
        Elemento *celula = dentroLinha->cabeca; //Primeira Celula [0][0]
		int i = 0;
		while (celula != NULL && i < matriz->numColunas) {
			if (((EntradaMatriz*) celula->info)->indice == i) {
				printf("%-4d ", *((int*)((EntradaMatriz*) celula->info)->info));
				celula = celula->proximo;
			} else {
				printf("%-4d ", 0);
			}
			i++;
		}
		//Imprime os 0 até o fim da linha
		for (; i < matriz->numColunas; i++) {
			printf("%-4d", 0);
		}
		printf("\n");
		walkOnLines = walkOnLines->proximo;
    }
}

MatrizEsparsa* multiplica_matrizes(MatrizEsparsa* matriz1, MatrizEsparsa* matriz2) {
    //Pré-requisito: o número de colunas da primeira linha deve ser igual ao número de coluna da segunda linha
    if (matriz1->numColunas != matriz2->numLinhas){
        printf("Numero de colunas da primeira matriz é diferente do número de linhas da segunda matriz!\n");
    } else {
		//Aloca a nova matriz
        MatrizEsparsa *matriz3 = aloca_matriz(matriz1->numLinhas, matriz2->numColunas, matriz1->tamInfoMatriz);
        int linhaAtual, colunaAtual, op;
        for(linhaAtual=0; linhaAtual<matriz3->numLinhas; linhaAtual++){//para cada linha da nova matriz
			for(colunaAtual=0; colunaAtual<matriz3->numColunas; colunaAtual++){//para cada coluna da nova matriz
				//Processa o valor da célula atual da nova matriz
				int valorSum = 0;
				for(op=0; op<matriz1->numColunas; op++){
					int *valorMat1 = (int*)pega_valor_matriz(matriz1, &linhaAtual, &op);
					int *valorMat2 = (int*)pega_valor_matriz(matriz2, &op, &colunaAtual);
					if(valorMat1!=NULL && valorMat2!=NULL){
						valorSum += (*valorMat1)*(*valorMat2);
					}
				}
				//Só é necessário adicionar caso for diferente de 0(não precisa verificar se precisa substituir por 0 pois está sendo construida em ordem)
				if(valorSum!=0){
					inclui_valor_matriz(matriz3, &linhaAtual, &colunaAtual, &valorSum);
				}
			}
		}
		//Adiciona a nova matriz na lista de matrizes
        return matriz3;
    }
    return NULL;
}

int valor_matrizEsparsa(MatrizEsparsa* mattriz, int linha, int coluna){
	int valor = 0;
	int *valor_ptr = (int*)pega_valor_matriz(mattriz, &linha, &coluna);
	if(valor_ptr!=NULL){
		valor = *valor_ptr;
	}
	return valor;
}
