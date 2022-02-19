/*
 * debouncer.h
 *
 *  Created on: 1 feb 2022
 *      Author: anacu
 */
#ifndef DEBOUNCER_H_
#define DEBOUNCER_H_
#include "MKL25Z4.h"



#define PIN_A16     ( 16 )
#define PIN_A17    ( 1 )


void vfnbuttonInit(void);
uint8_t bfndebounceUpdate (void);



#endif /* DEBOUNCE_H_ */

