#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "servo/servo.h"
#include "setup_pin/setup_pin.h"

const uint SERVO_PIN = 2;
const uint LED_PIN = 25;
const uint PIR_PIN = 0;

bool motion_detected = false;

int main()
{
    stdio_init_all();

    setup_servo(SERVO_PIN, 0);

    setup_pin(LED_PIN, GPIO_OUT);

    setup_pin(PIR_PIN, GPIO_IN);

    while (true)
    {
        if (gpio_get(PIR_PIN))
        {
            gpio_put(LED_PIN, 1);
            set_servo_position(SERVO_PIN, 2400);
            sleep_ms(1000);
        }
        else
        {
            gpio_put(LED_PIN, 0);
            set_servo_position(SERVO_PIN, 400);
        }
        sleep_ms(250);
    }

    return 0;
}
