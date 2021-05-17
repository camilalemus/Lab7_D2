//********************************************************************
// Camila Lemus Lone
// 18272
// Universidad del Valle de Guatemala
//********************************************************************

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

//********************************VARIABLES***************************

bool state = false;
bool flag = false;
int led;
char letra;

#define RED GPIO_PIN_1
#define GREEN GPIO_PIN_3
#define BLUE GPIO_PIN_2
#define OFF 0


//***************************INSTANCIAR FUNCIONES*********************

void Config_Timer0(void);
void Timer0IntHandler(void);
void UART_Config(void);
void UARTIntHandler(void);
/**
 * main.c
 */


//*******************************************************************

int main(void)
{
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN); // Clk a 40MHz
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF); //Periferal Enable port F
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3); // Salidas y entradas
    UART_Config();
    Config_Timer0();
 //   GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4);
 //  GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

    while (1)
        {
            if (state || flag == false){
                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, OFF);
            }
            else {
                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, led);
            }
        }
    }

void Config_Timer0(void){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    TimerConfigure(TIMER0_BASE,TIMER_CFG_PERIODIC); // Periodico
    // Para hacer 0.5Hz, con 40MHz, se configura a 20MHz
    TimerLoadSet(TIMER0_BASE, TIMER_A, 20000000);
    TimerIntRegister(TIMER0_BASE, TIMER_A, Timer0IntHandler); //Interrupt Enable Timer0A
    IntEnable(INT_TIMER0A);
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT); //Timeout enable
    IntMasterEnable(); //Interrupciones globales
    TimerEnable(TIMER0_BASE, TIMER_A);
}

void Timer0IntHandler(void){
    TimerIntClear(TIMER0_BASE, TIMER_A);
    state = !state;
}

//********************************* UART ********************************

void UARTIntHandler(void){
    UARTIntClear (UART0_BASE, UART_INT_RX);
    letra = UARTCharGet(UART0_BASE);

        switch (letra){
            case 'r':
                flag =!flag;
                led = RED;
                break;
            case 'g':
                flag =!flag;
                led = GREEN;
                break;
            case 'b':
                flag =!flag;
                led = BLUE;
                break;
            default:
                led = OFF;
        }
    }

void UART_Config(void){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0); //Peripheral del UART enable
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA); //Peripheral del puerto A enable
        GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0|GPIO_PIN_1); //Los pines TX y RX se ponen en modo UART
        //Inicializar el modulo UART con: 115200, 8 data bits, 1 stop bit, None parity.
        UARTConfigSetExpClk(UART0_BASE,SysCtlClockGet(), 115200, UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE);
        UARTIntEnable(UART0_BASE, UART_INT_RT | UART_INT_RX); //Habilitar la comunicacion UART
        UARTIntRegister(UART0_BASE, UARTIntHandler); //Interrupt enable
}
