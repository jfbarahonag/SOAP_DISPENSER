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
static bool status = true;

void timer_callback(void *args)
{
    static int cnt = 0;
    ESP_LOGI("TIMER [ISR]", "TICK %d %d", cnt++, status);
    //gpio_set_level(UI_LED_PIN, status ^= 1);
}


void gpio_callback(void *args)
{ 
    status ^= 1;

    //(status == true) ? status = false : status = true;

    gpio_set_level(UI_LED_PIN, status );
}

void app_main(void)
{
    ESP_ERROR_CHECK(timer_driver_init(1000000, &timer_callback));
    
    ESP_ERROR_CHECK(gpio_pin_init(UI_LED_PIN, GPIO_MODE_OUTPUT, GPIO_PULLDOWN_ENABLE, GPIO_PULLUP_DISABLE));
    ESP_ERROR_CHECK(gpio_pin_intr_init(SENSOR_INPUT_PIN, GPIO_PULLDOWN_DISABLE, GPIO_PULLUP_DISABLE, &gpio_callback));

    gpio_set_level(UI_LED_PIN, status);    
    while(1) {
        //gpio_set_level(UI_LED_PIN, gpio_get_level(SENSOR_INPUT_PIN));    
    }
}

