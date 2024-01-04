// #include "pico/stdlib.h"
// #include "hardware/pwm.h"
// #include "../setup_pin/setup_pin.h"
// #include "servo.h"

// pwm_generator setup_servo(uint pin, uint32_t frequency)
// {
//     setup_pin_fn(pin, GPIO_FUNC_PWM);

//     pwm_generator p;

//     p.slice = pwm_gpio_to_slice_num(pin);
//     p.channel = pwm_gpio_to_channel(pin);

//     pwm_set_freq_duty(p.slice, p.channel, frequency, 0);

//     return p;
// }

// void pwm_set_freq_duty(uint slice_number,
//                        uint channel, uint32_t frequency, int duty)
// {
//     uint32_t clock = 125000000;
//     uint32_t divider16 = clock / frequency / 4096 +
//                          (clock % (frequency * 4096) != 0);

//     if (divider16 / 16 == 0)
//         divider16 = 16;

//     uint32_t wrap = clock * 16 / divider16 / frequency - 1;

//     pwm_set_clkdiv_int_frac(slice_number, divider16 / 16,
//                             divider16 & 0xF);
//     pwm_set_wrap(slice_number, wrap);
//     pwm_set_chan_level(slice_number, channel, wrap * duty / 100);

//     pwm_set_enabled(slice_number, true);
// }

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