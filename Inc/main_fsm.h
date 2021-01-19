#ifndef __MAIN_FSM_H_
#define __MAIN_FSM_H_

#include <stdbool.h>

typedef enum main_internal_events_
{
	EV_MAIN_INT_INVALID,
	
	EV_MAIN_INT_HAND_DETECTED,
	EV_MAIN_INT_HAND_NOT_DETECTED,
	EV_MAIN_INT_SOAP_TIMEOUT,
	
	EV_MAIN_INT_COUNT,
}main_internal_events_t;

typedef enum main_external_events_
{
	EV_MAIN_EXT_INVALID,

	EV_MAIN_EXT_PATTERN_OK,

	EV_MAIN_EXT_COUNT,
}main_external_events_t;

typedef enum main_states_
{
	ST_MAIN_INVALID,
	
	ST_MAIN_IDLE,
	ST_MAIN_DISPENSE,
	ST_MAIN_RELEASE,
	ST_MAIN_LED_ERR_PATTERN,
	ST_MAIN_HALTED_PROCESS,
	
	ST_MAIN_TOTAL,
}main_states_t;

typedef struct main_events_
{
	main_internal_events_t internal;
	main_external_events_t external;
}main_events_t;

typedef struct main_fsm_
{
	main_states_t st;
	main_events_t evt;
	bool new_evt;
}main_fsm_t;

//global
main_fsm_t dispenser_fsm;

void main_fsm_init(main_fsm_t *fsm);
void main_fsm_run(main_fsm_t *fsm);

void main_fsm_set_external_evt(main_fsm_t *fsm, main_external_events_t evt);
void main_fsm_set_internal_evt(main_fsm_t *fsm, main_internal_events_t evt);

main_states_t main_fsm_get_state(main_fsm_t *fsm);

#endif