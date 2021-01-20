#ifndef __DISPENSER_MNGR_H_
#define __DISPENSER_MNGR_H_

#include <stdbool.h>

#include "gpio_iface.h"

#define DISPENSER_PIN       GPIO_NUM_23

#define TIMEOUT_VALUE_MS    1500

typedef struct dispenser_
{
    gpio_iface_t iface;
    volatile uint16_t time_counter;

}dispenser_t;

//global
dispenser_t dispenser_mngr;

void dispenser_manager_init(dispenser_t *disp, int pin);

void dispenser_manager_turn_on(dispenser_t *disp);
void dispenser_manager_turn_off(dispenser_t *disp);

void dispenser_manager_reset_timer_cnt(dispenser_t *disp);
void dispenser_manager_increment_timer_cnt(dispenser_t *disp);
uint16_t dispenser_manager_get_timer_cnt(dispenser_t *disp);
bool dispenser_manager_is_timeout_reached(dispenser_t *disp);
#endif