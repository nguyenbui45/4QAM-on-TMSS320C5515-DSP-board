/*
 * sinetab.h
 *
 *  Created on: Nov 7, 2021
 *      Author: COMPUTER
 */

#ifndef SINETAB_H_
#define SINETAB_H_
/* Pre-generated sine and cosine wave data
* 16-bit signed samples, 4 samples/period, f_carrier =
6000 kHz */
#include "usbstk5515.h"

static Int8 samplesPerPeriod = 4;
static Int16 sinetable[4] = {0, 16384,0, -16384 };
static Int16 cosinetable[4] = {16384, 0,-16384, 0 };

#endif /* SINETAB_H_ */
