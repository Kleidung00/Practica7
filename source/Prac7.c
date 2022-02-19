/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdio.h>
#include "fsl_debug_console.h"
#include "board.h"
#include "LCDDriver.h"
#include "ADC.h"
#include "fsl_adc16.h"
#include "PITDrv.h"
#include "fsl_uart.h"
#include "LEDDvr.h"
#include "pin_mux.h"
#include "peripherals.h"
#include "clock_config.h"
#include "MKL25Z4.h"
//#include "PWM.h"
#include "stdio.h"
#include "LCDDriver.h"
#include "Prac7.h"

static void (*vfnTmpStates[])(void) =
{
    (void (*)(void))vfnLecturaADC, 		//READ ADC VALUE
    (void (*)(void))vfnConversion,   		//CONVERT V TO TEMPERATURE
    (void (*)(void))vfnActualizacion			//PRINT
};

GPIO_Type *rGpioB = GPIOB;

uint16_t wVoltaje = 0;
uint16_t wTemperatura = 0;
uint8_t bEstadoActual = LECTURA_ESTADO;

int main(void)
{

    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();
    vfnDriverInit();
    vfnLEDsInit();

    while (1)
    {
    	vfnMaquinaEstados();
    	vfnBlinkAzul();
    }
}

void vfnMaquinaEstados(void)
{
	vfnTmpStates[bEstadoActual]();
}

void vfnLecturaADC(void)
{
	uint8_t bContador = 0;
	if(bContador < MUESTRAS)
	{
		bContador++;
		wVoltaje = wVoltaje + wfnReadADC(ADC_0);
		bEstadoActual = LECTURA_ESTADO;
	}
	else
	{
		bContador = 0;
		bEstadoActual = CONVERSION_ESTADO;
	}
}

void vfnConversion(void)
{
	wVoltaje /= MUESTRAS;
	wTemperatura = bfnConversionTemp(wVoltaje);
	bEstadoActual = ACTUALIZACION_ESTADO;
}

void vfnActualizacion(void)
{
	if(bfnPITCheck(PIT_1))
	{
		PRINTF("TEMP: %i\n\t", wTemperatura);
		bEstadoActual = LECTURA_ESTADO;
	}
	else
	{
		bEstadoActual = ACTUALIZACION_ESTADO;
	}
}

void vfnBlinkAzul(void)
{
	if(bfnPITCheck(PIT_0))
	{
		rGpioB->PTOR |= 1 << PIN_B8;
	}
}
