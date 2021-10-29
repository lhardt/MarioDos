/**
 * MarioDos.
 *   tipos.h - tipos de dados usados ao longo do programa.
 *
 * (C) 2021 Ana Laura e Léo Hardt.
 *
 * Este arquivo contém tipos de dados utilizados ao longo do programa.
 */
#ifndef TIPOS_H
#define TIPOS_H

#include <raylib.h>

typedef enum Tela {
	TELA_MENU,
	TELA_JOGO,
	TELA_HIGHSCORE,
	TELA_NENHUMA
	//TELA AJUDA/SOBRE
} Tela;

enum SoundId {
	S_AGUA = 0,
	S_DANO,
	S_INICIO,
	S_PULO,
	S_MENU_SELECT,
	S_MENU_SETA,
	S_MOEDA,
	S_GAMEOVER,
	S_MARIODIE,
	S_VIRAR,

	N_SONS
};

/* Todas as informações que são pertinentes somente a uma tela
 * deverão, idealmente, estar na estrutura da tela correspondente.
 * Cada uma dessas estruturas pode ser encontrada em seu respectivo
 * arquivo (tela_menu.c, tela_jogo.c, etc.)*/
typedef struct TelaMenuInfo TelaMenuInfo;
typedef struct TelaJogoInfo TelaJogoInfo;
typedef struct TelaHighscoreInfo TelaHighscoreInfo;

typedef struct Jogo {
	char		janela_titulo[256];
	int			janela_largura;
	int			janela_altura;

	Font 		fonte_menu;
	Sound		sons[N_SONS];

	Texture		spritesheet;

	Tela		tipo_tela;

	// Se o jogo deve fechar no próximo loop.
	bool		sair;
	// Qualquer informação que a tela atual queira guardar
	// ficaria aqui. Para a tela menu, por exemplo, pode ser
	// a opção do menu selecionada.
	union {
		TelaMenuInfo * 		tela_menu;
		TelaJogoInfo * 		tela_jogo;
		TelaHighscoreInfo * tela_highscore;
	};
} Jogo;

#endif /* TIPOS_H */
