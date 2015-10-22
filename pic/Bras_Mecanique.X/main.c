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
int c1, c2, c3, c4, c5 = 0;

char buffer[30];
int coordMassivePointer = 0;

/******************************************************************************/
/* Main Program                                                               */

/******************************************************************************/

int16_t main(void) {

    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize IO ports and peripherals */
    InitApp();
    // Init_Uart1();

    //main cycle 
    while (1) {

        PDC1 = 0;
        receiveCommand();
}
}
// char *itoa(char *buffer, int i) {
// unsigned int n;
// unsigned int negate = 0;
// int c = 6;
// 
// if (i < 0) {
// negate=1;
// n = -i;
// } else if (i == 0) {
// buffer[0] = '0';
// buffer[1] = 0;
// return buffer;
// } else {
// n = i;
// }
// buffer[c--] = 0;
// do {
// buffer[c--] = (n % 10) + '0';
// n = n / 10;
// } while (n);
// if (negate) {
// buffer[c--] = '-';
// }
// return &buffer[c+1];
// }