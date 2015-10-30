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
#include <stdlib.h>

#include "user.h"            /* variables/params used by user.c               */
#include "uart.h"


/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

/* <Initialize variables in user.h and insert code for user algorithms.> */
extern volatile int pot[];


void InitApp(void) {
    /* Setup analog functionality and port direction */

    //setup LED pin
    TRISFbits.TRISF6 = 0;
    LATFbits.LATF6 = 0;

    //Configuring PWM timer period
    PTCONbits.PTEN = 1; //enable PWM timer
    PTPER = 1000; // set PWM perion

    PWMCON1 = 0; //deattaching all PWM pins from timer
    PWMCON1bits.PEN1H = 1; // attach PWM1 to timer
    PWMCON1bits.PEN2H = 1; // attach PWM2 to timer
    PWMCON1bits.PEN3H = 1; // attach PWM3 to timer
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

    // set TRIS bits ports to be INPUTS
    potPin1mode = 1;
    potPin2mode = 1;
    potPin3mode = 1;
    potPin4mode = 1;
    potPin5mode = 1;

    //----------ANALOG INPUTS CONFIGURATION-------------
    //Ports configuration
    ADPCFG = 0b111111111100000; //configure AN0-AN5 as analog inputs
    ADCON2bits.VCFG = 0b000; // Voltage reference is AVdd-AVss
    ADCON3bits.ADRC = 0; // Clock derived from system clock
    ADCON3bits.ADCS = 0b000011; //A/D conversion clock = 4xTCY
    ADCON2bits.CHPS = 0b00; //using only one channel
    ADCON1bits.SIMSAM = 0; //multiple channels sampled sequentially
    ADCSSL = 0b0000000000000000; //A/D Input Pin Scan Selection - no scan, manual reading
    ADCHSbits.CH0SA = 0b0000; //Channel 0 positive input is AN0       
    ADCHSbits.CH0NA = 0b0; //Channel 0 negative input is VREF-     
    ADCON1bits.SSRC = 0b111; // Conversion Trigger Source - Internal counter ends sampling and starts conversion (auto convert)
    ADCON1bits.ASAM = 0; //Sampling begins when SAMP bit set
    ADCON1bits.SAMP = 0; //A/D sample/hold amplifiers are holding
    //!!!! writing 1 to this bit will start sampling
    //ADCONbits.DONE - A/D Conversion Status bit Cleared by software or start of a new conversion
    ADCON3bits.SAMC = 0b00001; //??? Auto-Sample time = 1TAD
    ADCON1bits.FORM = 0b00; //Output format is integer (DOUT = 0000 00dd dddd dddd)
    ADCON1bits.ADSIDL = 0; // Continue module operation in Idle mode

    ADCON1bits.ADON = 0; // A/D converter module is operating/off
    //!!!! this is another BIG SWITCH


    Init_Uart1();
    /* Initialize peripherals */
}



int analogRead(int port) {
    int value;

    switch (port) {
        case 0:
            ADCHSbits.CH0SA = 0x0; //Channel 0 positive input is AN0  
            break;

        case 1:
            ADCHSbits.CH0SA = 0x1; //Channel 0 positive input is AN1  
            break;

        case 2:
            ADCHSbits.CH0SA = 0x2; //Channel 0 positive input is AN2  
            break;

        case 3:
            ADCHSbits.CH0SA = 0x3; //Channel 0 positive input is AN3  
            break;

        case 4:
            ADCHSbits.CH0SA = 0x4; //Channel 0 positive input is AN4  
            break;

    }

    ADCON1bits.SAMP = 1; // start sampling  
    // ???converting should start automatically after sampling ends as set in ADCON1bits.SSRC???
    // ??? is ADCON1bits.DONE set to zero as SAMPLING begins ?
    while (!ADCON1bits.DONE); // infinite loop that ends only when A/D conv is done    
    value = ADCBUF0;
    return value;


}

void Delay(uint32_t repeats) {
    uint32_t i = 0;
    while (i < repeats) {
        i++;
    }
}

void scanPots(void)

{
    int i = 0;
        for (i = 0; i < 5; i++)
        {
            pot[i] = analogRead(i);
        }
}

long map(long x, long in_min, long in_max, long out_min, long out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

// runs motor on port(1-6) with speed from -100 to 100)

void runMotor(int port, int speed) {

    int PWMtime = abs(speed);
    switch (port) {
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