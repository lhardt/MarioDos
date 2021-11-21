#include <unity.h>
#include "maths.h"

#include "test_highscore.h"
#include "test_carregador.h"

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

// not needed when using generate_test_runner.rb
int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_grava_lista);
    RUN_TEST(teste_carrega_vec);
    RUN_TEST(teste_carrega_moeda);
    return UNITY_END();
}
