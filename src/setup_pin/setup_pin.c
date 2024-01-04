#include "pico/stdlib.h"

void setup_pin(uint pin, bool out)
{
    gpio_init(pin);
    gpio_set_dir(pin, out);
}

void setup_pin_fn(uint pin, enum gpio_function fn)
{
    gpio_set_function(pin, fn);
}