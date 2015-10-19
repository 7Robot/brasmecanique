/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

/* Device header file */




#include <stdint.h>        /* Includes uint16_t definition                    */
#include <stdbool.h>       /* Includes true/false definition                  */
#include <stdlib.h>   

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp              */

#include <libpic30.h>       //_delay_ms and other stuff
#include <math.h>       //_delay_ms and other stuff


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

/* i.e. uint16_t <variable_name>; */

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/

int16_t main(void)
{
    char c;
    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize IO ports and peripherals */
    InitApp();
    Init_Uart1();
    
   //main cycle 
    while(1)
    {

        PDC1 = 0;
         Transmit_String("wow");
        __delay_ms(1000);
        
        if (Get_Uart(&c)) {
            if (c == 'l' || c == 'L') {
                LED = !LED;
            }
        }
        
         
    }
}
