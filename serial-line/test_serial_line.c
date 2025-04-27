#include "contiki.h"
#include <stdio.h>
#include "os/dev/serial-line.h"
#include "usb/usb-serial.h"

PROCESS(test_serial_line, "Test Serial Line Processes");
AUTOSTART_PROCESSES(&test_serial_line);

PROCESS_THREAD(test_serial_line, ev, data){


    usb_serial_set_input(serial_line_input_byte);
    
    PROCESS_BEGIN();
    
    while(1) {
      
        PROCESS_WAIT_EVENT_UNTIL(ev == serial_line_event_message);
        printf("Received: %s\n", (char*)data);
    }
    
    PROCESS_END();
}
