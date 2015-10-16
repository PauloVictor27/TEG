#include <stdio.h>
#include <stdlib.h>

void floyd(int **matriz, int tamanho){
	int k, i, j; //Contadores
	int ***novamatriz;
	
	//Alocação nos 3 niveis
	novamatriz = (int***) malloc(sizeof(int**) * tamanho);
    for (i = 0; i < tamanho; i++) {
        novamatriz[i] = (int**) calloc(sizeof(int*), tamanho);
    } 
    for (i = 0; i < tamanho; i++) {
        for (j = 0; j < tamanho; j++){
				novamatriz[i][j] = (int*) calloc(sizeof(int), tamanho);
			}
    }
    
    //Inicializando a primeira matriz
    for (i = 0; i < tamanho; i++) {
        for (j = 0; j < tamanho; j++){
				if((matriz[i][j] < matriz[i][0] + matriz[0][j]) && (matriz[i][0] != 1000 && matriz[0][j] != 1000)){ // D[k-1][i][j] < D[k-1][i][k] + D[k-1][k][j]
					novamatriz[0][i][j] = matriz[i][j];
				} else if((matriz[i][j] > matriz[i][0] + matriz[0][j]) && (matriz[i][0] != 1000 && matriz[0][j] != 1000)) { // D[k-1][i][j] > D[k-1][i][k] + D[k-1][k][j]
					novamatriz[0][i][j] = matriz[i][0] + matriz[0][j];
				} else{ // D[k-1][i][j] == D[k-1][i][k] + D[k-1][k][j]
					novamatriz[0][i][j] = matriz[i][j];
				}
			}
    }
    
    //Criando as matrizes
	for (k = 1; k < tamanho; k++){
		for (i = 0; i < tamanho; i++){
			for (j = 0; j < tamanho; j++){
				//Condi��es basicas: as coordenadas [i][k] e [k][j] precisam ser diferentes de infinito (1000)
				if((novamatriz[k-1][i][j] < novamatriz[k-1][i][k] + novamatriz[k-1][k][j]) && (novamatriz[k-1][i][k] != 1000 && novamatriz[k-1][k][j] != 1000)){ // D[k-1][i][j] < D[k-1][i][k] + D[k-1][k][j]
					novamatriz[k][i][j] = novamatriz[k-1][i][j];
				} else if((novamatriz[k-1][i][j] > novamatriz[k-1][i][k] + novamatriz[k-1][k][j]) && (novamatriz[k-1][i][k] != 1000 && novamatriz[k-1][k][j] != 1000)) { // D[k-1][i][j] > D[k-1][i][k] + D[k-1][k][j]
					novamatriz[k][i][j] = novamatriz[k-1][i][k] + novamatriz[k-1][k][j];
				} else{ // D[k-1][i][j] == D[k-1][i][k] + D[k-1][k][j]
					novamatriz[k][i][j] = novamatriz[k-1][i][j];
				}
			}
		}
	}
	
	//Imprimindo as matrizes
	for (k = 0; k < tamanho; k++){
		for (i = 0; i < tamanho; i++){
			printf(" %d: ",i);
			for (j = 0; j < tamanho; j++){
				printf("%d ", novamatriz[k][i][j]);
			}
			printf("\n");
		}
		printf("\n\n");
	}
	return;
}

int main() {    
    int i, j; // contadores
    int nv; // n de vertices
    int **m; // matriz do grafo
    int u, v; // coordenadas
    int valor; //Valor das arestas
    FILE *arquivo; // arquivo
    arquivo = fopen("grafo.txt","r");
    
    fscanf(arquivo,"%d", &nv);
    m = (int**) malloc(sizeof(int*) * nv); // alocação

    for (i = 0; i < nv; i++) {
        m[i] = (int*) calloc(sizeof(int), nv);
    }
    
    //Iniciando a matriz, 1000 = infinito
    for (i = 0; i < nv; i++) {
        for (j = 0; j < nv; j++){
				m[i][j] = 1000;
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
			floyd(m, nv);
            return 0;
        } else {
            m[u][v] = valor;
            //m[v][u] = valor;
        }
    }
    fclose(arquivo);
}
