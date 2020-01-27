#include "FastLED.h"
 
//Constants
#define NUM_LEDS 144
#define OFF_SET 35
#define DATA_PIN 5

//#define CLOCK_PIN 13
 
CRGB leds[NUM_LEDS];
 
void setup() { 
    FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);
}

void setBlueAndTurnOff()
{
  for(int i=0; i<NUM_LEDS; i++){
        leds[i] = CHSV(160, 255, 128);
        FastLED.show();
        delay(50);
        leds[i] = CHSV(0,0,0);
        FastLED.show();
    }
}

 void setBlue()
{
  
  for(int i=convertMinToIndex(0); convertMinToIndex(60); i++){
        leds[i] = CHSV(160, 255, 128);
        FastLED.show();
        //delay(50);
        }
}

void setGreenWithMin(int start, int end)
{
  for(int i=convertMinToIndex(start); i<convertMinToIndex(end); i++){
        leds[i] = CHSV(255, 255, 255);
        FastLED.show();
        //delay(50);
        }
}

int convertMinToIndex(int min)
{
  return ((min * (NUM_LEDS / 60)) + OFF_SET);
}



void loop() {

    
    setBlueAndTurnOff();
    
}
