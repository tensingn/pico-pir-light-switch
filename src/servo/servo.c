#include "pico/stdlib.h"
#include <stdio.h>
#include "hardware/pwm.h"
#include "hardware/clocks.h"

float CLK_DIV = 64;
float WRAP = 39062;
float REPEAT = 20000;

void set_servo_position(uint pin, float position)
{
    pwm_set_gpio_level(pin, (position / REPEAT) * WRAP);
}

void setup_servo(uint pin, float startPosition)
{
    gpio_set_function(pin, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(pin);

    pwm_config config = pwm_get_default_config();

    pwm_config_set_clkdiv(&config, CLK_DIV);
    pwm_config_set_wrap(&config, WRAP);

    pwm_init(slice_num, &config, true);

    set_servo_position(pin, startPosition);
}