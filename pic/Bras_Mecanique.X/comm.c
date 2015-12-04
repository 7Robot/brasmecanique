#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "uart.h"
#include "comm.h"

extern volatile int coordinates[];
extern volatile int actualAngle[];
extern volatile int servoAngle[];

char tempBuf[50];
int bufIndx = 0;
int state = 0; // 0 - waiting for $, 1 - receiving smth interesting

int temp;

void receiveCommand(void) {
    char c;
    if (Get_Uart(&c)) {
        if (c == '$' && state == 0) {//if there is a beginning of command
            state = 1; // listening interesting things
            bufIndx = 0;
        }
        else if (state == 1) {
            tempBuf[bufIndx] = c;
            bufIndx++;
            if (c == ';') {
                state = 0; //command completed
                analyzeCommand();
            }
        }
        
    }
    
}

void analyzeCommand(void) {
    int cursor = 0;

    while (tempBuf[cursor] != ';') {
        cursor++;
    }

    tempBuf[cursor] = '\0';

    if (tempBuf[0] == 'x') {
        servoAngle[0] = atoi(&tempBuf[2]); 
        
    }

    if (tempBuf[0] == 'y') {
        servoAngle[1] = atoi(&tempBuf[2]);
    }

    if (tempBuf[0] == 'z') {
        servoAngle[2] = atoi(&tempBuf[2]);
    }

    if (tempBuf[0] == 'v') {
        servoAngle[3] = atoi(&tempBuf[2]);
    }

    if (tempBuf[0] == 'w') {
        servoAngle[4] = atoi(&tempBuf[2]);
    }

sendCurrentAngles();
}

void sendCurrentAngles(void)
{
Transmit_String("pot===angle===set==\r\n");
     __delay_ms(10);
     int i;
        for (i = 0; i < 5; i++) {

            sprintf(&buffer[0], "%d: %d, %d,  %d\r\n", i, pot[i], actualAngle[i], servoAngle[i]);
            __delay_ms(2);
            Transmit_String(&buffer[0]);
            __delay_ms(2);
        }

__delay_ms(200);
    
}