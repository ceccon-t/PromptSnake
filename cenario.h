#ifndef H_CONSTANTS
    #include "constants.h"
#endif // H_CONSTANTS



#ifndef H_CENARIO
#define H_CENARIO

#ifndef H_TUNEL
#include "tunel.h"
#endif


// popula_cenario
/*
    Preenche a matriz do cenario com a leitura do arquivo de texto
    Caso nao encontre o arquivo, usa cenarios padroes arbitrarios
*/
void popula_cenario(char addr_cenario[LINHAS_CENARIO][COLUNAS_CENARIO], int numero_cenario);

// inicializa_cenario
/*
    Popula array do cenario, faz a inicializacao dele na tela e trata tuneis.
*/
void inicializa_cenario(char cenario[LINHAS_CENARIO][COLUNAS_CENARIO], int numero_cenario, TUNEL tuneis[MAX_TUNEIS], int *num_tuneis);


// desenha_cenario
/*
    Inicializa o cenario na tela
*/
void desenha_cenario(char cenario[LINHAS_CENARIO][COLUNAS_CENARIO]);


#endif // H_CENARIO
