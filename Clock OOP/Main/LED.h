
#include "FastLED.h"

#include <Arduino.h>

class LED {


  private:
    byte pin;

  public: 
  LED();
  void init();
  void TurnAllBlue();
  int convertMinToIndex();

};
 
