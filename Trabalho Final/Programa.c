#include <stdio.h>
#include <stdlib.h>
#include "Floyd.c"

int main() {    
    int i, j; // contadores
    int ne; // n de esquinas (vertices)
    int nr; //n de ruas (arestas)
    Rua **r; // matriz do grafo de ruas
    int u, v; // coordenadas
    int ei, ef; //esquina inicial e esquina final

	//Leitura do numero de esquinas
	printf("Digite o numero de esquinas:\n");
	scanf("%d",&ne);
	printf("\n");
	
	//Alocação da matriz de ruas conforme o numero de esquinas
    r = (Rua**) malloc(sizeof(Rua*) * ne); 
    for (i = 0; i < ne; i++) {
        r[i] = (Rua*) calloc(sizeof(Rua), ne);
    }
    
    //Iniciando a matriz
    for (i = 0; i < ne; i++) {
        for (j = 0; j < ne; j++){
			if (i == j){
				r[i][j].distancia = 0;
				r[i][j].tempo = 0;
			}else{
				r[i][j].distancia = 1000;
				r[i][j].tempo = 1000;
				//1000 = infinito
				}
			}
    }
    
    //Leitura da esquina inicial, esquina final e o numero de ruas
    printf("Digite a esquina inicial, a esquina final e o numero de ruas:\n");
	scanf("%d %d %d",&ei, &ef, &nr);
	printf("\n");
	
	//Leitura das esquinas que compoe a rua e sua distancia e tempo, a leitura se repete conforme o numero de ruas dado
	for(i = 0; i < nr; i++){
		printf("Digite as esquinas da rua %d\n",(i+1));
		scanf("%d %d",&u, &v);
		printf("\n");
		printf("Digite a distancia e o tempo da rua %d\n",(i+1)); 
		scanf("%d %d",&r[u][v].distancia, &r[u][v].tempo); //Preenchimento da matriz de ruas 
		printf("\n");
	}
	
	//Imprimindo a matriz de ruas original
	printf("Matriz original:\n");
	for (i = 0; i < ne; i++) {
		printf(" %d: ",i);
        for (j = 0; j < ne; j++){
				printf("[%d,%d] ", r[i][j].distancia, r[i][j].tempo);
		}
		printf("\n");
    }
    printf("\n\n");
    
    //Aplicando o algoritmo de Floyd em distancia e tempo
    printf("Matrizes com floyd:\n");
    floyd(r,ne);
    
    printf("\n");
    printf("Menor distancia total de %d a %d: %d\n", ei, ef, r[ei][ef].distancia);
    printf("Menor tempo total de %d a %d: %d\n",ei, ef, r[ei][ef].tempo);
     
return 0;
}
