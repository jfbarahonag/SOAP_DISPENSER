#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
//IDF libraries
#include "esp_log.h"
//Custom libraries
#include "gpio_driver.h"
#include "timer_driver.h"

const char *TAG = "MAIN";

void timer_callback(void *args)
{
    static int cnt = 0;
    ESP_LOGI("TIMER [ISR]", "TICK %d", cnt++);
}

void app_main(void)
{
    ESP_ERROR_CHECK(timer_driver_init(1000000, &timer_callback));
    
    ESP_ERROR_CHECK(gpio_pin_init(UI_LED_PIN, GPIO_MODE_OUTPUT));
    ESP_ERROR_CHECK(gpio_pin_init(SENSOR_INPUT_PIN, GPIO_MODE_INPUT));
    
    while(1) {
        //gpio_set_level(UI_LED_PIN, gpio_get_level(SENSOR_INPUT_PIN));    
    }
}

