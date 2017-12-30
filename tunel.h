#ifndef H_TUNEL
#define H_TUNEL

#ifndef COORDENADA
    #include "coordenada.h"
#endif // COORDENADA

#ifndef H_CONSTANTS
    #include "constants.h"
#endif // H_CONSTANTS

#ifndef FILE
    #include<stdio.h>
#endif // FILE


#define FILENAME_TUNEIS "tuneis.bin"
#define MAX_TUNEIS 5

typedef struct tunel {
    COORDENADA pos;
    int id;
    char direcao;
    int id_saida;
    int cenario;
} TUNEL;

// inicializa_tuneis
/*
    Inicializa o array de tuneis
*/
int inicializa_tuneis(TUNEL tuneis[MAX_TUNEIS], int numero_cenario);

// posiciona_tuneis_no_cenario
/*
    Coloca os tuneis na matriz do cenario para a logica do jogo
*/
void posiciona_tuneis_no_cenario(char cenario[LINHAS_CENARIO][COLUNAS_CENARIO], TUNEL tuneis[MAX_TUNEIS], int num_tuneis);


//void cria_arquivo_tuneis();


// busca_tunel
/*
    Encontra o tunel em uma determinada coordenada, retorna sua id no array
*/
int busca_tunel(TUNEL *tuneis, COORDENADA coord, int num_tuneis);


// entra_tunel
/*
    Processa a logica da entrada em um tunel, returna 1 se entrou pela direcao errada, 0 se deu tudo certo
*/
int entra_tunel(TUNEL *tuneis, COORDENADA *corpo, char *direcao, int num_tuneis);


// desenha_tuneis
/*
    Desenha os tuneis na tela
*/
void desenha_tuneis(TUNEL tuneis[MAX_TUNEIS], int num_tuneis);


#endif // H_TUNEL
