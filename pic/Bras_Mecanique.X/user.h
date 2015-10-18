/******************************************************************************/
/* User Level #define Macros                                                  */
/******************************************************************************/
#define LED LATFbits.LATF6

//Direcrion pins mode
#define directionPin1mode TRISBbits.TRISB6
#define directionPin2mode TRISCbits.TRISC15
#define directionPin3mode TRISEbits.TRISE4
#define directionPin4mode TRISEbits.TRISE0
#define directionPin5mode TRISEbits.TRISE2
#define directionPin6mode TRISBbits.TRISB8

//Direcrion pins
#define directionPin1 LATBbits.LATB6
#define directionPin2 LATCbits.LATC15
#define directionPin3 LATEbits.LATE4
#define directionPin4 LATEbits.LATE0
#define directionPin5 LATEbits.LATE2
#define directionPin6 LATBbits.LATB8

//POTs pins mode 
#define potPin1mode  TRISBbits.RB0
#define potPin2mode  TRISBbits.RB1
#define potPin3mode  TRISBbits.RB2
#define potPin4mode  TRISBbits.RB3
#define potPin5mode  TRISBbits.RB4

//POTs pins 
#define potPin1  PORTBbits.RB0
#define potPin2  PORTBbits.RB1
#define potPin3  PORTBbits.RB2
#define potPin4  PORTBbits.RB3
#define potPin5  PORTBbits.RB4

//course end buttons mode
#define courseEndPinMode TRISEbits.TRISE8

//course end buttons
#define courseEndPin PORTEbits.RE8

//H-bridges Thermal protection pin mode
#define thermalPinMode TRISBbits.TRISB5

//H-bridges Thermal protection pin
#define thermalPin PORTBbits.RB5


/* TODO Application specific user parameters used in user.c may go here */

/******************************************************************************/
/* User Function Prototypes                                                   */
/******************************************************************************/

/* TODO User level functions prototypes (i.e. InitApp) go here */

void InitApp(void); /* I/O and Peripheral Initialization */




long map(long x, long in_min, long in_max, long out_min, long out_max);

// runs motor on port(1-6) with speed from -100 to 100)
void runMotor(int port, int speed);
