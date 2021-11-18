#include <unity.h>
#include "maths.h"

#include "test_highscore.h"

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void test_function_plustwo(void) {
    TEST_ASSERT_EQUAL_INT(9, plustwo(7));
}

// not needed when using generate_test_runner.rb
int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_grava_lista);
    return UNITY_END();
}
