#ifndef __TIMER_DRIVER_H_
#define __TIMER_DRIVER_H_

#include "esp_timer.h"
#include "esp_err.h"

#define __weak __attribute__((weak))

/**
 * @brief: Set a periodic timer. Its callback is triggered each desired usecs.
 * @param: time_in_us: time in usecs.
 * @param: void (*timer_callback)(void* arg): Pointer to callback function. User must create this function. E.g.
 *          void timer_callback(void *args)
 * @return: ESP_OK if timer was started correctly.
 **/
esp_err_t timer_driver_init(uint64_t time_in_us, void (*timer_callback)(void* arg));

#endif