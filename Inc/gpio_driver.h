#ifndef __GPIO_DRIVER_H_
#define __GPIO_DRIVER_H_

#include"driver/gpio.h"

esp_err_t gpio_driver_pin_init(gpio_num_t pin, gpio_mode_t mode, gpio_pulldown_t pulldown_en, gpio_pullup_t pullup_en);
esp_err_t gpio_driver_pin_intr_init(gpio_num_t pin, gpio_pulldown_t pulldown_en, gpio_pullup_t pullup_en, void (*gpio_callback)(void* arg));

void gpio_driver_pin_set_high(gpio_num_t pin);
void gpio_driver_pin_set_low(gpio_num_t pin);
#endif