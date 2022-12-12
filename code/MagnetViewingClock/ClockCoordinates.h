//==========================================================================
// Magnet Viewing Clock - ClockCoordinates.h
//
// Copyright (c) 2022, Moritz v. Sivers
//
// based on Slide Clock by Craig Colvin, https://github.com/moose408/SlideClock
//
// Licensed under Creative Commons License
// Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
//==========================================================================

#ifndef CLOCKCOORDINATES_H
#define CLOCKCOORDINATES_H

const long MAX_TOH_STEPS = 2048;
const long MAX_HOURS_STEPS = 2048;
const long MAX_TOM_STEPS = 2048;       //DEBUG DEBUG Need to confirm this
const long MAX_MINUTES_STEPS = 2048;


extern const long MINUTES_POSITIONS[];
extern const long TOM_POSITIONS[];
extern const long HOURS_POSITIONS[];
extern const long TOH_POSITIONS[];

// Number of absolute steps from home
// where a digit resides
#define POS_0 0
#define POS_1 205
#define POS_2 410
#define POS_3 615
#define POS_4 820
#define POS_5 1025
#define POS_6 1230
#define POS_7 1440
#define POS_8 1645
#define POS_9 1850

#endif //CLOCKCOORDINATES_H
