#include "gpio_driver.h"
#include "esp_log.h"//TEMPORAL

esp_err_t gpio_driver_pin_init(gpio_num_t pin, gpio_mode_t mode, gpio_pulldown_t pulldown_en, gpio_pullup_t pullup_en)
{
    gpio_config_t cfg = {
        .mode = mode,
        .pin_bit_mask = 1 << pin,
        .pull_down_en = pulldown_en,
        .pull_up_en = pullup_en
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

esp_err_t gpio_driver_pin_intr_init(gpio_num_t pin, gpio_pulldown_t pulldown_en, gpio_pullup_t pullup_en, void (*gpio_callback)(void* arg))
{
    gpio_config_t cfg = {
      .intr_type = GPIO_PIN_INTR_DISABLE,
      .pin_bit_mask = 1ULL << pin,
      .mode = GPIO_MODE_INPUT,
      .pull_up_en = pullup_en,
      .pull_down_en = pulldown_en,
    };
    gpio_config(&cfg);

    esp_err_t ret = gpio_install_isr_service(0);

    if (ret != ESP_OK)
    {
        ESP_LOGI("GPIO", "ISR install failed");
        return ret;
    }

    gpio_isr_handler_add(pin, gpio_callback, NULL);

    gpio_set_intr_type(pin, GPIO_INTR_POSEDGE);
    
    return gpio_intr_enable(pin);
}

void gpio_driver_pin_set_high(gpio_num_t pin)
{
    gpio_set_level(pin, 1);
}

void gpio_driver_pin_set_low(gpio_num_t pin)
{
    gpio_set_level(pin, 0);
}