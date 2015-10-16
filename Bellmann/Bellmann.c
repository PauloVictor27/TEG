#include <stdio.h>
#include <stdlib.h>

//Implementação do algoritmo
void bellmann(int *vetorvisita, int *vetordistancia, int tamanho, int **matriz){
	int i, j, k; //Contador
	int distancia = 1000000; //1000000 = infinito
	
	//Iniciando os vetores de distancia e de visita
	for(i = 0; i < tamanho; i++){
		vetordistancia[i] = distancia;
		vetorvisita[i] = -1;
	}
	//Primeira inserção
	vetordistancia[0] = 0;
	
	//Implementando o algoritmo
	for(k = 0; k < tamanho; k++){
		for(i = 0; i < tamanho; i++){
			for(j = 0; j < tamanho; j++){
				if(matriz[i][j] != 0 && vetorvisita[j] ==-1){
					int distancia_calculada = matriz[i][j] + vetordistancia[i];
					if(distancia_calculada < vetordistancia[j]){ //Relaxamento
					vetordistancia[j] = distancia_calculada; //Escolhe o menor caminho
					}
				}
			}		
		}
	}
	
	//Verifica se tem ciclos negativos
	for(i = 0; i < tamanho; i++){
		for(j = 0; j < tamanho; j++){
			if(vetordistancia[j] > vetordistancia[i] + matriz[i][j] && matriz[i][j] != 0) { //Relaxamento
				printf("Tem ciclo negativo em %d e %d\n",i,j);
			}
		}
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
    int *d; //Vetor de distancia
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
			bellmann(c, d, nv, m);
            return 0;
        } else {
            m[u][v] = valor;
        }
    }
    fclose(arquivo);
}
