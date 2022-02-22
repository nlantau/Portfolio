/***************************************************************************
 * Lab 2 - Timers and Counter
 *
 * Created: 2022-02-22
 * Updated: 2022-02-22
 * Author : nlantau
 **************************************************************************/

/***** Include guard ******************************************************/
#ifndef F_CPU
#define F_CPU 16000000UL
#endif /* F_CPU */

/***** Include section ****************************************************/
#include "lib/uart.h"
#include "lib/utils.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <string.h>

/***** Macro Definitions **************************************************/

/***** Function prototypes ************************************************/
void timer0_init(void);
void led_init(void);
void led_toggle(void);

/***** Constants **********************************************************/
static const uint16_t ONE_SEC = 7500;

/***** Variables **********************************************************/
static volatile uint16_t overflow_count = 0;

/***** MAIN ***************************************************************/
int main(void)
{
	led_init();
	timer0_init();
	sei();

	for (;;)
		;


	return 0;

} /* End main() */

void led_init(void)
{
	DDRB |= (1 << PINB1);
	PORTB &= ~(1 << PINB1);
} /* End led_init() */

void led_toggle(void)
{
	PORTB ^= (1 << PINB1);

} /* End led_toggle() */

void timer0_init(void)
{
    /* Timer/Counter0 Overflow Flag */
    TIFR0 |= (1 << TOV0);

    /* clk/8 prescaler */
    TCCR0B |= (1 << CS01);

    /* Timer/Counter 0 Overflow Interrupt Enable  */
    TIMSK0 |= (1 << TOIE0);

} /* End timer0_init() */

ISR(TIMER0_OVF_vect)
{

    overflow_count++;
    if (overflow_count == ONE_SEC) {
	    led_toggle();
	    overflow_count = 0;
    }

} /* End ISR() */

/* End main.c */

