#ifndef H_CONSTANTS
    #include "constants.h"
#endif // H_CONSTANTS

#ifndef H_COORDENADA
    #include "coordenada.h"
#endif // H_COORDENADA


#ifndef H_SNAKE
#define H_SNAKE

typedef struct snake {
    COORDENADA corpo[MAX_SNAKE];
    char direcao;
    int tamanho;
} SNAKE;


// inicizaliza_snake
/*
    Inicializa a estrutura da cobra e faz o desenho inicial na tela.
*/
void inicializa_snake(SNAKE *p_snake, int tamanho, char cenario[LINHAS_CENARIO][COLUNAS_CENARIO]);

// movimenta_snake
/*
    Dada a proxima coordenada da cabeca da cobra, atualiza todo o array de coordenadas.
*/
void movimenta_snake(SNAKE *p_snake, COORDENADA prox_coord);


// desenha_snake
/*
    Atualiza representacao da cobra na tela, desenhando a cabeca e apagando a cauda
*/
void desenha_snake(int x_cabeca, int y_cabeca, int x_cauda, int y_cauda);



#endif // H_SNAKE
