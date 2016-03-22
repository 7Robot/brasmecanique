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

int c1, c2, c3, c4, c5 = 0;

int cupAmmount = 16; // total ammount of cups on the plate +1 for waiting position
int clicksPerML = 4; //flow sensor clicks per 1 ml
int volumeToFill = 50; // required volume of beer for each cup

char buffer[30];
int coordMassivePointer = 0;

extern int cupXposition [];
extern int cupYposition [];
extern int cupZposition [];
extern int cupHeadposition [];

/******************************************************************************/
/* Main Program                                                               */

/******************************************************************************/


int16_t main(void) {

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
    Transmit_String("\r\n");

    manualCalibration();
    __delay_ms(100);

    _T1IE = 1; //enable T1 interrupt, i.e. start servoing




    //main cycle
    while (1) {
        //        PDC1 = 0;
        //receiveCommand();

        //go to the waiting position
        servoAngle[0] = cupXposition[cupAmmount - 1]; //-1 because array starts from 0
        servoAngle[1] = cupYposition[cupAmmount - 1];
        servoAngle[2] = cupZposition[cupAmmount - 1];
        servoAngle[4] = cupHeadposition[cupAmmount - 1];

        while (button1 == 1) { //button1 logic is reversed, i.e. there is voltage while it's not pressed
            // wait for the button
        }

        //start filling process
        int currentCup;
        for (currentCup = 0; currentCup < cupAmmount - 1; currentCup++) {
            servoAngle[0] = cupXposition[currentCup];
            servoAngle[1] = cupYposition[currentCup] - 40;
            servoAngle[2] = cupZposition[currentCup] + 20;
            servoAngle[4] = cupHeadposition[currentCup];
            __delay_ms(200);

            servoAngle[1] = cupYposition[currentCup];
            servoAngle[2] = cupZposition[currentCup];
            __delay_ms(500);


            fillML(volumeToFill);
            __delay_ms(200);

            servoAngle[1] = cupYposition[currentCup] - 40;
            servoAngle[2] = cupZposition[currentCup] + 20;
            __delay_ms(200);

        }



    }
}
