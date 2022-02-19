/*
 * PWM.h
 */

#ifndef PWM_H_
#define PWM_H_
#include<stdio.h>
#include "MKL25Z4.h"

void vfnPWMInit(void);
uint8_t bfnInitialPos (void);
uint8_t bfnPWMAngleAdjustment (void);
void vfndelayMs(uint16_t n);

#define PIN_E31 (31)

#endif /* PWM_H_ */
