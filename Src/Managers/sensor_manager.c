#include "gpio_driver.h"
#include "sensor_manager.h"
#include "main_fsm.h"

/*
* SET CALLBACK BEFORE TO CALL INIT FUNCTION !!!!
*/

void sensor_manager_set_callback(sensor_t *sensor, void (*callback)(void *arg))
{
    sensor->callback = callback;
}

int sensor_manager_init(sensor_t *sensor, int pin)
{
    sensor->iface.pin = pin;

    if (gpio_driver_pin_intr_init(pin, GPIO_PULLDOWN_DISABLE, GPIO_PULLUP_DISABLE, sensor->callback) != ESP_OK)
    {
        return -1;
    }
    return 0;
}

inline int sensor_manager_get_level(sensor_t *sensor)
{
    return gpio_driver_get_level(sensor->iface.pin);
}