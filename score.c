#include "score.h"

// carrega_score
/*
    Preenche um array com as 10 maiores pontuacoes salvas no arquivo
    ou, caso o arquivo nao seja encontrado, inicializa tudo com 0
*/
int carrega_score(SCORE *scores) {
    FILE *arq;
    SCORE buf;
    int i = 0;

    if (arq = fopen(FILENAME_HIGH_SCORES, "r")) {

        while (!feof(arq) && i < NUM_HIGH_SCORES) {
            if (fscanf(arq, "%d,%s", &buf.pontuacao, &buf.nome) != NULL) {
                scores[i].pontuacao = buf.pontuacao;
                strcpy(scores[i].nome, buf.nome);
                i++;
            }
        }

        fclose(arq);

    } else {
        for (i = 0; i < NUM_HIGH_SCORES; i++) {
            strcpy(scores[i].nome, "AAA");
            scores[i].pontuacao = 0;
        }
        return 1; // Erro ao abrir o arquivo, tudo zerado
    }

    return 0; // Tudo ok
}

// ordena_scores
/*
    Garante que um array de scores esteja ordenado em ordem decrescente,
    caso o array fornecido nao esteja, chama a funcao que aplica selection sort
*/
void ordena_score(SCORE *scores) {
    int i = 0, ordenado = 1;

    while(i < NUM_HIGH_SCORES - 1 && ordenado) {
        if (scores[i].pontuacao < scores[i+1].pontuacao) {
            ordenado = 0;
        }
        i++;
    }

    if (!ordenado) {
        selection_sort_score(scores, 0, NUM_HIGH_SCORES-1);
        salva_scores(scores);
    }

}

// separa_pivo_score: funcao AUXILIAR para o selection sort
int separa_pivo_score(SCORE * scores, int p, int r) {
    SCORE pivo = scores[p], t;
    int i = p + 1;
    int j = r;

    while (i <= j) {
        if (scores[i].pontuacao >= pivo.pontuacao) {
            i++;
        } else if (scores[j].pontuacao < pivo.pontuacao) {
            j--;
        } else {

            t.pontuacao = scores[i].pontuacao;
            strcpy(t.nome, scores[i].nome);

            scores[i].pontuacao = scores[j].pontuacao;
            strcpy(scores[i].nome, scores[j].nome);

            scores[j].pontuacao = t.pontuacao;
            strcpy(scores[j].nome, t.nome);

            i++;
            j--;
        }
    }


    t.pontuacao = scores[p].pontuacao;
    strcpy(t.nome, scores[p].nome);

    scores[p].pontuacao = scores[j].pontuacao;
    strcpy(scores[p].nome, scores[j].nome);

    scores[j].pontuacao = t.pontuacao;
    strcpy(scores[j].nome, t.nome);

    return j;
}

// selection_sort_score
/*
    Ordena um array de scores
*/
void selection_sort_score(SCORE * scores, int inicio, int fim) {
    int j;
    if (inicio < fim) {

        j = separa_pivo_score(scores, inicio, fim);

        selection_sort_score(scores, inicio, j-1);

        selection_sort_score(scores, j+1, fim);

    }
}

// insere_score
/*
    Dado um array de scores ordenado e um novo score, o insere no array
*/
void insere_score(SCORE *scores, SCORE novo_score){
    int i, j; //, index_colocar = -1;

    // Buscando posicao para inserir
    i = 0;
    while ((scores[i].pontuacao > novo_score.pontuacao) && (i < NUM_HIGH_SCORES)) {
        i++;
    }

    // Se entrar na lista, insere na posicao correta
    if (i < NUM_HIGH_SCORES) {
        for (j = NUM_HIGH_SCORES - 1; j > i ; j-- ) {
            strcpy(scores[j].nome, scores[j-1].nome);
            scores[j].pontuacao = scores[j-1].pontuacao;
        }
        strcpy(scores[i].nome, novo_score.nome);
        scores[i].pontuacao = novo_score.pontuacao;
    }

}

// salva_scores
/*
    Grava um array de scores no arquivo, no formato "pontuacao,nome"
*/
int salva_scores(SCORE *scores) {
    FILE *arq;
    int i;

    if (arq = fopen(FILENAME_HIGH_SCORES, "w")) {

        for (i = 0; i < NUM_HIGH_SCORES; i++) {
            if (!(fprintf(arq, "%d,%s\n", scores[i].pontuacao, scores[i].nome))) {
                fclose(arq);
                return 1; // Erro ao escrever para o arquivo
            }
        }

        fclose(arq);
    } else {
        return 1; // Erro ao abrir arquivo
    }

    return 0; // Tudo certo
}


// calcula_pontos
/*
    Calcula quantos pontos o usuario deve receber ao pegar determinado item
*/
int calcula_pontos(int velocidade, int tamanho, char item) {
    int pts_base, pontos_obtidos;
    switch(item) {
        case 'C':
            pts_base = PTS_BASE_COMIDA;
            break;
        case 'F':
            pts_base = PTS_BASE_FASTER;
            break;
        case 'S':
            pts_base = PTS_BASE_SLOWER;
            break;
        case 'V':
            pts_base = PTS_BASE_SKIP;
            break;
    }

    pontos_obtidos = pts_base * (tamanho / 5) * velocidade;

    return pontos_obtidos;
}

// display_high_scores
/*
    Mostra a tela com o ranking das dez melhores pontuacoes
*/
void display_high_scores() {
    SCORE scores[NUM_HIGH_SCORES];
    int i = 0;
    char str_score[MAXSIZE_STRING_HIGHSCORES];

    carrega_score(scores);
    ordena_score(scores);

    for(i = 0; i < NUM_HIGH_SCORES; i++) {
        switch(i) {
            case 0:
                seta_cor_bg(COR_BG_PRIMEIRO);
                seta_cor_texto(COR_TEXTO_TOPSCORES);
                break;
            case 1:
                seta_cor_bg(COR_BG_SEGUNDO);
                break;
            case 2:
                seta_cor_bg(COR_BG_TERCEIRO);
                break;
            default:
                seta_cor_bg(COR_BG_CENARIO);
                seta_cor_texto(COR_TEXTO_PADRAO);
                break;
        }
        sprintf(str_score, " %s\t%7d ", scores[i].nome, scores[i].pontuacao);
        escreve_str_xy(COLUNA_INICIO_HIGH_SCORES, LINHA_INICIO_HIGH_SCORES+i, str_score);
    }

    seta_cor_bg(COR_BG_MENU_SELECIONADO);
    seta_cor_texto(COR_TEXTO_MENU_SELECIONADO);
    escreve_str_xy(COLUNA_INICIO_HIGH_SCORES + 4, LINHA_INICIO_HIGH_SCORES+i+1, "  VOLTAR  "); // +4 para ficar visualmente um pouco mais centralizado
    seta_cor_bg(COR_BG_CENARIO);
    seta_cor_texto(COR_TEXTO_PADRAO);
    vai_para_xy(41, LINHA_INICIO_HIGH_SCORES+i+1); // x=41 para o cursos ficar embaixo da letra R

    while(pega_char() != ASCII_ENTER);
}



// PARA DEBUG

// display_scores: funcao auxiliar para DEBUG
/*
   Mostra um array de scores na tela com formatacao arbitraria para debug
*/
void display_scores(SCORE *scores, int num_scores) {
    int i;

    printf("========\nSCORES:\n\n");

    for (i = 0; i < num_scores; i++) {
        printf("%s\t%d\n", scores[i].nome, scores[i].pontuacao);
    }

    printf("========\n");

}


// processa_score_final
/*
    Verifica se a pontuacao final foi suficiente para entrar no ranking de High Scores.
    Em caso positivo, inicia o processo de insercao nele.
*/
void processa_score_final(int pontuacao){
    SCORE scores[NUM_HIGH_SCORES], novo_high_score;
    int i = 0, entra = 0;

    carrega_score(scores);

    while (i < NUM_HIGH_SCORES && !entra) {
        if (pontuacao > scores[i].pontuacao) {
            entra = 1;
        }
        i++;
    }

    if(entra) {
        novo_high_score.pontuacao = pontuacao;
        limpa_retangulo(LINHA_INICIO_ENTRAHIGHSCORE, LINHA_FIM_ENTRAHIGHSCORE, COLUNA_INICIO_ENTRAHIGHSCORE, COLUNA_FIM_ENTRAHIGHSCORE, COR_BG_MSG);
        escreve_str_xy(COLUNA_INICIO_ENTRAHIGHSCORE+5, LINHA_INICIO_ENTRAHIGHSCORE+1, "VOCE ENTROU NO TOP 10!!!");
        pega_nome(novo_high_score.nome);
        insere_score(scores, novo_high_score);
        salva_scores(scores);
    }

}

