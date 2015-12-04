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

#include "system.h" 
#include <libpic30.h>       //_delay_ms and other stuff

#include "user.h"            /* variables/params used by user.c               */
#include "uart.h"


/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

/* <Initialize variables in user.h and insert code for user algorithms.> */
extern volatile int pot[];
int pot0max = 800;
int pot0min = 200;
int pot0center = 500;

int actualAngle [5];
int potMin [5];
int potMax [5];

int servoAngle[5];

int pot1max = 350;
int pot1min = 250;

extern char buffer[];

void InitApp(void) {
    /* Setup analog functionality and port direction */

    //setup LED pin
    TRISFbits.TRISF6 = 0;
    LATFbits.LATF6 = 0;

    //Configuring PWM timer period
    PTCONbits.PTEN = 1; //enable PWM timer
    PTPER = 1000; // set PWM period

    PWMCON1 = 0; //deattaching all PWM pins from timer
        PWMCON1bits.PEN1H = 1; // attach PWM1 to timer
        PWMCON1bits.PEN2H = 1; // attach PWM2 to timer
        PWMCON1bits.PEN3H = 1; // attach PWM3 to timer
    //TODO configure PWMs 4,5,6
    PDC1 = 0;
    PDC2 = 0;
    PDC3 = 0;




    // configure direction pins as OUTPUTS
    directionPin0mode = 0;
    directionPin1mode = 0;
    directionPin2mode = 0;
    directionPin3mode = 0;
    directionPin4mode = 0;
    directionPin5mode = 0;



    //set all direction pins LOW
    directionPin0 = 0;
    directionPin1 = 0;
    directionPin2 = 0;
    directionPin3 = 0;
    directionPin4 = 0;
    directionPin5 = 0;


    //set courseEndPin as INPUT
    courseEndPinMode = 1;

    //set thermal protection pin as input 
    thermalPinMode = 1;

    // set TRIS bits ports to be INPUTS
    potPin0mode = 1;
    potPin1mode = 1;
    potPin2mode = 1;
    potPin3mode = 1;
    potPin4mode = 1;


    //----------ANALOG INPUTS CONFIGURATION-------------
    /* OLD
    
     //Ports configuration
     ADPCFG = 0b111111111100000; //configure AN0-AN5 as analog inputs
     ADCON2bits.VCFG = 0b000; // Voltage reference is AVdd-AVss
     ADCON3bits.ADRC = 0; // Clock derived from system clock
     ADCON3bits.ADCS = 0b111111; //A/D conversion clock = 32xTCY
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
     ADCON3bits.SAMC = 0b10100; //??? Auto-Sample time = 20TAD
     ADCON1bits.FORM = 0b00; //Output format is integer (DOUT = 0000 00dd dddd dddd)
     ADCON1bits.ADSIDL = 0; // Continue module operation in Idle mode

     ADCON1bits.ADON = 0; // A/D converter module is operating/off
     //!!!! this is another BIG SWITCH */

    //NEW 
    ADPCFG = 0b111111111100000; //configure AN0-AN5 as analog inputs
    ADCON2bits.VCFG = 0b000; // Voltage reference is AVdd-AVss
    ADCON3bits.ADRC = 0; // Clock derived from system clock
    // according to datasheet 17.1, this now have no effect
    ADCON3bits.ADCS = 0b111111; //A/D conversion clock = 32xTCY
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
    ADCON3bits.SAMC = 0b10101; //??? Auto-Sample time = MAX
    ADCON1bits.FORM = 0b00; //Output format is integer (DOUT = 0000 00dd dddd dddd)
    ADCON1bits.ADSIDL = 0; // Continue module operation in Idle mode

    ADCON1bits.ADON = 1; // A/D converter module is operating/off
    //!!!! this is another BIG SWITCH

    //--------------TIMERS CONFIGURATION-----------
    //-----------------Timer1----------------------
    T1CONbits.TCS = 0; //Timer Clock Source Select - Internal clock (FOSC/4)
    T1CONbits.TCKPS = 0b11; //Timer Input Clock Prescale (1/8/64/256) = 1:256
    T1CONbits.TSIDL = 0; //Continue timer operation in Idle mode
    T1CONbits.TON = 1; //start the timer
    _T1IE = 1; // enable the interrupt
    _T1IP = 5; //interrupt priority
    PR1 = 100; // timer 1 period
    LED = 0;



    Init_Uart1();
    /* Initialize peripherals */

    //default range, will be rewritten if calibration function is called
    potMin[0] = 136;
    potMax[0] = 699;

    potMin[1] = 225; //highest position]
    potMax[1] = 387; // lowest position

    potMin[2] = 563; //highest position]
    potMax[2] = 379; // lowest position

    servoAngle[0] = 180;
    servoAngle[1] = 45;
    servoAngle[2] = 45;
    
    initialScanPots();
}

int analogRead(int port) {
    int value;
    int tempValue[3];
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
    int i;
    for (i = 0; i < 4; i++) { // filtration 
        ADCON1bits.SAMP = 1; // start sampling  
        // ???converting should start automatically after sampling ends as set in ADCON1bits.SSRC???
        // ??? is ADCON1bits.DONE set to zero as SAMPLING begins ?
        while (!ADCON1bits.DONE); // infinite loop that ends only when A/D conv is done    
        tempValue[i] = ADCBUF0;
    }
    value = max3(tempValue[0], tempValue[1], tempValue[2]);
    return value;


}

int max3(int v0, int v1, int v2) {
    int max1;
    if (v0 > v1)
        max1 = v0;
    else
        max1 = v1;

    if (max1 > v2)
        return max1;
    else
        return v2;
}

void Delay(uint32_t repeats) {
    uint32_t i = 0;
    while (i < repeats) {
        i++;
    }
}

int oldPot[5];

void initialScanPots (void){
    int i = 0;
    for (i = 0; i < 5; i++) {
        oldPot[i] = analogRead(i);
       }
}

void scanPots(void) {
    int i = 0;
    for (i = 0; i < 5; i++) {
        pot[i] = analogRead(i);
        if (abs(pot[i]-oldPot[i]>10)) pot[i] = oldPot[i]; //additional filtering - if reading looks  strange (changed too fast), ignore it 
        if (i == 0) actualAngle[i] = map(pot[i], potMin[i], potMax[i], 0, 359);
        if (i == 1) actualAngle[i] = map(pot[i], potMin[i], potMax[i], 90, 0);
        if (i == 2) actualAngle[i] = map(pot[i], potMin[i], potMax[i], 90, 0);
        //         if (i==0)       actualAngle[i] = map(pot[i], potMin[i], potMax[i], 0, 359);
        //         if (i==0)       actualAngle[i] = map(pot[i], potMin[i], potMax[i], 0, 359);
        oldPot[i] = pot[i];
    }
}

long map(long x, long in_min, long in_max, long out_min, long out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

// runs motor on port(1-6) with speed from 0 to 100)

void runMotor(int port, int speed, bool direction) {

    int PWMvalue = map(speed, 0, 100, 0, 2000);
    switch (port) {

        case 0:
            if (speed == 0) {
                PDC1 = 0;
                PWMCON1bits.PEN1H = 0;
                TRISEbits.TRISE1 = 0;
                LATEbits.LATE1 = 0;
            } else {
                PWMCON1bits.PEN1H = 1;
                PDC1 = PWMvalue;
                directionPin0 = direction;
            }
            break;

        case 1:
            if (speed == 0) {
                PDC2 = 0;
                PWMCON1bits.PEN2H = 0;
                TRISEbits.TRISE3 = 0;
                LATEbits.LATE3 = 0;
            } else {
                PWMCON1bits.PEN2H = 1;
                PDC2 = PWMvalue;
                directionPin1 = direction;
            }
            break;

        case 2:
            if (speed == 0) {
                PDC3 = 0;
                PWMCON1bits.PEN3H = 0;
                TRISEbits.TRISE5 = 0;
                LATEbits.LATE5 = 0;
            } else {
                PWMCON1bits.PEN3H = 1;
                PDC3 = PWMvalue;
                directionPin2 = !direction;
            }
            break;

        case 3:

            break;

        case 4:

            break;

        case 5:

            break;


    }
}

void __attribute__((interrupt, auto_psv)) _T1Interrupt(void) {

    LED = !LED;
    // servo run routine
    scanPots();
    setServo(0, servoAngle[0]);
    setServo(1, servoAngle[1]);
    setServo(2, servoAngle[2]);



    _T1IF = 0; // clear the interrupt flag

}

/*********************************************************************
 * Function:        void calibrate (int axis)
 *
 * PreCondition:    None
 *
 * Input:           desired axis to calibrate
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        reads extreme values of the pots and set them to global array
 *
 * Note:            None
 ********************************************************************/
void calibrate(int axis) {
    _T1IE = 0; //disable timer interrupt
    int tempCenter = analogRead(axis);
    int speed = 80;

    __delay_ms(1000);
    if (courseEndPin != 0) { // if robot is turned on with at least one axis in limit position, skip the calibration and use default values
        switch (axis) {
            case 0:
                while (courseEndPin == 1) { //go CCW until course end
                    runMotor(0, speed, CCW);
                }
                potMin[0] = analogRead(0); // save value as minimum
                // go to initial center
                while (analogRead(0) < tempCenter) {
                    runMotor(0, speed, CW);
                }
                // go CW until course end
                while (courseEndPin == 1) { //go CCW until course end
                    runMotor(0, speed, CW);
                }
                // save value as max
                potMax[0] = analogRead(0);
                // calculate real center
                pot0center = (potMin[0] + potMax[0]) / 2;
                //go to real center
                while (analogRead(0) > pot0center) {
                    runMotor(0, speed, CCW);
                }
                // stop the motor when reached real center
                runMotor(0, 0, CCW);
                servoAngle[0] = 180;
                break;

            case 1:
                while (courseEndPin == 1) { //go CCW until course end
                    runMotor(1, speed, UP);
                }
                potMin[1] = analogRead(1); // save value as max
                // go to initial position
                while (analogRead(1) < tempCenter) {
                    runMotor(1, speed, DOWN);
                }
                // go down until course end
                while (courseEndPin == 1) { //go down until course end
                    runMotor(1, speed, DOWN);
                }
                // save value as max
                potMax[1] = analogRead(1);
                // calculate real center
                pot0center = (potMin[1] + potMax[1]) / 2;
                //go to real center
                while (analogRead(1) > pot0center) {
                    runMotor(1, speed, UP);
                }
                // stop the motor when reached real center
                runMotor(1, 0, CCW);
                servoAngle[1] = 45;
                break;


            case 2:

                while (courseEndPin == 1) { //go CCW until course end
                    runMotor(2, speed, UP);
                }
                potMin[2] = analogRead(1); // save value as max
                // go to initial position
                while (analogRead(2) < tempCenter) {
                    runMotor(2, speed, DOWN);
                }
                // go down until course end
                while (courseEndPin == 1) { //go down until course end
                    runMotor(2, speed, DOWN);
                }
                // save value as max
                potMax[2] = analogRead(2);
                // calculate real center
                pot0center = (potMin[2] + potMax[2]) / 2;
                //go to real center
                while (analogRead(2) > pot0center) {
                    runMotor(2, speed, UP);
                }
                // stop the motor when reached real center
                runMotor(2, 0, CCW);
                servoAngle[2] = 45;
                break;

            case 3:

                break;

            case 4:

                break;

            case 5:

                break;

        }
    }
    _T1IE = 1; //enable timer interrupt
}

void setServo(int axis, int angle) {
    long speed = 0;
    int diff;
    switch (axis) {
        case 0:
            diff = actualAngle[axis] - angle;

            if (diff > 3) {

                speed = abs(diff)*3;
                if (speed > 100) speed = 100;
                runMotor(axis, speed, CCW);
            } else if (diff<-3) {
                speed = abs(diff)*3;
                ;
                if (speed > 100) speed = 100;
                runMotor(axis, speed, CW);
            } else runMotor(axis, 0, CW);

            break;



        case 1:

            diff = actualAngle[axis] - angle;

            if (diff > 3) {
                speed = (abs(diff)*3)-11;
                if (speed > 100) speed = 100;
                runMotor(axis, speed, DOWN);
            } else if (diff<-3) {
                speed = (abs(diff)*3)-11;
                ;
                if (speed > 100) speed = 100;
                runMotor(axis, speed, UP);
            } else runMotor(axis, 0, UP);
            break;

        case 2:
            diff = actualAngle[axis] - angle;

            if (diff > 3) {
                speed = (abs(diff)*3)-11;
                if (speed > 100) speed = 100;
                runMotor(axis, speed, DOWN);
            } else if (diff<-3) {
                speed = (abs(diff)*3)-11;
                ;
                if (speed > 100) speed = 100;
                runMotor(axis, speed, UP);
            } else runMotor(axis, 0, UP);
            break;

        case 3:

            break;

        case 4:

            break;

        case 5:

            break;


    }
}