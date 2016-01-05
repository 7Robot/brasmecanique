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
extern volatile int actualAngle[];
extern volatile int servoAngle[];

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
  
//if (courseEndPin != 0) { // if robot is turned on with at least one axis in limit position, skip the calibration and use default values
//    calibrate(0);
//    calibrate(1); 
//    calibrate(2);
//   
//}
    
    servoAngle[0] = 180;
    servoAngle[1] = 0;
    servoAngle[2] = 0;
 
    while (1) {
        //        PDC1 = 0;
         receiveCommand();
         

//        servoAngle[0] = 180;
//         __delay_ms(4000);
//        servoAngle[0] = 90;
//         __delay_ms(4000);
//         servoAngle[0] = 270;
//         __delay_ms(4000);
//        setServo(0, 180);
//        __delay_ms(4000);
//        setServo(0, 160);
//        __delay_ms(4000);
//        setServo(0, 180);
//        __delay_ms(4000);
        
//Transmit_String("==================\r\n");
//     __delay_ms(10);
//        for (i = 0; i < 5; i++) {
//
//            sprintf(&buffer[0], "%d: %d, %d\r\n", i, pot[i], actualAngle[i]);
//            __delay_ms(10);
//            Transmit_String(&buffer[0]);
//            __delay_ms(20);
//        }
//
//__delay_ms(200);
       // LED = !LED;
 
    

    }
}
