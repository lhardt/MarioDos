/**
 * MarioDos.
 *   jogo.h - funções gerais para a divisão do jogo em telas.
 *
 * (C) 2021 Ana Laura e Léo Hardt.
 *
 * Este arquivo contém funções do loop de jogo básico, bem como
 * a declaração destas funções para cada uma das telas.
 */
#ifndef JOGO_H
#define JOGO_H

#include <raylib.h>


#define TELA_TITULO ("MarioDos - Ana Laura e Léo Hardt")

/* Dados na Especificação, pg. 3 */
#define TELA_ALTURA  (700)
#define TELA_LARGURA (1200)
/* Dados na especificação, pg. 5 */
#define FASE_ALTURA (28)
#define FASE_LARGURA (121)
/* Definidos na especificação, pg. 5 */
#define TILE_LARGURA (10)  /* Equivalentemente, (TELA_LARGURA / FASE_LARGURA) */
#define TILE_ALTURA  (25)  /* Equivalentemente, (TELA_ALTURA  / FASE_ALTURA ) */

/* Definidos nas especificaçoes 3.2 (pg.4) 3.13 (pg.5) */
#define HIGHSCORES_NUM (5)

/*Alterar conforme quiser. É mais fácil que (re-)alocar memória */
#define NMAX_MOEDAS   (100)
#define NMAX_INIMIGOS (100)
#define NMAX_CANOS    ( 5 )

/* Tamanho EM TILES! */
#define MARIO_LARGURA ( 4.5*16.0 / TILE_LARGURA )
#define MARIO_ALTURA  ( 4.5*21.0 / TILE_ALTURA  )

/* Velocidade Y aumenta em 0.05 Tiles/60s a cada 1/60 segundos, isso dá 180 Tiles/s^2, se não me engano */
#define GRAVIDADE (0.05)

typedef enum Tela {
	TELA_MENU,
	TELA_JOGO,
	TELA_HIGHSCORE,
	TELA_AJUDA,
	TELA_SOBRE,
	TELA_NENHUMA
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

typedef enum Direcao {
	PARADO = 0,
	DIR_L,
	DIR_R,
	DIR_U,
	DIR_D
} Direcao;


typedef struct Moeda {
	Vector2 posicao;
	Direcao direcao;
} Moeda;


typedef enum TipoInimigo {
	T_TARTARUGA,
	T_CARANGUEJO
} TipoInimigo;

typedef enum Vulnerabilidade {
	V_IVULNERAVEL,
	/* NOTE: tartarugas não ficam furiosas. */
	V_FURIOSO,
	V_VULNERAVEL,
} Vulnerabilidade;

typedef struct Inimigo {
	TipoInimigo tipo;
	bool vivo;
	Vector2 posicao;
	Direcao direcao;

	Vulnerabilidade vulnerabilidade; /* TODO: nome mais curto? */

	/* NOTE: já que a velocidade depende inteiramente
	* do tipo e do level, não precisamos dela aqui.  */
} Inimigo;

typedef struct Vector2f {
	double x,y;
} Vector2f;

typedef struct Mario {
	Vector2f pos;
	Vector2f vel;

	int score;
	int vidas;
} Mario;

typedef struct Fase {
	char mapa[FASE_ALTURA + 1][FASE_LARGURA + 1];

	Mario mario;

	int n_moedas;
	Moeda moedas[NMAX_MOEDAS];

	int n_inimigos;
	Inimigo inimigos[NMAX_INIMIGOS];

	// vindo diretamente do arquivo
	int n_carangueijos, n_tartarugas, delay;
} Fase;


/**
 * Formas que o jogo como um todo tem de responder a eventos.
 * Geralmente mais amplas do que a de cada tela porticular.
 * Ex: Se definirmos o atalho CTRL+Q para sair do jogo, esse
 * atalho pertencerá a jogo_entrada, e não a uma tela em específico.
 *
 * Ex: se a tela atual é TELA_MENU,
 * 		tela_inicia chamará telamenu_inicia.
 */
bool jogo_inicia(Jogo * j);
void jogo_desenha(Jogo * j);
void jogo_entrada(Jogo * j);
void jogo_logica(Jogo * j);
void jogo_termina(Jogo * j);
void jogo_troca_tela(Jogo * j, Tela nova_tela);

bool imagens_inicia(Jogo * j);
void imagens_termina(Jogo * j);

bool fonte_inicia(Jogo * j);
void fonte_termina(Jogo * j);

bool sons_inicia(Jogo * j);
void sons_termina(Jogo * j);

bool fases_inicia(Jogo * j);
void fases_termina(Jogo * j);
void fases_desenha(Fase * f);
bool load_fases(Fase* f, char* arquivo);

/**
 * Funções que 'repassam' para a tela atual uma chamada.
 *
 * Ex: se a tela atual é TELA_MENU,
 * 		tela_inicia chamará telamenu_inicia.
 */
void tela_inicia(Jogo * j);
void tela_desenha(Jogo * j);
void tela_entrada(Jogo * j);
void tela_logica(Jogo * j);
void tela_termina(Jogo * j);

/**
 * Formas que o programa deve responder a um evento
 * a depender da tela em que está.
 *
 * Ex: telamenu_desenha usará informações do atributo j->tela_menu
 *      e a dsenhará.
 */
void telamenu_inicia(Jogo * j);
void telamenu_desenha(Jogo * j);
void telamenu_entrada(Jogo * j);
void telamenu_logica(Jogo * j);
void telamenu_termina(Jogo * j);

void telajogo_inicia(Jogo * j);
void telajogo_desenha(Jogo * j);
void telajogo_entrada(Jogo * j);
void telajogo_logica(Jogo * j);
void telajogo_termina(Jogo * j);

bool fase_mario_no_teto(Fase * fase);
bool fase_mario_no_chao(Fase * fase);
Rectangle mario_pos_to_screen_rect(Vector2 pos);

#endif /* JOGO_H */
