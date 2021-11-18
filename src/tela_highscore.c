/**
 * MarioDos.
 *   tela_highscore.c - tela que mostra os jogadores com maior pontuação.
 *
 * (C) 2021 Ana Laura e Léo Hardt.
 *
 * Este arquivo contém as definições da tela de menu do jogo.
 * é nesta tela em que o jogo inicia, e nela o usuário pode
 * escolher jogar, carregar mapas, etc.
 */

#include "jogo.h"
#include "textura.h"
#include "assert.h"
#include <stdlib.h>
#include <string.h>

#define TAM_MAX 22

struct TelaHighscoreInfo {
    char arquivo[TAM_MAX];
    int nChar;
};

void telahighscore_inicia(Jogo * j){
    j->tela_highscore = calloc(1, sizeof(TelaHighscoreInfo));
    j->tela_highscore->nChar =0;
}

void telahighscore_desenha(Jogo * j){
    TelaHighscoreInfo * tela = j->tela_highscore;
    Rectangle textBox = {TELA_LARGURA/2.0f - 250, 300, 500, 50 };
    ClearBackground(BLACK);
    Vector2 pos = {.x=600, .y=200};
    texto_centralizado(j->fonte_menu, "Highscores: ", pos, WHITE );

    texto_centralizado(j->fonte_menu, "Pressione ENTER para voltar ao menu", (Vector2){.x=600,.y=500}, WHITE );

}

void telahighscore_entrada(Jogo *j){
    TelaHighscoreInfo * tela = j->tela_highscore;
    if (IsKeyPressed(KEY_ENTER)){
        jogo_troca_tela(j, TELA_MENU);
    }
}

void telahighscore_logica(Jogo * j){

}

void telahighscore_termina(Jogo * j){
	free(j->tela_highscore);
	j->tela_carrega = NULL;
}
