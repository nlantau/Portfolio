/***************************************************************************
 *  printf() - Direct FILE uart_putchar() to printf()
 *             Something we should've been taught years ago...
 *
 *  Created: 2022-02-18
 *  Updated: 2022-02-18
 *  Author : nlantau
 **************************************************************************/

/***** Include section ****************************************************/

#include <stdio.h>
#include <avr/io.h>

/***** Macro Definitions **************************************************/
#ifndef F_CPU
#define F_CPU        16000000UL
#endif /* F_CPU */

#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1

#define sbi(var, mask) ((var) |= (uint8_t)(1 << mask))
#define cbi(var, mask) ((var) &= (uint8_t)~(1 << mask))

/***** Function prototypes ************************************************/
void ioinit(void);
void delay_ms(uint16_t x);
static int uart_putchar(char c, FILE *stream);
static FILE mystdout = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);

/***** Constants **********************************************************/

/***** Variables **********************************************************/

/***** MAIN ***************************************************************/
int main(void)
{
	uint8_t x = 0;
	ioinit();

	for (;;) {
		x++;
		printf("Testing: x = %d\n", x);
		delay_ms(500);
	}

	return 0;

} /* End main() */


/***** UART ***************************************************************/
void ioinit(void)
{
	UBRR0H = MYUBRR >> 8;
	UBRR0L = MYUBRR;
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);

	stdout = &mystdout;

} /* End ioinit() */

static int uart_putchar(char c, FILE *stream)
{
	if (c == '\n') uart_putchar('\r', stream);

	//while (!(UCSR0A & (1 << UDRE0))) ;
	loop_until_bit_is_set(UCSR0A, UDRE0);
	UDR0 = c;

	return 0;

} /* End uart_putchar() */

/***** DELAY **************************************************************/
void delay_ms(uint16_t x)
{
	uint8_t y, z;
	for ( ; x > 0; x--) 
		for (y = 0; y < 80; y++) 
			for (z = 0; z < 40; z++) 
				asm volatile ("nop");

} /* End delay_ms() */

/* End main.c */

