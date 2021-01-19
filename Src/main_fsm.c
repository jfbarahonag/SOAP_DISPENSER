#include <stdbool.h>

#include"esp_log.h"

#include "main_fsm.h"
#include "led_manager.h" //Temporal

const char *MAIN_FSM_TAG = "MAIN_FSM";

static void main_fsm_reset_variables(main_fsm_t *fsm)
{
    fsm->new_evt = false;
    
    fsm->evt.internal = EV_MAIN_INT_INVALID;
    fsm->evt.external = EV_MAIN_EXT_INVALID;

    fsm->st = ST_MAIN_IDLE;
}

main_states_t main_fsm_get_state(main_fsm_t *fsm)
{
    return fsm->st;
}

static void main_fsm_set_next_state(main_fsm_t *fsm, main_states_t next_st)
{
    fsm->st = next_st;
}

static void main_fsm_error_handler()
{
    ESP_LOGI(MAIN_FSM_TAG, "MAIN FSM ERROR HANDLER\r\n");
    while (1);  
}

static void main_fsm_clear_new_evt_flag(main_fsm_t *fsm)
{
    fsm->new_evt = false;
}

void main_fsm_init(main_fsm_t *fsm)
{
    main_fsm_reset_variables(fsm);
}


void main_fsm_run(main_fsm_t *fsm)
{
    if (fsm->new_evt == true)
    {
        main_fsm_clear_new_evt_flag(fsm);

        ESP_LOGI(MAIN_FSM_TAG, "New event ON");
        switch (main_fsm_get_state(fsm))
        {
        case ST_MAIN_IDLE:

            if(fsm->evt.internal == EV_MAIN_INT_HAND_DETECTED)
            {
                main_fsm_set_next_state(fsm, ST_MAIN_DISPENSE);
                // open dispenser & start countdown
                gpio_set_level(ui_dispenser.iface.pin, 1);
            }

            break;

        case ST_MAIN_DISPENSE:
            
            if(fsm->evt.internal == EV_MAIN_INT_SOAP_TIMEOUT)
            {
                main_fsm_set_next_state(fsm, ST_MAIN_RELEASE);
            }

            break;

        case ST_MAIN_RELEASE:

            if(fsm->evt.internal == EV_MAIN_INT_HAND_DETECTED)
            {
                main_fsm_set_next_state(fsm, ST_MAIN_LED_ERR_PATTERN);
            }
            else if (fsm->evt.internal == EV_MAIN_INT_HAND_NOT_DETECTED) //TODO: HOW TO TRIGGER THIS EVENT?
            {
                main_fsm_set_next_state(fsm, ST_MAIN_IDLE);
            }

            break;
        
        case ST_MAIN_LED_ERR_PATTERN:

            if (fsm->evt.external == EV_MAIN_EXT_PATTERN_OK)
            {
                main_fsm_set_next_state(fsm, ST_MAIN_RELEASE);
            }

            break;
        
        default:
        
            main_fsm_error_handler();

            break;
        }
    }
}

void main_fsm_set_external_evt(main_fsm_t *fsm, main_external_events_t evt)
{
    fsm->evt.external = evt;
    fsm->new_evt = true;
}

inline void main_fsm_set_internal_evt(main_fsm_t *fsm, main_internal_events_t evt)
{
    fsm->evt.internal = evt;
    fsm->new_evt = true;
}
