/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

/* Device header file */




#include <stdint.h>        /* Includes uint16_t definition                    */
#include <stdbool.h>       /* Includes true/false definition                  */
#include <stdlib.h>   
#include <stdio.h>  
#include <string.h> 

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp              */

#include <libpic30.h>       //_delay_ms and other stuff
#include <math.h>       //_delay_ms and other stuff

#include "comm.h"


#if defined(__XC16__)
#include <xc.h>
#elif defined(__C30__)
#if defined(__dsPIC30F__)
#include <p30F4011.h>
#endif
#endif

#include "uart.h"

/******************************************************************************/
/* Global Variable Declaration                                                */
/******************************************************************************/

volatile int coordinates [5] = {0, 0, 0, 0, 0};
volatile int pot [5] = {0, 0, 0, 0, 0};

// 0 : 0/360/644 : Z axis
// 1 : 385/217
// 2 : 579/350
// 3 : 0/400   400 = 360deg
// 4 : 
int c1, c2, c3, c4, c5 = 0;

char buffer[30];
int coordMassivePointer = 0;

/******************************************************************************/
/* Main Program                                                               */

/******************************************************************************/

int16_t main(void) {
    int i;
    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize IO ports and peripherals */
    InitApp();
    // Init_Uart1();

    ADCON1bits.ADON = 1; // turn on ADC here
    while (1) {
        //        PDC1 = 0;
        //  receiveCommand();

        scanPots();
        
        for (i = 0; i<5; i++) {
            sprintf (&buffer[0], "%d: %d\r\n", i, pot[i]);
            __delay_ms (10);
            Transmit_String(&buffer[0]);
            __delay_ms (20);
        }
        __delay_ms(1000);
        LED = !LED;

    }
}
