#include "LED.h"

#define NUM_LEDS2 140
#define NUM_LEDS 144
#define OFF_SET 40
#define DATA_PIN 5
#define PHOTOCELLPIN 0

int photocellReading;
int LEDbrightness;

CRGB leds[NUM_LEDS];

void LED::init() {
  FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);
}

int LED::convertMinToIndex(double min)
{
  return ((min * ( (NUM_LEDS - OFF_SET) / 60.0)) + OFF_SET);
}


void LED::TurnAllBlue() {

        for(int i=convertMinToIndex(0); convertMinToIndex(60); i++){
        leds[i] = CHSV(160, 255, 128);
        FastLED.show();
        //delay(50);
        }
  
}
