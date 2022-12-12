//==========================================================================
// Magnet Viewing Clock - MagnetViewingClock.ino
//
// Copyright (c) 2022, Moritz v. Sivers
//
// based on Slide Clock by Craig Colvin, https://github.com/moose408/SlideClock
//
// Licensed under Creative Commons License
// Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
//==========================================================================

#include "hardware.h"
#include "stepper.h"
#include "clock.h"

#include "ClockCoordinates.h"     //DEBUG DEBUG

//=======================================
// C o n s t a n t s
//=======================================
#define UP_ARROW  0x75 // 'u'
#define DOWN_ARROW 0x64 // 'd'
#define EQUALS_SIGN 0x3D
#define PLUS_SIGN 0x2B
#define MINUS_SIGN 0x2D
#define CTRL_C  0x78 //'x'


typedef struct {
  int minutes;
  int tensOfMinutes;
  int hours;
  int tensOfHours;
}myDateTime;

//=======================================
// Global Variables
//=======================================
int iCurrentMotor;


//========================================
// K e y p a d C o n t r o l
//========================================
void KeypadControl() {
  bool bLoop;
  bool bArrowSequence;
  int in;
  long lSteps;


  // initialize variables
  bLoop = true;
  //bArrowSequence = false;
  lSteps = 50;
  iCurrentMotor = MINUTES;

  while (bLoop) {  
 
    if(Serial.available()){
      in = Serial.read();



      switch (in) {
        case CTRL_C:      //'x'
            bLoop=false;
            return;
            break;
        case DOWN_ARROW:
              Serial.print(F("DOWN\n"));
              MoveRelative(iCurrentMotor,lSteps);
            break;
        case UP_ARROW:
              Serial.print(F("UP\n"));
              MoveRelative(iCurrentMotor, -lSteps);
            break;
        case PLUS_SIGN:
        case EQUALS_SIGN:   //plus (or equals)
            Serial.print(F("Increase Steps\n"));
             lSteps = lSteps+100;
            break;
        case MINUS_SIGN:        // minus
            Serial.print(F("Decrease Steps\n"));
             lSteps = lSteps-100;
            break;
        case 0x7A:      // 'z'
            ZeroPosition(iCurrentMotor);
            break;
        case '0':
          iCurrentMotor = MINUTES;
          break;
        case '1':
          iCurrentMotor = TOM;
          break;
        case '2':
          iCurrentMotor = HOURS;
          break;
        case '3':
          iCurrentMotor = TOH;
          break;
        case '4':
          lSteps = 10;
          break;
        case '5':
          lSteps = 50;
          break;
        case '6':
          lSteps = 100;
          break;
       case '7':
          lSteps = 200;
          break;
       case '8':
          lSteps = 800;
          break;
       case '9':
          lSteps = 1000;
          break;
       default:
          Serial.print(F("Input detected: '"));
          Serial.print(in);
          Serial.print(F("' 0x"));
          Serial.print(in, HEX);
          Serial.print("\n");
          break;
     }  //switch  

    //show current values
    Serial.print("Current Position: ");
    Serial.println(GetCurrentPosition(iCurrentMotor));

    Serial.print("Steps: ");
    Serial.print(lSteps);
    Serial.print("\n");
     
    } // if
  } // while

}
//=======================================
// R u n C l o c k
//=======================================
void RunClock() {

  while(1) {
    UpdateDisplayTime();
    
    delay(1000);
  }
}
//-------------------------------------
// s e t u p
//-------------------------------------
void setup()
{
    Serial.begin(9600);
    Serial.print("Magnet Viewing Clock version 1.0\n");

    pinMode(BTN_MODE, INPUT_PULLUP);
    pinMode(BTN_ADVANCE, INPUT_PULLUP);
    pinMode(NOT_ENABLE_PIN, OUTPUT);


  iCurrentMotor = MINUTES;

  RTCInit();
  InitSteppers();

  delay(1000);
  KeypadControl();
  //TestMotors();
  RunClock();
  //UpdateDisplayShow();


}
//-------------------------------------
// l o o p
//
// If we make it to loop() then we are
// processing user input from terminal
// window.
//-------------------------------------
void loop()
{
}
