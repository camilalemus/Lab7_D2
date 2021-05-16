//******************************************************************************************
// Camila Lemus Lone
// 18272
// Universidad del Valle de Guatemala
//******************************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.h"
#include "driverlib/systick.h"
#include "driverlib/uart.h"

//************************************VARIABLES**********************************************



//*********************************INSTANCIAR FUNCIONES**************************************

void TimerConfig(void);
void Timer0IntHandler(void);
void UARTconfig(void);
void UARTIntHandler(void);
void SendString(char* frase);
/**
 * main.c
 */


//*******************************************************************************************

int main(void)
{
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN); // Clk a 40MHz
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF); //Periferal Enable port F
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3); // Salidas y entradas
 //   GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4);
 //  GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

    while (1)
    {

    }
}
