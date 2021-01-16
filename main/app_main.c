/* GPIO Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "driver/gpio.h"

#define UI_LED_PIN GPIO_NUM_19
#define SENSOR_INPUT_PIN GPIO_NUM_22

void gpio_pin_init(gpio_num_t pin, gpio_mode_t mode)
{
    gpio_config_t cfg = {
        .mode = mode,
        .pin_bit_mask = 1 << pin,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .pull_up_en = GPIO_PULLUP_DISABLE
    };
    gpio_config(&cfg);

    if (mode == GPIO_MODE_OUTPUT) {
        gpio_set_level(pin, 1);
    }
}

void app_main(void)
{
   
    gpio_pin_init(UI_LED_PIN, GPIO_MODE_OUTPUT);
    gpio_pin_init(SENSOR_INPUT_PIN, GPIO_MODE_INPUT);
    
    while(1) {
        gpio_set_level(UI_LED_PIN, gpio_get_level(SENSOR_INPUT_PIN));
    }
}

