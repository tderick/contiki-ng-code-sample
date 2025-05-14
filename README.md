# contiki-ng-code-sample

```
make TARGET=nrf52840 BOARD=dongle mqtt-client.dfu-upload PORT=/dev/ttyACM0
```

```
make login TARGET=nrf52840 BOARD=dongle PORT=/dev/ttyACM0
```

# RUNNING the border router.

1. Add the cooja mote or flash the code inside the sensor
2. Add the border router to cooja or flash the border router insider another dongle
3. Start the border router:
    3.1. Cooja
        ```
        make TARGET=cooja connect-router-cooja
        ```
    3.2. Use the dongle
        ■ Deploy and flash the code for the border router
            – cd examples/rpl-border-router
            – connect the dongle to the USB 
            – make TARGET=nrf52840 BOARD=dongle PORT=/dev/ttyACM0 border-router.dfu-upload
        ■ Use the tunslip6:
            – cd examples/rpl-border-router/
            – make TARGET=nrf52840 BOARD=dongle PORT=/dev/ttyACM0 connect-router
