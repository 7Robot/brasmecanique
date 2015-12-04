/* 
 * File:   comm.h
 * Author: ster
 *
 * Created on 21 ??????? 2015 ?., 20:03
 */

#include <stdint.h>          /* For uint32_t definition                       */
#include <stdbool.h>         /* For true/false definition                     */
#include <stdlib.h>

#include "system.h" 
#include <libpic30.h>       //_delay_ms and other stuff

extern char buffer[30];
extern volatile int pot[];
#ifndef COMM_H
#define	COMM_H

#ifdef	__cplusplus
extern "C" {
#endif

void receiveCommand(void);
void analyzeCommand(void);
void sendCurrentAngles(void);

#ifdef	__cplusplus
}
#endif

#endif	/* COMM_H */


