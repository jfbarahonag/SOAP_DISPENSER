#ifndef __GPIO_IFACE_H_
#define __GPIO_IFACE_H_

#include "driver/gpio.h"

//- - - - MCU SPECIFIC - - - -//
#define UI_LED_PIN GPIO_NUM_19
//#define UI_LED_DISPENSER_PIN GPIO_NUM_23
#define SENSOR_INPUT_PIN GPIO_NUM_22
//- - - - - - - - - - - - - - //
typedef struct gpio_iface_
{
    int pin;
	bool state;
}gpio_iface_t;

//global
gpio_iface_t gpio_iface;

int gpio_iface_init (gpio_iface_t *iface, int pin);

#endif