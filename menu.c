#include "menu.h"


// ini_display_menu
/*
    Inicializa a parte estatica do menu na tela
*/
void ini_display_menu() {
    int i, j;

    // Nome do jogo na parte superior do menu
    char tela[][MAX_X_TELA] = {
                            {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                            {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                            {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                            {"10000000000000000000011111001111011001111100110011001111100000000000000000000001"},
                            {"10000000000000000000011000001111011001101100110110001100000000000000000000000001"},
                            {"10000000000000000000011111001101011001111100111100001111100000000000000000000001"},
                            {"10000000000000000000000011001101111001101100110110001100000000000000000000000001"},
                            {"10000000000000000000011111001101111001101100110011001111100000000000000000000001"},
                            {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                            {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                            {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"}};

    // Desenha moldura
    seta_cor_bg(COR_MOLDURA);
    limpa_linha(1, 1, MAX_X_TELA+1, COR_MOLDURA); // Primeira linha da tela, prompt inicia contagem em 1
    limpa_linha(MAX_Y_TELA, 1, MAX_X_TELA+1, COR_MOLDURA); // Ultima linha da tela, prompt inicia contagem em 1
    for (i = 1; i < MAX_Y_TELA+1; i++) { // Preenche primeira e ultima coluna da tela
        escreve_char_xy(1, i, ' ');
        escreve_char_xy(MAX_X_TELA, i, ' ');
    }
    vai_para_xy(1,1);

    // Desenha titulo
    seta_cor_bg(COR_BG_CENARIO);
    for (i = 1; i <= (MAX_Y_TELA-LINHA_INICIO_MENU); i++) {
        for (j = 0; j < MAX_X_TELA; j++) {
            if (tela[i][j] == '1') {
                seta_cor_bg(COR_TITULO);
                //escreve_char_xy(j+OFFSET_X, i+OFFSET_Y, ' ');
            } else {
                seta_cor_bg(COR_BG_CENARIO);
                //escreve_char_xy(j+OFFSET_X, i+OFFSET_Y, ' ');
            }
            escreve_char_xy(j+OFFSET_X, i+OFFSET_Y, ' ');
        }
    }
    seta_cor_bg(COR_BG_CENARIO);
    vai_para_xy(1,1); // Volta o cursor para o início da tela
}


// display_menu
/*
    Inicializa o menu na tela
*/
void display_menu(char items_menu[NUM_OPCOES][MAXSIZE_STRINGS_MENU], int selecionado) {
    int i;

    seta_cor_bg(COR_BG_CENARIO);
    limpa_tela_full();
    ini_display_menu();
    for (i = 0; i < NUM_OPCOES; i++) {
        if (i == selecionado) {
            seta_cor_bg(COR_BG_MENU_SELECIONADO);
            seta_cor_texto(COR_TEXTO_MENU_SELECIONADO);
        }
        escreve_str_xy(( MAX_X_TELA - strlen(items_menu[i]))/2, LINHA_INICIO_MENU + i, items_menu[i]);
        if (i == selecionado) {
            seta_cor_bg(COR_BG_CENARIO);
            seta_cor_texto(COR_TEXTO_PADRAO);
        }
    }
}


// atualiza_menu
/*
    Redesenha na tela apenas o item do menu selecionado e o recem de-selecionado
*/
void atualiza_menu(char items_menu[NUM_OPCOES][MAXSIZE_STRINGS_MENU], int selecionado, int old_selecionado) {
    int i;


    for (i = 0; i < NUM_OPCOES; i++) {

        if (i == old_selecionado) { // Restaura visualizacao do previamente selecionado para o padrao
            seta_cor_bg(COR_BG_CENARIO);
            seta_cor_texto(COR_TEXTO_PADRAO);
            escreve_str_xy(( MAX_X_TELA - strlen(items_menu[i]))/2, LINHA_INICIO_MENU + i, items_menu[i]);
        }

        if (i == selecionado) { // Mostra o item selecionado com cor de fundo e texto diferentes
            seta_cor_bg(COR_BG_MENU_SELECIONADO);
            seta_cor_texto(COR_TEXTO_MENU_SELECIONADO);
            escreve_str_xy(( MAX_X_TELA - strlen(items_menu[i]))/2, LINHA_INICIO_MENU + i, items_menu[i]);
        }
    }
    seta_cor_bg(COR_BG_CENARIO);
    seta_cor_texto(COR_TEXTO_PADRAO);
}


// controla_menu
/*
    Logica principal do menu principal, controla as funcionalidades do jogo
*/
void controla_menu(int *score, int *num_cenario, CONFIG *opcoes) {
    char items_menu[NUM_OPCOES][MAXSIZE_STRINGS_MENU] = {"   NOVO JOGO  ", "  HIGH SCORES ", "    OPCOES    ", "   CREDITOS   ", "     SAIR     "};
    int encerrar = 0, selecionado = 0, op, result, old_selecionado;
    display_menu(items_menu, selecionado);

    while (!encerrar) {
        if (tecla_pressionada()) {
            op = pega_char();

            if (op == TECLADO_ESTENDIDO) {
                switch(pega_char()) {
                    case ASCII_CIMA:
                        old_selecionado = selecionado;
                        selecionado--;
                        if (selecionado < 0) selecionado = NUM_OPCOES - 1;
                        selecionado = selecionado % NUM_OPCOES;
                        atualiza_menu(items_menu, selecionado, old_selecionado);
                        break;
                    case ASCII_BAIXO:
                        old_selecionado = selecionado;
                        selecionado++;
                        selecionado = selecionado % NUM_OPCOES;
                        atualiza_menu(items_menu, selecionado, old_selecionado);
                        break;
                    default:
                        break;
                }
            } else if (op == ASCII_ENTER) {
                switch (selecionado) {
                    case NOVO_JOGO:
                        *score = 0; // Novo jogo, score zerado
                        result = 0;
                        do {
                            result = roda_jogo(score, num_cenario, opcoes);
                        } while (result == CENARIO_COMPLETO && *num_cenario != 4);
                        processa_score_final(*score); // Fim de jogo, verifica se entrou no top ten
                        *num_cenario = 1; // Proximo novo jogo inicializa no primeiro cenario
                        break;
                    case HIGH_SCORES:
                        display_high_scores();
                        break;
                    case OPCOES:
                        controla_menu_opcoes(opcoes);
                        break;
                    case CREDITOS:
                        display_creditos();
                        break;
                    case SAIR:
                        encerrar = 1;
                        break;
                }
                display_menu(items_menu, selecionado); // Voltando de uma tela diferente, necessario reinicializar o menu na tela
            } else if (op == ASCII_ESC) {
                encerrar = 1;
            }

        }

    }

}



// limpa_tela_menu
/*
    Funcao auxiliar para limpar a area do menu na tela
*/
void limpa_tela_menu() {
    limpa_retangulo(LINHA_INICIO_MENU, MAX_Y_TELA, 2, MAX_X_TELA, BROWN); // x_ini = 2 para nao apagar a moldura da tela na primeira coluna
}


// converte_index_menu_para_valor_config
/*
    Funcao auxiliar para display_menu_opcoes, recebe o index de uma opcao no array do menu
    e converte para o valor da opcao nas configuracoes (apenas para display)
*/
int converte_index_menu_para_valor_config(int index, CONFIG opcoes) {
    switch(index) {
        case MENU_CONFIG_VELOCIDADEINICIAL:
            return opcoes.velocidade_inicial;
            break;
        case MENU_CONFIG_MAXTAMANHO:
            return opcoes.maxtamanho;
            break;
        case MENU_CONFIG_MAXITENS:
            return opcoes.maxitens;
            break;
        default:
            return 0;
            break;
    }
}


// display_menu_opcoes
/*
    Inicializa o menu de opcoes na tela
*/
void display_menu_opcoes(char items_menu[NUM_OPCOES_CONFIG][MAXSIZE_STRINGS_MENU], int selecionado, CONFIG *opcoes) {
    char str_opcao[MAXSIZE_STRINGS_MENU + 3]; // 3 espacos extra para valor das opcoes
    int i;

    seta_cor_bg(COR_BG_CENARIO);
    limpa_tela_full();
    ini_display_menu();
    for (i = 0; i < NUM_OPCOES_CONFIG; i++) {
        if (i == selecionado) { // Display especifico para item selecionado
            seta_cor_bg(COR_BG_MENU_SELECIONADO);
            seta_cor_texto(COR_TEXTO_MENU_SELECIONADO);
        }

        if (i != MENU_CONFIG_VOLTAR) {
            sprintf(str_opcao, "%s%3d", items_menu[i], converte_index_menu_para_valor_config(i, *opcoes));
        } else {
            strcpy(str_opcao, items_menu[i]);
        }

        escreve_str_xy(COLUNA_INICIO_MENU_OPCOES, LINHA_INICIO_MENU + i, str_opcao);

        if (i == selecionado) { // Retorna display para o estado normal
            seta_cor_bg(COR_BG_CENARIO);
            seta_cor_texto(COR_TEXTO_PADRAO);
        }
    }

}

// atualiza_menu_opcoes
/*
    Redesenha na tela apenas o item do menu selecionado e o recem de-selecionado, para o menu de opcoes
*/
void atualiza_menu_opcoes(char items_menu[NUM_OPCOES_CONFIG][MAXSIZE_STRINGS_MENU], int selecionado, int old_selecionado, CONFIG *opcoes) {
    char str_opcao[MAXSIZE_STRINGS_MENU + 3]; // 3 espacos extra para valor das opcoes
    int i;

    for (i = 0; i < NUM_OPCOES_CONFIG; i++) {

        if (i == old_selecionado) { // Atualiza na tela o que estava previamente selecionado
            seta_cor_bg(COR_BG_CENARIO);
            seta_cor_texto(COR_TEXTO_PADRAO);

            if (i != MENU_CONFIG_VOLTAR) {
                sprintf(str_opcao, "%s%3d", items_menu[i], converte_index_menu_para_valor_config(i, *opcoes));
            } else {
                strcpy(str_opcao, items_menu[i]);
            }

            escreve_str_xy(COLUNA_INICIO_MENU_OPCOES, LINHA_INICIO_MENU + i, str_opcao);
        }

        if (i == selecionado) { // Atualiza na tela o atualmente selecionado
            seta_cor_bg(COR_BG_MENU_SELECIONADO);
            seta_cor_texto(COR_TEXTO_MENU_SELECIONADO);
            if (i != MENU_CONFIG_VOLTAR) {
                sprintf(str_opcao, "%s%3d", items_menu[i], converte_index_menu_para_valor_config(i, *opcoes));
            } else {
                strcpy(str_opcao, items_menu[i]);
            }

            escreve_str_xy(COLUNA_INICIO_MENU_OPCOES, LINHA_INICIO_MENU + i, str_opcao);
        }

        seta_cor_bg(COR_BG_CENARIO); // Volta para o display padrao
        seta_cor_texto(COR_TEXTO_PADRAO);

    }

}


// controla_menu
/*
    Logica principal do menu de opcoes, controla as configuracoes do jogo
*/
void controla_menu_opcoes(CONFIG *opcoes) {
    char items_menu[NUM_OPCOES_CONFIG][MAXSIZE_STRINGS_MENU] = {"VELOCIDADE\t", "MAX TAMANHO\t", "MAX ITENS\t", "VOLTAR"};
    int voltar = 0, selecionado = 0, old_selecionado, alterou_config = 0, op;
    display_menu_opcoes(items_menu, selecionado, opcoes);

    while (!voltar) {
        if (tecla_pressionada()) {
            op = pega_char();

            if (op == TECLADO_ESTENDIDO) {
                old_selecionado = selecionado;
                switch(pega_char()) {
                    case ASCII_CIMA:
                        selecionado--;
                        if (selecionado < 0) selecionado = NUM_OPCOES_CONFIG - 1 ;
                        selecionado = selecionado % NUM_OPCOES_CONFIG;
                        break;
                    case ASCII_BAIXO:
                        selecionado++;
                        selecionado = selecionado % NUM_OPCOES_CONFIG;
                        break;
                    case ASCII_DIREITA:
                        switch(selecionado) {
                            case 0: // Velocidade Inicial
                                if (opcoes->velocidade_inicial < MAX_VELOCIDADEINICIAL) {
                                    opcoes->velocidade_inicial += 1;
                                    alterou_config = 1;
                                }
                                break;
                            case 1: // MaxTamanho
                                if (opcoes->maxtamanho < MAX_MAXTAMANHO) {
                                    opcoes->maxtamanho += 1;
                                    alterou_config = 1;
                                }
                                break;
                            case 2: // MaxItens
                                if (opcoes->maxitens < MAX_MAXITENS) {
                                    opcoes->maxitens += 1;
                                    alterou_config = 1;
                                }
                                break;
                            default:
                                break;
                        }
                        break;
                    case ASCII_ESQUERDA:
                        switch(selecionado) {
                            case 0: // Velocidade Inicial
                                if (opcoes->velocidade_inicial > MIN_VELOCIDADEINICIAL) {
                                    opcoes->velocidade_inicial -= 1;
                                    alterou_config = 1;
                                }
                                break;
                            case 1: // MaxTamanho
                                if (opcoes->maxtamanho > MIN_MAXTAMANHO) {
                                    opcoes->maxtamanho -= 1;
                                    alterou_config = 1;
                                }
                                break;
                            case 2: // MaxItens
                                if (opcoes->maxitens > MIN_MAXITENS) {
                                    opcoes->maxitens -= 1;
                                    alterou_config = 1;
                                }
                                break;
                            default:
                                break;
                        }
                        break;
                    default:
                        break;
                }
                atualiza_menu_opcoes(items_menu, selecionado, old_selecionado, opcoes);
            } else if (op == ASCII_ENTER) {
                switch (selecionado) {
                    case MENU_CONFIG_VOLTAR:
                        voltar = 1;
                        break;
                    default:
                        break;
                }
            } else if (op == ASCII_ESC) {
                voltar = 1;
            }

            if (alterou_config) {
                salva_config(*opcoes);
            }

            alterou_config = 0; // reseta para nao ficar salvando sempre.

        }
    }
}



// display_creditos
/*
    Mostra a tela de creditos
*/
void display_creditos() {
    int i, linhas;
    char creditos[][MAX_X_TELA] = {"Desenvolvido por Tiago Ceccon",
                           "para a cadeira de Algoritmos E Programacao (INF01202)",
                           "do curso de Ciencia da Computacao da UFRGS.",
                           "2017-01"};


    limpa_tela_menu();

    linhas = sizeof(creditos)/sizeof(creditos[0]);
    for (i = 0; i < linhas; i++) {
        escreve_str_xy((MAX_X_TELA - strlen(creditos[i]))/2, LINHA_INICIO_MENU + i, creditos[i]); // Coloca linha (mais ou menos) centralizada na tela
    }

    seta_cor_bg(COR_BG_MENU_SELECIONADO);
    seta_cor_texto(COR_TEXTO_MENU_SELECIONADO);
    escreve_str_xy(COLUNA_INICIO_MENU_OPCOES, LINHA_INICIO_MENU+i+2, "  VOLTAR  ");
    seta_cor_bg(COR_BG_CENARIO);
    seta_cor_texto(COR_TEXTO_PADRAO);
    vai_para_xy(42, LINHA_INICIO_MENU+i+2); // x=42 apenas para o cursos ficar abaixo da letra R do "VOLTAR"

    while(pega_char() != ASCII_ENTER);
}

