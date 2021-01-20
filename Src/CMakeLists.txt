file(GLOB SOURCES "*.c")

set(srcs 
        "app_main.c"
        "gpio_driver.c"
        "gpio_iface.c"
        "led_fsm.c"
        "main_fsm.c"
        "Managers/dispenser_manager.c"
        "Managers/led_manager.c"
        "Managers/sensor_manager.c"
        "Managers/timer_manager.c")

idf_component_register(SRCS ${srcs}
                    INCLUDE_DIRS "../Inc" "../Inc/Managers") 