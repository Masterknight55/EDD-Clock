// Date and time functions using RX8025 RTC connected via I2C and Wire lib

#include <Wire.h>
#include "Sodaq_DS3231.h"

char weekDay[][4] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };

uint32_t old_ts;


//LED Clock 

#include "FastLED.h"
 
//Constants
//104 LEDS
#define NUM_LEDS2 140
#define NUM_LEDS 144
#define OFF_SET 40
#define DATA_PIN 5

int photocellPin = 0;
int photocellReading;
int LEDbrightness;


//#define CLOCK_PIN 13
 
CRGB leds[NUM_LEDS];


//This is a Regular Day Schedule
int StartHour[] = {0 , 7 , 8 ,9 ,10,11,11,11,12,12,13,13};
int StartMin[] =  {0 , 33, 26,17,8 ,0 ,25,50,15,40,4 ,54};

int EndHour[] = {0 , 8, 9, 10,10,11,11,12,12,13,13};
int EndMin[] =  {0 , 22,13, 4,56,21,46,11,36, 0,50};

int CurrentMin = 4;
int CurrentHour = 8;






// SETUP Methods




//LED Methods

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


int getCurrentPeroid()
{

  for(int i = 0; i < 12; i ++)
  {
    if (CurrentMin > StartMin[i] && CurrentMin > EndMin[i])
    {
      //Then it is in range of min
      for(int k=0; k < 12; k++)
      {
        if (CurrentHour > StartHour[k] && CurrentHour < EndHour[k])
        {
          return k;
        }
  
      }

      }
  }

  
}

void display(int currentMin, int currentHour)
{
  
//Display from current min to end of peroid
for(int i=0; i<NUM_LEDS; i++){
        leds[i] = CHSV(0,0,0);
        FastLED.show();
    }

    
if((double)CurrentHour - (double)StartHour[1] <= 1.0 && (double)EndHour[1] - (double)StartHour[1] > 0)
{
  setWithMin(currentMin,60,255,255,255);
}
else
{
  setWithMin(currentMin,EndMin[1], 255,255,255);
}

 
}

void SetBrightness()
{
 
  if(analogRead(photocellPin) > 800)
  {
    FastLED.setBrightness(150);  
  }
  else if(analogRead(photocellPin) < 800 && analogRead(photocellPin) > 400)
  {
    FastLED.setBrightness(50);
  }
  else if(analogRead(photocellPin) < 400)
  {
    FastLED.setBrightness(25);
  }
  
  
  Serial.println(analogRead(photocellPin));
}



//LED Main Loop
void LEDMainLoop() 
{

    //setWithMin(CurrentHour,CurrentHour+1, 160,255,128);
    //setWithMin(getCurrentPeroid(),getCurrentPeroid()+1, 160,255,128);
    
    SetBrightness();
    display(CurrentMin, CurrentHour);
    
  
}



void setup() {

  FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);
  RTCSetup();
}

// Main loop
void loop() {

  RTCMainLoop();
  LEDMainLoop();

}







//RTC Shit

void RTCMainLoop()
{
   DateTime now = rtc.now(); //get the current date-time
    uint32_t ts = now.getEpoch();

    if (old_ts == 0 || old_ts != ts) {
  old_ts = ts;
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.date(), DEC);
  Serial.print(' ');
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.print(' ');
  Serial.print(weekDay[now.dayOfWeek()]);
  Serial.println();
  Serial.print("Seconds since Unix Epoch: "); 
  Serial.print(ts, DEC);
  Serial.println();
      } 
    delay(1000);
}


void RTCSetup()
{
    Serial.begin(57600);
    Wire.begin();
    rtc.begin();
}
