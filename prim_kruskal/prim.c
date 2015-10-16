#include <stdio.h>
#include <stdlib.h>


//Implementação do algoritmo
void prim(int *vetorvisita, int *vetordistancia, int tamanho, int **matriz){
	int i, j; //Contadores
	int k = 0; //Marcador
	int menorlinha;	//Menor aresta da linha
	//Percuso para procurar a menor aresta
		for (i = 0; i < tamanho-1; i++){ //Procura (tamanho-1) vezez, que é o numero minimo de arestas que um grafo pode ter
		menorlinha = 1000;	//Menor aresta da linha
			for(j = 0; j < tamanho; j++){
				if(vetorvisita[j] != 1 && (i < j) && matriz[i][j] < vetordistancia[j]){ //A coluna não pode ter sido visitada, a aresta precisa estar acima da diagonal principal da matriz e a distancia precisa ser menor do que a atual
					vetordistancia[j-1] = matriz[i][j];
				}
				if(vetorvisita[j] != 1 && i != j && matriz[i][j] < menorlinha){ //Encontra a menor aresta
					menorlinha = matriz[i][j];
					k = j; //Marca a coluna da menor aresta
				}
			}
			vetorvisita[k] = 1;	//Marca a posicao da menor aresta da linha como visitada
		}
		
		for (i = 0; i < tamanho-1; i++) {
			printf("Menor distancia: %d\n", vetordistancia[i]);
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
    d = (int*) calloc(nv,sizeof(int)); // alocação para o numero minimo de arestas que um grafo pode ter
    
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
    
    //Iniciando o vetor de distancias
    for (i = 0; i < nv; i++) {
        d[i] = 1000;
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
			prim(c, d, nv, m);
            return 0;
        } else {
            m[u][v] = valor;
            m[v][u] = valor; //Se for um digrafo, comente essa linha
        }
    }
    fclose(arquivo);
}
