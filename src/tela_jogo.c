/**
 * MarioDos.
 *   tela_jogo.c - tela de jogo do jogo.
 *
 * (C) 2021 Ana Laura e Léo Hardt.
 *
 * Este arquivo contém as definições da tela de jogo do jogo.
 * é nesta tela em que o mapa do jogo é montado e o usuário pode
 * começar a jogar.
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
	j->tela_jogo->nMapa = 0;// Depois tem que mudar pra funcionar com os jogos carregados, mas por padrão começa em 0
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
	}///Teste carregando só a fase 1



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
