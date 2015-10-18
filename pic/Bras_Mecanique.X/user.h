/******************************************************************************/
/* User Level #define Macros                                                  */
/******************************************************************************/

/* TODO Application specific user parameters used in user.c may go here */

/******************************************************************************/
/* User Function Prototypes                                                   */
/******************************************************************************/

/* TODO User level functions prototypes (i.e. InitApp) go here */

void InitApp(void); /* I/O and Peripheral Initialization */

#define LED LATFbits.LATF6
#define direction1 LATBbits.LATB6

void Delay (uint32_t repeats);