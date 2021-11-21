#include <unity.h>
#include <stdbool.h>
#include "carregador.h"

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

	TEST_ASSERT_TRUE(moeda.pos.x == moeda_cp.pos.x);
	TEST_ASSERT_TRUE(moeda.pos.y == moeda_cp.pos.y);
	TEST_ASSERT_TRUE(moeda.vel.x == moeda_cp.vel.x);
	TEST_ASSERT_TRUE(moeda.vel.y == moeda_cp.vel.y);
	TEST_ASSERT_TRUE(moeda.coletada == moeda_cp.coletada);

}
