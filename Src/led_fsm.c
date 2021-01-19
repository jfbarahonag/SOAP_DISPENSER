#include "led_fsm.h"

static void led_fsm_reset_variables(led_fsm_t *fsm)
{
    fsm->st = ST_LED_IDLE;
    fsm->evt.internal = EV_LED_INT_INVALID;
    fsm->new_evt = false;
}

static led_states_t led_fsm_get_state(led_fsm_t *fsm)
{
    return fsm->st;
}

static void led_fsm_set_next_state(led_fsm_t *fsm, led_states_t next_st)
{
    fsm->st = next_st;
}

void led_fsm_init (led_fsm_t *fsm)
{
    led_fsm_reset_variables(fsm);
}

void led_fsm_run(led_fsm_t *fsm)
{
    if (fsm->new_evt == true)
    {
        switch (led_fsm_get_state(fsm))
        {
        case ST_LED_IDLE:
            
            if (fsm->evt.external == EV_LED_EXT_PATTERN_START)
            {
                led_fsm_set_next_state(fsm, ST_LED_ON);
            }

            break;

        case ST_LED_ON:

            if (fsm->evt.internal == EV_LED_INT_ON_TIMEOUT)
            {
                led_fsm_set_next_state(fsm, ST_LED_OFF);
            }

            break;

        case ST_LED_OFF:

            if (fsm->evt.internal == EV_LED_INT_OFF_TIMEOUT)
            {
                led_fsm_set_next_state(fsm, ST_LED_CHECK_FINISH);
            }

            break;

        case ST_LED_CHECK_FINISH:

            if (fsm->evt.internal == EV_LED_INT_PATTERN_OK)
            {
                led_fsm_set_next_state(fsm, ST_LED_IDLE);
            }
            else if (fsm->evt.internal == EV_LED_INT_FINISH_NOK)
            {
                led_fsm_set_next_state(fsm, ST_LED_ON);
            }

            break;
        /* UNKNOWN STATE */
        default:
            break;
        }
    }
}

void led_fsm_set_external_evt(led_fsm_t *fsm, led_external_events_t evt)
{
    fsm->evt.external = evt;
    fsm->new_evt = true;
}

void led_fsm_set_internal_evt(led_fsm_t *fsm, led_internal_events_t evt)
{
    fsm->evt.internal = evt;
    fsm->new_evt = true;
}


