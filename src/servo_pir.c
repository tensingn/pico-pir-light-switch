#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "servo/servo.h"
#include "setup_pin/setup_pin.h"

const uint SERVO_PIN = 2;
const uint LED_PIN = 25;
const uint PIR_PIN = 0;

bool motion_detected = false;

// void pir_irq(uint pin, uint32_t event)
// {
//     if (event == GPIO_IRQ_EDGE_RISE)
//     {
//         motion_detected = true;
//     }
//     else
//     {
//         motion_detected = false;
//     }
// }

int main()
{
    stdio_init_all();

    setup_servo(SERVO_PIN, 0);

    setup_pin(LED_PIN, GPIO_OUT);

    setup_pin(PIR_PIN, GPIO_IN);

    // gpio_set_irq_enabled_with_callback(PIR_PIN, GPIO_IRQ_EDGE_FALL | GPIO_IRQ_EDGE_RISE, true, &pir_irq);

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
        // if (motion_detected)
        // {
        //     gpio_put(LED_PIN, 1);
        //     set_servo_position(SERVO_PIN, 2400);
        //     sleep_ms(1000);
        // }
        // else
        // {
        //     gpio_put(LED_PIN, 0);
        //     set_servo_position(SERVO_PIN, 400);
        //     sleep_ms(1000);
        // }
    }

    return 0;
}
