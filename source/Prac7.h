#include <stdio.h>
#include "board.h"

#define TIMER_700ms   ( 0x2160EBF )
#define TIMER_2s		( 0x5F5E0FF )
#define ADC_0 	    ( 0 )
#define PIT_0		( 0 )
#define PIT_1		( 1 )
#define PIN_B8      ( 8 )
#define MUESTRAS	    ( 10 )

typedef enum
{
    LECTURA_ESTADO,
    CONVERSION_ESTADO,
    ACTUALIZACION_ESTADO
}Estados;

void vfnBlinkAzul(void);

void vfnLecturaADC(void);
void vfnConversion(void);
void vfnActualizacion(void);

void vfnMaquinaEstados(void);
