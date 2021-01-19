#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
//IDF libraries
#include "esp_log.h"
//Custom libraries
#include "led_manager.h"
#include "sensor_manager.h"
#include "dispenser_manager.h"
#include "main_fsm.h"

#include "timer_manager.h"

const char *TAG = "MAIN";
static bool status = true;

void init_components(void);

void timer_callback(void *args)
{
    static int cnt = 0;
    ESP_LOGI("TIMER [ISR]", "TICK %d %d", cnt++, status);
    //gpio_set_level(UI_LED_PIN, status ^= 1);
}

void sensor_callback(void *args)
{
    gpio_set_level(UI_LED_PIN, status ^= 1);
}

void app_main(void)
{
    init_components();
    
    main_fsm_init(&dispenser_fsm);

    gpio_set_level(UI_LED_PIN, status);    
    
    while(1) {
        main_fsm_run(&dispenser_fsm);
    }
}


{
    sensor_manager_set_callback(&sensor, &sensor_callback);
    sensor_manager_init(&sensor, SENSOR_INPUT_PIN);

    led_manager_init(&ui_led, UI_LED_PIN);
    
    dispenser_manager_init(&dispenser_mngr, DISPENSER_PIN);

    timer_manager_init(1000000, &timer_callback);
}
