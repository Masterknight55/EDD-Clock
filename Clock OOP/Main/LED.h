
#include "FastLED.h"

#include <Arduino.h>

class LED {

  
  public: 
  LED();
  void init();
  void TurnAllBlue();
  int convertMinToIndex(double min);

};
 
