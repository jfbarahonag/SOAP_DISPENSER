#ifndef __LED_FSM_H_
#define __LED_FSM_H_

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "gpio_iface.h"

typedef enum led_internal_events_
{
	EV_LED_INT_INVALID,
	
	EV_LED_INT_ON_TIMEOUT,
	EV_LED_INT_OFF_TIMEOUT,
	EV_LED_INT_FINISH_NOK,
	EV_LED_INT_PATTERN_OK,
	
	EV_LED_INT_COUNT,
}led_internal_events_t;

typedef enum led_external_events_
{
	EV_LED_EXT_INVALID,
	
	EV_LED_EXT_PATTERN_START,
	
	EV_LED_EXT_COUNT,
}led_external_events_t;

typedef enum led_states_
{
	ST_INVALID,
	
	ST_LED_IDLE,
	ST_LED_ON,
	ST_LED_OFF,
	ST_LED_CHECK_FINISH,
	
	ST_TOTAL,
}led_states_t;

typedef struct led_events_
{
	led_internal_events_t internal;
	led_external_events_t external;
}led_events_t;

typedef struct led_fsm_
{
	led_states_t st;
	led_events_t evt;
	bool new_evt;
}led_fsm_t;

typedef struct led_handle_
{
	led_fsm_t fsm;
	gpio_iface_t iface;
}led_handle_t;

//global
led_handle_t ui_led;
led_handle_t ui_dispenser;

void led_fsm_init(led_fsm_t *fsm);
void led_fsm_run(led_fsm_t *fsm);

void led_fsm_set_external_evt(led_fsm_t *fsm, led_external_events_t evt);
void led_fsm_set_internal_evt(led_fsm_t *fsm, led_internal_events_t evt);
#endif
