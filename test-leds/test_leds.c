#include "contiki.h"
#include <stdio.h>
#include "os/dev/serial-line.h"
#include "usb/usb-serial.h"
#include "os/dev/leds.h"
#include "sys/etimer.h"

PROCESS(test_led_blink, "Test Serial Line Processes");
AUTOSTART_PROCESSES(&test_led_blink);

PROCESS_THREAD(test_led_blink, ev, data){

    static struct etimer et;

    PROCESS_BEGIN();

    etimer_set(&et, 2*CLOCK_SECOND);
    leds_single_on(LEDS_YELLOW);

    while(1) {
      
        PROCESS_YIELD();
        if (ev == PROCESS_EVENT_TIMER){
            if(etimer_expired(&et)){
                leds_single_toggle(LEDS_YELLOW);
                etimer_restart(&et);
            }
        }
    }
    
    PROCESS_END();
}


