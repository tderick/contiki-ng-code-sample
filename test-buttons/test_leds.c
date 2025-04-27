#include "contiki.h"
#include <stdio.h>
#include "os/dev/serial-line.h"
#include "usb/usb-serial.h"
#include "os/dev/leds.h"
#include "sys/etimer.h"
#include "os/dev/button-hal.h"


PROCESS(test_buttons, "Test Buttons");
AUTOSTART_PROCESSES(&test_buttons);

PROCESS_THREAD(test_buttons, ev, data){

    button_hal_button_t *btn;
    
    PROCESS_BEGIN();
    
    btn = button_hal_get_by_index(0);
    
    while(1) {
        PROCESS_YIELD();
        if(ev == button_hal_press_event) {
            leds_single_on(LEDS_YELLOW);
        }else if(ev == button_hal_release_event){
            leds_on(LEDS_BLUE);
        }else if(ev == button_hal_periodic_event) {
            btn = (button_hal_button_t *)data;
            if(btn->press_duration_seconds > 3) {
                leds_single_off(LEDS_YELLOW);
                leds_off(LEDS_BLUE);
            }
        }
    }
    
    
    PROCESS_END();
}


