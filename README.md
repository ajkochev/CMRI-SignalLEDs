# CMRI-SignalLEDs
Control up to 67 LEDs in JMRI via CMRI


CMRI-SignalLED sketch by Anthony Kochevar v1-10-2022

Code is Open Source and can be modified and distributed
as long as it is done so freely.
I make no warranty with the code it is distrbuted as is.

This a simple no frills sketch that gives you the ability to turn on 
and off a large number of LEDs using JMRI via CMRI
on and Arduino Mega with sensor shield.
This will give you a lot of LEDs to control for your signal heads.
Ports(Mega Pins) 0, 1, and 2 are used elsewhere in the code and cannot drive a LED.
Starting port(pin) on the Mega is 3.
Connect the positive side of the LED to the Signal(S) pin of the port.
and the ground side of the LED to the GND(G) pin on the shield.
You should only need to change CMRI_ADDR and numLEDs in the code.
Change CMRI_ADDR if you want to use a different node 
and numLEDs to only use the number of LEDs you need.
JMRI Example:
If CMRI_ADDR is 3.  The JMRI node needs to be 3 and its addresses will
start with 3001.  The code below takes into account that the starting port for LEDs 
on the shield is 3 and there is a 1 offset in JMRI as well.
The LED on port 3 will map to hardware address 3003 in JMRI.  
LED on port 4 will map to hardware address 3004 in JMRI.
LED on 20 to 3020, LED on 52 to 3052.
LED on A0 to 3054 and LED on A6 to 3060 and A16 to 3069.

It is recomended you use a separate power supply for the 
shield and appropriate resistors on each of the LEDs.
