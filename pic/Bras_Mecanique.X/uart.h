#ifndef UART_H
#define	UART_H


#define UART1_BAUDRATE 57600
#define UART_SIZE_BUFF 50


void Init_Uart1(void);
void Transmit_String(char *str);

uint8_t Get_Uart(char *c);


#endif	/* UART_H */

