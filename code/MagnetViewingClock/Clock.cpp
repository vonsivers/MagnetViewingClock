//==========================================================================
// Magnet Viewing Clock -  Clock.cpp
//
// Copyright (c) 2022, Moritz v. Sivers
//
// based on Slide Clock by Craig Colvin, https://github.com/moose408/SlideClock
//
// Licensed under Creative Commons License
// Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
//==========================================================================

#include <Arduino.h>

#include "ClockCoordinates.h"
#include "Clock.h"
#include "RTClib.h" // https://github.com/adafruit/RTClib
#include "hardware.h"
#include "stepper.h"

RTC_DS3231 rtc;
DateTime dtCurrentDisplayedTime;

const int MINS_GETDIGIT           = 0;
const int TENS_OF_MINS_GETDIGIT   = 1;
const int HOURS_GETDIGIT          = 2;
const int TENS_OF_HOURS_GETDIGIT  = 3;

const int MODE_CHANGE_MINS = 0;
const int MODE_CHANGE_TOM = 1;
const int MODE_CHANGE_HOURS = 2;
const int MODE_CHANGE_TOH = 3;
const int MODE_STANDBY = 4;


//=========================================
// I n c r e m e n t T i m e 
//=========================================
int IncrementTime(int iTimeValue, int iMaxValue) {
  int iNewValue;

  iNewValue = iTimeValue + 1;
  if (iNewValue > iMaxValue) {
    iNewValue = 0;
  }

  return (iNewValue);
}
//=========================================
// H a s A M i n u t e P a s s e d
//
// This expects both times to be in 24h
// notation
//=========================================
bool HasAMinutePassed() {
  DateTime dtNow = rtc.now();

  if ((dtNow.unixtime() - dtCurrentDisplayedTime.unixtime()) >= 60) 
    {
    return true;
    }
  else
    {
    return false; 
    }

}

//=========================================
// G e t D i g i t
//
// Returns a single digit out of the DateTime
//=========================================
int GetDigit(DateTime dtTime,int iDigitPos)
{
  switch(iDigitPos) 
  {
    case MINS_GETDIGIT:
      return dtTime.minute() % 10;
      break;
    case TENS_OF_MINS_GETDIGIT:
     return dtTime.minute() / 10;
     break;
    case HOURS_GETDIGIT:
      return dtTime.hour() % 10;
      break;
    case TENS_OF_HOURS_GETDIGIT:
      return dtTime.hour() / 10;
      break;  
  }
}

//=========================================
// R T C I n i t 
//=========================================
void RTCInit() {
    //------------
    // Setup RTC
    //------------

 if (! rtc.begin()) {
        Serial.println("RTC is NOT running!");
      }

  //Uncommenting this will initialize the clock to the
  //compile time of this code.
  //rtc.adjust(DateTime(__DATE__, __TIME__));

}

//=========================================
// P r i n t T i m e
//=========================================
void PrintCurrentTime() {
    DateTime dtTime;

    dtTime = rtc.now(); 
    
    Serial.print(GetDigit(dtTime,TENS_OF_HOURS_GETDIGIT));
    Serial.print(GetDigit(dtTime,HOURS_GETDIGIT));
    Serial.print(":");
    Serial.print(GetDigit(dtTime,TENS_OF_MINS_GETDIGIT));
    Serial.print(GetDigit(dtTime,MINS_GETDIGIT));
    Serial.print("\n");
}//=========================================
// P r i n t T i m e
//=========================================
void PrintTime(DateTime dtTime) {

    Serial.print(GetDigit(dtTime,TENS_OF_HOURS_GETDIGIT));
    Serial.print(GetDigit(dtTime,HOURS_GETDIGIT));
    Serial.print(":");
    Serial.print(GetDigit(dtTime,TENS_OF_MINS_GETDIGIT));
    Serial.print(GetDigit(dtTime,MINS_GETDIGIT));
    Serial.print("\n");
}
//=========================================
// U p d a t e D i s p l a y T i m e
//
// This will get current time and move 
// any digits that have changed 
//=========================================
void UpdateDisplayTime() {
    DateTime dtNow, dtNewDisplayedTime;
    long lMinPos, lTOMPos, lHoursPos, lTOHPos;

    dtNow = rtc.now(); 

    // Check if minute has passed 
    if (! HasAMinutePassed()) {
      return;
    }

    //Display time 
    dtNewDisplayedTime = dtNow;
    dtCurrentDisplayedTime = dtCurrentDisplayedTime;

    //Just to clarify, at this point we have 2 DateTime variables
    //    dtNewDisplayedTime = current time read from RTC in 24h format
    //dtCurrentDisplayedTime = time that is currently being displayed and is going to be replaced

    Serial.print("\n\nCurrent displayed time: ");
    PrintTime(dtCurrentDisplayedTime);
    Serial.print("New time: ");
    PrintTime(dtNewDisplayedTime);

    // current positions
    long oldMinPos = MINUTES_POSITIONS[GetDigit(dtCurrentDisplayedTime,MINS_GETDIGIT)];
    long oldTOMPos = TOM_POSITIONS[GetDigit(dtCurrentDisplayedTime,TENS_OF_MINS_GETDIGIT)];
    long oldHoursPos = HOURS_POSITIONS[GetDigit(dtCurrentDisplayedTime,HOURS_GETDIGIT)];
    long oldTOHPos = TOH_POSITIONS[GetDigit(dtCurrentDisplayedTime,TENS_OF_HOURS_GETDIGIT)];
   
    // new positions
    lMinPos = MINUTES_POSITIONS[GetDigit(dtNewDisplayedTime,MINS_GETDIGIT)];
    lTOMPos = TOM_POSITIONS[GetDigit(dtNewDisplayedTime,TENS_OF_MINS_GETDIGIT)];
    lHoursPos = HOURS_POSITIONS[GetDigit(dtNewDisplayedTime,HOURS_GETDIGIT)];
    lTOHPos = TOH_POSITIONS[GetDigit(dtNewDisplayedTime,TENS_OF_HOURS_GETDIGIT)];

    // if new position != old, first move to random position
    long randMinPos, randTOMPos, randHoursPos, randTOHPos;
    if(oldMinPos!=lMinPos) {
      randMinPos = MINUTES_POSITIONS[random(10)];
    }
    else {
      randMinPos = lMinPos;
    }

    if(oldTOMPos!=lTOMPos) {
      randTOMPos = MINUTES_POSITIONS[random(10)];
    }
    else {
      randTOMPos = lTOMPos;
    }

    if(oldHoursPos!=lHoursPos) {
      randHoursPos = MINUTES_POSITIONS[random(10)];
    }
    else {
      randHoursPos = lHoursPos;
    }
    
   if(oldTOHPos!=lTOHPos) {
      randTOHPos = MINUTES_POSITIONS[random(10)];
    }
    else {
      randTOHPos = lTOHPos;
    }

    MoveAllSteppers(randTOHPos, randHoursPos, randTOMPos, randMinPos);

    // now move to real positions
    MoveAllSteppers(lTOHPos, lHoursPos, lTOMPos, lMinPos);

    //Update current display time
    dtCurrentDisplayedTime = dtNow;

}

// speeded up mode for showing clock functionality
//
void UpdateDisplayShow() {
    DateTime dtNewDisplayedTime;
    long lMinPos, lTOMPos, lHoursPos, lTOHPos;

    DateTime dtNow("2022-01-01T11:55:00");   

    while(1) {
      
      //Display time 
      dtNewDisplayedTime = dtNow;
      dtCurrentDisplayedTime = dtCurrentDisplayedTime;

      //Just to clarify, at this point we have 2 DateTime variables
      //    dtNewDisplayedTime = current time read from RTC in 24h format
      //dtCurrentDisplayedTime = time that is currently being displayed and is going to be replaced

      Serial.print("\n\nCurrent displayed time: ");
      PrintTime(dtCurrentDisplayedTime);
      Serial.print("New time: ");
      PrintTime(dtNewDisplayedTime);

      // current positions
      long oldMinPos = MINUTES_POSITIONS[GetDigit(dtCurrentDisplayedTime,MINS_GETDIGIT)];
      long oldTOMPos = TOM_POSITIONS[GetDigit(dtCurrentDisplayedTime,TENS_OF_MINS_GETDIGIT)];
      long oldHoursPos = HOURS_POSITIONS[GetDigit(dtCurrentDisplayedTime,HOURS_GETDIGIT)];
      long oldTOHPos = TOH_POSITIONS[GetDigit(dtCurrentDisplayedTime,TENS_OF_HOURS_GETDIGIT)];
    
      // new positions
      lMinPos = MINUTES_POSITIONS[GetDigit(dtNewDisplayedTime,MINS_GETDIGIT)];
      lTOMPos = TOM_POSITIONS[GetDigit(dtNewDisplayedTime,TENS_OF_MINS_GETDIGIT)];
      lHoursPos = HOURS_POSITIONS[GetDigit(dtNewDisplayedTime,HOURS_GETDIGIT)];
      lTOHPos = TOH_POSITIONS[GetDigit(dtNewDisplayedTime,TENS_OF_HOURS_GETDIGIT)];

      // if new position != old, first move to random position
      long randMinPos, randTOMPos, randHoursPos, randTOHPos;
      if(oldMinPos!=lMinPos) {
        randMinPos = MINUTES_POSITIONS[random(10)];
      }
      else {
        randMinPos = lMinPos;
      }

      if(oldTOMPos!=lTOMPos) {
        randTOMPos = MINUTES_POSITIONS[random(10)];
      }
      else {
        randTOMPos = lTOMPos;
      }

      if(oldHoursPos!=lHoursPos) {
        randHoursPos = MINUTES_POSITIONS[random(10)];
      }
      else {
        randHoursPos = lHoursPos;
      }
      
    if(oldTOHPos!=lTOHPos) {
        randTOHPos = MINUTES_POSITIONS[random(10)];
      }
      else {
        randTOHPos = lTOHPos;
      }

      MoveAllSteppers(randTOHPos, randHoursPos, randTOMPos, randMinPos);

      // now move to real positions
      MoveAllSteppers(lTOHPos, lHoursPos, lTOMPos, lMinPos);

      //Update current display time
      dtCurrentDisplayedTime = dtNow;

      dtNow = dtNow + TimeSpan(0, 0, 1, 0);
      delay(6000);

    }

    
}
