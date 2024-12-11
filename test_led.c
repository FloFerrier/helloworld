#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <cmocka.h>

#include "led.h"

static void test_led_should_be_init(void **state) {
    (void) state;
    led_init();
}

static void test_led_should_get_value(void **state) {
    (void) state;
    uint16_t value = led_get();
    assert_int_equal(value, 0u);
}

static void test_led_should_set_value(void **state) {
    (void) state;
    uint16_t pin = 0u;
    (void)led_set(pin);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_led_should_be_init),
        cmocka_unit_test(test_led_should_get_value),
        cmocka_unit_test(test_led_should_set_value),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}