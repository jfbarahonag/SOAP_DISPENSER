#include "dispenser_manager.h"
#include "gpio_driver.h"

void dispenser_manager_init(dispenser_t *disp, int pin)
{
    gpio_driver_pin_init(pin, GPIO_MODE_OUTPUT, GPIO_PULLDOWN_ENABLE, GPIO_PULLUP_DISABLE);

    disp->iface.pin = pin;
    disp->iface.state = false;

    disp->time_counter = 0;
}

void dispenser_manager_turn_on(dispenser_t *disp)
{
    gpio_driver_pin_set_high(disp->iface.pin);
}

void dispenser_manager_turn_off(dispenser_t *disp)
{
    gpio_driver_pin_set_low(disp->iface.pin);
}

void dispenser_manager_reset_timer_cnt(dispenser_t *disp)
{
    disp->time_counter = 0; 
}

void dispenser_manager_increment_timer_cnt(dispenser_t *disp)
{
    disp->time_counter++; 
}

inline uint16_t dispenser_manager_get_timer_cnt(dispenser_t *disp) //maybe is called in timer callback [DEBUG]
{
    return disp->time_counter;
}

inline bool dispenser_manager_is_timeout_reached(dispenser_t *disp)
{
    return disp->time_counter >= TIMEOUT_VALUE_MS;
}