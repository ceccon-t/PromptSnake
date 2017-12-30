#include "snake.h"

// inicizaliza_snake
/*
    Inicializa a estrutura da cobra e faz o desenho inicial na tela.
*/
void inicializa_snake(SNAKE *p_snake, int tamanho, char cenario[LINHAS_CENARIO][COLUNAS_CENARIO]) {
    int i;

    p_snake->tamanho = tamanho;

    p_snake->direcao = 'd';


    textbackground(BACK_SNAKE);
    for (i = 0; i < tamanho; i++) {
        p_snake->corpo[i].x = INI_X_SNAKE - i;
        p_snake->corpo[i].y = INI_Y_SNAKE;
        cenario[p_snake->corpo[i].y - 2][p_snake->corpo[i].x - 1] = 'B';
        putchxy(p_snake->corpo[i].x, p_snake->corpo[i].y, ' ');
    }

}

// movimenta_snake
/*
    Dada a proxima coordenada da cabeca da cobra, atualiza todo o array de coordenadas.
*/
void movimenta_snake(SNAKE *p_snake, COORDENADA prox_coord) {
    int i;

    for (i=p_snake->tamanho; i > 0; i--) {
            p_snake->corpo[i].x = p_snake->corpo[i-1].x;
            p_snake->corpo[i].y = p_snake->corpo[i-1].y;
    }
    p_snake->corpo[0] = prox_coord;
}

// desenha_snake
/*
    Atualiza representacao da cobra na tela, desenhando a cabeca e apagando a cauda
*/
void desenha_snake(int x_cabeca, int y_cabeca, int x_cauda, int y_cauda) {
    seta_cor_bg(BACK_SNAKE);
    escreve_char_xy(x_cabeca, y_cabeca, ' ');
    seta_cor_bg(BACK_CENARIO);
    escreve_char_xy(x_cauda, y_cauda, ' ');
    //seta_cor_bg(BACK_CENARIO);
}

