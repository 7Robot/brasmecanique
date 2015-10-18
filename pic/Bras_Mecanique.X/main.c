/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

/* Device header file */




#include <stdint.h>        /* Includes uint16_t definition                    */
#include <stdbool.h>       /* Includes true/false definition                  */
   

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp              */
#include <libpic30.h>       //_delay_ms and other stuff
#include <math.h>       //_delay_ms and other stuff
//#include <stdlib.h> 

#if defined(__XC16__)
   #include <xc.h>
#elif defined(__C30__)
    #if defined(__dsPIC30F__)
        #include <p30F4011.h>
    #endif
#endif
/******************************************************************************/
/* Global Variable Declaration                                                */
/******************************************************************************/

/* i.e. uint16_t <variable_name>; */

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/

int16_t main(void)
{

    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize IO ports and peripherals */
    InitApp();

    
   //main cycle 
    while(1)
    {
        

        PDC1 = 0;
        LED = !LED;
        __delay_ms(1000);
        LED = !LED;
        PDC1 = 500;
        __delay_ms(1000);
        LED = !LED;
        PDC1 = 1000;
        __delay_ms(1000);
        LED = !LED;
        PDC1 = 1500;
        __delay_ms(1000);
        LED = !LED;
        PDC1 = 2000;
        __delay_ms(1000);
        LED = !LED;
        __delay_ms(1000);
         
         
       
    }
}
