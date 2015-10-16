#include "Funcoes.h"

//Funcoes Principais
void verifica_order(MatrizEsparsa* grafo, int digrafo){
	int tam = grafo->numLinhas;
	int sum, i, y;
	if(digrafo){
		for(i=0;i<tam;i++){
			sum = 0;
			for(y=0;y<tam;y++){
				sum += valor_matrizEsparsa(grafo, i, y);
			}
			printf("Grau saida de %d = %d\n",i+1,sum);
		}
		for(i=0;i<tam;i++){
			sum = 0;
			for(y=0;y<tam;y++){
				sum += valor_matrizEsparsa(grafo, y, i);
			}
			printf("Grau entrada de %d = %d\n",i+1,sum);
		}
	}else{
		for(i=0;i<tam;i++){
			sum = 0;
			for(y=0;y<tam;y++){
				sum += valor_matrizEsparsa(grafo, i, y);
				if(i==y){
                    sum += valor_matrizEsparsa(grafo, i, y);
				}
			}
			printf("Grau de %d = %d\n",i+1,sum);
		}

	}
}

int main(void){
	int vertices,arestas;
	int digrafo=0;
	int i,v1,v2, grau;
	
	printf("E um  Digrafo? 1-Sim 0-Nao\n");
	scanf("%d", &digrafo);
	printf("Insira a quantidade de Vertices e Arestas do grafo\n");
	scanf("%d %d", &vertices, &arestas);
	MatrizEsparsa *grafo = aloca_matriz(vertices, vertices, sizeof(int));
	
	for(i=0; i<arestas; i++){
		printf("Insira o Vertice 1 e Vertice 2 da Aresta %d\n",i);
		scanf("%d %d", &v1, &v2);
		int linha = v1-1;
		int coluna = v2-1;
		int valor = valor_matrizEsparsa(grafo, linha, coluna);
		int novo_valor = valor+1;
		inclui_valor_matriz(grafo, &linha, &coluna, &novo_valor);
		if(!digrafo && v1!=v2){
			linha = v2-1;
			coluna = v1-1;
			valor = valor_matrizEsparsa(grafo, linha, coluna);
			novo_valor = valor+1;
			inclui_valor_matriz(grafo, &linha, &coluna, &novo_valor);
		}
	}
	
	mostra_matriz(grafo);
	printf("Insira o tamanho da adjacencia\n");
	scanf("%d", &grau);
	MatrizEsparsa* result = grafo;
	
	for(i=1;i<grau;i++){
		if(i==1){
			result = multiplica_matrizes(grafo, grafo);
		}else{
			result = multiplica_matrizes(grafo, result);
		}
	}
	mostra_matriz(result);
	verifica_order(grafo, digrafo);
	return 0;
}
