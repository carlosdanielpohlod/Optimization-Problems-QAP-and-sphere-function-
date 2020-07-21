#include "const.h"
// #include "randomlib.h"
#include <stdbool.h>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void bubbleSort(double Populacao[][CROMOSSOMO]);
void substituirIndividuo(double individuoSubstituido[], double individuoPassado[][CROMOSSOMO],  int individuo);
void copia(double a[CROMOSSOMO], double b[CROMOSSOMO]){
    for (int i = 0; i < CROMOSSOMO; i++)
        a[i] = b[i];
}

double RandomDouble(int a, int b)
{
    double r;
    r = (double) rand()/RAND_MAX;
    return (double)(a + r*(b-a));
}      
   
void exibirMelhores(double Populacao[][CROMOSSOMO]){
    printf("\n\n\n %d Melhores Individuos : \n\n", NUMMELHORES);
    bubbleSort(Populacao);
    int j;
     for(int i = 0; i < NUMMELHORES ; i ++){
        printf("|%d|\t",i);

        for( j = 0; j < CROMOSSOMO -1; j ++){
            printf("%0.2f \t", Populacao[i][j]);
        }
        printf("| %f | \t", Populacao[i][j]);
        printf("\n");
    }
}

void exibeBest(double Populacao[][CROMOSSOMO]){
    bubbleSort(Populacao);
    
    
    printf("%0.2f \n", Populacao[0][CROMOSSOMO - 1]);
}
int encontrarMelhor(double Populacao[][CROMOSSOMO]){
    int best = 0;
    for(int i = 0; i < NUMINDIVIDUO; i++){
        if(Populacao[best][CROMOSSOMO - 1]> Populacao[i][CROMOSSOMO - 1]){
            best = i;
        }

    }
    return best;
}
void salvarResultado(double valor){
    FILE *arquivo;
    arquivo = fopen("resultado","a");
    fprintf(arquivo,"%c", '\n');
    fprintf(arquivo,"%0.2f", valor);
    fclose(arquivo);
}
void exibirPopulacao(double Populacao[][CROMOSSOMO]){
    for(int i = 0; i < NUMINDIVIDUO; i ++){
        printf("|%d|\t",i);
        for(int j = 0; j < CROMOSSOMO ; j ++){
            printf("%0.2f \t", Populacao[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
}
void bubbleSort(double Populacao[][CROMOSSOMO]){
    double aux[CROMOSSOMO];
    for(int j = 0; j < NUMINDIVIDUO; j++){
        for(int i = 0; i < NUMINDIVIDUO - 1; i ++){

            if(Populacao[i][CROMOSSOMO - 1] > Populacao[i + 1][CROMOSSOMO - 1] ){
                for(int k = 0; k < CROMOSSOMO; k ++)
                    aux[k] = Populacao[i][k];
                
                for(int k = 0; k < CROMOSSOMO; k ++)
                    Populacao[i][k] = Populacao[i + 1][k];
                
                for(int k = 0; k < CROMOSSOMO; k ++)
                    Populacao[i + 1][k] = aux[k];
            }
        } 
    }   
}
void substituirIndividuo(double individuoSubstituido[], double individuoPassado[][CROMOSSOMO],  int individuo){

    for(int i = 0; i < CROMOSSOMO; i ++){
        individuoPassado[individuo][i] = individuoSubstituido[i];
    }

}
void Pausar(){
  char vazio;
  scanf("%c", &vazio);
}