/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

/* Device header file */
#if defined(__XC16__)
    #include <xc.h>
#elif defined(__C30__)
    #if defined(__dsPIC30F__)
        #include <p30Fxxxx.h>
    #endif
#endif

#include <stdint.h>          /* For uint32_t definition                       */
#include <stdbool.h>         /* For true/false definition                     */

#include "user.h"            /* variables/params used by user.c               */

/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

/* <Initialize variables in user.h and insert code for user algorithms.> */

/* TODO Initialize User Ports/Peripherals/Project here */

void InitApp(void)
{
    /* Setup analog functionality and port direction */
    TRISFbits.TRISF6 = 0;
    LATFbits.LATF6 = 0;
    
    PTCONbits.PTEN = 1;
    PTPER = 1000;
    
    PWMCON1 = 0;
    PWMCON1bits.PEN1H = 1;
    
    PDC1 = 500;
    TRISBbits.TRISB6 = 0;
    direction1 = 1;
    
    /* Initialize peripherals */
}

void delay (long repeats)
{
    long i=0;
    while (i<repeats)
    {i++;}
}