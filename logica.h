#ifndef H_CONSTANTS
    #include "constants.h"
#endif // H_CONSTANTS

#ifndef H_LOGICA
#define H_LOGICA

#ifndef H_COORDENADA
#include "coordenada.h"
#endif // Se necessario importa COORDENADA

#ifndef H_SNAKE
#include "snake.h"
#endif // Se necessario importa SNAKE

#ifndef H_TUNEL
#include "tunel.h"
#endif // Se necessario importa TUNEL

#ifndef RAND_MAX
#include<stdlib.h>
#endif

#ifndef CONFIG
#include "config.h"
#endif // Se necessario importa CONFIG


// processa_proximo_movimento
/*
    Controla a logica da movimentacao a cada turno da partida
*/
void processa_proximo_movimento(COORDENADA proxima_coord, int *p_pontuacao, int *p_velocidade, SNAKE *snake, int max_tamanho, char cenario[LINHAS_CENARIO][COLUNAS_CENARIO], TUNEL *tuneis, int num_tuneis, int *p_encerrar, int num_cenario);


// processa_colisao
/*
    Faz o processamento necessario quando o jogador pega um item
*/
void processa_colisao(int *p_pontuacao, int *p_velocidade, int *p_tamanho, int *p_encerrar, char item, int max_tamanho, char cenario[LINHAS_CENARIO][COLUNAS_CENARIO], TUNEL *tuneis, int num_tuneis, SNAKE *snake, COORDENADA *proxima_coord);


// escolhe_item
/*
    Escolhe um item aleatoriamente e retorna um caracter correspondente.
*/
char escolhe_item();


// gera_novo_item
/*
    Cria um novo item e o coloca em uma posicao aleatoria no cenario que nao esteja ocupada
*/
void gera_novo_item(char cenario[LINHAS_CENARIO][COLUNAS_CENARIO]);


// fim_cenario
/*
    Processa o final de uma partida
*/
void fim_cenario(int result, int pontuacao, int num_cenario);


// roda_jogo
/*
    Logica principal do jogo, controla o processamento de uma partida do comeco ao fim
*/
int roda_jogo(int *score, int *num_cenario, CONFIG *opcoes);


#endif // H_LOGICA
