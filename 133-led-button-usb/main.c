#include "pico/stdlib.h"
#include <stdio.h>

const uint BUTTON_PIN = 15;
const uint LED_PIN = 14;
const uint DEBOUNCE_MS = 20;


bool get_button_debounce(uint pin)
{
    bool state = gpio_get(pin);
    sleep_ms(DEBOUNCE_MS);
    return state && gpio_get(pin);
}
void set_led(bool on)
{
    gpio_put(LED_PIN, on);
    printf("led %s\n", on ? "on" : "off");
}

int main()
{
    stdio_init_all();

    // Настройка светодиода
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    set_led(false);

    // Настройка кнопки
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);


    bool previous = true;
    bool led = false;

    while (1)
    {
        bool current = get_button_debounce(BUTTON_PIN);

        // Проверяем нажатие кнопки
        if (previous == true && current == false)
        {
            led = !led;
            set_led(led);


        }

        previous = current;

        sleep_ms(10);
    }
}
