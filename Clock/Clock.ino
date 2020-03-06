#include "FastLED.h"
 
//Constants
//104 LEDS
#define NUM_LEDS2 140
#define NUM_LEDS 144
#define OFF_SET 40
#define DATA_PIN 5

//RTC Shit
#define DS3231
#define SOFTWARE_WIRE_SDA SDA  // Or whatever other pin you use
#define SOFTWARE_WIRE_SCL SCL  // Or whatever other pin you use
#include <time.h>
#include "RTCtimeUtils.h"
#ifdef RTC_SOFTWARE_WIRE
  #include <SoftwareWire.h>
  #define myWire SoftwareWire
  myWire I2C(SOFTWARE_WIRE_SDA, SOFTWARE_WIRE_SCL);
#else
  #include <Wire.h>
  #define myWire TwoWire
  #define I2C Wire
#endif
#ifdef DS3231
  #include <RtcDS3231.h>
  RtcDS3231<myWire> Rtc(I2C);
#else
  #include <RtcDS1307.h>
  RtcDS1307<myWire> Rtc(I2C);
#endif
unsigned long prev_millis = 0;
unsigned long interval = 1000;

int photocellPin = 1;
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
 
void setup() { 
    FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);
     Serial.begin(9600);

      #ifdef DEBUG
      Serial.println(F("Setup started."));
      #endif
      Rtc.Begin();
      #define COMPILE_DATE_TIME (__DATE__ " " __TIME__)
      char* compile_date_time = COMPILE_DATE_TIME;
     time_t compiled_time_t = str20ToTime(compile_date_time);  // str20ToTime converts a 20 chars date and time string to a time_t value (See it in RtcUtility.h)
     #ifndef DEBUG
       if (!Rtc.IsDateTimeValid())
     #endif
        {
     #ifndef DEBUG
          Serial.println(F("WARNING: RTC invalid time, setting RTC with compile time!"));
      #else
          Serial.println(F("DEBUG mode: ALWAYS setting RTC with compile time!"));
      #endif
          Rtc.SetTime(&compiled_time_t);
        }
        if (!Rtc.GetIsRunning())
        {
          Serial.println(F("WARNING: RTC was not actively running, starting it now."));
          Rtc.SetIsRunning(true);
        }
        time_t now = Rtc.GetTime();
        if (now < compiled_time_t)
        {
          Serial.println(F("WARNING: RTC is older than compile time, setting RTC with compile time!"));
          Rtc.SetTime(&compiled_time_t);
        }
        #ifdef DS3231
        Rtc.Enable32kHzPin(false);
        Rtc.SetSquareWavePin(DS3231SquareWavePin_ModeNone);
        #endif
      
        #ifdef DEBUG
          Serial.println(F("Setup done."));
        #endif
      
        Serial.println("");

      
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

void RTCStuff()
{
  unsigned long current_millis = millis();
  unsigned long elapsed_millis = current_millis - prev_millis;
  if (elapsed_millis >= interval - accuracy and elapsed_millis <= interval + accuracy)
  {
    prev_millis = prev_millis + interval;
    time_t now = Rtc.GetTime();
    Serial.print(F("Arduino time (Y2K based):  "));
    Serial.println(now);
    Serial.println(""); 
}

}



void loop() {

    RTCStuff();
    //setWithMin(CurrentHour,CurrentHour+1, 160,255,128);
    //setWithMin(getCurrentPeroid(),getCurrentPeroid()+1, 160,255,128);
    
    //SetBrightness();
    display(CurrentMin, CurrentHour);
    CurrentMin = CurrentMin + 1;
    if (CurrentMin == 60)
    {
      CurrentMin = 0;
      CurrentHour = CurrentHour +1;
    }
    
}
