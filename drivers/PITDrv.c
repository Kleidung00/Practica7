/*
 * PITDrv.c
 *
 *  Created on: Feb 10, 2022
 *      Author: Mario Castaneda
 */
/******************************************************************************/
/***        Include files                                                   ***/
/******************************************************************************/
#include "PITDrv.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Local Function Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Local Variables
 ******************************************************************************/
SIM_Type *pSIM_RegPIT = SIM;
PIT_Type *pPIT0_Reg = PIT;
/*******************************************************************************
 * Code
 ******************************************************************************/

/*******************************************************************************
 * vfnPIT0Init
 * DESCRIPTION:
 *
 * RETURNS:
 * void
 ******************************************************************************/
void vfnPIT0Init(unsigned long dwValue)
{
	pSIM_RegPIT->SCGC6 |= SIM_SCGC6_PIT_MASK;
	pPIT0_Reg->MCR = PIT_MCR_FRZ_MASK;					/*Timer Enable during debug*/
	pPIT0_Reg->CHANNEL[0].LDVAL = dwValue;
	pPIT0_Reg->CHANNEL[0].TCTRL =  PIT_TCTRL_TEN_MASK | PIT_TCTRL_TIE_MASK; 	/*Timer Enable*/
}

void vfnPIT1Init(unsigned long dwValue)
{
	pSIM_RegPIT->SCGC6 |= SIM_SCGC6_PIT_MASK;
	pPIT0_Reg->MCR = PIT_MCR_FRZ_MASK;					/*Timer Enable during debug*/
	pPIT0_Reg->CHANNEL[1].LDVAL= dwValue;
	pPIT0_Reg->CHANNEL[1].TCTRL= PIT_TCTRL_TEN_MASK | PIT_TCTRL_TIE_MASK; 	/*Timer Enable*/
}
/*******************************************************************************
 * bfnPIT0Check
 * DESCRIPTION:
 *
 * RETURNS:
 * void
 *******************************************************************************/
unsigned char bfnPITCheck(uint8_t bChannel)
{
	if(pPIT0_Reg->CHANNEL[0].TFLG & PIT_TFLG_TIF_MASK) 	/*Timer Overflow*/
	{
		pPIT0_Reg->CHANNEL[bChannel].TCTRL = 0;
		pPIT0_Reg->CHANNEL[bChannel].TFLG = PIT_TFLG_TIF_MASK;
		pPIT0_Reg->CHANNEL[0].TCTRL = PIT_TFLG_TIF_MASK;
		return ( 1 );
	}
	return ( 0 );
}
