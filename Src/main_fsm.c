#include <stdbool.h>

#include"esp_log.h"

#include "main_fsm.h"

const char *TAG = "MAIN_FSM";

static void main_fsm_reset_variables(main_fsm_t *fsm)
{
    fsm->new_evt = false;
    
    fsm->evt.internal = EV_MAIN_INT_INVALID;
    fsm->evt.external = EV_MAIN_EXT_INVALID;

    fsm->st = ST_MAIN_IDLE;
}

static main_states_t get_state(main_fsm_t *fsm)
{
    return fsm->st;
}

static void set_next_state(main_fsm_t *fsm, main_states_t next_st)
{
    fsm->st = next_st;
}

static void main_fsm_error_handler()
{
    ESP_LOGI(TAG, "MAIN FSM ERROR HANDLER\r\n");
    while (1);
    
}

void main_fsm_init(main_fsm_t *fsm)
{
    main_fsm_reset_variables(fsm);
}


void main_fsm_run(main_fsm_t *fsm)
{
    if (fsm->new_evt == true)
    {
        switch (get_state(fsm))
        {
        case ST_MAIN_IDLE:

            if(fsm->evt.internal == EV_MAIN_INT_HAND_DETECTED)
            {

                set_next_state(fsm, ST_MAIN_DISPENSE);
            }

            break;

        case ST_MAIN_DISPENSE:
            
            if(fsm->evt.internal == EV_MAIN_INT_SOAP_TIMEOUT)
            {

                set_next_state(fsm, ST_MAIN_RELEASE);
            }

            break;

        case ST_MAIN_RELEASE:

            if(fsm->evt.internal == EV_MAIN_INT_HAND_DETECTED)
            {
                set_next_state(fsm, ST_MAIN_LED_ERR_PATTERN);
            }
            else if (fsm->evt.internal == EV_MAIN_INT_HAND_NOT_DETECTED) //TODO: HOW TO TRIGGER THIS EVENT?
            {
                set_next_state(fsm, ST_MAIN_IDLE);
            }

            break;
        
        case ST_MAIN_LED_ERR_PATTERN:

            if (fsm->evt.external == EV_MAIN_EXT_PATTERN_OK)
            {
                set_next_state(fsm, ST_MAIN_RELEASE);
            }

            break;
        
        default:
        
            main_fsm_error_handler();

            break;
        }
    }
}