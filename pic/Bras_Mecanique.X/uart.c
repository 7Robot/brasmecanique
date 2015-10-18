


#include <xc.h>

#include <stdint.h>        /* Includes uint16_t definition                    */
#include <stdbool.h>       /* Includes true/false definition                  */

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp              */





volatile char TX_Buff[UART_SIZE_BUFF] = {'f'};
volatile u16  i_TX_Buff = 1;

volatile char RX_Buff[UART_SIZE_BUFF];
volatile u16 i_RX_Buff = 0;


void Init_Uart1(void)
{
    u32 val32 = FCY;
    U1MODEbits.ALTIO = 1;       // utilisation des pina alternatives de l'uart 1
    U1STAbits.UTXISEL = 0;      // mode d'interuption de transmit
                                // interrupt receive à chaque caractère
    // calcul de la valeur à mettre dans le BaudRate Generator
    // formule : BRG = (FCY/(16*Baudrate))-1
    // petit passage en * 10 pour gestion de l'arondi

    val32 = (val32*10)/16;
    val32 = val32 / UART1_BAUDRATE;
    if ((val32 %10) >= 5)
        val32 = val32 + (10 - (val32 % 10));
    else
        val32 = val32 - (val32 % 10);

    val32 = (val32 / 10) - 1;

    U1BRG = val32;

    IFS0bits.U1RXIF = 0;    // clear les flags
    IFS0bits.U1TXIF = 0;

    IPC2bits.U1RXIP = 7;    // faut réagir dès que l'on a reçu un truc
    IPC2bits.U1TXIP = 2;    // mais on peut attendre un peu avant la prochaine transmission

    U1MODEbits.UARTEN = 1;
    U1STAbits.UTXEN = 1;        // allow transmit
    IEC0bits.U1RXIE = 1;
    IEC0bits.U1TXIE = 1;

    Delay(10);

    U1TXREG = 's';
    

    
}

void __attribute__((interrupt,auto_psv)) _U1TXInterrupt(void)
{
    static u16 i_TX_Transmit = 0;

    IFS0bits.U1TXIF = 0;
    U1TXREG = TX_Buff[i_TX_Transmit];
    i_TX_Transmit ++;
    if (i_TX_Transmit == UART_SIZE_BUFF)
        i_TX_Transmit = 0;
    
    if (i_TX_Transmit == i_TX_Buff)     // si on a tout transmit, on s'arrete
        IEC0bits.U1TXIE = 0;

}

void __attribute__((interrupt,auto_psv)) _U1RXInterrupt(void)
{
    RX_Buff[i_RX_Buff] = U1RXREG;
    i_RX_Buff++;
    if (i_RX_Buff == UART_SIZE_BUFF)
        i_RX_Buff = 0;
    IFS0bits.U1RXIF = 0;
}


void Transmit_String(char *str)
{
    u16 i = i_TX_Buff;
    char c;
    c = *str;

    while (c != 0)
    {
        TX_Buff[i] = c;
        i++;
        if (i == UART_SIZE_BUFF)
            i = 0;
        str++;
        c = *str;
    }
    i_TX_Buff = i;
    IEC0bits.U1TXIE = 1;
}

u8 Get_Uart(char *c)
{
    static u16 i_RX = 0;

    if (i_RX != i_RX_Buff) { // si il y a qq chose dans le buffer
        *c = RX_Buff[i_RX];
        i_RX ++;
        if (i_RX == UART_SIZE_BUFF)
            i_RX = 0;
        return 1;
    }
    else {
        return 0;
    }
}

