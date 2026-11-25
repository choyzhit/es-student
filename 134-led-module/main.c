#include "pico/stdlib.h"
#include <stdio.h>
#include "led.h"
#include "hardware/gpio.h"
#include "log.h"

const uint BUTTON_PIN = 15;


bool get_button_debounce(uint pin)
{
   int count = 0;
   for (int i = 0; i < 10; i++)
   {
    if (gpio_get(pin))
    {
        count++;
    }
    sleep_ms(1);
   }
   return count > 5;
}
void handle_command(int command)
{
   if (command == 'e')
   {
    led_set(true);
    LOG_INF("led %s\n", led_is_on() ? "on" : "off");
   }
   else if (command == 'd')
   {
    led_set(false);
    LOG_INF("led %s\n", led_is_on() ? "on" : "off");
   }
   else if (command == 'v')
   {
    log_version();
   }
   else
   {
   LOG_ERR("unknown command: %c\n", command);
   }
}


int main()
{
    stdio_init_all();
    log_version();

    // Настройка светодиода
    led_init();

    // Настройка кнопки
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);


    bool previous = true;


    while (1)
    {
        bool current = get_button_debounce(BUTTON_PIN);

        // Проверяем нажатие кнопки
        if (previous == true && current == false)
        {
            led_toggle();
            LOG_INF("led %s/n", led_is_on() ? "on" : "off");
        }
        previous = current;

            int command = getchar_timeout_us(0);
            if (command == PICO_ERROR_TIMEOUT)
            {
                continue;
            }


            LOG_DBG("GOT %c\n", command);


        handle_command(command);

}
}
