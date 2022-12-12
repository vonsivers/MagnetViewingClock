//==========================================================================
// Magnet Viewing Clock - hardware.h
//
// Copyright (c) 2022, Moritz v. Sivers
//
// based on Slide Clock by Craig Colvin, https://github.com/moose408/SlideClock
//
// Licensed under Creative Commons License
// Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
//==========================================================================

#ifndef HARDWARE_H
#define HARDWARE_H

//-----------------------------------
// Pinout and motor constants
// Using CNC Stepper Motor Shield
//-----------------------------------

// Arduino pin usage
const int MINS_STEP_PIN = 3;        //This is y-axis motor
const int MINS_DIR_PIN = 6;

const int TOM_STEP_PIN = 2;         //This is x-axis motor
const int TOM_DIR_PIN = 5;

const int HOURS_STEP_PIN = 12;       //This is a-axis motor
const int HOURS_DIR_PIN = 13;

const int TOH_STEP_PIN = 4;         //This is z-axis motor
const int TOH_DIR_PIN = 7;

const int NOT_ENABLE_PIN = 8;       //Active low ENABLE pin to turn on stepper drivers

// Pushbutton switches
#define BTN_MODE A1
#define BTN_ADVANCE A2


#endif //HARDWARE_H