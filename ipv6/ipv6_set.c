#include "contiki.h"
#include "net/netstack.h"
#include "net/nullnet/nullnet.h"
#include <string.h>
#include <stdio.h>
#include "sys/log.h"
#include "os/net/linkaddr.h"
#include "net/ipv6/uip.h"
#include "net/ipv6/uip-ds6.h"
#include "net/ipv6/uip-debug.h"
 
 
#define LOG_MODULE "App"
#define LOG_LEVEL LOG_LEVEL_INFO
 
#define SEND_INTERVAL (8 * CLOCK_SECOND)

#define DEBUG 1

PROCESS(ipv6_Set, "Setting Ipv6");
AUTOSTART_PROCESSES(&ipv6_Set);

PROCESS_THREAD(ipv6_Set, ev, data){
    static struct etimer periodic_timer;
    static uip_ipaddr_t ipaddr;
 
    PROCESS_BEGIN();

    // Set the periodic timer
    etimer_set(&periodic_timer, CLOCK_SECOND * 1);

    // Set the IPV6 Address
    uip_ip6addr(&ipaddr, 0xfd00, 0, 0, 0, 0, 0, 0, 0)
    
    while(1){
        PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&periodic_timer));

        static int i;
        static uint8_t state;
        printf("IPv6 addresses: ");
        for(i = 0; i < UIP_DS6_ADDR_NB; i++){
        state = uip_ds6_if.addr_list[i].state;
        if(uip_ds6_if.addr_list[i].isused && (state== ADDR_TENTATIVE||state== ADDR_PREFERRED)){
        uip_debug_ipaddr_print(&uip_ds6_if.addr_list[i].ipaddr);
        printf("\n");
        }
        }

        etimer_reset(&periodic_timer);

    }
    PROCESS_END();
}
