#include "config.h"

// salva_config
/*
    Salva configuracao em arquivo binario
*/
void salva_config(CONFIG opcoes) {
    FILE *arq;

    arq = fopen(FILENAME_CONFIG, "wb");

    fwrite(&opcoes, sizeof(CONFIG), 1, arq);

    fclose(arq);

}

// carrega_config
/*
    Carrega configuracoes do arquivo binario e preenche a struct passada por referencia
    Caso haja erro ao abrir arquivo, seta um conjunto padrao de configuracoes
*/
int carrega_config(CONFIG *opcoes) {
    FILE *arq;

    if (arq = fopen(FILENAME_CONFIG, "rb")) {
        fread(opcoes, sizeof(CONFIG), 1, arq);
        return 1;
    } else {
        opcoes->velocidade_inicial = VELOCIDADEINICIAL_PADRAO;
        opcoes->maxtamanho = MAXTAMANHO_PADRAO;
        opcoes->maxitens = MAXITENS_PADRAO;
        return 0;
    }

}

