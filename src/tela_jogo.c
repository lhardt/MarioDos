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
	// NOTE: a fun��o calloc garante que tudo ser�
	// inicializado com 0000, ent�o todas as outras
	// op��es estar�o em branco.
	j->tela_jogo = calloc(1, sizeof(TelaJogoInfo));
	j->tela_jogo->nMapa = 0;// Depois tem que mudar pra funcionar com os jogos carregados, mas por padr�o come�a em 0
}

void telajogo_desenha(Jogo * j){
	ClearBackground(BLACK);

	//Vector2 pos;
	//pos.x = 190;
	//pos.y = 200;

	//TelaJogoInfo *tela = j->tela_jogo;
	Fase *fase = &j->tela_jogo->fase;

	if (load_fases(fase, "fase1.txt")){
        fases_desenha(fase);
	}///Teste carregando s� a fase 1



    //DrawTextEx(j->fonte_menu, text, pos, 20, 5, tela->cores[tela->options[x]]);


	textura_desenha(j, T_LOGO, (Vector2){.x=500, .y=50});
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
