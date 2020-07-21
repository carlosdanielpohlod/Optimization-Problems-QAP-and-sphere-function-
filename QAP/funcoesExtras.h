#include"const.h"
#include<stdbool.h>
#include<string.h>

void zerar(int individuo[]);

double RandomDouble(int a, int b)
{
    double r;
    r = (double) rand()/RAND_MAX;
    return (double)(a + r*(b-a));
} 

void salvarResultado(double valor){
    FILE *arquivo;
    arquivo = fopen("resultado","a");
    fprintf(arquivo,"%c", '\n');
    fprintf(arquivo,"%0.2f", valor);
    fclose(arquivo);
}
void exibirIndividuo(int individuo[]){
    printf("\n");
    for(int i = 0; i < TAMCROMOSSOMO; i ++)
        printf("%d ", individuo[i]);
    printf("\n");
}

void copia(int individuoCopiado[], int individuoCopia[]){
    for(int i = 0; i < TAMCROMOSSOMO; i ++)
        individuoCopia[i] = individuoCopiado[i];
}
void inserir(int receptor[], int copiado[]){
    for(int i = 0; i < TAMCROMOSSOMO; i++){
        
        receptor[i] = copiado[i];
    }
}
int buscarMelhor(int populacao[][TAMCROMOSSOMO]){
    int melhor = 0;
    for(int i = 0; i < TAMPOPULACAO; i ++){
        if(populacao[i][TAMCROMOSSOMO - 1] < populacao[melhor][i])
            melhor = i;
    }
    return melhor;
}
void mostrarMatriz(int matriz[][N]){
    for (int i = 0; i < N; i ++){
        printf("\n");
        for(int j = 0; j < N; j++){
            printf("%d ", matriz[i][j]);
        }
    }
}
bool jaExiste(int novoIndividuo[], int gene){
    for(int i = 0; i < N; i ++){
        if(novoIndividuo[i] == gene){
            return true;
        }        
    }
    return false;
}
void exibirPopulacao(int matriz[][TAMCROMOSSOMO]){
    for(int lin = 0; lin < TAMPOPULACAO ; lin ++){
        for(int col = 0; col < TAMCROMOSSOMO - 1; col ++){
            printf("%d ", matriz[lin][col]);
        }
        printf("| %d |",matriz[lin][TAMCROMOSSOMO - 1]);
        printf("\n");
    }

}

void ordenar(int matriz[][TAMCROMOSSOMO]){
    int aux[TAMCROMOSSOMO];
    
    for(int j = 0; j < NUMMAXIMOFILHOS + 2; j++){
        for(int i = 0; i < NUMMAXIMOFILHOS + 1; i ++){

            if(matriz[i][TAMCROMOSSOMO - 1] > matriz[i + 1][TAMCROMOSSOMO - 1] ){
                for(int k = 0; k < TAMCROMOSSOMO; k ++)
                    aux[k] = matriz[i][k];
                
                for(int k = 0; k < TAMCROMOSSOMO; k ++)
                    matriz[i][k] = matriz[i + 1][k];
                
                for(int k = 0; k < TAMCROMOSSOMO; k ++)
                    matriz[i + 1][k] = aux[k];
            }
        } 
    }   
}
void ordenarPopulacao(int populacao[][TAMCROMOSSOMO]){
    int aux[TAMCROMOSSOMO];
    
    for(int j = 0; j < TAMPOPULACAO; j++){
        for(int i = 0; i < TAMPOPULACAO - 1; i ++){

            if(populacao[i][TAMCROMOSSOMO - 1] > populacao[i + 1][TAMCROMOSSOMO - 1] ){
                for(int k = 0; k < TAMCROMOSSOMO; k ++)
                    aux[k] = populacao[i][k];
                
                for(int k = 0; k < TAMCROMOSSOMO; k ++)
                    populacao[i][k] = populacao[i + 1][k];
                
                for(int k = 0; k < TAMCROMOSSOMO; k ++)
                    populacao[i + 1][k] = aux[k];
            }
        } 
    }

}
void persistirMelhores(int matriz[][TAMCROMOSSOMO], int populacao[][TAMCROMOSSOMO], int pai01, int pai02){
    for(int i = 0; i < TAMCROMOSSOMO; i ++)
    {
        populacao[pai01][i] = matriz[0][i];
        populacao[pai02][i] = matriz[1][i];
    }
}
void zerar(int individuo[]){
    for(int i = 0; i < N; i ++){
        individuo[i] = TAMCROMOSSOMO + 3;
    }
}