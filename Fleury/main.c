#include <stdio.h>
#include <stdlib.h>

//Função de busca de profundidade para retornar o ultimo vertice percorido
int dfs(int **matriz, int *vetor, int tamanho, int linha){
	int i;
	int ultimo=-1; //Iniciando o ultimo vertice
	vetor[linha]++;
	for(i = 0; i < tamanho; i++){
		if(vetor[i] != 1 && matriz[linha][i] != 0){
			matriz[linha][i] = 0;
			ultimo = dfs(matriz,vetor,tamanho,i);
		}
		
	}
	if(ultimo == -1){
		ultimo = linha;
	}
	return ultimo;
}

int main() {    
    int i, j, cont1, cont2 = 0, arestas = 0; // contadores
    int nv; // n de vertices
    int **m; // matriz do grafo
    int *c; //Vetor de visitas
    int u, v; // coordenadas
    FILE *arquivo; // arquivo
    arquivo = fopen("grafo.txt","r");
    
    fscanf(arquivo,"%d", &nv);
    m = (int**) malloc(sizeof(int*) * nv);
    c = (int*) calloc(nv,sizeof(int)); // alocação
    
    for (i = 0; i < nv; i++) {
        m[i] = (int*) calloc(sizeof(int), nv);
    }
    while (1) {
        fscanf(arquivo,"%d %d", &u, &v);
        arestas++;
        if (u == -1 && v == -1) {
            // fim da leitura
            arestas--;
            for (i = 0; i < nv; i++) {
                printf("\n%2d : ", i);
                for (j = 0; j < nv; j++) {
                    printf("%d ", m[i][j]);
                }
            }
            
            printf("\n");
            printf("\nArestas: %d\n",arestas);
            printf("Testando se eh euclidiano:\n");
            cont1 = dfs(m, c, nv, 0);
            printf("Ultimo elemento visidado = %d\n\n",cont1);
            for(i = 0; i < nv; i++){
				printf("Vetor de visitas[%d] = %d\n",i,c[i]); 
				if(c[i] != 1){
					cont2++;
//Primeira condição: se algum elemento do vetor de visitas for diferente 1, ou seja, passou mais de uma vez ou nenhuma vez em tal aresta o grafo não é euclidiano.
				}
			}
			
			if (cont2 != 0)
			{
				printf("\nO grafo nao .eh euclidiano\n");
			}
			
			else{
				if(m[cont1][0] == 1){ //Se o ultimo vertice liga com o primeiro, ele é euclidiano. Se não ele não é.
					printf("\nO grafo eh euclidiano\n");
				}
				else{
					printf("\nO grafo nao eh euclidiano\n");
				}
			}
			
            return 0;
        } else {
            m[u][v] = 1;
            m[v][u] = 1;
        }
    }
    
    fclose(arquivo);
}
