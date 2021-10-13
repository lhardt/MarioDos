/**
 * MarioDos.
 *   jogo.c - funções gerais para a divisão do jogo em telas.
 *
 * (C) 2021 Ana Laura e Léo Hardt.
 *
 * Este arquivo contém funções do loop de jogo básico, bem como
 * a declaração destas funções para cada uma das telas.
 */
#include "jogo.h"

#include <string.h>

void jogo_inicia(Jogo * j){
	j->janela_largura = 800;
	j->janela_altura = 450;
	strcpy(j->janela_titulo, "MarioDos - Ana Laura e Léo Hardt");

	InitWindow(j->janela_largura, j->janela_altura, j->janela_titulo);

	// NOTE: carregar fontes só DEPOIS InitWindow();
	j->fonte_menu = LoadFont("resources/fonts/SuperMario256.ttf");

	// O jogo começa no menu.
	j->tipo_tela = TELA_MENU;
	telamenu_inicia(j);

    SetTargetFPS(60);
}
void jogo_entrada(Jogo * j){
	switch(j->tipo_tela){
		case TELA_MENU:
			telamenu_entrada(j);
			break;
		// ...
		default: break;
	}
}
void jogo_desenha(Jogo * j){
	switch(j->tipo_tela){
		case TELA_MENU:
			telamenu_desenha(j);
			break;
		// ...
		default: break;
	}
}
void jogo_logica(Jogo * j){
	switch(j->tipo_tela){
		case TELA_MENU:
			telamenu_logica(j);
			break;
		// ...
		default: break;
	}
}
void jogo_termina(Jogo * j){
	tela_termina(j);

	UnloadFont(j->fonte_menu);
	CloseWindow();
}
void jogo_troca_tela(Jogo * j, Tela nova_tela){
	tela_termina(j);
	j->tipo_tela = nova_tela;
	tela_inicia(j);
}

void tela_inicia(Jogo * j){
	switch(j->tipo_tela){
		case TELA_MENU:
			telamenu_inicia(j);
			break;
		// ...
		default: break;
	}
}
void tela_desenha(Jogo * j){
	switch(j->tipo_tela){
		case TELA_MENU:
			telamenu_desenha(j);
			break;
		// ...
		default: break;
	}
}
void tela_entrada(Jogo * j){
	switch(j->tipo_tela){
		case TELA_MENU:
			telamenu_entrada(j);
			break;
		// ...
		default: break;
	}
}
void tela_logica(Jogo * j){
	switch(j->tipo_tela){
		case TELA_MENU:
			telamenu_logica(j);
			break;
		// ...
		default: break;
	}
}
void tela_termina(Jogo * j){
	switch(j->tipo_tela){
		case TELA_MENU:
			telamenu_termina(j);
			break;
		// ...
		default: break;
	}
}
