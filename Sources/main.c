
/*==================[inclusions]=============================================*/
#include "board.h"
#include "MKL46Z4.h"
#include "mma8451.h"
#include "fsl_lpsci_hal.h"
#include "fsl_clock_manager.h"
#include "fsl_pit_hal.h"
#include <stdio.h>
#include <string.h>



#define EJE_X	1
#define EJE_Y	2
#define EJE_Z	3


// Prototipo de funciones
void UART_Init(void);
void PIT_Init(void);



int choice = EJE_Z;
int16_t TEST_ACC = false;


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


