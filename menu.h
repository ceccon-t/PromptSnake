#ifndef H_CONSTANTS
    #include "constants.h"
#endif // H_CONSTANTS

#ifndef H_MENU
#define H_MENU

#ifndef H_INTERFACE
    #include "interface.h"
#endif // H_INTERFACE

#ifndef H_CONFIG
    #include "config.h"
#endif // H_CONFIG

// ini_display_menu
/*
    Inicializa a parte estatica do menu na tela
*/
void ini_display_menu();

// display_menu
/*
    Inicializa o menu na tela
*/
void display_menu(char items_menu[NUM_OPCOES][MAXSIZE_STRINGS_MENU], int selecionado);

// atualiza_menu
/*
    Redesenha na tela apenas o item do menu selecionado e o recem de-selecionado
*/
void atualiza_menu(char items_menu[NUM_OPCOES][MAXSIZE_STRINGS_MENU], int selecionado, int old_selecionado);

// controla_menu
/*
    Logica principal do menu principal, controla as funcionalidades do jogo
*/
void controla_menu(int *score, int *num_cenario, CONFIG *opcoes);

// limpa_tela_menu
/*
    Funcao auxiliar para limpar a area do menu na tela
*/
void limpa_tela_menu();

// converte_index_menu_para_valor_config
/*
    Funcao auxiliar para display_menu_opcoes, recebe o index de uma opcao no array do menu
    e converte para o valor da opcao nas configuracoes (apenas para display)
*/
int converte_index_menu_para_valor_config(int index, CONFIG opcoes);

// display_menu_opcoes
/*
    Inicializa o menu de opcoes na tela
*/
void display_menu_opcoes(char items_menu[NUM_OPCOES_CONFIG][MAXSIZE_STRINGS_MENU], int selecionado, CONFIG *opcoes);

// atualiza_menu_opcoes
/*
    Redesenha na tela apenas o item do menu selecionado e o recem de-selecionado, para o menu de opcoes
*/
void atualiza_menu_opcoes(char items_menu[NUM_OPCOES_CONFIG][MAXSIZE_STRINGS_MENU], int selecionado, int old_selecionado, CONFIG *opcoes);

// controla_menu
/*
    Logica principal do menu de opcoes, controla as configuracoes do jogo
*/
void controla_menu_opcoes(CONFIG *opcoes);

// display_creditos
/*
    Mostra a tela de creditos
*/
void display_creditos();


#endif // H_MENU
