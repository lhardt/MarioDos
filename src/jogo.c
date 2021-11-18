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
#include "recursos.h"
#include "assert.h"

#include <string.h>

bool jogo_inicia(Jogo * j){
	bool sucesso = true;

	j->janela_largura = TELA_LARGURA;
	j->janela_altura = TELA_ALTURA;
	strcpy(j->janela_titulo, TELA_TITULO);
	j->ticks = 0;

	InitWindow(j->janela_largura, j->janela_altura, j->janela_titulo);

	// o uso do && impede que o próximo passo rode se o anterior deu false.
	// NOTE: carregar fontes só DEPOIS InitWindow();
	sucesso = IsWindowReady()
	       && fonte_inicia(j)
		   && sons_inicia(j)
		   && imagens_inicia(j)
		   && fases_inicia(j);

	if(sucesso){
		// O jogo começa no menu.
		j->tipo_tela = TELA_MENU;
		telamenu_inicia(j);

		SetTargetFPS(60);

		return true;
	}
	return false;
}
void jogo_entrada(Jogo * j){
	tela_entrada(j);
}
void jogo_desenha(Jogo * j){
	tela_desenha(j);
}
void jogo_logica(Jogo * j){
	++j->ticks;
	tela_logica(j);
}
void jogo_termina(Jogo * j){
	tela_termina(j);
	fonte_termina(j);
	sons_termina(j);
	fases_termina(j);
	CloseWindow();
}
void jogo_troca_tela(Jogo * j, Tela nova_tela){
	tela_termina(j);
	j->tipo_tela = nova_tela;
	tela_inicia(j);
}

bool fonte_inicia(Jogo * j){
	j->fonte_menu = LoadFont(CAMINHO_FONTE_MENU);
	// Não temos como conferir se a fonte carregou?
	return true;
}

void fonte_termina(Jogo * j){
	UnloadFont(j->fonte_menu);
}

bool som_inicia(Sound * retval, const char * const file){
	ASSERT(retval != NULL && file != NULL);
	*retval = LoadSound(file);

	return retval->stream.buffer != NULL;
}

bool sons_inicia(Jogo * j){
	InitAudioDevice();
	return IsAudioDeviceReady()
		&& som_inicia(& j->sons[S_AGUA], CAMINHO_SONS "agua.wav")
		&& som_inicia(& j->sons[S_DANO], CAMINHO_SONS "dano.wav")
		&& som_inicia(& j->sons[S_INICIO], CAMINHO_SONS "inicio.wav")
		&& som_inicia(& j->sons[S_PULO], CAMINHO_SONS "pulo.wav")
		&& som_inicia(& j->sons[S_MENU_SELECT], CAMINHO_SONS "sel_menu.mp3")
		&& som_inicia(& j->sons[S_MENU_SETA], CAMINHO_SONS "seta_menu.wav")
		&& som_inicia(& j->sons[S_MOEDA], CAMINHO_SONS "smb_coin.wav")
		&& som_inicia(& j->sons[S_GAMEOVER], CAMINHO_SONS "smb_gameover.wav")
		&& som_inicia(& j->sons[S_MARIODIE], CAMINHO_SONS "smb_mariodie.wav")
		&& som_inicia(& j->sons[S_VIRAR], CAMINHO_SONS "virar.wav");
}

void sons_termina(Jogo * j){
	for(int i = 0; i < N_SONS; ++i){
		if(j->sons[i].stream.buffer != NULL)
			UnloadSound(j->sons[i]);
	}
}

bool imagens_inicia(Jogo * j){
	j->spritesheet = LoadTexture(CAMINHO_SPRITESHEET);
	// TODO: não temos uma forma de ver se carregou corretamente?
	return j->spritesheet.format != 0;
}
void imagens_termina(Jogo * j){
	UnloadTexture(j->spritesheet);
}


void tela_inicia(Jogo * j){
	switch(j->tipo_tela){
		case TELA_MENU:
			telamenu_inicia(j);
			break;
        case TELA_JOGO:
            telajogo_inicia(j);
            break;
        case TELA_CARREGA:
            telacarrega_inicia(j);
            break;
        case TELA_NOME:
            telanome_inicia(j);
            break;
		case TELA_HIGHSCORE:
			telahighscore_inicia(j);
			break;
		default: break;
	}
}
void tela_desenha(Jogo * j){
	switch(j->tipo_tela){
		case TELA_MENU:
			telamenu_desenha(j);
			break;
        case TELA_JOGO:
            telajogo_desenha(j);
            break;
        case TELA_CARREGA:
            telacarrega_desenha(j);
            break;
        case TELA_NOME:
            telanome_desenha(j);
            break;
		case TELA_HIGHSCORE:
			telahighscore_desenha(j);
			break;
		default: break;
	}
}
void tela_entrada(Jogo * j){
	switch(j->tipo_tela){
		case TELA_MENU:
			telamenu_entrada(j);
			break;
        case TELA_JOGO:
            telajogo_entrada(j);
            break;
        case TELA_CARREGA:
            telacarrega_entrada(j);
            break;
        case TELA_NOME:
            telanome_entrada(j);
            break;
		case TELA_HIGHSCORE:
			telahighscore_entrada(j);
			break;
		default: break;
	}
}
void tela_logica(Jogo * j){
	switch(j->tipo_tela){
		case TELA_MENU:
			telamenu_logica(j);
			break;
        case TELA_JOGO:
            telajogo_logica(j);
            break;
        case TELA_CARREGA:
            telacarrega_logica(j);
            break;
        case TELA_NOME:
            telanome_logica(j);
            break;
		case TELA_HIGHSCORE:
			telahighscore_logica(j);
			break;
		default: break;
	}
}
void tela_termina(Jogo * j){
	switch(j->tipo_tela){
		case TELA_MENU:
			telamenu_termina(j);
			break;
        case TELA_JOGO:
            telajogo_termina(j);
            break;
        case TELA_CARREGA:
            telacarrega_termina(j);
            break;
        case TELA_NOME:
            telanome_termina(j);
            break;
		case TELA_HIGHSCORE:
			telahighscore_termina(j);
			break;
		default: break;
	}
}
