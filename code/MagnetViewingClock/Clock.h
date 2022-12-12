//==========================================================================
// Magnet Viewing Clock -  Clock.h
//
// Copyright (c) 2022, Moritz v. Sivers
//
// based on Slide Clock by Craig Colvin, https://github.com/moose408/SlideClock
//
// Licensed under Creative Commons License
// Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
//==========================================================================

#include "ClockCoordinates.h"

#ifndef CLOCK_H
#define CLOCK_H


void UpdateDisplayTime();
void RTCInit();
void UpdateDisplayShow();

void PrintCurrentTime();


#endif //CLOCK_H
