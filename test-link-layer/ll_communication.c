#include "contiki.h"
#include "net/netstack.h"
#include "net/nullnet/nullnet.h"
#include <string.h>
#include <stdio.h>
#include "sys/log.h"
#include "os/net/linkaddr.h"
 
 
#define LOG_MODULE "App"
#define LOG_LEVEL LOG_LEVEL_INFO
 
#define SEND_INTERVAL (8 * CLOCK_SECOND)

//static linkaddr_t dest_addr = {{0x0002, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000}};
static linkaddr_t dest_addr = {{0x00f4, 0x00ce, 0x0036, 0x0043, 0x0001, 0x00c3, 0x005d, 0x00cd }};
static int uni_period = 0;
PROCESS(comm_proc, "unicast example");
AUTOSTART_PROCESSES(&comm_proc);
 
static void input_callback(const void *data, uint16_t len, const linkaddr_t *src, const linkaddr_t *dest){
    char received_data[strlen((char *)data) + 1];
    if(len == strlen((char *)data) + 1) {
        memcpy(& received_data, data, strlen((char *)data) + 1);
        LOG_INFO("TIMESTAMP: %lu, Received \"%s\", from ", clock_seconds(), received_data);
        LOG_INFO_LLADDR(src);
        LOG_INFO_("\n");
     }
}
 
PROCESS_THREAD(comm_proc, ev, data){
    static struct etimer periodic_timer;
    static char uni_msg[70];
    sprintf(uni_msg, "Hello from kubectl at time: %d", uni_period);
 
    PROCESS_BEGIN();
     nullnet_buf = (uint8_t *)uni_msg;
     nullnet_set_input_callback(input_callback);
 
/* Send data */
     if(!linkaddr_cmp(&dest_addr, &linkaddr_node_addr)) {
         etimer_set(&periodic_timer, SEND_INTERVAL);
         while(1) {
              PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&periodic_timer));
              LOG_INFO("TIMESTAMP: %lu, Sending UNICAST \"%s\", to ", clock_seconds(), uni_msg);
              LOG_INFO_LLADDR(&dest_addr);
              LOG_INFO_("\n");
              nullnet_len = strlen(uni_msg)+1;

              // UNICAST MESSAGE
              NETSTACK_NETWORK.output(&dest_addr);

              // BROADCAST MESSAGE
              NETSTACK_NETWORK.output(NULL);

              uni_period += 8;
              etimer_reset(&periodic_timer);
          }
       }
     PROCESS_END();
}
