/*
 * LEDDrv.c
 *
 *  Created on: Jan 16, 2022
 *      Author: Mario Castañeda
 */
/****************************************************************************/
/***        Include files                                                 ***/
/****************************************************************************/
#include"LEDDvr.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Local Function Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Local Variables
 ******************************************************************************/
		/* Peripheral GPIOA base address */
extern GPIO_Type *rGpioB ;			/* Peripheral GPIOB base address */
/*******************************************************************************
 * Code
 ******************************************************************************/

/*******************************************************************************
 * vfnLEDsInit
 * DESCRIPTION: Pin leds Initialization
 *
 * RETURNS:
 * void
 ******************************************************************************/
void vfnLEDsInit(void)
{
	SIM_Type *rclkSIM_gpio= SIM;		/* Peripheral SIM base pointer */
		/* Peripheral PORTA base pointer */
	PORT_Type *rPortB = PORTB;			/* Peripheral PORTB base pointer */

	/*Enable Clks*/
	rclkSIM_gpio->SCGC5 = SIM_SCGC5_PORTB_MASK;

		/*Alternative pin MUX*/
	rPortB->PCR[PIN_B9] = PORT_PCR_MUX(1);
	rPortB->PCR[PIN_B10] = PORT_PCR_MUX(1);
			/*Port Data Direction Register*/
    rGpioB->PDDR = 1u << PIN_B9 | 1u << PIN_B10;
			/*Turn OFF*/
	rGpioB->PSOR |= 1u << PIN_B9;
	rGpioB->PSOR |= 1u << PIN_B10;
}
/*******************************************************************************
 * vfnLEDRed
 * DESCRIPTION: Turn on RED
 *
 * RETURNS:
 * void
 ******************************************************************************/

/*******************************************************************************
 * vfnLEDGreen
 * DESCRIPTION: Turn on GREEN
 *
 * RETURNS:
 * void
 ******************************************************************************/

/*******************************************************************************
 * vfnLEDBlue
 * DESCRIPTION: Turn on BLUE
 *
 * RETURNS:
 * void
 ******************************************************************************/

/*******************************************************************************
 * vfnLEDsOff
 * DESCRIPTION: Turn off all the LEDs RGB
 *
 * RETURNS:
 * void
 ******************************************************************************/
