//==========================================================================
// Magnet Viewing Clock - stepper.h
//
// Copyright (c) 2022, Moritz v. Sivers
//
// based on Slide Clock by Craig Colvin, https://github.com/moose408/SlideClock
//
// Licensed under Creative Commons License
// Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
//==========================================================================

#ifndef STEPPER_H
#define STEPPER_H

const int MINUTES = 0;
const int TOM = 1;
const int HOURS = 2;
const int TOH = 3;

// Motor parameters
const int FULL_STEPS_PER_REVOLUTION = 2048;
const int MAXSPEED = 500; 
const int ACCELERATION = 1000;

// position where hall sensor is triggered
const int TOH_OFFSET = -1510;
const int HOURS_OFFSET = 1880;
const int TOM_OFFSET = -1570;
const int MINS_OFFSET = 1340;


void InitSteppers();
void MoveRelative(int iMotor, long lSteps);
void MoveAbsolute(int iMotor, long lSteps);
long GetCurrentPosition(int iMotor);
void ZeroPosition(int iMotor);
void MoveAllSteppers(long lTOHSteps, long lHoursSteps, long lTOMSteps, long lMinutesSteps);
void FindHomePosition();
void SetHomePosition();
void TestMotors();

#endif //STEPPER_H
