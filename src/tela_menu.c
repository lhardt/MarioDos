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
#include "jogo.h"
#include "textura.h"

#include <stdlib.h>
#include <stdio.h> // TEMPORARIO PRA DEBUG

#define OPTIONS 7

struct TelaMenuInfo {
	Color cores[2];
	int options[10];
	int selecionada;
};

Tela escolheTela(int selecionada){
    switch (selecionada){ //ADICIONAR OUTRAS TELAS
        case 0: return TELA_JOGO;
        break;
    }
    return TELA_JOGO;//TIRAR DPS
}

void trocarSelecionada(int upDown, int *options, int *selecionada){
    /*int selecionada = -1;

    for (int x=0; x<OPTIONS && selecionada==-1;x++ ){
        if (options[x] !=0){
            selecionada = x;
        }
    }*/
     options[(*selecionada)]=0;
    if(upDown==1){  //KEY_DOWN
        if (*selecionada == OPTIONS-1){ // Se selecionada é a última opção
            options[0] = 1; // A primeira opção agora a selecionada
            *selecionada = 0;
        }
        else{
            options[(*selecionada)+1] =1;
            (*selecionada) ++;
        }
    }
    else if (upDown ==-1){  //KEY_UP
        if (*selecionada == 0){ // Se selecionada é a primeira opção
            options[OPTIONS-1] = 1; // A última opção agora é a selecionada
            *selecionada = OPTIONS-1;
        }
        else{
            options[(*selecionada)-1] =1;
            (*selecionada) --;
        }
    }
}


void telamenu_inicia(Jogo * j){
	// NOTE: a função calloc garante que tudo será
	// inicializado com 0000, então todas as outras
	// opções estarão em branco.
	j->tela_menu = calloc(1, sizeof(TelaMenuInfo));
	j->tela_menu->cores[0] = WHITE;
    j->tela_menu->cores[1] = BLUE;
	j->tela_menu->options[0] = 1;
	j->tela_menu->selecionada=0;
}

void telamenu_desenha(Jogo * j){
	ClearBackground(BLACK);

	Vector2 pos;
	pos.x = 190;
	pos.y = 200;

	TelaMenuInfo * tela = j->tela_menu;

		char * text;

	// NOTE: isso pode ser feito com um FOR. Cada elemento fica a uma altura fixa dos outros.
	for (int x=0; x< OPTIONS; x++){
            pos.y +=30;
    // Tried to, didn't work : char texts[][] = {"Continuar", "Carregar mapa", "Ranking", "Ajuda", "Sobre", "Sair" };, so:
        switch (x){
            case 0: text =  "Novo jogo";
            break;
            case 1: text =  "Continuar";
            break;
            case 2: text =  "Carregar mapa";
            break;
            case 3: text =  "Ranking";
            break;
            case 4: text =  "Ajuda";
            break;
            case 5: text =  "Sobre";
            break;
            case 6: text =  "Sair";
            break;
        }
        DrawTextEx(j->fonte_menu, text, pos, 20, 5, tela->cores[tela->options[x]]);
	}

	textura_desenha(j, T_LOGO, (Vector2){.x=500, .y=50});
}

void telamenu_entrada(Jogo * j){
    TelaMenuInfo * tela = j->tela_menu;

	if (IsKeyPressed(KEY_UP)){
		trocarSelecionada(-1, tela->options, &(tela->selecionada));
	}
	else if(IsKeyPressed(KEY_DOWN)){
		trocarSelecionada(1, tela->options, &(tela->selecionada));
	}
	else if(IsKeyPressed(KEY_ENTER)){
         //Se não for "sair"
        if (tela->selecionada!= OPTIONS-1){ //CRIAR CONSTANTES?
            jogo_troca_tela(j, escolheTela(tela->selecionada));
        }
        // O QUE A GENTE VAI FAZER NO FIM? EXIBER ALGUMA TELA "ADEUS" OU SÒ FECHAR?

    }
}

void telamenu_logica(Jogo * j){
	// Animação de início caberia aqui.
}

void telamenu_termina(Jogo * j){
	free(j->tela_menu);
	j->tela_menu = NULL;
}
