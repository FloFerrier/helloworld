#include <stdio.h>

#include "led.h"

int main(void)
{
    printf("Hello, from helloworld!\n");

    led_init();

    led_set(0);
    uint16_t pin = led_get();

    return 0;
}
