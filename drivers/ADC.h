#ifndef ADC_H_
#define ADC_H_

extern void ADC_vfnDriverInit(void);

uint16_t wfnReadADC (uint8_t bChannel);

#define PIN_E20 (20)

#endif /* ADC_H_ */
