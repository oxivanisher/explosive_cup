# "Explosive" cup

This is a tinkering project used for a "exploding" cup in a theatre production. The word explosion is in quotation marks, since there is no fire involved. It will heat a wire to pop a balloon.

It functions the following way:
1) The RC receiver gets a signal
1) The arduino closes the circuit for the 9V battery relay
1) The balloon will pop
1) The relay is switched it off after about 2 seconds
1) System enters locked state for 30 minutes


## Some notes

* My implementation takes about 1 second from receiving the RC signal to exploding the ballon.
* The locked state is implemented, so that the 9V battery is not drained even if the RC receiver still gets the "explode now" signal after a pop.
* The 3d printed case could definitely be optimized, but this needs to change depending on the implementation. You probably have to design one on your own.
 to get the nichrome wire so hot
* The arduino code requires the [SBUS2-Telemetry](https://github.com/BrushlessPower/SBUS2-Telemetry/) library.
* The relay is connected to pin 3 on the arduino
* The RC receiver is connected to the RX and TX pins

## Requirements

* Some 18650 to 5V PSU (or another 5V power source) to power the RC receiver, the relay and the arduino
* A 9V battery (will only be used to pop the balloon for maximal system uptime duration)
* A buck converter to 3.3V to power the [SBUS inverter](https://github.com/BrushlessPower/SBUS2-Telemetry/) (the SBUS RC signals are 3.3V!)
* A arduino pro mini (and the means to program it ie. with a FTDI adapter)
* A relay
* A RC receiver (I use a FrSKY XSR) that supports SBUS
