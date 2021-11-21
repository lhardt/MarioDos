#include <unity.h>
#include <stdbool.h>
#include "carregador.h"

void assert_mario_igual(Mario mario, Mario mario_cp){
	TEST_ASSERT_TRUE(mario.vel.x == mario_cp.vel.x);
	TEST_ASSERT_TRUE(mario.vel.y == mario_cp.vel.y);
	TEST_ASSERT_TRUE(mario.pos.x == mario_cp.pos.x);
	TEST_ASSERT_TRUE(mario.pos.y == mario_cp.pos.y);
	TEST_ASSERT_TRUE(mario.score == mario_cp.score);
	TEST_ASSERT_TRUE(mario.vidas == mario_cp.vidas);
}

void assert_moeda_igual(Moeda moeda, Moeda moeda_cp){
	TEST_ASSERT_TRUE(moeda.pos.x == moeda_cp.pos.x);
	TEST_ASSERT_TRUE(moeda.pos.y == moeda_cp.pos.y);
	TEST_ASSERT_TRUE(moeda.vel.x == moeda_cp.vel.x);
	TEST_ASSERT_TRUE(moeda.vel.y == moeda_cp.vel.y);
	TEST_ASSERT_TRUE(moeda.coletada == moeda_cp.coletada);
}

void assert_inimigo_igual(Inimigo inimigo, Inimigo inimigo_cp){
	TEST_ASSERT_TRUE(inimigo.tipo == inimigo_cp.tipo);
	TEST_ASSERT_TRUE(inimigo.vivo == inimigo_cp.vivo);
	TEST_ASSERT_TRUE(inimigo.vel.x == inimigo_cp.vel.x);
	TEST_ASSERT_TRUE(inimigo.vel.y == inimigo_cp.vel.y);
	TEST_ASSERT_TRUE(inimigo.pos.x == inimigo_cp.pos.x);
	TEST_ASSERT_TRUE(inimigo.pos.y == inimigo_cp.pos.y);
	TEST_ASSERT_TRUE(inimigo.vulnerabilidade == inimigo_cp.vulnerabilidade);
}

void teste_carrega_vec(void){
	FILE * saida;
	bool open = abre_arquivo("teste.state", &saida, false);

	TEST_ASSERT_TRUE(open);

	Vector2 vec1 = {.x=5, .y=20}, vec1_cp;
	Vector2 vec2 = {.x=8, .y=-15}, vec2_cp;

	print_vector2(saida, vec1);
	print_vector2(saida, vec2);

	fclose(saida);

	bool open2 = abre_arquivo("teste.state", &saida, true);

	TEST_ASSERT_TRUE(open2);

	scan_vector2(saida, &vec1_cp);
	scan_vector2(saida, &vec2_cp);

	fclose(saida);

	TEST_ASSERT_EQUAL_INT(vec1_cp.x, vec1.x);
	TEST_ASSERT_EQUAL_INT(vec2_cp.x, vec2.x);
	fclose(saida);
}

void teste_carrega_moeda(void) {
	FILE * saida;
	bool open = abre_arquivo("teste.state", &saida, false);

	TEST_ASSERT_TRUE(open);

	Moeda moeda_cp, moeda = {
		.pos = {0.6, 1.07},
		.vel = {125, 15.7},
		.coletada = true
	};
	bool success = print_moeda(saida, moeda);

	TEST_ASSERT_TRUE(success);

	fclose(saida);

	success = abre_arquivo("teste.state", &saida, true);

	scan_moeda(saida, &moeda_cp);

	assert_moeda_igual(moeda, moeda_cp);

	fclose(saida);
}

void teste_carrega_inimigo(void) {
	FILE * saida;
	bool open = abre_arquivo("teste.state", &saida, false);

	TEST_ASSERT_TRUE(open);

	Inimigo inimigo_cp, inimigo = {
		.tipo = T_CARANGUEJO,
		.vivo = true,
		.pos = (Vector2f) {.x = 15.5, .y = 18.8},
		.vel = (Vector2f) {.x = 15.5, .y = 18.8},
		.vulnerabilidade = V_VULNERAVEL,
	};
	bool success = print_inimigo(saida, inimigo);
	TEST_ASSERT_TRUE(success);
	fclose(saida);

	success = abre_arquivo("teste.state", &saida, true);

	success = scan_inimigo(saida, &inimigo_cp);

	assert_inimigo_igual(inimigo, inimigo_cp);

	fclose(saida);
}

void teste_carrega_mario(void) {
	FILE * saida;
	bool open = abre_arquivo("teste.state", &saida, false);

	TEST_ASSERT_TRUE(open);

	Mario mario_cp, mario = {
		.pos = (Vector2f) {.x = 15.5, .y = 18.8},
		.vel = (Vector2f) {.x = 15.5, .y = 18.8},
		.score = 1671,
		.vidas = 2,
	};
	bool success = print_mario(saida, mario);
	TEST_ASSERT_TRUE(success);
	fclose(saida);

	success = abre_arquivo("teste.state", &saida, true);

	scan_mario(saida, &mario_cp);

	TEST_ASSERT_TRUE(mario.vel.x == mario_cp.vel.x);
	TEST_ASSERT_TRUE(mario.vel.y == mario_cp.vel.y);
	TEST_ASSERT_TRUE(mario.pos.x == mario_cp.pos.x);
	TEST_ASSERT_TRUE(mario.pos.y == mario_cp.pos.y);
	TEST_ASSERT_TRUE(mario.score == mario_cp.score);
	TEST_ASSERT_TRUE(mario.vidas == mario_cp.vidas);


	fclose(saida);
}

void teste_carrega_fase(void){
	FILE * saida;
	bool open = abre_arquivo("teste.state", &saida, false);

	TEST_ASSERT_TRUE(open);

	Fase f_cp, f = {
		.mapa={{'0'}},
		.mario = {
			.pos = (Vector2f) {.x = 15.5, .y = 18.8},
			.vel = (Vector2f) {.x = 15.5, .y = 18.8},
			.score = 1671,
			.vidas = 2,
		},

		.n_moedas = 2,
		.moedas = {
			(Moeda){
				.pos = {0.6, 1.07},
				.vel = {125, 15.7},
				.coletada = true
			},
			(Moeda){
				.pos = {6.6, 9.07},
				.vel = {125, 5.7},
				.coletada = false
			}
		},

		.n_inimigos = 3,
		.inimigos = {
			{
				.tipo = T_CARANGUEJO,
				.vivo = true,
				.pos = (Vector2f) {.x = 15.5, .y = 18.8},
				.vel = (Vector2f) {.x = 15.5, .y = 18.8},
				.vulnerabilidade = V_VULNERAVEL,
			},
			{
				.tipo = T_TARTARUGA,
				.vivo = true,
				.pos = (Vector2f) {.x = 15.5, .y = 18.8},
				.vel = (Vector2f) {.x = 15.5, .y = 18.8},
				.vulnerabilidade = V_VULNERAVEL,
			},
			{
				.tipo = T_CARANGUEJO,
				.vivo = false,
				.pos = (Vector2f) {.x = 0.5, .y = 18.8},
				.vel = (Vector2f) {.x = 1.5, .y = 18.8},
				.vulnerabilidade = V_INVULNERAVEL,
			}
		},

		.n_mapa=1,

		.n_caranguejos=5,
		.n_tartarugas=3,
		.delay=78
	};

	for(int i = 0; i < FASE_ALTURA; ++i){
		for(int j = 0; j < FASE_LARGURA; ++j){
			f.mapa[i][j] = 'p';
		}
	}

 	bool success = print_fase(saida, f);

	fclose(saida);
	success = abre_arquivo("teste.state", &saida, true);

	success = scan_fase(saida, &f_cp);

	TEST_ASSERT_TRUE(success);

	assert_mario_igual(f.mario, f_cp.mario);

	TEST_ASSERT_TRUE(f.n_moedas == f_cp.n_moedas);
	for(int i = 0; i < f.n_moedas; ++i){
		assert_moeda_igual(f.moedas[i], f_cp.moedas[i]);
	}

	TEST_ASSERT_TRUE(f.n_inimigos == f_cp.n_inimigos);
	for(int i = 0; i < f.n_inimigos; ++i){
		assert_inimigo_igual(f.inimigos[i], f_cp.inimigos[i]);
	}

	fclose(saida);
}
