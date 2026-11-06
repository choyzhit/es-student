#include "pico/stdlib.h"
const uint BUTTON_PIN = 15;
const uint LED_PIN = 14;

int main()
{
    // Настройка светодиода
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_put(LED_PIN, 0);

    // Настройка кнопки
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);

    bool previous = true;
    bool led = false;

    while (1)
    {
        bool current = gpio_get(BUTTON_PIN);

        // Проверяем нажатие кнопки
        if (previous == true && current == false)
        {
            led = !led;
            gpio_put(LED_PIN, led);

            sleep_ms(30);
        }

        previous = current;

        sleep_ms(10);
    }
}
