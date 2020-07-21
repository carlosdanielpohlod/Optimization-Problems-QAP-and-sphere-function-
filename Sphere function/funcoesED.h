#include "funcoesExtras.h"


//PC = probabilistic Crowding
// void avaliaIndividuo(double Individuo[]);
void avaliaPopulacao(double Populacao[][CROMOSSOMO], int *numAvaliacoes);
double CalcularSomatorio(double Populacao[][CROMOSSOMO]);
double PC(double Populacao[][CROMOSSOMO], int a, double Individuo[]);
void carregarVetor(double Populacao[][CROMOSSOMO]);
void cruzamentoBinomial(double Populacao[][CROMOSSOMO],int alvo, double experimental[], int *numAvaliacoes);
// void cruzamentoExponencial (double populacao[][CROMOSSOMO], int pai, double experimental[]);
void comumO2(double Populacao[][CROMOSSOMO], int best, double experimental[]);
void rand01(double Populacao[][CROMOSSOMO], int alvo, double experimental[], int *numAvaliacoes);
void comumO1(double Populacao[][CROMOSSOMO], int best, double experimental[], int *numAvaliacoes);
void operadorBuscaLocal(double Populacao[][CROMOSSOMO], int individuo, int *numAvaliacoes);
void bin02(double Populacao[][CROMOSSOMO], int best, double experimental[], int *numAvaliacoes);


void avaliaIndividuo(double Individuo[]){
    double quadrado = 0.00, somatorio = 0.00;
     Individuo[CROMOSSOMO - 1] = 0;
     
    for(int i = 0; i < CROMOSSOMO - 1; i ++){
            quadrado = pow(Individuo[i],2);
            somatorio += quadrado;
    }
        Individuo[CROMOSSOMO - 1] = somatorio;
}

double CalcularSomatorio(double Populacao[][CROMOSSOMO]){
    double somatorioFitness = 0;
    for(int i = 0; i < NUMINDIVIDUO; i ++)
        somatorioFitness += Populacao[i][CROMOSSOMO - 1];
    return somatorioFitness;
}

double PC(double Populacao[][CROMOSSOMO], int a, double Individuo[]){
    //probabilistic Crowding
    return ( Populacao[a][CROMOSSOMO - 1] + Individuo[CROMOSSOMO - 1] ) / Individuo[CROMOSSOMO - 1];
}

void avaliaPopulacao(double Populacao[][CROMOSSOMO], int *numAvaliacoes){
    double somatorio = 0.00,  quadrado = 0.00;

    for(int j = 0; j < NUMINDIVIDUO; j ++){
        *numAvaliacoes = *numAvaliacoes + 1;
        for(int i = 0; i < CROMOSSOMO - 1; i ++){
            quadrado = pow(Populacao[j][i],2);
            somatorio += quadrado;
        }
        Populacao[j][CROMOSSOMO - 1] = somatorio;
        somatorio = 0.00;
        quadrado = 0.00;
    }
}




void carregarVetor(double Populacao[][CROMOSSOMO]){
     double aux = 6.00;

    for(int j = 0; j < NUMINDIVIDUO; j++){
        for(int i = 0; i < CROMOSSOMO - 1; i ++){

            aux = RandomDouble(MIN, MAX);

            Populacao[j][i] = aux ;
            Populacao[j][CROMOSSOMO - 1] = 0;
       
        }
    }
}


void cruzamentoBinomial(double Populacao[][CROMOSSOMO],int alvo, double experimental[],int *numAvaliacoes){
    double novoIndividuo[CROMOSSOMO];
    int genePassado = 0;
    double intercalar;
    double roleta, somatorio;
    double pc;
    for(int i = 0; i < CROMOSSOMO - 1; i++){
        intercalar = RandomDouble(0, 1);
        if(intercalar > CR)
             novoIndividuo[i] = Populacao[alvo][i];
        else
            novoIndividuo[i] = experimental[i];
    }
    avaliaIndividuo(novoIndividuo);
    *numAvaliacoes = *numAvaliacoes + 1;  
         
        // pc =  PC(Populacao, alvo, novoIndividuo);
        
        // somatorio = Populacao[alvo][CROMOSSOMO - 1] + novoIndividuo[CROMOSSOMO - 1];
        // roleta = RandomDouble(0, somatorio);
        
        // if(pc <= roleta){
        //     for(int i = 0; i < CROMOSSOMO; i ++)
        //         Populacao[alvo][i] = novoIndividuo[i];
        // }  


        // printf("pc %0.2f roleta %0.2f\n", pc, roleta);
    if(novoIndividuo[CROMOSSOMO - 1] < Populacao[alvo][CROMOSSOMO - 1]){
         for(int i = 0; i < CROMOSSOMO; i ++)
             Populacao[alvo][i] = novoIndividuo[i];
    }            
    

}

    
// void cruzamentoExponencial (double populacao[][CROMOSSOMO], int pai, double experimental[]){
// //Implementado juntamente com PC


//     double individuo[CROMOSSOMO] = {VAZIO};
     
//     int locusInicial = rand ()% CROMOSSOMO - 2, genesPreenchidos = 0;
//     int controladorPosicoes = locusInicial;
//     int constCruzamento = 0;
//     double roleta, somatorio;
//     double pc;

//         while( genesPreenchidos <= CROMOSSOMO - 2 )  {
        
//             while((constCruzamento <= CR2) && ( genesPreenchidos <= CROMOSSOMO - 2 )){
               
//                 if(controladorPosicoes == CROMOSSOMO - 1)
//                     controladorPosicoes = 0;
                
//                 if((individuo[controladorPosicoes] == VAZIO) && ( genesPreenchidos <= CROMOSSOMO - 2 )){
//                     individuo[controladorPosicoes] = experimental[controladorPosicoes];
//                     constCruzamento = rand()%100;
//                     genesPreenchidos ++;
//                 }
//                 controladorPosicoes ++;
                
                 
//             }
            
//             while(( constCruzamento > CR2) && (genesPreenchidos <= CROMOSSOMO - 2)) {
             
//                 if(controladorPosicoes == CROMOSSOMO - 1)
//                     controladorPosicoes = 0;

//                 if((individuo[controladorPosicoes] == 9.0) && (genesPreenchidos <= CROMOSSOMO - 2)){
//                     individuo[controladorPosicoes] = populacao[pai][controladorPosicoes];
//                     genesPreenchidos ++;
//                     constCruzamento = rand() % 100;
//                 }
//                  controladorPosicoes ++;
//             }
            
           
//         }
    
        
//         avaliaIndividuo(individuo);
      
// ///////////////////////////////////////////Substituir individuo
//         // printf("Cheguei antes do PC \n");
//         pc =  PC(populacao, pai, individuo);
//         // printf("PC\n");
//         somatorio = CalcularSomatorio(populacao);
//         roleta = RandomDouble(0, somatorio);

//         if(pc < roleta){
//             for(int i = 0; i < CROMOSSOMO; i ++)
//                 populacao[pai][i] = individuo[i];
//         }

        

// }

void operadorBuscaLocal(double Populacao[][CROMOSSOMO], int individuo, int *numAvaliacoes){
   int locus = 0;
    int tempoBuscaLocal = (CROMOSSOMO * MAXIMAPCTBUSCA);
    //printf("busca local maxima %d \n", tempoBuscaLocal);
    double individuoTrabalhado[CROMOSSOMO];
    double soma[CROMOSSOMO];
    double subtracao[CROMOSSOMO];
    bool parar = false;
    copia(individuoTrabalhado, Populacao[individuo]);
    
    while((locus <= CROMOSSOMO - 1) && (parar == false)){
        copia(soma, individuoTrabalhado);
        copia(subtracao, individuoTrabalhado);
        // printf("%d\n", locus);
        soma[locus] = individuoTrabalhado[locus] + PORCENMUDANCA;
        subtracao[locus] = individuoTrabalhado[locus] - PORCENMUDANCA;
        avaliaIndividuo(soma);
        *numAvaliacoes = *numAvaliacoes + 1;  
        avaliaIndividuo(subtracao);
        *numAvaliacoes = *numAvaliacoes + 1;  
        // printf("Fitness da soma %0.2f subtracao %0.2f \n", soma[CROMOSSOMO - 1], subtracao[CROMOSSOMO - 1]);
        if( ( soma[CROMOSSOMO - 1] < individuoTrabalhado[CROMOSSOMO - 1] ) || ( subtracao[CROMOSSOMO - 1] < individuoTrabalhado[CROMOSSOMO - 1] )){
            if((soma[locus] >= MIN) && (soma[locus]<= MAX)){
                if(( soma[CROMOSSOMO - 1] < subtracao[CROMOSSOMO - 1]) && (subtracao[locus] >= MIN) && (subtracao[locus]<= MAX)) {
                    copia(individuoTrabalhado, soma); // (x = y)
                    // printf("Substitui a soma \n");
                }
                else{
                    if( (subtracao[locus] < MIN) && (subtracao[locus] > MAX) && (soma[CROMOSSOMO - 1]) < individuoTrabalhado[CROMOSSOMO - 1] ) {
                        copia(individuoTrabalhado, soma);
                        // printf("Substitui a soma \n");
                    }
                }                    
            }
            
            if( (subtracao[locus] >= MIN) && (subtracao[locus]<= MAX)) { 
                if(( subtracao[CROMOSSOMO - 1] < soma[CROMOSSOMO - 1]) && (soma[locus] >= MIN) && (soma[locus]<= MAX)) {
                    copia(individuoTrabalhado, subtracao); // (x = y)
                    // printf("Substitui a subtração \n");
                }
                else{
                    if( (soma[locus] < MIN) && (soma[locus] > MAX) && (subtracao[CROMOSSOMO - 1]) < individuoTrabalhado[CROMOSSOMO - 1] ) {
                        copia(individuoTrabalhado, subtracao);
                        // printf("Substitui a subtração \n");
                    }
                }  
            }
            // system("pause");
        }
        locus ++;
        
            
        
        if(locus == tempoBuscaLocal){ //verificar se houve evolução significativa apos certo tempo
            double evolucaoRequirida = 0;
            evolucaoRequirida = Populacao[individuo][CROMOSSOMO - 1] * EVMA;
            if(individuoTrabalhado[CROMOSSOMO - 1] > (Populacao[individuo][CROMOSSOMO - 1] - evolucaoRequirida))
               {
                    parar = true; // senao houve, interromper processo
                    // printf("Requerido %0.2f total %0.2f",Populacao[individuo][CROMOSSOMO - 1] - evolucaoRequirida, individuoTrabalhado[CROMOSSOMO - 1] );
               }
        }        
        
    }         
    avaliaIndividuo(individuoTrabalhado);
    *numAvaliacoes = *numAvaliacoes + 1;  
    // printf("\nAntes\n");
    // for(int i = 0; i < CROMOSSOMO; i++)
    //     printf("%0.2f ", Populacao[individuo][i]);
    // printf("Depois\n");
    // for(int i = 0; i < CROMOSSOMO; i++)
    //     printf("%0.2f ", individuoTrabalhado[i]);
    // printf("\n\n");
    
        for(int i = 0; i < CROMOSSOMO; i++)
            Populacao[individuo][i] = individuoTrabalhado[i];
    
}
void rand01(double Populacao[][CROMOSSOMO], int alvo, double experimental[], int *numAvaliacoes){
    int aleatorio01 = 0, aleatorio02 = 0;
    double aux = 0;
    aleatorio01 = rand() % NUMINDIVIDUO;
    while(aleatorio01 == alvo)
        aleatorio01 = rand() % NUMINDIVIDUO;

    aleatorio02 = rand() % NUMINDIVIDUO;
    while( (aleatorio01 == aleatorio02) || (aleatorio02 == alvo) )
        aleatorio02 = rand() % NUMINDIVIDUO;

    for (int i = 0; i < CROMOSSOMO - 1; i++)
    {
        
        aux = Populacao[alvo][i] + (F * (Populacao[aleatorio01][i] - Populacao[aleatorio02][i]));
        if(aux < MIN)
            aux = MIN;
        if(aux > MAX)
            aux = MAX;
        experimental[i] = aux;
    }
    
    avaliaIndividuo(experimental);
    *numAvaliacoes = *numAvaliacoes + 1;  
}

void bin01(double Populacao[][CROMOSSOMO], int best, double experimental[], int *numAvaliacoes){
    int aleatorio01 = 0, aleatorio02 = 0;
    double aux = 0;
    aleatorio01 = rand() % NUMINDIVIDUO;
    while(aleatorio01 == best)
        aleatorio01 = rand() % NUMINDIVIDUO;

    aleatorio02 = rand() % NUMINDIVIDUO;
    while( (aleatorio01 == aleatorio02) || (aleatorio02 == best) )
        aleatorio02 = rand() % NUMINDIVIDUO;
    
    for (int i = 0; i < CROMOSSOMO - 1; i++)
    {
        
        aux = Populacao[best][i] + (F * (Populacao[aleatorio01][i] - Populacao[aleatorio02][i]));
        if(aux < MIN)
            aux = MIN;
        if(aux > MAX)
            aux = MAX;
        experimental[i] = aux;
    }
    
    avaliaIndividuo(experimental);
   *numAvaliacoes = *numAvaliacoes + 1;  
}

void bin02(double Populacao[][CROMOSSOMO], int best, double experimental[], int *numAvaliacoes){
    int aleatorio01 = 0, aleatorio02 = 0, aleatorio03 = 0, aleatorio04 = 0;
    double aux = 0;
    aleatorio01 = rand() % NUMINDIVIDUO;
    while(aleatorio01 == best)
        aleatorio01 = rand() % NUMINDIVIDUO;

    aleatorio02 = rand() % NUMINDIVIDUO;
    while( (aleatorio01 == aleatorio02) || (aleatorio02 == best) )
        aleatorio02 = rand() % NUMINDIVIDUO;

    aleatorio03 = rand() % NUMINDIVIDUO;
    while( (aleatorio03 == aleatorio01) || (aleatorio03 == aleatorio02) || (aleatorio03 == best))
        aleatorio03 = rand() % NUMINDIVIDUO;
    
    aleatorio04 = rand() % NUMINDIVIDUO;
    while( (aleatorio04 == aleatorio01) || (aleatorio04 == aleatorio02) || (aleatorio04 == best) || (aleatorio04 == aleatorio03))
        aleatorio04 = rand() % NUMINDIVIDUO;
    
    for (int i = 0; i < CROMOSSOMO - 1; i++)
    {
        aux = Populacao[best][i] + (F * (Populacao[aleatorio01][i] + Populacao[aleatorio02][i] - 
                                                    Populacao[aleatorio03][i] - Populacao[aleatorio04][i]));
        if(aux < MIN)
            aux = MIN;
        if(aux)
            aux = MAX;
        experimental[i] = aux;
    }
    
    avaliaIndividuo(experimental);
   *numAvaliacoes = *numAvaliacoes + 1;  
}


