/*
 * CMRI-SignalLED sketch by Anthony Kochevar v1-10-2022
 * Code is Open Source and as is and can be modified and distributed
 * as long as it is done so freely.
 * I make no warranty with the code it is distrbuted as is.
 *
 * This a simple no frills sketch that gives you the ability to turn on 
 * and off a large number of LEDs using JMRI via CMRI
 * on and Arduino Mega with sensor shield.
 * This will give you a lot of LEDs to control for your signal heads.
 * Ports(Mega Pins) 0, 1, and 2 are used elsewhere in the code and cannot drive a LED.
 * Starting port(pin) on the Mega is 3.
 * Connect the positive side of the LED to the Signal(S) pin of the port.
 * and the ground side of the LED to the GND(G) pin on the shield.
 * You should only need to change CMRI_ADDR and numLEDs in the code.
 * Change CMRI_ADDR if you want to use a different node 
 * and numLEDs to only use the number of LEDs you need.
 * JMRI Example:
 * If CMRI_ADDR is 3.  The JMRI node needs to be 3 and its addresses will
 * start with 3001.  The code below takes into account that the starting port for LEDs 
 * on the shield is 3 and there is a 1 offset in JMRI as well.
 * The LED on port 3 will map to hardware address 3003 in JMRI.  
 * LED on port 4 will map to hardware address 3004 in JMRI.
 * LED on 20 to 3020, LED on 52 to 3052.
 * LED on A0 to 3054 and LED on A6 to 3060 and A16 to 3069.
 * 
 * It is recomended you use a separate power supply for the 
 * shield and appropriate resistors on the LEDs.
*/

#include <CMRI.h>
#include <Auto485.h>


#define CMRI_ADDR 3 //CMRI node address in JMRI.  Change if needed.
#define DE_PIN 2  // Arduino pin used internally for CMRI communication.  Do not change or use this pin.

Auto485 bus(DE_PIN);
CMRI cmri(CMRI_ADDR, 0, 70, bus);  // Initalize CMRI with up to 0 inputs and 70 outputs.

// numPorts sets the total number of LEDs on the board you want to use.  Maximum is 67.
const int numLEDs = 67; 
const int numPorts = numLEDs + 3;  //  +3 offset added to match port # to code.
int ledStatus[numPorts];

//Below array is for use of the analog pins as digital.  Do not change.
const int anaPin[16] = 
  { A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15 };



void setup() {
  Serial.begin(19200); 
  for (int x = 3; x < numPorts; x++) ledStatus[x] = 0;
  if (numPorts <= 53)  {  //  This if only runs if numLEDs is 53 or less
    for (int x = 3; x <= numPorts; x++) {
      pinMode(x, OUTPUT);
    }
  }
  if (numPorts >= 54) {  //  This if only runs if numLEDs is 54 and higher so Analog pins get initalized as well.
    for (int x = 3; x <= 53; x++) {
      pinMode(x, OUTPUT);
    }
    int a = numPorts - 54;
    for (int z = 0; z < a; z++) {
      pinMode(anaPin[z], OUTPUT);
    }
  }
}  //End void setup

void loop() {
  cmri.process();
  for (int x = 3; x < numPorts; x++) {
    if (cmri.get_bit(x-1) != ledStatus[x]) {  // x-1 is to account for JMRI offset.  Port 3 on board will now be address #003 in JMRI.
      ledStatus[x] = cmri.get_bit(x-1);
      if (ledStatus[x] == 1) digitalWrite(x, HIGH);
      else digitalWrite(x, LOW);
    } 
  }  // End for x
}
