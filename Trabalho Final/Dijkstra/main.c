#include <stdio.h>
#include <stdlib.h>

//Implementação do algoritmo
void dijkstra(int *vetorvisita, int *vetordistancia, int tamanho, int **matriz){
	int i; //Contador
	int m = 0; //Marcador
	int cont = 0; //Contador de busca
	int vertice_atual = 0; //Vertice para o percurso, começando em 0
	
	//Iniciando os vetores de distancia e de visita
	for(i = 0; i < tamanho; i++){
		vetordistancia[i] = 1000000; //1000000 = infinito
		vetorvisita[i] = 0; //0 = não visitado
	}
	
	//Primeira inserção
	vetordistancia[0] = 0; //De 0 pra 0 a distancia é 0
	vetorvisita[0] = 1; //1 = visitado
	
	//Encando o while for diferente do numero de vertices, ou seja, enquanto o vertice atual não tiver percorido todos os vertices
	while (cont != tamanho){
		printf("Processando %d:\n",vertice_atual); //Mostra qual vertice esta sendo usado
		int menor = 1000000; //Menor distancia dos vertices visitados
		
		//Percuso para procurar o menor caminho
		for (i = 0; i < tamanho; i++){
			if(matriz[vertice_atual][i] != 0){ //Se é diferente de zero, significa que existe uma aresta de tal valor entre o vertice atual e o vertice visitado 				
				int distancia_calculada = matriz[vertice_atual][i] + vetordistancia[vertice_atual]; //Somas as distancias as arestas
				if(distancia_calculada < vetordistancia[i]){
					vetordistancia[i] = distancia_calculada; //Relaxamento
				}			
			}
		}
		
		//Percuso para procurar proximo vertice
		for (i = 0; i < tamanho; i++){
			if(vetorvisita[i] != 1 && vetordistancia[i] < menor){ //Se o vertice ainda não visitado e sua distancia é a menor de todas os que não foram visitados			
				menor = vetordistancia[i]; //Salva a menor distancia atual
				m = i;	//Salva a possição da distancia
			}
		}
		vertice_atual = m;  //Atualiza o vertice
		vetorvisita[m] = 1; //Marca o vertice como visitado
		cont +=1; //O cont recebe um emcremento ate chegar na sua condição de parada (cont = tamanho), ou seja, ate visitar todos os vertices 
	}
	
	printf("\n");
	
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
    int *dis; //Vetor de distancias
    int *vis; //Vetor de visitas
    int u, v; // coordenadas
    int valor;
    FILE *arquivo; // arquivo
    arquivo = fopen("grafo1.txt","r");
    
    fscanf(arquivo,"%d", &nv);
    m = (int**) malloc(sizeof(int*) * nv); // alocação
    dis = (int*) calloc(nv,sizeof(int)); // alocação
    vis = (int*) calloc(nv,sizeof(int)); // alocação
    
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
			dijkstra(vis, dis, nv, m);
            return 0;
        } else {
            m[u][v] = valor;
        }
    }
    fclose(arquivo);
}
