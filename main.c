/*
    ========== SNAKE =============
    Desenvolvido por Tiago Ceccon.
       2017-01 INF01202-ALGPROG
*/

#include<stdio.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>

#include "constants.h"
#include "coordenada.h"
#include "tunel.h"
#include "config.h"
#include "score.h"
#include "snake.h"
#include "cenario.h"
#include "logica.h"
#include "interface.h"
#include "menu.h"


// main
/*
    Entrada do programa, inicializa configuracoes e chama o menu, que controla as funcionalidades do jogo
*/
int main() {
    CONFIG opcoes;
    int score = 0, num_cenario = 1; // Pontuacao do jogador e cenario atual precisam ser mantidos atraves das partidas

    // Inicializa a estrutura com as configuracoes do jogo
    carrega_config(&opcoes);

    // Seed para numeros aleatorios
    srand(time(0));

    // Inicializa o menu que controla o jogo
    controla_menu(&score, &num_cenario, &opcoes);

    // Jogo encerrado, volta as cores para o padrao do terminal
    display_padrao_prompt();
    limpa_tela_full();

    return 0;
}

