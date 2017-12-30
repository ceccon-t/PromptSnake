#include "coordenada.h"

// proxima_coordenada
/*
    Recebendo a coordenada atual da cabeca da cobra e sua direcao atual, retorna a proxima coordenada em que ela deve estar.
*/
COORDENADA proxima_coordenada(COORDENADA coord_atual, char direcao) {
    COORDENADA proxima_coord;

    switch(direcao) {
        case 'c':
            proxima_coord.x = coord_atual.x;
            proxima_coord.y = coord_atual.y - 1;
            break;
        case 'b':
            proxima_coord.x = coord_atual.x;
            proxima_coord.y = coord_atual.y + 1;
            break;
        case 'd':
            proxima_coord.x = coord_atual.x + 1;
            proxima_coord.y = coord_atual.y;
            break;
        case 'e':
            proxima_coord.x = coord_atual.x - 1;
            proxima_coord.y = coord_atual.y;
            break;
    }

    return proxima_coord;
}

