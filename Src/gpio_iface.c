#include <stdbool.h>

#include "gpio_driver.h"
#include "gpio_iface.h"

int gpio_iface_init (gpio_iface_t *iface, int pin)
{
    iface->pin = pin;
    iface->state = false;
    if (gpio_driver_pin_init(pin, GPIO_MODE_OUTPUT, GPIO_PULLDOWN_ENABLE, GPIO_PULLUP_DISABLE) != ESP_OK)
    {
        return -1;
    }

    return 0;
}