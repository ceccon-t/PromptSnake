#include "interface.h"


// limpa_linha
/*
    Funcao auxiliar que preenche uma linha na tela com a cor de fundo passada
*/
void limpa_linha(int linha, int x_ini, int x_fim, int cor) {
    int i;

    textbackground(cor);
    for ( i=x_ini ; i < x_fim ; i++) {
        putchxy(i, linha, ' ');
    }

}

// limpa_retangulo
/*
    Funcao auxiliar que preenche um retangulo na tela com a cor de fundo passada
*/
void limpa_retangulo(int y_ini, int y_fim, int x_ini, int x_fim, int cor) {
    int i;

    for (i = y_ini; i < y_fim; i++) {
        limpa_linha(i, x_ini, x_fim, cor);
    }

}

// seta_cores
/*
    Altera tanto cor de fundo quanto do texto ao mesmo tempo
*/
void seta_cores(int background, int foreground) {
    textbackground(background);
    textcolor(foreground);
}

// display_padrao_prompt
/*
    Seta as cores do console para o padrao
*/
void display_padrao_prompt() {
    seta_cores(BLACK, WHITE);
}

// display_padrao_cenario
/*
    Seta as cores do console para o padrao do cenario do jogo
*/
void display_padrao_cenario() {
    seta_cores(BROWN, BLACK);
}


// pega_letra
/*
    Funcao auxiliar a pega_nome, usada apenas para pegar o nome de um jogador que tenha conseguido entrar
    para o ranking de melhores pontuacoes. Implementa uma escolha de letra atraves de selecao pela setas do teclado.
*/
char pega_letra(int x) {
    char letra = 'A';
    int op, fim = 0;

    putchxy(x, LINHA_NOME_HIGHSCORE, letra); // Mostra a letra atualmente selecionada
    gotoxy(x, LINHA_NOME_HIGHSCORE);

    while(!fim){

        if (kbhit()) {
            op = getch();
            if (op == TECLADO_ESTENDIDO) {
                switch(getch()) {
                    case ASCII_CIMA:
                        letra++; // Tratando char como int, facilita a operacao
                        if (letra > 'Z') { // Limita escolhas ao intervalo 'A-Z'
                            letra = 'A';
                        }
                        break;
                    case ASCII_BAIXO:
                        letra--;
                        if (letra < 'A') { // Idem acima
                            letra = 'Z';
                        }
                        break;
                }
                putchxy(x, LINHA_NOME_HIGHSCORE, letra); // Atualiza a letra na tela
                gotoxy(x, LINHA_NOME_HIGHSCORE);
            } else if(op == ASCII_ENTER) {
                fim = 1;
            }
        }

    }

    return letra;
}

// pega_nome
/*
    Pega o nome do jogador para entrar no ranking, preenchendo a string da estrutura
*/
void pega_nome(char *nome) {
    cputsxy(COLUNA_NOME_HIGHSCORE, LINHA_NOME_HIGHSCORE, "Nome: ");
    nome[0] = pega_letra(COLUNA_NOME_HIGHSCORE + 7); // Cada vez aumenta um para que as letras aparecam uma do lado da outra
    nome[1] = pega_letra(COLUNA_NOME_HIGHSCORE + 8);
    nome[2] = pega_letra(COLUNA_NOME_HIGHSCORE + 9);
    nome[3] = '\0';
    //fgets(nome, 4, stdin);
    fflush(stdin);
}


// processa_input
/*
    Processa entradas do usuario durante a partida.
*/
void processa_input(SNAKE *p_snake, int *p_pause, int *p_encerrar, int *p_inicializar,/* tirar */ char cenario[LINHAS_CENARIO][COLUNAS_CENARIO]) {
    int op, inicializado_agora = 0;

    if (kbhit()) {
            if (!(*p_inicializar)) {
                *p_inicializar = 1;
                inicializado_agora = 1;
                *p_pause = 0;
            }
            op = getch();

            if (op == TECLADO_ESTENDIDO /*-32*/) {
                switch(getch()) {
                    case ASCII_CIMA:
                        if (p_snake->direcao != 'b') {
                            p_snake->direcao = 'c';
                        }

                        break;
                    case ASCII_BAIXO:
                        if (p_snake->direcao != 'c') {
                            p_snake->direcao = 'b';
                        }
                        break;
                    case ASCII_DIREITA:
                        if (p_snake->direcao != 'e') {
                            p_snake->direcao = 'd';
                        }
                        break;
                    case ASCII_ESQUERDA:
                        if (p_snake->direcao != 'd') {
                            p_snake->direcao = 'e';
                        }
                        break;
                    default:
                        break;
                }

            } else if (op == ASCII_SPACEBAR) {
                if (*p_pause) {
                    *p_pause = 0;
                } else if (!inicializado_agora){ // Para evitar de pausar o jogo logo quando inicia, se primeira tecla apertada for espaco
                    *p_pause = 1;
                }
            } else if (op == ASCII_ESC) {
                *p_encerrar = USER_EXIT;
            } else if (op == 'w') {
                if (p_snake->direcao != 'b') {
                    p_snake->direcao = 'c';
                }
            } else if (op == 's') {
                if (p_snake->direcao != 'c') {
                    p_snake->direcao = 'b';
                }
            } else if (op == 'd') {
                if (p_snake->direcao != 'e') {
                    p_snake->direcao = 'd';
                }
            } else if (op == 'a') {
                if (p_snake->direcao != 'd') {
                    p_snake->direcao = 'e';
                }
            }
        }
}


// desenha_interface
/*
    Desenha a interface com as informacoes da partida
*/
void desenha_interface(int pontuacao, int velocidade, int tamanho, int cenario_atual) {
    char status[MAX_X_TELA];
    int i;

    // Todas as informacoes aparecem contanto que pontuacao seja menor do que 99999999, acima disso estoura o limite da tela
    sprintf(status, "Score: %d\tVelocidade: %d\t\tSNAKE\t\tTamanho: %d\tMapa: %d\n",  pontuacao, velocidade, tamanho, cenario_atual);
    textbackground(WHITE);
    for (i = 1; i <= MAX_X_TELA; i++) {
        putchxy(i, 1, ' ');
    }
    cputsxy(1,1,status);


}


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
void clock_jogo(int base, int velocidade) {
    Sleep(base/velocidade);
}


// limpa_tela_full
/*
    Wrapper para clrscr
*/
void limpa_tela_full() {
    clrscr();
}


// seta_cor_bg
/*
    Wrapper para textbackground
*/
void seta_cor_bg(int cor) {
    textbackground(cor);
}

// seta_cor_texto
/*
    Wrapper para textcolor
*/
void seta_cor_texto(int cor) {
    textcolor(cor);
}

// escreve_str_xy
/*
    Wrapper para cputsxy
*/
void escreve_str_xy(int x, int y, char *str) {
    cputsxy(x, y, str);
}

// escreve_char_xy
/*
    Wrapper para putchxy
*/
void escreve_char_xy(int x, int y, char c) {
    putchxy(x, y, c);
}

// vai_para_xy
/*
    Wrapper para gotoxy
*/
void vai_para_xy(int x, int y) {
    gotoxy(x, y);
}

// tecla_pressionada
/*
    Wrapper para kbhit
*/
int tecla_pressionada() {
    return kbhit();
}

// pega_char
/*
    Wrapper para getch
*/
int pega_char() {
    return getch();
}


