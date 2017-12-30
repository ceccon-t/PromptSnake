#ifndef H_COORDENADA
#define H_COORDENADA

#ifndef H_CONSTANTS
    #include "constants.h"
#endif

#define X_POS 0
#define Y_POS 1

typedef struct coordenada {
    int x;
    int y;
} COORDENADA;

// proxima_coordenada
/*
    Recebendo a coordenada atual da cabeca da cobra e sua direcao atual, retorna a proxima coordenada em que ela deve estar.
*/
COORDENADA proxima_coordenada(COORDENADA coord_atual, char direcao);

#endif // H_COORDENADA

