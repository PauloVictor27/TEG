#include <stdio.h>
#include <stdlib.h>

//Função de busca de profundidade para os filhos do vertice
int dfsfilho(int **matriz, int **caminho, int tamanho, int linha){
	int i; //Contador
	int maior = 0;
	int cont = 0;
	int ultimo; //Ultima folha
	for(i = 0; i < tamanho; i++){	
			if(matriz[linha][i] != 0){ //Verifica se o vertice tem um filho
				cont +=1; //Se tiver marca 1
			}
	}
	if(cont == 0){
		ultimo = linha; //Se n�o tiver marca o anterior como folha
	}
	else{
		for(i = 0; i < tamanho; i++){
			if(matriz[linha][i] > maior){ //Procura o maior valor
			maior = matriz[linha][i]; //Atualiza o maior valor
			}
		}
		for(i = 0; i < tamanho; i++){
			if(caminho[linha][i] != 1 && matriz[linha][i] == maior){
				printf("%d ",i); //Imprime os filhos do vertice
				caminho[linha][i] = 1; //Marca o caminho visitado
				ultimo = dfsfilho(matriz,caminho,tamanho,i);
			}
		}
	}
	return ultimo;
}

//Implementação do algoritmo
void ford(int tamanho, int **matriz, int **caminho){
	int i, j; //Contadores
	int fluxo;
	int fluxototal = 0;

	while((dfsfilho(matriz, caminho, tamanho, 0) == (tamanho-1))){ //Enquanto existir um caminho do vertice 0 ate o vertice (tamanho-1) fa�a:
		fluxo = 1000;
		//Procura o fluxo
		for(i = 0; i < tamanho; i++){
			for(j = 0; j < tamanho; j++){
					if(caminho[i][j] != 0 && matriz[i][j] < fluxo){ //Seleciona a menor a resta como fluxo
						fluxo = matriz[i][j];
					}
			}
		}
		printf("Fluxo: %d\n",fluxo); //Imprime o fluxo do caminho atual
		fluxototal +=fluxo; //Soma os fluxos
		
		//Relaxamento
		for(i = 0; i < tamanho; i++){
			for(j = 0; j < tamanho; j++){
				if(caminho[i][j] == 1){ //Procura o caminho percorido
						matriz[i][j] -= fluxo; //Desconta o valor do fluxo
						caminho[i][j] = 0; //Reinicia o caminho
				}
			}
		}
	}
	printf("Fluxo total: %d\n",fluxototal); //Imprime o fluxo total
	return;
}

int main() {    
    int i, j; // contadores
    int nv; // n de vertices
    int **m; // matriz do grafo
    int **c; // matriz do caminho, marca as arestas percoridas do vertice 0 ate o vertice n
    int u, v; // coordenadas
    int valor; //Valor da aresta
    FILE *arquivo; // arquivo
    arquivo = fopen("grafo.txt","r");
    
    fscanf(arquivo,"%d", &nv);
    m = (int**) malloc(sizeof(int*) * nv); // alocação
    c = (int**) malloc(sizeof(int*) * nv); // alocação
    
    for (i = 0; i < nv; i++) {
        m[i] = (int*) calloc(sizeof(int), nv);
        c[i] = (int*) calloc(sizeof(int), nv);
    }
	
	//Iniciando a matriz
    for (i = 0; i < nv; i++) {
        for (j = 0; j < nv; j++){
				m[i][j] = 0;
				c[i][j] = 0;
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
				ford(nv, m, c);
            return 0;
        } else {
            m[u][v] = valor;
        }
    }
    fclose(arquivo);
}
