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
#include "assert.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h> // TEMPORARIO PRA DEBUG

#define OPTIONS 7

typedef enum TelaMenuOption {
    O_NOVO_JOGO =0,
	O_CONTINUAR,
	O_CARREGAR_MAPA,
	O_RANKING,
	O_AJUDA,
	O_SOBRE,
	O_SAIR,
	N_OPTIONS,
} TelaMenuOption;

struct TelaMenuInfo {
	Color cores[2];
	int options[10];
	TelaMenuOption selecionada;
};

// NOTE: Antigo escolheTela(). Não sei se o que eu fiz é o melhor modelo
// Mas se fossemos divorciar o handling do 'escolheTela', acabaríamos tendo
// que verificar se opcao == O_SAIR duas vezes.
void menu_opcao_selecionada(Jogo * j, TelaMenuOption opcao){
    switch (opcao){
        case O_NOVO_JOGO:
            strcpy(j->nome_fase, "fase1.txt");
            j->num_fase = 1;
            jogo_troca_tela(j, TELA_NOME);
            break;
        case O_CONTINUAR:
			jogo_troca_tela(j, TELA_NOME);
			break;
		case O_CARREGAR_MAPA:
            j->num_fase =-1;
		    jogo_troca_tela(j, TELA_CARREGA);
		    break;
		case O_RANKING:
		    jogo_troca_tela(j,TELA_HIGHSCORE);
		    break;
		case O_AJUDA:
		case O_SOBRE:
			TODO();
			break;
		case O_SAIR:

			j->sair=true;
			break;
		default:
			ASSERT(false /* ? */);
	        break;
    }

	ASSERT(false /* Opção inválida */);
}

void trocarSelecionada(int upDown, int *options, TelaMenuOption *selecionada){
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

	j->pontos =0;
	j->num_power =0;
}

void telamenu_desenha(Jogo * j){
	ClearBackground(BLACK);

	Vector2 pos;
	pos.x = TELA_LARGURA / 2;
	pos.y = 300;

	TelaMenuInfo * tela = j->tela_menu;

	// NOTE: isso pode ser feito com um FOR. Cada elemento fica a uma altura fixa dos outros.
	char * texts[] = {"Novo Jogo", "Continuar", "Carregar mapa", "Ranking", "Ajuda", "Sobre", "Sair"};
	for (int x=0; x< OPTIONS; x++){
        pos.y +=40;
		texto_centralizado(j->fonte_menu, texts[x], pos, tela->cores[tela->options[x]]);
	}

	pos.x = TELA_LARGURA / 2;
	pos.y = TELA_ALTURA - 50;
	texto_centralizado(GetFontDefault(), "Algorítmos e Programação.", pos, WHITE);
	pos.y += 20;
	texto_centralizado(GetFontDefault(), "Ana Laura & Léo Hardt.", pos, WHITE);

	textura_desenha(j, T_LOGO, (Vector2){.x=TELA_LARGURA/2, .y=150});
	// textura_desenha(j, T_LOGO, (Vector2){.x=500, .y=50});
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
		menu_opcao_selecionada(j, tela->selecionada);

    }
}

void telamenu_logica(Jogo * j){
	// Animação de início caberia aqui.
}

void telamenu_termina(Jogo * j){
	free(j->tela_menu);
	j->tela_menu = NULL;
}
