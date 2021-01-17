#include "gpio_driver.h"

esp_err_t gpio_pin_init(gpio_num_t pin, gpio_mode_t mode)
{
    gpio_config_t cfg = {
        .mode = mode,
        .pin_bit_mask = 1 << pin,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .pull_up_en = GPIO_PULLUP_DISABLE
    };

    esp_err_t ret =  gpio_config(&cfg);

    if (ret != ESP_OK)
    {
        return ret;
    }

    if (mode == GPIO_MODE_OUTPUT) {
        return gpio_set_level(pin, 0);
    }

    return ret;
}