#ifndef ADC_H_
#define ADC_H_

extern void vfnDriverInit(void);

uint16_t wfnReadADC (uint8_t bChannel);
uint8_t bfnConversionTemp (uint16_t wVoltaje);

#define PIN_E20 (20)

#define VALOR_CONVERSION    ( 1.29 )

#endif /* ADC_H_ */
