//==========================================================================
// Magnet Viewing Clock - ClockCoordinates.cpp
//
// Copyright (c) 2022, Moritz v. Sivers
//
// based on Slide Clock by Craig Colvin, https://github.com/moose408/SlideClock
//
// Licensed under Creative Commons License
// Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
//==========================================================================
#include <arduino.h>
#include <avr/pgmspace.h> 
#include "ClockCoordinates.h"



// Absolute location in steps for each digit 0-9
const long MINUTES_POSITIONS[10] = {
  POS_0,      // digit 0
  POS_1,      // digit 1 
  POS_2,      // digit 2 
  POS_3,      // digit 3 
  POS_4,      // digit 4 
  POS_5,      // digit 5 
  POS_6,      // digit 6 
  POS_7,      // digit 7 
  POS_8,      // digit 8 
  POS_9       // digit 9 
};

// Absolute location in steps for each digit 0-5
const long TOM_POSITIONS[6]  = {
  -POS_0,      // digit 0
  -POS_1,      // digit 1 
  -POS_2,      // digit 2 
  -POS_3,      // digit 3 
  -POS_4,      // digit 4 
  -POS_5,      // digit 5 
};

// Absolute location in steps for each digit 0-9
const long HOURS_POSITIONS[10]  = {
  POS_0,      // digit 0
  POS_1,      // digit 1 
  POS_2,      // digit 2 
  POS_3,      // digit 3 
  POS_4,      // digit 4 
  POS_5,      // digit 5 
  POS_6,      // digit 6 
  POS_7,      // digit 7 
  POS_8,      // digit 8 
  POS_9       // digit 9 
};

// Absolute location in steps for each digit 0-2
const long TOH_POSITIONS[3]  = {
  -POS_0,      // digit 0
  -POS_1,      // digit 1 
  -POS_2       // digit 2
};
