/* Copyright 2017, DSI FCEIA UNR - Sistemas Digitales 2
 *    DSI: http://www.dsi.fceia.unr.edu.ar/
 * Copyright 2017, Diego Alegrechi
 * Copyright 2017, Gustavo Muro
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

/*==================[inclusions]=============================================*/
#include "board.h"
#include "MKL46Z4.h"
#include "mma8451.h"
#include "fsl_lpsci_hal.h"
#include "fsl_clock_manager.h"
#include "fsl_pit_hal.h"
#include <stdio.h>
#include <string.h>

/*==================[macros and definitions]=================================*/
#define EJE_X	1
#define EJE_Y	2
#define EJE_Z	3

/*==================[internal data declaration]==============================*/
int choice = EJE_Z;
int16_t TEST_ACC = false;

/*==================[internal functions declaration]=========================*/
void UART_Init(void);
void PIT_Init(void);

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

void UART_Init(void)
{
	// Enable the UART transmitter and receiver

	LPSCI_HAL_SetIntMode(UART0, kLpsciIntRxDataRegFull, true);
	/* habilita transmisor y receptor */
	LPSCI_HAL_EnableReceiver(UART0);
	LPSCI_HAL_EnableTransmitter(UART0);
}

void PIT_Init(void)
{
	SIM_HAL_EnableClock(SIM, kSimClockGatePit0);
	PIT_HAL_Enable(PIT);
	PIT_HAL_SetTimerPeriodByCount(PIT, 1, 0xFFFFF);
	PIT_HAL_SetIntCmd(PIT, 1, true);
	PIT_HAL_SetTimerRunInDebugCmd(PIT, false);
	PIT_HAL_StartTimer(PIT, 1);
}

/*==================[external functions definition]==========================*/

int main(void)
{
	int16_t acc;

	char Buffer[10];

    // Enable clock for PORTs, setup board clock source, config pin
    board_init();

    // Se inicializa el UART0
    UART_Init();

	// Se inicializa el timer PIT
	PIT_Init();

	NVIC_ClearPendingIRQ(UART0_IRQn);
    NVIC_EnableIRQ(UART0_IRQn);

    NVIC_ClearPendingIRQ(PIT_IRQn);
    NVIC_EnableIRQ(PIT_IRQn);

    while(true)
    {
    	if(TEST_ACC == true)
    	{
			switch(choice)
			{
				case EJE_X:
					acc = iAcclReadX();
					sprintf(Buffer,"x= %d\r",acc);
					break;
				case EJE_Y:
					acc = iAcclReadY();
					sprintf(Buffer,"y= %d\r",acc);
					break;
				case EJE_Z:
					acc = iAcclReadZ();
					sprintf(Buffer,"z= %d\r",acc);
					break;
			}

			LPSCI_HAL_SendDataPolling(UART0, (uint8_t *)"         \r",10);
			LPSCI_HAL_SendDataPolling(UART0, (uint8_t *)Buffer,strlen(Buffer));
    	}
    	TEST_ACC = false;
   }
}

void UART0_IRQHandler(void)
{
	uint8_t  rxChar	= 0;

	LPSCI_HAL_Getchar(UART0, &rxChar);
	switch(rxChar)
	{
		case 'x':
			choice = EJE_X;
			break;
		case 'y':
			choice = EJE_Y;
			break;
		case 'z':
			choice = EJE_Z;
			break;
	}

	LPSCI_HAL_ClearStatusFlag(UART0,kLpsciRxActiveEdgeDetect);
}

void PIT_IRQHandler(void)
{
	PIT_HAL_ClearIntFlag(PIT, 1);
	TEST_ACC = true;
}

/*==================[end of file]============================================*/
















