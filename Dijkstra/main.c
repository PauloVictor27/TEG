#include <stdio.h>
#include <stdlib.h>
#include "Interface.h"

//Implementação do algoritmo
void dijkstra(int *vetorvisita, int *vetordistancia, int tamanho, int **matriz){
	int i; //Contador
	int distancia = 1000000; //1000000 = infinito
	int vertice_atual = 0; //Vertice para o percurso, começando em 0
	Lista l; //Lista para as inserções
	inicializa_lista(&l, sizeof(int));
	
	//Iniciando os vetores de distancia e de visita
	for(i = 0; i < tamanho; i++){
		vetordistancia[i] = distancia;
		vetorvisita[i] = -1;
	}
	//Primeira inserção
	vetordistancia[0] = 0;
	insere_inicio(&l, &vertice_atual);
	
	while (l.cabeca != NULL){
		remove_inicio(&l, &vertice_atual); //Remove o vertice da lista para colocar nos vetores e na matriz
		if(vetorvisita[vertice_atual]==1)continue;
		printf("Processando:%d\n",vertice_atual);
		vetorvisita[vertice_atual] = 1;

		//Percuso para procurar o menor caminho
		for (i = 0; i < tamanho; i++){
			if(vetorvisita[i] != 1 && matriz[vertice_atual][i] != 0){				
				int distancia_calculada = matriz[vertice_atual][i] + vetordistancia[vertice_atual]; //Somas as distancias as arestas
				if(distancia_calculada < vetordistancia[i]){
					vetordistancia[i] = distancia_calculada; //Escolhe o menor caminho
				}
				insere_inicio(&l, &i); //Escolhe o proximo vertice atual
			}
		}
		vetorvisita[vertice_atual] = -1;
	}
	
	//Imprimindo as distancias a partir de 0
	for (i = 0; i < tamanho; i++){
		printf("Distancia para %d: %d\n",i,vetordistancia[i]);
	}
	return;
}

int main() {    
    int i, j; // contadores
    int nv; // n de vertices
    int **m; // matriz do grafo
    int *c; //Vetor de visitas
    int *d; //Vetor de visitas
    int u, v; // coordenadas
    int valor;
    FILE *arquivo; // arquivo
    arquivo = fopen("grafo.txt","r");
    
    fscanf(arquivo,"%d", &nv);
    m = (int**) malloc(sizeof(int*) * nv); // alocação
    c = (int*) calloc(nv,sizeof(int)); // alocação
    d = (int*) calloc(nv,sizeof(int)); // alocação
    
    for (i = 0; i < nv; i++) {
        m[i] = (int*) calloc(sizeof(int), nv);
    }
    while (1) {
        fscanf(arquivo,"%d %d %d", &u, &v, &valor);
        if (u == -1 && v == -1 && valor ==-1) {
            // fim da leitura
            for (i = 0; i < nv; i++) {
                printf("\n%2d : ", i);
                for (j = 0; j < nv; j++) {
                    printf("%d ", m[i][j]);
                }
            }
            printf("\n\n");
			dijkstra(c, d, nv, m);
            return 0;
        } else {
            m[u][v] = valor;
            m[v][u] = valor; //Se for um digrafo, comente essa linha
        }
    }
    fclose(arquivo);
}
