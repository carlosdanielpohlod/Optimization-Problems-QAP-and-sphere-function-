#include<stdio.h>
#include<stdlib.h>
#include"funcoes.h"
#include<time.h>
#include"const.h"

void lerDistancias(FILE *arquivo, int fluxo[][N]){
    for(int i = 0; i < 12; i++){
        for(int j = 0; j < 12; j ++){
            fscanf(arquivo,"%d", &fluxo[i][j]);
        }
    }
}
void lerFluxo(FILE *arquivo, int distancias[][N]){
    while(!feof(arquivo)){
        for(int i = 0; i < 12; i++){
            for(int j = 0; j < 12; j ++){
                fscanf(arquivo,"%d", &distancias[i][j]);
            }
        }
    }
}
int main (){
    srand(time(NULL));
    FILE *arquivo;
    arquivo = fopen("nug12.dat", "r");
    int fluxo[N][N] = {0};
    int distancias[N][N] = {0};
    int populacao[TAMPOPULACAO][TAMCROMOSSOMO];
    int pai01 = 8;
    int pai02 = 0;
    int melhor = 0;
    int numAvaliacao = 0;
    lerDistancias(arquivo, distancias);
    lerFluxo(arquivo, fluxo);
    gerarPopulacao(populacao);
    
    
    avaliarPopulacao(populacao, fluxo, distancias, &numAvaliacao);
    // ordenarPopulacao(populacao);
    // exibirPopulacao(populacao);

    
    for(int indice = 0; (numAvaliacao < MAXAVALIACOES) && (indice < (TAMCROMOSSOMO * TAMPOPULACAO * 1000)); indice ++){
        
        escolherPais(&pai01, &pai02, populacao);
        if(chanceReproduzir()){
            
            reproduzir(populacao, fluxo, distancias, pai01, pai02, &numAvaliacao);
        }
        melhor = rand()%TAMPOPULACAO;
        buscaLocal(populacao[melhor], fluxo, distancias, &numAvaliacao);
    }
   
    printf("%d\n", numAvaliacao);

    // ordenarPopulacao(populacao);
    // exibirPopulacao(populacao);

    melhor = buscarMelhor(populacao);
    
    salvarResultado(populacao[melhor][TAMCROMOSSOMO - 1]);
    system("pause");
    fclose(arquivo);
    
}