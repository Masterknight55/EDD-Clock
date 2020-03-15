
#include "LED.h"

LED ClockLights();



void setup() {
  ClockLights.init();
  // put your setup code here, to run once:
  
  

}

void loop() {
  // put your main code here, to run repeatedly:
  ClockLights.TurnAllBlue();

}
