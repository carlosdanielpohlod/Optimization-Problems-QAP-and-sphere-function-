#include "funcoesED.h"

int main(){
    
    srand(time(NULL));
   
    double Populacao[NUMINDIVIDUO][CROMOSSOMO] = {0}, experimental[CROMOSSOMO] = {0};
    int numAvaliacoes = 0;

    int best = 0;
    
    carregarVetor(Populacao);
    avaliaPopulacao(Populacao, &numAvaliacoes);
    bubbleSort(Populacao);
    // exibirPopulacao(Populacao);
    

    int k = (NUMINDIVIDUO * CROMOSSOMO);
    for(int i = 0; (i < k) && (numAvaliacoes < MAXAVALIACOES); i ++){
        
        best = encontrarMelhor(Populacao);
        
        rand01(Populacao, best, experimental, &numAvaliacoes);
        
        cruzamentoBinomial(Populacao, best, experimental, &numAvaliacoes);
        
        best = encontrarMelhor(Populacao);
        operadorBuscaLocal(Populacao, best, &numAvaliacoes);
    }
   
    best = encontrarMelhor(Populacao);
    salvarResultado(Populacao[best][CROMOSSOMO - 1]);
    // printf("avaliacoes %d", numAvaliacoes);

    // Pausar();
    
}
