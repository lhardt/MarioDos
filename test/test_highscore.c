#include <unity.h>
#include "jogo.h"

#include <stdbool.h>
#include <string.h>


void test_grava_lista(void){
	Highscore lista[] = {
		{.score = 300},
		{.score = 200},
		{.score = 100},
	};
	strncpy(lista[0].nome, "ANA", 4);
	strncpy(lista[1].nome, "TOM", 4);
	strncpy(lista[2].nome, "LEO", 4);

	TEST_ASSERT_TRUE(highscore_grava_lista(lista, 3));

	Highscore * lista2;
	int n_lista2;
	TEST_ASSERT_TRUE(highscore_carrega(&lista2, &n_lista2));
	TEST_ASSERT_EQUAL_INT(0, strcmp(lista2[0].nome, "ANA"));
	TEST_ASSERT_EQUAL_INT(0, strcmp(lista2[1].nome, "TOM"));
	TEST_ASSERT_EQUAL_INT(0, strcmp(lista2[2].nome, "LEO"));

	TEST_ASSERT_EQUAL_INT(lista[0].score, lista2[0].score);
	TEST_ASSERT_EQUAL_INT(lista[1].score, lista2[1].score);

}
