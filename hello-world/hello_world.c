#include "contiki.h"
#include <stdio.h>

PROCESS(hello_world_process, "Hello world process");
AUTOSTART_PROCESSES(&hello_world_process);

PROCESS_THREAD(hello_world_process, ev, data){
    static struct etimer timer;
    
    PROCESS_BEGIN();
    
    /* Setup a periodic timer that expires after 10 seconds. */
    etimer_set(&timer, CLOCK_SECOND * 1);
    
    while(1) {
        printf("Hello, world. My name is Derick Temfack. I'm the best of my generation\n");
        /* Wait for the periodic timer to expire and then restart the timer. */
        
        PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timer));
        etimer_reset(&timer);
    }
    
    PROCESS_END();
}
