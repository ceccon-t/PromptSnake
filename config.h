#ifndef H_CONSTANTS
    #include "constants.h"
#endif // H_CONSTANTS

#ifndef H_CONFIG
#define H_CONFIG


#ifndef FILE
    #include<stdio.h>
#endif // FILE


typedef struct config {
    int velocidade_inicial;
    int maxtamanho;
    int maxitens;
} CONFIG;

// salva_config
/*
    Salva configuracao em arquivo binario
*/
void salva_config(CONFIG opcoes);

// carrega_config
/*
    Carrega configuracoes do arquivo binario e preenche a struct passada por referencia
    Caso haja erro ao abrir arquivo, seta um conjunto padrao de configuracoes
*/
int carrega_config(CONFIG *opcoes);



#endif // H_CONFIG
