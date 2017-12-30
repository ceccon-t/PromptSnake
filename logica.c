#include "logica.h"


// processa_proximo_movimento
/*
    Controla a logica da movimentacao a cada turno da partida
*/
void processa_proximo_movimento(COORDENADA proxima_coord, int *p_pontuacao, int *p_velocidade, SNAKE *snake, int max_tamanho, char cenario[LINHAS_CENARIO][COLUNAS_CENARIO], TUNEL *tuneis, int num_tuneis, int *p_encerrar, int num_cenario){
    char item_no_proximo_movimento = cenario[ proxima_coord.y-OFFSET_Y ][ proxima_coord.x-OFFSET_X ];

    if (item_no_proximo_movimento != '0') {
        processa_colisao(p_pontuacao, p_velocidade, &snake->tamanho, p_encerrar, item_no_proximo_movimento, max_tamanho, cenario, tuneis, num_tuneis, snake, &proxima_coord);
        desenha_interface(*p_pontuacao, *p_velocidade, snake->tamanho, num_cenario);
    }

    // Atualiza posicao da cobra na estrutura
    movimenta_snake(snake, proxima_coord);

    // Atualiza posicao da cobra na matriz do cenario
    cenario[ snake->corpo[0].y-OFFSET_Y ][ snake->corpo[0].x-OFFSET_X ] = 'B';
    cenario[ snake->corpo[snake->tamanho].y-OFFSET_Y ][ snake->corpo[snake->tamanho].x-OFFSET_X ] = '0';
}

// processa_colisao
/*
    Faz o processamento necessario quando o jogador pega um item
*/
void processa_colisao(int *p_pontuacao, int *p_velocidade, int *p_tamanho, int *p_encerrar, char item, int max_tamanho, char cenario[LINHAS_CENARIO][COLUNAS_CENARIO], TUNEL *tuneis, int num_tuneis, SNAKE *snake, COORDENADA *proxima_coord) {
    COORDENADA coord_temp;

    switch(item) {
        case '1': // Obstaculo
        case 'B': // Corpo da cobra
            *p_encerrar = GAME_OVER;
            break;
        case 'C': // Comida
            *p_pontuacao += calcula_pontos(*p_velocidade, *p_tamanho, item);
            if (*p_tamanho < max_tamanho - 1) {
                *p_tamanho += 1;
            } else {
                *p_encerrar = CENARIO_COMPLETO; // Passa de cenario ao atingir tamanho maximo da cobra
            }
            gera_novo_item(cenario);
            break;
        case 'S': // Slower
            *p_pontuacao += calcula_pontos(*p_velocidade, *p_tamanho, item);
            gera_novo_item(cenario);
            if (*p_velocidade > MIN_VELOCIDADEINICIAL) {
                *p_velocidade -= 1;
            }
            break;
        case 'F': // Faster
            *p_pontuacao += calcula_pontos(*p_velocidade, *p_tamanho, item);
            gera_novo_item(cenario);
            if (*p_velocidade < MAX_VELOCIDADEINICIAL) {
                *p_velocidade += 1;
            }
            break;
        case 'V': // Skip = vitoria = cenario completo
            *p_pontuacao += calcula_pontos(*p_velocidade, *p_tamanho, item);
            *p_encerrar = CENARIO_COMPLETO;
            break;
        case 'T': // Tunel
            if (!entra_tunel(tuneis, proxima_coord, &snake->direcao, num_tuneis )) {
                coord_temp.x = proxima_coord->x+OFFSET_X;
                coord_temp.y = proxima_coord->y+OFFSET_Y;
                coord_temp = proxima_coordenada(coord_temp, snake->direcao);
                *proxima_coord = coord_temp;

                // Chama uma versao atualizada de si propria para processar o caso de haver um item significativo
                // logo na frente do tunel
                processa_colisao(p_pontuacao, p_velocidade, p_tamanho, p_encerrar, cenario[ proxima_coord->y-OFFSET_Y ][ proxima_coord->x-OFFSET_X ], max_tamanho, cenario, tuneis, num_tuneis, snake, proxima_coord);

            } else {
                *p_encerrar = GAME_OVER;
            }
            break;
        default:
            break;

    }
}

// escolhe_item
/*
    Escolhe um item aleatoriamente e retorna um caracter correspondente.
*/
char escolhe_item() {
    // val: Valor aleatorio de 0 a 99, a faixa onde ele cair determina o objeto a ser retornado
    // probabilidades deteminadas: Comida 67%, Faster 20%, Slower 10%, Skip 3%
    int val = (int) (rand() / (double) RAND_MAX * 100);
    char objeto;

    // Verifica o range em que val caiu e retorna um objeto de acordo com a probabilidade
    if (val < 3) {
        objeto = 'V';
    } else if (val < 13) {
        objeto = 'S';
    } else if (val < 33) {
        objeto = 'F';
    } else {
        objeto = 'C';
    }

    return objeto;
}


// gera_novo_item
/*
    Cria um novo item e o coloca em uma posicao aleatoria no cenario que nao esteja ocupada
*/
void gera_novo_item(char cenario[LINHAS_CENARIO][COLUNAS_CENARIO]) {
    int novo_x, novo_y;
    char novo_item = escolhe_item();

    do {
        novo_y = ((int) (rand() / (double) RAND_MAX * (LINHAS_CENARIO - 2) )) + 1; // Ajusta a escolha do numero aleatorio para evitar
        novo_x = ((int) (rand() / (double) RAND_MAX * (COLUNAS_CENARIO - 3))) + 1; // testes nas extremidades (que sempre estao ocupadas com obstaculos)
    } while (cenario[novo_y][novo_x] != '0');

    cenario[novo_y][novo_x] = novo_item;
    escreve_char_xy(novo_x+OFFSET_X, novo_y+OFFSET_Y, novo_item);

}



// fim_cenario
/*
    Processa o final de uma partida
*/
void fim_cenario(int result, int pontuacao, int num_cenario) {
    char mensagem[MAXSIZE_MSGS_FIMCENARIO];
    char mensagem_pontuacao[MAXSIZE_MSGS_FIMCENARIO];
    int mostrar_pontuacao = 1;

    switch(result) {
        case GAME_OVER:
            sprintf(mensagem, "   GAME OVER   ");
            break;
        case CENARIO_COMPLETO:
            sprintf(mensagem, "CENARIO COMPLETO");
            if (num_cenario != NUM_CENARIOS) { // Nao finalizou o ultimo cenario
                mostrar_pontuacao = 0;
            }
            break;
        case USER_EXIT:
            sprintf(mensagem, "   VOCE SAIU   ");
            break;
        default:
            break;
    }

    limpa_retangulo(LINHA_INICIO_FIMCENARIO, LINHA_FIM_FIMCENARIO, COLUNA_INICIO_FIMCENARIO, COLUNA_FIM_FIMCENARIO, COR_BG_MSG);

    seta_cor_texto(COR_TEXTO_PADRAO);
    escreve_str_xy(COLUNA_MSG_FIMCENARIO, LINHA_MSG_FIMCENARIO, mensagem);
    if (mostrar_pontuacao) {
        sprintf(mensagem_pontuacao, "%s%8d", "PONTUACAO FINAL: ", pontuacao);
        escreve_str_xy(COLUNA_PONTUACAO_FIMCENARIO, LINHA_PONTUACAO_FIMCENARIO, mensagem_pontuacao);
    }
    escreve_str_xy(COLUNA_SAIR_FIMCENARIO, LINHA_SAIR_FIMCENARIO, "Aperte ENTER para sair.");

    while(pega_char() != ASCII_ENTER);
}


// roda_jogo
/*
    Logica principal do jogo, controla o processamento de uma partida do comeco ao fim
*/
int roda_jogo(int *score, int *num_cenario, CONFIG *opcoes) {
    // Inicializacao de variaveis
    char cenario[LINHAS_CENARIO][COLUNAS_CENARIO], item_no_proximo_movimento;
    TUNEL tuneis[MAX_TUNEIS] = {0};
    int num_tuneis, encerrar = 0, pause = 1, inicializado = 0, op, i;
    int velocidade = opcoes->velocidade_inicial;
    SNAKE snake = {0};
    COORDENADA proxima_coord;

    // Inicio do processamento
    display_padrao_cenario();
    limpa_tela_full();

    inicializa_cenario(cenario, *num_cenario, tuneis, &num_tuneis);

    inicializa_snake(&snake, INI_TAM_SNAKE, cenario);

    desenha_interface(*score, velocidade, snake.tamanho, *num_cenario);

    display_padrao_cenario();  // Garante que alteracoes no display nas funcoes anteriores nao interfiram

    // Inicializa os itens
    for(i = 0; i < opcoes->maxitens ; i++) {
        gera_novo_item(cenario);
    }

    // Loop principal do jogo
    while (!encerrar) {

        // Entradas do usuario
        processa_input(&snake, &pause, &encerrar, &inicializado, cenario);

        if (!pause) {

            proxima_coord = proxima_coordenada(snake.corpo[0], snake.direcao);

            item_no_proximo_movimento = cenario[ proxima_coord.y-OFFSET_Y ][ proxima_coord.x-OFFSET_X ];

            // Parte logica da movimentacao
            processa_proximo_movimento(proxima_coord, score, &velocidade, &snake, opcoes->maxtamanho, cenario, tuneis, num_tuneis, &encerrar, *num_cenario);

            // Parte visual da movimentacao, de acordo com a versao atualizada da parte logica
            desenha_snake(snake.corpo[0].x, snake.corpo[0].y, snake.corpo[snake.tamanho].x, snake.corpo[snake.tamanho].y);

        }

        // Controle da velocidade
        clock_jogo(UM_SEGUNDO_EM_MS, velocidade);

    }

    fim_cenario(encerrar, *score, *num_cenario);

    if (encerrar == CENARIO_COMPLETO) {
        *num_cenario += 1;
        *score += BONUS_COMPLETA_CENARIO; // Pontuacao extra ao completar cenario
    }

    return encerrar;
}

