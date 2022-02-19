/*
 * debouncer.c
 *
 *  Created on: 1 feb 2022
 *      Author: Mario Castaneda
 */
#include "debouncer.h"

GPIO_Type *rDEBGpioA = GPIOA;			/* Peripheral GPIOB base address */
GPIO_Type *rDEBGpioC = GPIOC;			/* Peripheral GPIOB base address */

uint8_t bPreviousStateGlo	= ((1 << PIN_A16) |(1 << PIN_A17));
uint8_t bCurrentState 		= ((1 << PIN_A16) |(1 << PIN_A17));

void vfnbuttonInit(void)
{
	SIM_Type *rclkSIM_gpio= SIM;		/* Peripheral SIM base pointer */
	PORT_Type *rPortA = PORTA;			/* Peripheral PORTA base pointer */
	PORT_Type *rPortC = PORTC;			/* Peripheral PORTB base pointer */
	//Enable Clks
	rclkSIM_gpio->SCGC5 |= SIM_SCGC5_PORTA_MASK | SIM_SCGC5_PORTC_MASK;

	rPortC->PCR[1] = PORT_PCR_MUX(1) | PORT_PCR_PS_MASK | PORT_PCR_PE_MASK;	/*Alternative pin MUX*/
	rPortA->PCR[4] = PORT_PCR_MUX(1) | PORT_PCR_PS_MASK | PORT_PCR_PE_MASK;

    rDEBGpioA->PDDR &= ~(1u << PIN_A17);			/*Port Data Direction Register*/
    rDEBGpioC->PDDR &= ~(1u << PIN_A16);			/*Port Data Direction Register*/
}

uint8_t bfndebounceUpdate (void)  //regresa cero
{
	static uint8_t bCnt=0;
	static uint8_t bCnt2=0;
	uint8_t bButtonStateLocal = ((rDEBGpioC->PDIR & (1u << PIN_A16)) | (rDEBGpioA->PDIR & (1u << PIN_A17))) ;  //se lee el estado del boton, CURRENTbuttonstate local
	uint8_t bButtonChange = bButtonStateLocal ^ bPreviousStateGlo;

	if (bButtonChange & (1 << PIN_A16))
	{
		bCnt=3;
	}
	/*cada 20ms*/
	else
	{
		if (bCnt)
		{
			bCnt--;
		}
		else
		{
			bCurrentState &= ~(1 << PIN_A16); /*ya está en 0, cln GLOBAL variable*/
			bCurrentState |= ((1<<PIN_A16) & bButtonStateLocal) ; //bCurrentState= 1 | 1
		}
	}
	//bOTON 2
	if (bButtonChange & (1 << PIN_A17))
	{
		bCnt2=3;
	}
	/*cada 20ms*/
	else
	{
		if (bCnt2)
		{
			bCnt2--;
		}
		else
		{
			bCurrentState &= ~(1 << PIN_A17); /*ya está en 0, cln GLOBAL variable*/
			bCurrentState |= ((1<<PIN_A17) & bButtonStateLocal) ; //bCurrentState= 1 | 1
		}
	}

	bPreviousStateGlo = bButtonStateLocal;

	return bCurrentState;
}
