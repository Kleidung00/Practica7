#include "PWM.h"
#include "MKL25Z4.h"
#include<stdio.h>
#include "ADC.h"

void vfnPWMInit (void)
{
    SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;
    SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK;
    PORTC->PCR[PIN_E31] = PORT_PCR_MUX(1);

    SIM->SOPT2 |= SIM_SOPT2_TPMSRC_MASK;

    TPM0->CONTROLS[1].CnSC |= TPM_CnSC_MSB_MASK  | TPM_CnSC_ELSB_MASK;

    TPM0->MOD = TPM_MOD_MOD_MASK;

    TPM0->CONTROLS[1].CnV = TPM_CnV_VAL_MASK;

    TPM0->SC |= (TPM_SC_PS_MASK >> 2);
    TPM0->SC |= 0x8;
    TPM0->SC |= TPM_SC_DMA_MASK | TPM_SC_TOF_MASK | TPM_SC_TOIE_MASK;
}

uint8_t bfnInitialPos (void)
{
	  TPM0->CONTROLS[1].CnV = 500;
	  vfndelayMs(500);
	  return 0;
}

uint8_t bfnPWMAngleAdjustment (void){
	int result;
	result = wfnReadADC(PIN_E20);
	TPM0->CONTROLS[1].CnV = 500 +  result*5/8;
	 /* duty cicle 10%, señal en alto de 2ms, permite girar hasta 180°*/

	return 0;
}

void vfndelayMs(uint16_t n)
{
	uint8_t bValue1;
	uint8_t bValue2;
	for(bValue1 = 0 ; bValue1 < n; bValue1++)
	for(bValue2 = 0 ; bValue2 < 7000; bValue2++)
	{

	}
}
