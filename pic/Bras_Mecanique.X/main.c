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

extern int pot0max;
extern int pot0min;
extern int pot0center;

// 0 : 0/360/644 : Z axis 230/511/798
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
void stopmotor(void) {
    
    PDC1 = 0;
PWMCON1bits.PEN1H = 0;
//setup LED pin
   
}

int16_t main(void) {
    int i;
    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize IO ports and peripherals */
    InitApp();
    // Init_Uart1();

    ADCON1bits.ADON = 1; // turn on ADC here

  
    
   calibrate(0);
   
       sprintf (&buffer[0], "min:%d\r\n", pot0min);
        Transmit_String (&buffer[0]); 
        
         sprintf (&buffer[0], "max:%d\r\n", pot0max);
        Transmit_String (&buffer[0]); 
        
  sprintf (&buffer[0], "center:%d\r\n", pot0center);
        Transmit_String (&buffer[0]); 
    
    while (1) {
        //        PDC1 = 0;
        //  receiveCommand();
        scanPots();
     
        
   
       


 sprintf (&buffer[0], "pot0:%d\r\n", pot[0]);
        Transmit_String (&buffer[0]); 
                
//                for (i = 0; i<5; i++) {
//        
//                    sprintf (&buffer[0], "%d: %d\r\n", i, pot[0]);
//                    __delay_ms (10);
//                    Transmit_String(&buffer[0]);
//                    __delay_ms (20);
//                }
               __delay_ms(2000);
                LED = !LED;

    }
}
