/**
 * MarioDos.
 *   main.c - loop principal do jogo.
 *
 * (C) 2021 Ana Laura e Léo Hardt.
 *
 * Este arquivo contém o loop principal do jogo.
 */
#include <raylib.h>
#include <stdio.h>

#include "jogo.h"

int main(void) {
    Jogo j;
    bool sucesso = jogo_inicia(&j);

    if(! sucesso ){
        printf("Saindo sem sucesso...\n");
        return -1;
    }

    while (!WindowShouldClose() && !j.sair) {
        // FIX: console não printaria nada porque o
        // programa não manda nada se não for obrigado.
        fflush(stdout);

        jogo_entrada(&j);
        jogo_logica(&j);

        BeginDrawing();
        jogo_desenha(&j);
        EndDrawing();
    }
    jogo_termina(&j);
    return 0;
}
