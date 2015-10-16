#include <stdio.h>
#include <stdlib.h>
#include "Descritor.h"

void floyd(Rua **matriz, int tamanho){
	int k, i, j; //Contadores
	Rua ***novamatriz; //Matriz tridimencional [k][i][j] para guardar as matrizes do floyd
	
	//Alocação nos 3 niveis
	novamatriz = (Rua***) malloc(sizeof(Rua**) * tamanho);
    for (i = 0; i < tamanho; i++) {
        novamatriz[i] = (Rua**) calloc(sizeof(Rua*), tamanho);
    } 
    for (i = 0; i < tamanho; i++) {
        for (j = 0; j < tamanho; j++){
				novamatriz[i][j] = (Rua*) calloc(sizeof(Rua), tamanho);
			}
    }
    
    //Inicializando a primeira matriz
    for (i = 0; i < tamanho; i++) {
        for (j = 0; j < tamanho; j++){
				//Iniciando a distancia
				if((matriz[i][j].distancia < matriz[i][0].distancia + matriz[0][j].distancia) && (matriz[i][0].distancia != 1000 && matriz[0][j].distancia != 1000)){ // D[k-1][i][j] < D[k-1][i][k] + D[k-1][k][j]
					novamatriz[0][i][j].distancia = matriz[i][j].distancia;
				} else if((matriz[i][j].distancia > matriz[i][0].distancia + matriz[0][j].distancia) && (matriz[i][0].distancia != 1000 && matriz[0][j].distancia != 1000)) { // D[k-1][i][j] > D[k-1][i][k] + D[k-1][k][j]
					novamatriz[0][i][j].distancia = matriz[i][0].distancia + matriz[0][j].distancia;
				} else{ // D[k-1][i][j] == D[k-1][i][k] + D[k-1][k][j]
					novamatriz[0][i][j].distancia = matriz[i][j].distancia;
				}
				//Iniciando o tempo
				if((matriz[i][j].tempo < matriz[i][0].tempo + matriz[0][j].tempo) && (matriz[i][0].tempo != 1000 && matriz[0][j].tempo != 1000)){ // D[k-1][i][j] < D[k-1][i][k] + D[k-1][k][j]
					novamatriz[0][i][j].tempo = matriz[i][j].tempo;
				} else if((matriz[i][j].tempo > matriz[i][0].tempo + matriz[0][j].tempo) && (matriz[i][0].tempo != 1000 && matriz[0][j].tempo != 1000)) { // D[k-1][i][j] > D[k-1][i][k] + D[k-1][k][j]
					novamatriz[0][i][j].tempo = matriz[i][0].tempo + matriz[0][j].tempo;
				} else{ // D[k-1][i][j] == D[k-1][i][k] + D[k-1][k][j]
					novamatriz[0][i][j].tempo = matriz[i][j].tempo;
				}
			}
    }
    
    //Criando as matrizes
	for (k = 1; k < tamanho; k++){
		for (i = 0; i < tamanho; i++){
			for (j = 0; j < tamanho; j++){
				//Condições basicas: as coordenadas [i][k] e [k][j] precisam ser diferentes de infinito (1000)
				//Distancia
				if((novamatriz[k-1][i][j].distancia < novamatriz[k-1][i][k].distancia + novamatriz[k-1][k][j].distancia) && (novamatriz[k-1][i][k].distancia != 1000 && novamatriz[k-1][k][j].distancia != 1000)){ // D[k-1][i][j] < D[k-1][i][k] + D[k-1][k][j]
					novamatriz[k][i][j].distancia = novamatriz[k-1][i][j].distancia;
				} else if((novamatriz[k-1][i][j].distancia > novamatriz[k-1][i][k].distancia + novamatriz[k-1][k][j].distancia) && (novamatriz[k-1][i][k].distancia != 1000 && novamatriz[k-1][k][j].distancia != 1000)) { // D[k-1][i][j] > D[k-1][i][k] + D[k-1][k][j]
					novamatriz[k][i][j].distancia = novamatriz[k-1][i][k].distancia + novamatriz[k-1][k][j].distancia;
				} else{ // D[k-1][i][j] == D[k-1][i][k] + D[k-1][k][j]
					novamatriz[k][i][j].distancia = novamatriz[k-1][i][j].distancia;
				}
				//Tempo
				if((novamatriz[k-1][i][j].tempo < novamatriz[k-1][i][k].tempo + novamatriz[k-1][k][j].tempo) && (novamatriz[k-1][i][k].tempo != 1000 && novamatriz[k-1][k][j].tempo != 1000)){ // D[k-1][i][j] < D[k-1][i][k] + D[k-1][k][j]
					novamatriz[k][i][j].tempo = novamatriz[k-1][i][j].tempo;
				} else if((novamatriz[k-1][i][j].tempo > novamatriz[k-1][i][k].tempo + novamatriz[k-1][k][j].tempo) && (novamatriz[k-1][i][k].tempo != 1000 && novamatriz[k-1][k][j].tempo != 1000)) { // D[k-1][i][j] > D[k-1][i][k] + D[k-1][k][j]
					novamatriz[k][i][j].tempo = novamatriz[k-1][i][k].tempo + novamatriz[k-1][k][j].tempo;
				} else{ // D[k-1][i][j] == D[k-1][i][k] + D[k-1][k][j]
					novamatriz[k][i][j].tempo = novamatriz[k-1][i][j].tempo;
				}
			}
		}
	}
	
	//Imprimindo as matrizes
	for (k = 1; k < tamanho; k++){
		for (i = 0; i < tamanho; i++){
			printf(" %d: ",i);
			for (j = 0; j < tamanho; j++){
					printf("[%d,%d] ", novamatriz[k][i][j].distancia, novamatriz[k][i][j].tempo);
			}
			printf("\n");
		}
		printf("\n");
	}
	
	//Atualizando a matriz original com a ultima matriz criada
	for (i = 0; i < tamanho; i++){
			for (j = 0; j < tamanho; j++){
				matriz[i][j].distancia = novamatriz[tamanho-1][i][j].distancia;
				matriz[i][j].tempo = novamatriz[tamanho-1][i][j].tempo;
			}
		}
	}
