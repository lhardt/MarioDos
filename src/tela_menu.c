/**
 * MarioDos.
 *   tela_menu.c - tela de menu do jogo.
 *
 * (C) 2021 Ana Laura e Léo Hardt.
 *
 * Este arquivo contém as definições da tela de menu do jogo.
 * é nesta tela em que o jogo inicia, e nela o usuário pode
 * escolher jogar, carregar mapas, etc.
 */
#include "telas.h"

#include <stdlib.h>

#define OPTIONS 7

struct TelaMenuInfo {
	Color cores[2];
	int options[10];
};

void changeSelected(int upDown, int *options){
    int selecionada = -1;

    for (int x=0; x<OPTIONS && selecionada==-1;x++ ){
        if (options[x] !=0){
            selecionada = x;
        }
    }
    if(upDown==1){  //KEY_DOWN
        if (selecionada == OPTIONS-1){ // Se selecionada é a última opção
            options[0] = 1; // A primeira opção agora a selecionada
        }
        else{
            options[selecionada+1] =1;
        }
    }
    else if (upDown ==-1){  //KEY_UP
        if (selecionada == 0){ // Se selecionada é a primeira opção
            options[OPTIONS-1] = 1; // A última opção agora é a selecionada
        }
        else{
            options[selecionada-1] =1;
        }
    }

     options[selecionada]=0;
}


void telamenu_inicia(Jogo * j){
	// NOTE: a função calloc garante que tudo será
	// inicializado com 0000, então todas as outras
	// opções estarão em branco.
	j->tela_menu = calloc(1, sizeof(TelaMenuInfo));
	j->tela_menu->cores[0] = WHITE;
    j->tela_menu->cores[1] = BLUE;
	j->tela_menu->options[0] = 1;
}

void telamenu_desenha(Jogo * j){
	ClearBackground(BLACK);

	Vector2 pos;
	pos.x = 190;
	pos.y = 200;

	TelaMenuInfo * tela = j->tela_menu;

	// NOTE: isso pode ser feito com um FOR. Cada elemento fica a uma altura fixa dos outros.
	DrawTextEx(j->fonte_menu, "Novo jogo", pos, 20, 5, tela->cores[tela->options[0]]);
	DrawText("Continuar", 190, 230, 20, tela->cores[tela->options[1]]);
	DrawText("Carregar mapa", 190, 260, 20, tela->cores[tela->options[2]]);
	DrawText("Ranking", 190, 290, 20, tela->cores[tela->options[3]]);
	DrawText("Ajuda", 190, 320, 20, tela->cores[tela->options[4]]);
	DrawText("Sobre", 190,350, 20, tela->cores[tela->options[5]]);
	DrawText("Sair", 190, 380, 20, tela->cores[tela->options[6]]);
}

void telamenu_entrada(Jogo * j){
	TelaMenuInfo * tela = j->tela_menu;

	if (IsKeyPressed(KEY_UP)){
		changeSelected(-1, tela->options);
	}
	else if(IsKeyPressed(KEY_DOWN)){
		changeSelected(1, tela->options);
	}
}

void telamenu_logica(Jogo * j){

}

void telamenu_termina(Jogo * j){
	free(j->tela_menu);
	j->tela_menu = NULL;
}
