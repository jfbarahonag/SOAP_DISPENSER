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

#include "timer_manager.h"

#include "main_fsm.h"

const char *TAG = "MAIN";
static bool status = true;

void init_components(void);

void timer_callback(void *args)
{
    if (main_fsm_get_state(&dispenser_fsm) == ST_MAIN_DISPENSE)
    {
        dispenser_manager_increment_timer_cnt(&dispenser_mngr);

        if (dispenser_manager_is_timeout_reached(&dispenser_mngr) == true)
        {
            ESP_LOGI(TAG, "TIMEOUT REACHED");
            dispenser_manager_reset_timer_cnt(&dispenser_mngr);
            main_fsm_set_internal_evt(&dispenser_fsm, EV_MAIN_INT_SOAP_TIMEOUT);
        }
    }
}

void sensor_callback(void *args)
{
    gpio_set_level(UI_LED_PIN, status ^= 1);
    
    if (main_fsm_get_state(&dispenser_fsm) == ST_MAIN_IDLE)
    {
        main_fsm_set_internal_evt(&dispenser_fsm, EV_MAIN_INT_HAND_DETECTED);
    }
    else if (main_fsm_get_state(&dispenser_fsm) == ST_MAIN_RELEASE)
    {
        if (sensor_manager_get_level(&sensor) != 0) //HAND DETECTED //
        {
            main_fsm_set_internal_evt(&dispenser_fsm, EV_MAIN_INT_HAND_DETECTED);
        }
        else
        {
            main_fsm_set_internal_evt(&dispenser_fsm, EV_MAIN_INT_HAND_NOT_DETECTED);
        }
    }
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

void init_components(void)
{
    sensor_manager_set_callback(&sensor, &sensor_callback);
    sensor_manager_init(&sensor, SENSOR_INPUT_PIN);

    led_manager_init(&ui_led, UI_LED_PIN);
    
    dispenser_manager_init(&dispenser_mngr, DISPENSER_PIN);

    timer_manager_init(1000, &timer_callback);
}
