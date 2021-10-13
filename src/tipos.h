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
} Tela;

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

	Tela		tipo_tela;

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
