#ifndef __GPIO_DRIVER_H_
#define __GPIO_DRIVER_H_

#define UI_LED_PIN GPIO_NUM_19
#define SENSOR_INPUT_PIN GPIO_NUM_22

#include"driver/gpio.h"

esp_err_t gpio_pin_init(gpio_num_t pin, gpio_mode_t mode, gpio_pulldown_t pulldown_en, gpio_pullup_t pullup_en);
esp_err_t gpio_pin_intr_init(gpio_num_t pin, gpio_pulldown_t pulldown_en, gpio_pullup_t pullup_en, void (*gpio_callback)(void* arg));

#endif