/***************************************************************************
 * Lab 3 - Example code for traffic LEDs using timer0 ISR
 *         to keep track of time
 *
 *  Created: 2022-02-03
 *  Updated: 2022-02-04
 *  Author : nlantau
 **************************************************************************/

/***** Include guard ******************************************************/
#ifndef F_CPU
#define F_CPU        16000000UL
#endif /* F_CPU */

#define SERIAL_COMMUNICATION 0

/***** Include section ****************************************************/
#if SERIAL_COMMUNICATION == 1
#include "lib/serial.h"
#endif /* SERIAL_COMMUNICATION */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>

/***** Macro Definitions **************************************************/
#define BIT(x)       (1 << (x))
#define LEDOFF(p, m) ((p) &= ~(m))
#define LEDON(p, m)  ((p) |= (m))

#define RED_START  1

#define GREEN        PIND3
#define YELLOW       PIND4
#define RED          PIND5

#define TIME0        0
#define TIME1        400
#define TIME2        600
#define TIME3        1200
#define TIME4        1400
#define TIME5        1403
#define TIME6        1700

/***** Function prototypes ************************************************/
static void timer0_init(void);

/***** Constants **********************************************************/
static const uint16_t ONE_SEC = 7500;
static const uint8_t TRUE = 1;

/***** Variables **********************************************************/
static volatile uint16_t overflow_count = 0;
static volatile uint8_t seconds = 0;
static volatile uint8_t mins = 0;
static volatile uint8_t minutes = 0;

/***** MAIN ***************************************************************/
int main(void)
{
#if SERIAL_COMMUNICATION == 1

	serial_init(E_BAUD_9600);
	serial_install_interrupts(E_FLAGS_SERIAL_RX_INTERRUPT);
	serial_flush();

#endif /* SERIAL_COMMUNICATION */

	timer0_init();
	sei();

	/* Set Data Direction on LED pins */
	DDRD |= (1 << GREEN) | (1 << YELLOW) | (1 << RED);


	while (TRUE) {

#if RED_START == 1

		switch(seconds) {
			case 0 ... 1:
				LEDOFF(PORTD, BIT(GREEN));
				LEDOFF(PORTD, BIT(YELLOW));
				LEDON(PORTD, BIT(RED));
				break;
			case 2 ... 3:
				LEDOFF(PORTD, BIT(GREEN));
				LEDON(PORTD, BIT(YELLOW));
				LEDON(PORTD, BIT(RED));
				break;
			case 4 ... 6:
				LEDON(PORTD, BIT(GREEN));
				LEDOFF(PORTD, BIT(YELLOW));
				LEDOFF(PORTD, BIT(RED));
				break;
			case 7 ... 8:
				LEDOFF(PORTD, BIT(GREEN));
				LEDON(PORTD, BIT(YELLOW));
				LEDOFF(PORTD, BIT(RED));
				break;
			case 11 ... 12:
				LEDON(PORTD, BIT(GREEN));
				LEDOFF(PORTD, BIT(YELLOW));
				LEDOFF(PORTD, BIT(RED));
				seconds = 0;
				break;
		}

#endif /* RED_START */

	}
	return 0;

} /* End main() */


/***** TIMER **************************************************************/
static void timer0_init(void)
{
	/* Timer Overflow Interrupt Enable  */
	TIMSK0 |= (1 << TOIE0);

	/* Timer Overflow Flag */
	TIFR0 |= (1 << TOV0);

	/* 1024 prescaler */
	TCCR0B |= (1 << CS01);

} /* End timer0_init() */


ISR(TIMER0_OVF_vect)
{
	overflow_count++;
	if (overflow_count == ONE_SEC) {
		seconds++;
		overflow_count = 0;
		if (seconds == 100) {
			seconds = 0;
			mins++;
		}
		if (mins == 60) {
			mins = 0;
			minutes++;
		}
	}

} /* End ISR() */

