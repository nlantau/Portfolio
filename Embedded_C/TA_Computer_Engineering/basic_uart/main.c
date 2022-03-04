/***************************************************************************
 * Basic UART RX & TX
 *
 * Created: 2022-03-03
 * Updated: 2022-03-03
 * Author : nlantau
 **************************************************************************/

/***** Include guard ******************************************************/
#define F_CPU 16000000UL

/***** Include section ****************************************************/
#include <avr/io.h>
#include <util/delay.h>

/***** Macro Definitions **************************************************/
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1

/***** Function prototypes ************************************************/
void uart_init(void);
uint8_t uart_getc(void);
void uart_putc(uint8_t data);
void uart_puts(const char *s);

/***** Constants **********************************************************/

/***** Variables **********************************************************/

/***** MAIN ***************************************************************/
int main(void)
{
    uart_init();

    for (;;) {
        uart_puts("Testing\n");
        _delay_ms(500);
    }

    return 0;

} /* End main() */

void uart_init(void)
{
	/* Sets BAUD to 9600 */
	UBRR0H = MYUBRR >> 8;
	UBRR0L = MYUBRR;

	/* Enable RX and TX */
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);

} /* End uart_init() */

uint8_t uart_getc(void)
{
	loop_until_bit_is_set(UCSR0A, RXC0);
	return UDR0;

} /* End uart_getc() */

void uart_putc(uint8_t data)
{
	loop_until_bit_is_set(UCSR0A, UDRE0);
	UDR0 = data;
} /* uart_putc() */

void uart_puts(const char *s)
{
	while (*s) uart_putc(*s++);

} /* End uart_puts */

/* End main.c */

