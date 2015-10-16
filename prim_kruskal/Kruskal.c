#include <stdio.h>
#include <stdlib.h>


//Implementação do algoritmo
void kruskal(int *vetorvisita, int *vetordistancia, int tamanho, int **matriz){
	int i, j, k; //Contadores
	int x = 0, y = 0; //Coordenadas da menor aresta
	
	//Percuso para procurar a menor aresta de toda a matriz
	for(k = 0; k < (tamanho-1); k++){ //Procura (tamanho-1) vezez, que é o numero minimo de arestas que um grafo pode ter
		int menor_distancia = 1000; //Valor inicial
		for (i = 0; i < tamanho; i++){
			for(j = 0; j < tamanho; j++){
				if(vetorvisita[j] != 1 && i != j && matriz[i][j] < menor_distancia){ //Encontra a menor aresta
					menor_distancia = matriz[i][j];
					x = i; //Guarda as coordenadas
					y = j;
				}
			}	
		}
		vetordistancia[x] = y; //Marca a aresta visitada
		vetorvisita[y] = 1;
		if(k==0){ //Primeira vez
			vetorvisita[x] = 1;
		}
		printf("Menor distancia: %d\n", matriz[x][y]);
	}	
	return;
}

int main() {    
    int i, j; // contadores
    int nv; // n de vertices
    int **m; // matriz do grafo
    int *c; //Vetor de visitas
    int *d; //Vetor de distancias
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
	
	//Iniciando a matriz
    for (i = 0; i < nv; i++) {
        for (j = 0; j < nv; j++){
			if (i == j){
				m[i][j] = 0;
			}else{
				m[i][j] = 1000;
				//1000 = infinito
				}
			}
    }
	
    while (1) {
        fscanf(arquivo,"%d %d %d", &u, &v, &valor);
        if (u == -1 && v == -1 && valor ==-1) {
            // fim da leitura
            for (i = 0; i < nv; i++) {
                printf("\n%2d :\t", i);
                for (j = 0; j < nv; j++) {
                    printf("%d\t", m[i][j]);
                }
            }
            printf("\n\n");
			kruskal(c, d, nv, m);
            return 0;
        } else {
            m[u][v] = valor;
            m[v][u] = valor; //Se for um digrafo, comente essa linha
        }
    }
    fclose(arquivo);
}
