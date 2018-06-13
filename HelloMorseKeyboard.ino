/*********************************************************************
 This is an example for our nRF52 based Bluefruit LE modules
 Pick one up today in the adafruit shop!
 Adafruit invests time and resources providing this open source code,
 please support Adafruit and open-source hardware by purchasing
 products from Adafruit!
 MIT license, check LICENSE for more information
 All text above, and the splash screen below must be included in
 any redistribution

 Arduino Classes built using tutorial from adafruit: https://learn.adafruit.com/multi-tasking-the-arduino-part-1/a-classy-solution

 Built with NottLimited for the GBoard Morse Keyboard
*********************************************************************/
int speedTyper = 300;
int speedSense = 2;

#include "customKeyboard.h"

//KeyboardKey varName (pin, primary ascii character, alternate ascii character, pressSpeed)
//ModifierKey varName (pin)

KeyboardKey periodKey(A0, 46, 120, speedTyper);
KeyboardKey hyphonKey(A1, 45, 121, speedTyper);


ModifierKey shiftKey(11);

void setup()
{
  Serial.begin(115200);                                                                                                                                                             
  Serial.println("HelloMorse BLE Keyboard");
  Serial.println("--------------------------------\n");
  Serial.println();
  blueToothSetup();
}

void loop()
{ 
  boolean shiftValue = shiftKey.Check();
  speedTyper = analogRead(A2)/speedSense;
  Serial.println(speedTyper);
  
  periodKey.Press(shiftValue);
  hyphonKey.Press(shiftValue);
  
  // Request CPU to enter low-power mode until an event/interrupt occurs
  waitForEvent();  
}

