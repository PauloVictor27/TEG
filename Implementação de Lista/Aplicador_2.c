#include <stdio.h>
#include <stdlib.h>
#include "Codificador.h"

int main() {
    int i; // contadores
    int nv; // n de vertices
    LDSE *vet; // matriz do grafo
    int u, v; // coordenadas
    FILE *arquivo; // arquivo
    arquivo = fopen("grafo.txt","r");

    //Leitura do n de vertices
    fscanf(arquivo,"%d", &nv);

    //Criacao da lista principal
    cria(&vet,sizeof(LDSE));


    //Criacao das listas
    for (i = 0; i < nv; i++) {
        LDSE *temp1;
        cria(&temp1,sizeof(int));
        insereNovoPrimeiro(vet,temp1);

    }

    //Leitura do arquivo
    while (fscanf(arquivo,"%d %d", &u, &v)&&u!=-1&&v!=-1) {
            LDSE temp2;
            buscaNaPosLog(vet,&temp2,u);
            insereNovoPrimeiro(&temp2,&v);
        }

        fclose(arquivo);

    //Impressao da lista
    printf("Numero de vertices: %d\n\n",nv);
    NoLDSE *aux;
    aux = vet->primeiro;
    int p = 1 ;
    while (aux != NULL) {
        printf("%d : ",p++);
        NoLDSE *aux2;
        aux2 = ((LDSE*)aux->dados)->primeiro;
        while (aux2 != NULL) {
                printf(" [%d]",*(int*)aux2->dados);
                aux2 = aux2->proximo;
         }
       printf(".\n");
       aux = aux->proximo;
    }
        return 0;
    }


