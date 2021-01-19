#ifndef __SENSOR_MANAGER_H_
#define __SENSOR_MANAGER_H_

#include "gpio_iface.h"

#define SENSOR_INPUT_PIN GPIO_NUM_22

typedef struct sensor_
{
    gpio_iface_t iface;
    void (*callback)(void *arg);

}sensor_t;

//global
sensor_t sensor;

void sensor_manager_set_callback(sensor_t *sensor, void (*callback)(void *arg));
int sensor_manager_init(sensor_t *sensor, int pin);

#endif