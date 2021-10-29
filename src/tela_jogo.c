/**
 * MarioDos.
 *   tela_jogo.c - tela de jogo do jogo.
 *
 * (C) 2021 Ana Laura e L�o Hardt.
 *
 * Este arquivo cont�m as defini��es da tela de jogo do jogo.
 * � nesta tela em que o mapa do jogo � montado e o usu�rio pode
 * come�ar a jogar.
 */
#include "jogo.h"
#include "textura.h"
#include <stdlib.h>

#include <unistd.h>
#include <stdio.h>

struct TelaJogoInfo {
    Fase fase;
    int nMapa;
};

void telajogo_inicia(Jogo * j){
	// NOTE: a função calloc garante que tudo será
	// inicializado com 0000, então todas as outras
	// opções estarão em branco.
	j->tela_jogo = calloc(1, sizeof(TelaJogoInfo));
	j->tela_jogo->nMapa = 0;// Depois tem que mudar pra funcionar com os jogos carregados, mas por padr�o come�a em 0

    load_fases(& j->tela_jogo->fase, "fase1.txt");

}

void telajogo_desenha(Jogo * j){
	ClearBackground(BLACK);

    fases_desenha(& j->tela_jogo->fase);

    Mario * mario = & j->tela_jogo->fase.mario;
    Vector2 pos_mario = posfloat_para_tela(mario->pos);
    textura_desenha(j, T_MARIO1, (Vector2){.x=150, .y=190});
}

void telajogo_entrada(Jogo * j){
	//TelaJogoInfo * tela = j->tela_jogo;
	if (IsKeyPressed(KEY_UP)){
	}
	else if(IsKeyPressed(KEY_DOWN)){
	}
	else if(IsKeyPressed(KEY_RIGHT)){
	}
	else if(IsKeyPressed(KEY_LEFT)){
	}
	else if (IsKeyPressed(KEY_RIGHT)){
    }
}

void telajogo_logica(Jogo * j){

}

void telajogo_termina(Jogo * j){
	free(j->tela_jogo);
	j->tela_jogo = NULL;
}
