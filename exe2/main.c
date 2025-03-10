#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

#define BTN_PIN_R 28
#define BTN_PIN_V 26
#define LED_PIN_R 4
#define LED_PIN_V 6

volatile bool btn_r = false;
volatile bool btn_v = false;
volatile bool timer_ativo_r = false;
volatile bool timer_ativo_v = false;

bool timer_callback_r(repeating_timer_t *rt)
{
    timer_ativo_r = true;
    return true;
}
bool timer_callback_g(repeating_timer_t *rt)
{
    timer_ativo_v = true;
    return true;
}

void btn_callback(uint gpio, uint32_t events)
{
    if (events & GPIO_IRQ_EDGE_FALL)
    {
        if {(gpio == BTN_PIN_R)
            btn_r = !btn_r;
        }
        if {(gpio == BTN_PIN_V)
            btn_g = !btn_v;
        }
    }
}

int main()
{
    stdio_init_all();
    repeating_timer_t timer_r;

    repeating_timer_t timer_v;

    gpio_init(LED_PIN_R);
    gpio_set_dir(LED_PIN_R, GPIO_OUT);
    gpio_put(LED_PIN_R, 0);

    gpio_init(BTN_PIN_R);
    gpio_set_dir(BTN_PIN_R, GPIO_IN);
    gpio_pull_up(BTN_PIN_R);

        
    gpio_init(LED_PIN_V);
    gpio_set_dir(LED_PIN_V, GPIO_OUT);
    gpio_put(LED_PIN_V, 0);

    gpio_init(BTN_PIN_V);
    gpio_set_dir(BTN_PIN_V, GPIO_IN);
    gpio_pull_up(BTN_PIN_V);

    gpio_set_irq_enabled_with_callback(BTN_PIN_R, GPIO_IRQ_EDGE_FALL, true, &btn_callback);



    gpio_set_irq_enabled(BTN_PIN_V, GPIO_IRQ_EDGE_FALL, true);

    if (!add_repeating_timer_ms(500, timer_callback_r, NULL, &timer_r))
    {
        printf("Failed/n");
    }

    if (!add_repeating_timer_ms(250, timer_callback_g, NULL, &timer_v))
    {
        printf("Failed /n");
    }
    while (true)
    {
        if (btn_r)
        {
            if (timer_ativo_r)
            {
                gpio_put(LED_PIN_R, !gpio_get(LED_PIN_R));
                timer_ativo_r = false;
            }
        }
        else
        {
            gpio_put(LED_PIN_R, 0);
        }
        if (btn_v)
        {
            if (timer_ativo_v)
            {
                gpio_put(LED_PIN_V, !gpio_get(LED_PIN_G));
                timer_ativo_v = false;
            }
        }
        else
        {
            gpio_put(LED_PIN_V, 0);
        }
    }
}