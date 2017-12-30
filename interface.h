#ifndef H_CONSTANTS
    #include "constants.h"
#endif // H_CONSTANTS

#ifndef WHITE
    #include<conio2.h>
#endif // WHITE

#ifndef Sleep
    #include<windows.h>
#endif // Sleep

#ifndef stdin
    #include<stdio.h>
#endif // STDIO

#ifndef SNAKE
    #include "snake.h"
#endif // SNAKE

#ifndef H_INTERFACE
#define H_INTERFACE

// limpa_linha
/*
    Funcao auxiliar que preenche uma linha na tela com a cor de fundo passada
*/
void limpa_linha(int linha, int x_ini, int x_fim, int cor);

// limpa_retangulo
/*
    Funcao auxiliar que preenche um retangulo na tela com a cor de fundo passada
*/
void limpa_retangulo(int y_ini, int y_fim, int x_ini, int x_fim, int cor);

// seta_cores
/*
    Altera tanto cor de fundo quanto do texto ao mesmo tempo
*/
void seta_cores(int background, int foreground);

// display_padrao_prompt
/*
    Seta as cores do console para o padrao
*/
void display_padrao_prompt();

// display_padrao_cenario
/*
    Seta as cores do console para o padrao do cenario do jogo
*/
void display_padrao_cenario();

// pega_letra
/*
    Funcao auxiliar a pega_nome, usada apenas para pegar o nome de um jogador que tenha conseguido entrar
    para o ranking de melhores pontuacoes. Implementa uma escolha de letra atraves de selecao pela setas do teclado.
*/
char pega_letra(int x);

// pega_nome
/*
    Pega o nome do jogador para entrar no ranking, preenchendo a string da estrutura
*/
void pega_nome(char *nome);

// processa_input
/*
    Processa entradas do usuario durante a partida.
*/
void processa_input(SNAKE *p_snake, int *p_pause, int *p_encerrar, int *p_inicializar, /* tirar */ char cenario[LINHAS_CENARIO][COLUNAS_CENARIO]);

// desenha_interface
/*
    Desenha a interface com as informacoes da partida
*/
void desenha_interface(int pontuacao, int velocidade, int tamanho, int cenario_atual);


/*
    =================
    Wrappers para centralizar acesso a funcoes que utilizam bibliotecas especificas para determinada plataforma, como as de IO.
    Assim quando for feita a versao para Linux apenas essa biblioteca precisa ser alterada para carregar a biblioteca
    referente a plataforma em que se esta.
    =================
*/


// clock_jogo
/*
    Wrapper para funcao Sleep
*/
void clock_jogo(int base, int velocidade);

// limpa_tela_full
/*
    Wrapper para clrscr
*/
void limpa_tela_full();

// seta_cor_bg
/*
    Wrapper para textbackground
*/
void seta_cor_bg(int cor);

// seta_cor_texto
/*
    Wrapper para textcolor
*/
void seta_cor_texto(int cor);

// escreve_str_xy
/*
    Wrapper para cputsxy
*/
void escreve_str_xy(int x, int y, char *str);

// escreve_char_xy
/*
    Wrapper para putchxy
*/
void escreve_char_xy(int x, int y, char c);

// vai_para_xy
/*
    Wrapper para gotoxy
*/
void vai_para_xy(int x, int y);

// tecla_pressionada
/*
    Wrapper para kbhit
*/
int tecla_pressionada();

// pega_char
/*
    Wrapper para getch
*/
int pega_char();


#endif // H_INTERFACE
