#include "timer_manager.h"

esp_err_t timer_manager_init(uint64_t time_in_us, void (*timer_callback)(void* arg))
{
    const esp_timer_create_args_t timer_args = {
        .callback = timer_callback,
        .name = "periodic"
    };

    esp_timer_handle_t timer;
    ESP_ERROR_CHECK(esp_timer_create(&timer_args, &timer));

    return esp_timer_start_periodic(timer, time_in_us);
}
