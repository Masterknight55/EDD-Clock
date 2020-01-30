#include "FastLED.h"
 
//Constants
//104 LEDS
#define NUM_LEDS2 140
#define NUM_LEDS 144
#define OFF_SET 40
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

 void setAllBlue()
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

void setWithMin(int start, int end, int color1, int color2, int color3)
{
  
  for(int i=convertMinToIndex(start); i<convertMinToIndex(end); i++){
        leds[i] = CHSV(color1, color2, color3);
        FastLED.show();
        //delay(50);
        }

        
}

int convertMinToIndex(double min)
{
  return ((min * ( (NUM_LEDS - OFF_SET) / 60.0)) + OFF_SET);
}



void loop() {

    
    setWithMin(0,10,255,255,255);
    setWithMin(10,20,160,255,128);
    setWithMin(20,30,100,100,100);
    
    
}
