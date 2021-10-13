/**
 * MarioDos.
 *   main.c - loop principal do jogo.
 *
 * (C) 2021 Ana Laura e Léo Hardt.
 *
 * Este arquivo contém o loop principal do jogo.
 */
#include <raylib.h>

#include "jogo.h"

int main(void) {
    Jogo j;
    jogo_inicia(&j);

    while (!WindowShouldClose()) {
        jogo_entrada(&j);
        jogo_logica(&j);

        BeginDrawing();
        jogo_desenha(&j);
        EndDrawing();
    }
    jogo_termina(&j);
    return 0;
}
