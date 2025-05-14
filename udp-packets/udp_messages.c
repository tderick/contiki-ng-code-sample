#include "contiki.h"
#include "os/net/ipv6/simple-udp.h"
#include "simple-udp.h"
#include <stdio.h>
#include <string.h>

#define SEND_INTERVAL (10 * CLOCK_SECOND)
#define UDP_PORT 1234

static struct simple_udp_connection udp_conn;
static struct etimer periodic_timer;

/*---------------------------------------------------------------------------*/
/* Callback for receiving UDP packets */
static void
udp_rx_callback(struct simple_udp_connection *c,
                const uip_ipaddr_t *sender_addr,
                uint16_t sender_port,
                const uip_ipaddr_t *receiver_addr,
                uint16_t receiver_port,
                const uint8_t *data,
                uint16_t datalen)
{
  printf("Received UDP packet from ");
  uip_debug_ipaddr_print(sender_addr);
  printf(" with data: '%.*s'\n", datalen, (char *)data);
}
/*---------------------------------------------------------------------------*/
PROCESS(udp_multicast_process, "UDP multicast example");
AUTOSTART_PROCESSES(&udp_multicast_process);
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(udp_multicast_process, ev, data)
{
  static uip_ipaddr_t addr;
  static char message[] = "Hello multicast";

  PROCESS_BEGIN();

  // Create the link-local all-nodes multicast address: ff02::1
  uip_create_linklocal_allnodes_mcast(&addr);

  // Register the UDP connection
  simple_udp_register(&udp_conn, UDP_PORT, NULL, UDP_PORT, udp_rx_callback);

  // Set timer for periodic sending
  etimer_set(&periodic_timer, SEND_INTERVAL);

  while(1) {
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&periodic_timer));

    printf("Sending multicast UDP packet to ");
    uip_debug_ipaddr_print(&addr);
    printf("\n");

    simple_udp_sendto(&udp_conn, message, strlen(message), &addr);

    etimer_reset(&periodic_timer);
  }

  PROCESS_END();
}
