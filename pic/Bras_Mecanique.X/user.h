/******************************************************************************/
/* User Level #define Macros                                                  */
/******************************************************************************/
#define LED LATFbits.LATF6

//Direcrion pins mode
#define directionPin0mode TRISBbits.TRISB6
#define directionPin1mode TRISCbits.TRISC15
#define directionPin2mode TRISEbits.TRISE4
#define directionPin3mode TRISEbits.TRISE0
#define directionPin4mode TRISEbits.TRISE2
#define directionPin5mode TRISBbits.TRISB8

//Direcrion pins
#define directionPin0 LATBbits.LATB6
#define directionPin1 LATCbits.LATC15
#define directionPin2 LATEbits.LATE4
#define directionPin3 LATEbits.LATE0
#define directionPin4 LATEbits.LATE2
#define directionPin5 LATBbits.LATB8



//POTs pins mode 
#define potPin0mode  TRISBbits.TRISB0
#define potPin1mode  TRISBbits.TRISB1
#define potPin2mode  TRISBbits.TRISB2
#define potPin3mode  TRISBbits.TRISB3
#define potPin4mode  TRISBbits.TRISB4

//POTs pins 
#define potPin0  PORTBbits.RB0
#define potPin1  PORTBbits.RB1
#define potPin2  PORTBbits.RB2
#define potPin3  PORTBbits.RB3
#define potPin4  PORTBbits.RB4

//course end buttons mode
#define courseEndPinMode TRISEbits.TRISE8

//course end buttons
#define courseEndPin PORTEbits.RE8

//H-bridges Thermal protection pin mode
#define thermalPinMode TRISBbits.TRISB5

//H-bridges Thermal protection pin
#define thermalPin PORTBbits.RB5

// directions
#define CW 1
#define CCW 0
#define UP 0
#define DOWN 1

/* TODO Application specific user parameters used in user.c may go here */

/******************************************************************************/
/* User Function Prototypes                                                   */
/******************************************************************************/

/* TODO User level functions prototypes (i.e. InitApp) go here */

void InitApp(void); /* I/O and Peripheral Initialization */

int analogRead(int port);

void scanPots (void);

void Delay(uint32_t repeats);


long map(long x, long in_min, long in_max, long out_min, long out_max);

// runs motor on port(1-6) with speed from -100 to 100)
void runMotor(int port, int speed, bool direction);

void calibrate (int axis);