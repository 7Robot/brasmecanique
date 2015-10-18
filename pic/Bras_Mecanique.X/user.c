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
#include "uart.h"

/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

/* <Initialize variables in user.h and insert code for user algorithms.> */

/* TODO Initialize User Ports/Peripherals/Project here */

void InitApp(void)
{
    /* Setup analog functionality and port direction */
   
    //setup LED pin
    TRISFbits.TRISF6 = 0;
    LATFbits.LATF6 = 0;
    
    //Configuring PWM timer period
    PTCONbits.PTEN = 1;//enable PWM timer
    PTPER = 1000;// set PWM perion
    
    PWMCON1 = 0;//deattaching all PWM pins from timer
    PWMCON1bits.PEN1H = 1;// attach PWM1 to timer
    PWMCON1bits.PEN2H = 1;// attach PWM2 to timer
    PWMCON1bits.PEN3H = 1;// attach PWM3 to timer
    //TODO configure PWMs 4,5,6
    
    PDC1 = 500;
    
    // configure direction pins as OUTPUTS
    directionPin1mode = 0;
    directionPin2mode = 0;
    directionPin3mode = 0;
    directionPin4mode = 0;
    directionPin5mode = 0;
    directionPin6mode = 0;
    
    
    //set all direction pins LOW
    directionPin1 = 0;
    directionPin2 = 0;
    directionPin3 = 0;
    directionPin4 = 0;
    directionPin5 = 0;
    directionPin6 = 0;
    
    //set courseEndPin as INPUT
    courseEndPinMode = 1;
    
    //set thermal protection pin as input 
    thermalPinMode = 1;
    
    
    Init_Uart1();
    /* Initialize peripherals */
}

void Delay (uint32_t repeats)
{
    uint32_t i=0;
    while (i<repeats)
    {i++;}
}

long map(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

// runs motor on port(1-6) with speed from -100 to 100)
void runMotor(int port, int speed)
{
    
    int PWMtime = abs (speed);
    switch (port)
    {
            case 1:
            
            break;
                
            case 2:
            
            break;  
            
            case 3:
            
            break; 
            
            case 4:
            
            break;
                
            case 5:
            
            break;  
            
            case 6:
            
            break;              
    }           
}