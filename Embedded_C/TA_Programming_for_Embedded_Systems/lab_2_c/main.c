/***************************************************************************
 * Lab 2 - Timers and Counter
 *
 * Modified to use 5 IR-sensors that toggle 5 LEDs if value of 
 * IR-sensor is greater than a threshold. Play time with my son.
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
#include "lib/adc.h"
#include "lib/uart.h"
#include "lib/utils.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

/***** Macro Definitions **************************************************/
#define LAB2 0
#define PLAYTIME 1

/***** Function prototypes ************************************************/
void timer0_init(void);
void led_init(void);
void led_toggle(void);

/***** Constants **********************************************************/
static const uint16_t ONE_SEC = 7500;
static const uint8_t THRESHOLD = 200;

/***** Variables **********************************************************/
/* Since overflow_count is 16 bit, perhaps an atomic block is in order? */
static volatile uint16_t overflow_count = 0;


/***** MAIN ***************************************************************/
int main(void)
{
#if PLAYTIME
	uint8_t i, j, adc_ports[5] = {0x00, 0x01, 0x02, 0x03, 0x04};
	uint16_t adc_value[5] = {0};
	adc_init();
#endif /* PLAYTIME */

	stdout_init();
	uart_init();
	led_init();
#if LAB2
	timer0_init();
	sei();
	printf("Start\n");
#endif /* LAB2 */

	for (;;) {
		/* Fun test
		 * Use asm
		 * loop:
		 * rjump loop
		 *
		 */
		asm volatile ("nop");
		__no_operation();
#if PLAYTIME
		/* IR-array is connected (HW) in the opposite order
		 * of the LEDs, hence the need for incrementing 
		 * and decrementing variables
		 */
		for (i = 0, j = 6; i < 5; ++i, --j) {
			adc_read_to_array(adc_ports[i], adc_value);
			if (adc_value[i] > THRESHOLD) {
				PORTD ^= (1 << j);
			}
			_delay_ms(5);
		}

#endif /* PLAYTIME */
	}

	return 0;

} /* End main() */


void led_init(void)
{
	DDRD |= (1 << PIND2) | (1 << PIND3) | (1 << PIND4) | (1 << PIND5) | (1 << PIND6);
	PORTD &= ~((1 << PIND2) | (1 << PIND3) | (1 << PIND4) | (1 << PIND5) | (1 << PIND6));


} /* End led_init() */

void led_toggle(void)
{
#if LAB2
	int i;
	printf("> Toggling LED: %s\n", PINB & (1 << PINB1) ? "Off" : "On");
	for (i = 0; i < 40; ++i) {
		printf("%c", uart_getc());
	}
	printf("\n");
#endif
	PORTD ^= (1 << PIND2) | (1 << PIND3) | (1 << PIND4) | (1 << PIND5) | (1 << PIND6);

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

