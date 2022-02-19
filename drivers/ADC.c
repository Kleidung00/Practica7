#include "MKL25Z4.h"
#include<stdio.h>
#include "ADC.h"

void ADC_vfnDriverInit (void){
	GPIO_Type *rGpioE = GPIOE;
    SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;
    PORTE->PCR[PIN_E20] = PORT_PCR_MUX(1);
    rGpioE->PDDR &= ~(1u << PIN_E20);
    SIM->SCGC6  |= SIM_SCGC6_ADC0_MASK ;

    ADC0->CFG1 |= (ADC_CFG1_ADIV_MASK);
    ADC0->CFG1 |=  ADC_CFG1_ADIV_MASK | ADC_CFG1_ADLSMP_MASK | ADC_CFG1_ADICLK_MASK;
    ADC0->CFG1 &= ~ADC_CFG1_MODE_MASK;

    ADC0->SC3 |= ADC_SC3_ADCO_MASK;
}

uint16_t wfnReadADC (uint8_t bChannel){
	uint16_t bValueADC;
    ADC0->SC1[0] = bChannel & ~ADC_SC1_DIFF_MASK;
    while(!(ADC0->SC1[0] & ADC_SC1_COCO_MASK))
    {

    }
    bValueADC = ADC0->R[0];
    return bValueADC;
}
