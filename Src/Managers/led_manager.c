#include "led_manager.h"
#include "led_fsm.h"

void led_manager_init (led_handle_t *led, int pin)
{
    // fsm init
    led_fsm_init(&led->fsm);
    // iface init
    gpio_iface_init(&led->iface, pin);
}

void led_manager_run (led_handle_t *led)
{
    led_fsm_run(&led->fsm);
}

void led_manager_start_error_pattern(led_handle_t *led)
{
    ///led->fsm.
}