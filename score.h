#ifndef H_CONSTANTS
    #include "constants.h"
#endif // H_CONSTANTS

#ifndef H_SCORE
#define H_SCORE


#ifndef FILE
    #include<stdio.h>
#endif // FILE

typedef struct score {
    char nome[MAX_NOME + 1];
    int pontuacao;
} SCORE;


// carrega_score
/*
    Preenche um array com as 10 maiores pontuacoes salvas no arquivo
    ou, caso o arquivo nao seja encontrado, inicializa tudo com 0
*/
int carrega_score(SCORE *scores);


// ordena_scores
/*
    Garante que um array de scores esteja ordenado em ordem decrescente,
    caso o array fornecido nao esteja, chama a funcao que aplica selection sort
*/
void ordena_score(SCORE *scores);


// insere_score
/*
    Dado um array de scores ordenado e um novo score, o insere no array
*/
void insere_score(SCORE *scores, SCORE novo_score);


// salva_scores
/*
    Grava um array de scores no arquivo, no formato "pontuacao,nome"
*/
int salva_scores(SCORE *scores);

// calcula_pontos
/*
    Calcula quantos pontos o usuario deve receber ao pegar determinado item
*/
int calcula_pontos(int velocidade, int tamanho, char item);


// display_high_scores
/*
    Mostra a tela com o ranking das dez melhores pontuacoes
*/
void display_high_scores();


// processa_score_final
/*
    Verifica se a pontuacao final foi suficiente para entrar no ranking de High Scores.
    Em caso positivo, inicia o processo de insercao nele.
*/
void processa_score_final(int pontuacao);


#endif // H_SCORE

