#include "tunel.h"


// inicializa_tuneis
/*
    Inicializa o array de tuneis
*/
int inicializa_tuneis(TUNEL tuneis[MAX_TUNEIS], int numero_cenario){
    int tamanho = 0, tam_buff;
    TUNEL tun_buff;
    FILE *arq_tuneis;

    arq_tuneis = fopen(FILENAME_TUNEIS, "rb");

    while (!feof(arq_tuneis)) {
        tam_buff = fread(&tun_buff, sizeof(TUNEL), 1, arq_tuneis);

        if (tam_buff == 1 && tun_buff.cenario == numero_cenario) {
            tuneis[tamanho] = tun_buff;
            tamanho += tam_buff;
        }
    }

    fclose(arq_tuneis);

    return tamanho;

}

// posiciona_tuneis_no_cenario
/*
    Coloca os tuneis na matriz do cenario para a logica do jogo
*/
void posiciona_tuneis_no_cenario(char cenario[LINHAS_CENARIO][COLUNAS_CENARIO], TUNEL tuneis[MAX_TUNEIS], int num_tuneis) {
    int i;

    for (i = 0; i < num_tuneis; i++) {
        cenario[tuneis[i].pos.y][tuneis[i].pos.x] = 'T';
    }
}

// busca_tunel
/*
    Encontra o tunel em uma determinada coordenada, retorna sua id no array
*/
int busca_tunel(TUNEL *tuneis, COORDENADA coord, int num_tuneis) {
    int i, i_encontrado = -1; //printf("\n\n\n%d\t%d\t%d\t%d", tuneis[0].pos.x, tuneis[0].pos.y, coord.x, coord.y); getch();

    for (i = 0; i < num_tuneis; i++) {
        if ((tuneis[i].pos.x == coord.x -OFFSET_X ) && (tuneis[i].pos.y == coord.y - OFFSET_Y)) { // Arrumar offsets nas representacoes das pos x, y de cobra e tunel
            i_encontrado = i;
        }
    }

    return i_encontrado;
}

// entra_tunel
/*
    Processa a logica da entrada em um tunel, returna 1 se entrou pela direcao errada, 0 se deu tudo certo
*/
int entra_tunel(TUNEL *tuneis, COORDENADA *corpo, char *direcao, int num_tuneis) {
    int i, novo_x, novo_y;
    char nova_direcao;

    i = busca_tunel(tuneis, *corpo, num_tuneis);

    if (*direcao != tuneis[i].direcao) {
        return 1; // Cobra entrou pela direcao errada, morreu
    }

    novo_x = tuneis[tuneis[i].id_saida].pos.x;
    novo_y = tuneis[tuneis[i].id_saida].pos.y;
    nova_direcao = tuneis[tuneis[i].id_saida].direcao;

    corpo->x = novo_x;
    corpo->y = novo_y;
    *direcao = nova_direcao;

    return 0; // Sucesso

}


// desenha_tuneis
/*
    Desenha os tuneis na tela
*/
void desenha_tuneis(TUNEL tuneis[MAX_TUNEIS], int num_tuneis) {
    int i;
    char direcao;

    seta_cor_texto(COR_TEXTO_PADRAO);
    seta_cor_bg(COR_BG_CENARIO);
    for (i = 0; i < num_tuneis; i++) {
        // Determina caracter de acordo com a direcao de entrada do tunel
        switch(tuneis[i].direcao) {
            case 'b':
                direcao = '\x19';
                break;
            case 'c':
                direcao = '\x18';
                break;
            case 'e':
                direcao = '\x1b';
                break;
            case 'd':
                direcao = '\x1a';
                break;
            default:
                direcao = '0';
                break;
        }
        escreve_char_xy((tuneis[i].pos.x)+1, (tuneis[i].pos.y)+2, direcao); // Coloca tunel na tela
    }
}

