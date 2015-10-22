#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "uart.h"
#include "comm.h"

extern volatile int coordinates[];

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
        coordinates[0] = atoi(&tempBuf[2]);
       //  coordinates[0] = atoi("444");
        
    }

    if (tempBuf[0] == 'y') {
        coordinates[1] = atoi(&tempBuf[2]);
    }

    if (tempBuf[0] == 'z') {
        coordinates[2] = atoi(&tempBuf[2]);
    }

    if (tempBuf[0] == 'v') {
        coordinates[3] = atoi(&tempBuf[2]);
    }

    if (tempBuf[0] == 'w') {
        coordinates[4] = atoi(&tempBuf[2]);
    }


}
