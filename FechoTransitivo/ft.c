#include <stdio.h>
#include <stdlib.h>

void ftd(int **matriz, int vertice, int tamanho){ //fecho transitivo direto
	int i;//Contador
	printf("FTD de %d: ",vertice);
	for(i = 0; i < tamanho; i++){
		if(matriz[vertice][i] != 0) //verifica se o vertice tem descendentes (vertice -> i)
			printf("%d ",i);
	}
	printf("\n\n");
	return;
}

void fti(int **matriz, int vertice, int tamanho){ //fecho transitivo indireto
	int i;//Contador
	printf("FTI de %d: ",vertice);
	for(i = 0; i < tamanho; i++){
		if(matriz[i][vertice] != 0) //verifica se o vertice tem ascendentes (i ->vertice)
			printf("%d ",i);
	}
	printf("\n\n");
	return;
}

int main() {    
    int i, j; // contadores
    int nv; // n de vertices
    int **m; // matriz do grafo
    int u, v; // coordenadas
    int valor; //Valor das arestas
    int vertice; //vertice para os FT
    FILE *arquivo; // arquivo
    arquivo = fopen("grafo.txt","r");
    
    fscanf(arquivo,"%d", &nv);
    m = (int**) malloc(sizeof(int*) * nv); // alocação

    for (i = 0; i < nv; i++) {
        m[i] = (int*) calloc(sizeof(int), nv);
    }
    
    //Iniciando a matriz
    for (i = 0; i < nv; i++) {
        for (j = 0; j < nv; j++){
				m[i][j] = 0;
			}
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
            printf("Digite um vertice: ");
            scanf("%d",&vertice);
            printf("\n");
			ftd(m,vertice,nv);
			fti(m,vertice,nv);
            return 0;
        } else {
            m[u][v] = valor;
        }
    }
    fclose(arquivo);
}
