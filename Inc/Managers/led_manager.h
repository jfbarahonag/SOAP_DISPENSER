#ifndef __LED_MANAGER_H_
#define __LED_MANAGER_H_

#include "led_fsm.h"

void led_manager_init (led_handle_t *led, int pin);
void led_manager_run (led_handle_t *led);

#endif