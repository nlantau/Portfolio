/***************************************************************************
 *  Ultrasonice Header
 *
 *
 *	Created: 2020-09-21
 *  Updated: 2020-10-06
 *  Author: nlantau
 **************************************************************************/

/***** Include guard ******************************************************/

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_
#ifndef F_CPU
#define F_CPU 16000000UL
#endif

/***** Include section ****************************************************/
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/sfr_defs.h>
#include <stdlib.h>
#include <stdio.h>

/***** Macro Definitions **************************************************/

#define echoPin PIND2
#define trigPin PIND3

/***** Global Variables ***************************************************/

volatile float result;
volatile int stop;

/***** Function prototypes ************************************************/

void ultrasonic_initTrigEcho(void);
void ultrasonic_initINT0(void);
void ultrasonic_initTimer2(void);
void ultrasonic_sendTrigPulse(void);

#endif /* ULTRASONIC_H_ */

/*** end of file ***/