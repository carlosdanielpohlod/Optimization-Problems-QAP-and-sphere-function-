#include"const.h"
#include<stdbool.h>
#include<string.h>
#include"funcoesExtras.h"
// #include "randomlib.h"
void gerarPopulacao(int populacao[][TAMCROMOSSOMO]);
void selecaoComum(int populacao[][TAMCROMOSSOMO], int *pai01, int *pai02, int mediaPopulacao);

void avaliarIndividuo(int individuo[], int fluxo[][N], int distancias[][N]){;
    int fitness ;
  
    fitness = 0;
    // printf("%d", fitness);
    for(int i = 0; i < N; i ++){
        for(int j = 0; j < N ; j ++){
           
            fitness += distancias[i][j] * fluxo[ individuo[i] ] [individuo[j] ];
            // printf("fluxo -> %d e distancia -> %d [%d][%d]\n", fluxo[ individuo[i] ] [individuo[j] ], distancias[i][j],i,j);
        }
        
    }
    // printf("-> %d \n", fitness);
    individuo[TAMCROMOSSOMO - 1] = fitness;
}

void avaliarPopulacao(int populacao[][TAMCROMOSSOMO], int fluxo[][N], int distancias[][N], int *numAvaliacao){
    int fitness ;
    for (int individuo = 0; individuo < TAMPOPULACAO; individuo ++){
       avaliarIndividuo(populacao[individuo], fluxo, distancias);
       *numAvaliacao = *numAvaliacao + 1;
       
    }
}
void gerarPopulacao(int populacao[][TAMCROMOSSOMO]){
    int novoIndividuo[N];
    bool existe;
    int num;
    int individuo = 0;
    
    int locus = 0;

    for(individuo = 0; individuo < TAMPOPULACAO; individuo ++){
        zerar(novoIndividuo);
        while(locus < N){
            // printf("%d,", locus);

            num = rand()%N;
            existe = false;

            for (int i = 0; i < TAMCROMOSSOMO - 1; i++){
                if(novoIndividuo[i] == num){
                    existe = true;
                    break;
                }
                // printf("for"); 
            }
            if(existe == false){               
                novoIndividuo[locus] = num;   
                locus ++;      
                
            }
               
        }
        locus = 0;
        for(int j = 0; j < TAMCROMOSSOMO - 1; j ++){
            populacao[individuo][j] = novoIndividuo[j];
        }
        populacao[individuo][TAMCROMOSSOMO - 1] = 0;
    }    
    
}



void mutar(int individuo[]){
    int locus01 = rand()%N;
    int locus02 = rand()%N;
    int aux = 0;
    while(locus01 == locus02){
        locus02 = rand()%N;
    }
    aux = individuo[locus01];
    individuo[locus01] = individuo[locus02];
    individuo[locus02] = aux;
}
bool chanceMutar(){
    int mutar = rand()%100;
    if(mutar <= PORCENTAGEMMUTACOES){
        
        return true;
    }else{
        
        return false;
    }
}
bool chanceReproduzir(){
    int chance = rand()%100;
    if(chance <= PORCENTAGEMREPRODUCOES)
        return true;
    else 
        return false;
}
void reproduzir(int populacao[][TAMCROMOSSOMO], int fluxo[][N], int distancias[][N],int pai01, int pai02, int *numAvaliacao){
    int escolhido = 0;
    int novoIndividuo[N];
    int genePassado = 0;
    int listaAuxiliar[NUMMAXIMOFILHOS + 2][TAMCROMOSSOMO];
    int contadorAuxiliar = 0;

   
    inserir(listaAuxiliar[contadorAuxiliar], populacao[pai01]); 
    contadorAuxiliar ++;
    inserir(listaAuxiliar[contadorAuxiliar], populacao[pai02]); 
    
   
    for (int filho = 0; filho < NUMMAXIMOFILHOS; filho ++){
        contadorAuxiliar ++;
        genePassado = 0;
        escolhido = 0;
        zerar(novoIndividuo);

        for (int i = 0; i < N; i++){
            escolhido = rand()%2;
            genePassado = rand()%N;

            if(escolhido == 0){
                while(jaExiste(novoIndividuo, populacao[pai01][genePassado]))
                    genePassado = rand()%N;
                
                novoIndividuo[i] = populacao[pai01][genePassado];
            }else{
                while(jaExiste(novoIndividuo, populacao[pai02][genePassado])){
                    genePassado = rand()%N;
                }
                    novoIndividuo[i] = populacao[pai02][genePassado];
            }
        }
        if(chanceMutar())
            mutar(novoIndividuo);

        avaliarIndividuo(novoIndividuo, fluxo, distancias);
        *numAvaliacao = *numAvaliacao + 1;
        
        inserir(listaAuxiliar[contadorAuxiliar], novoIndividuo); 
        
    }
    
    ordenar(listaAuxiliar);
    persistirMelhores(listaAuxiliar, populacao, pai01, pai02);
    // printf("Melhores %d e %d ", populacao[pai01][TAMCROMOSSOMO - 1], populacao[pai02][TAMCROMOSSOMO - 1]);
       
}
int somatorioFitnessPopulacao(int populacao[][TAMCROMOSSOMO]){
    int somatorio = 0;
    for(int i = 0; i < TAMPOPULACAO; i ++)
        somatorio += populacao[i][TAMCROMOSSOMO - 1];
    return somatorio;
}
void escolherPais(int *pai01, int*pai02, int populacao[][TAMCROMOSSOMO]){
    double mediaHabilidade;
    double mediaPais = 0;
    double minimoAceitavel = 0;
    double mediaPopulacao = 0;
    double somatorioPopulacao = 0;
    bool encontrado = false;
    int antiCrash = 0;
    *pai01 = rand()%TAMPOPULACAO;
    *pai02 = rand()%TAMPOPULACAO;
    while(*pai01 == *pai02){
        *pai01 = rand()%TAMPOPULACAO ;
        *pai02 = rand()%TAMPOPULACAO ;
    }
    // printf("Fiteness pai 01 (%d) : %d \n",*pai01, populacao[*pai01][TAMCROMOSSOMO - 1]);
    // printf("Fiteness pai 02 (%d): %d \n", *pai02, populacao[*pai02][TAMCROMOSSOMO - 1]);
    
    somatorioPopulacao = (double)(somatorioFitnessPopulacao(populacao));
    mediaPopulacao = (somatorioPopulacao / TAMPOPULACAO);
    // printf("media populacao %f \n", mediaPopulacao);

    while(!encontrado){
        if(antiCrash == TAMPOPULACAO * 3)
            selecaoComum(populacao, pai01, pai02, mediaPopulacao);
        antiCrash++;
        
        if(populacao[*pai01][TAMCROMOSSOMO - 1] <= mediaPopulacao)
        {
            while((populacao[*pai02][TAMCROMOSSOMO - 1] <= mediaPopulacao) || (*pai01 == *pai02)){
                *pai02 = rand()%TAMPOPULACAO;
            }
            encontrado = true;
        }else{
            if(populacao[*pai02][TAMCROMOSSOMO - 1] <= mediaPopulacao){
                while( (populacao[*pai01][TAMCROMOSSOMO - 1] <= mediaPopulacao)|| (*pai01 == *pai02)){
                    *pai02 = rand()%TAMPOPULACAO;
                }
                encontrado = true;
            }
        }
    }
       
      
    // printf("Média Populacao %f\n", mediaPopulacao);
    // printf("Fitness pais escolhidos : %d e %d \n", populacao[*pai01][TAMCROMOSSOMO - 1], populacao[*pai02][TAMCROMOSSOMO - 1]);
}
void selecaoComum(int populacao[][TAMCROMOSSOMO], int *pai01, int *pai02, int mediaPopulacao){
    // printf("Seleção comum");
    for(int i = 0; i < TAMPOPULACAO; i ++){
        if(populacao[i][TAMCROMOSSOMO - 1] >= mediaPopulacao){
            *pai01 = i;
            break;
        }
    }
    for(int i = 0; i < TAMPOPULACAO; i ++){
        if(populacao[i][TAMCROMOSSOMO - 1] < mediaPopulacao){
            *pai02 = i;
            break;
        }
    }
}
void buscaLocal(int individuo[TAMCROMOSSOMO], int fluxo[][N],int distancias[][N], int *numAvaliacao){
    int copiaIndividuo[TAMCROMOSSOMO];
    int aux2,aux = 0;
    int fitness=0;
    int auxilioFitness = 0;
    int fitnessInicialIndividuo = individuo[TAMCROMOSSOMO - 1];
    int tempoBuscaLocal =  (TAMCROMOSSOMO) * MAXIMAPCTBUSCA;
    int evolucaoRequerida = 0;
    avaliarIndividuo(individuo, fluxo, distancias);
    *numAvaliacao = *numAvaliacao + 1;
    
    // printf("Tempo de busca local : %d \n",  tempoBuscaLocal);
    

    for (int i= 0; i < TAMCROMOSSOMO - 1; i ++){
       
        
        fitness = individuo[TAMCROMOSSOMO - 1];
        for (int j = 0; j < TAMCROMOSSOMO - 1; j ++){
            
            if(i != j){
                // printf("\n.................. : \n");
                // printf("Individuo atual : \n");
                // exibirIndividuo(individuo);
                // printf(".................. : \n");
                aux = individuo[i];
                
                individuo[i] = individuo[j];
                
               
                individuo[j] = aux;
                auxilioFitness = individuo[TAMCROMOSSOMO - 1];
               
                avaliarIndividuo(individuo, fluxo, distancias);
                *numAvaliacao = *numAvaliacao + 1;
                
                if(individuo[TAMCROMOSSOMO - 1] > fitness){
                 
                    aux2 = individuo[j];
                    individuo[j] = individuo[i];
  
                    
                    individuo[i] = aux2;
                    individuo[TAMCROMOSSOMO - 1] = auxilioFitness;
                    
                 }else{
                    //  printf("\n.......................Trocado de posicao:.......................... \n ");
                    //  exibirIndividuo(individuo);
                    //  printf(" ................... ................................................................");
                      fitness = individuo[TAMCROMOSSOMO - 1];
                     
                    
                }
            }
        }

        if(tempoBuscaLocal == i){
            
            evolucaoRequerida = individuo[TAMCROMOSSOMO - 1] * EVMA;
            
            if(individuo[TAMCROMOSSOMO - 1] > (fitnessInicialIndividuo - evolucaoRequerida)){
                printf("Evolucao requerida: %d individuo = %d \n",fitnessInicialIndividuo - evolucaoRequerida, individuo[TAMCROMOSSOMO - 1]);
                printf("Busca parada por nao melhoria \n");
                break; // senao houve, interromper processo
            }
        }

    }
    // printf("sai");
    // printf("\nResultado final: \n");
    
    // exibirIndividuo(individuo);
}