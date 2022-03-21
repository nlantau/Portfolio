/***************************************************************************
 * Basic UART RX & TX
 *
 * Created: 2022-03-03
 * Updated: 2022-03-03
 * Author : nlantau
 **************************************************************************/

/***** Include guard ******************************************************/

/***** Include section ****************************************************/
#include <avr/io.h>
#include <util/delay.h>

/***** Macro Definitions **************************************************/

#include <avr/io.h>
#define F_CPU 16000000UL
/* F_CPU needs to be defined prior to import of delay */
#include <util/delay.h>

#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1

void uart_init(void)
{
	/* Set baud rate */
	UBRR0H = MYUBRR >> 8;
	UBRR0L = MYUBRR;

	/* Enable RX and TX */
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);

    /* Set frame format: 8 data, 2 stop bit*/
    UCSR0C = (1 << USBS0) | (1 << UCSZ01) | (1 << UCSZ00);

} /* End uart_init() */

int main(void)
{
    uart_init();

    while(1) {
        /* Do nothing */
    }
    return 0;

} /* End main() */

#if 0
#include <util/delay.h>


void uart_putc(uint8_t data)
{
    /* Wait for empty transmit buffer */
    while (!(UCSR0A & (1 << UDRE0))) ;

    /* Put data into buffer, sends the data */
    UDR0 = data;

} /* End uart_putc() */

void uart_puts(const char *s)
{
	while (*s) uart_putc(*s++);

} /* End uart_puts() */

uint8_t uart_getc(void)
{
    /* Wait for data to be received */
    while (!(UCSR0A & (1 << RXC0))) ;

    /* Get and return received data from buffer */
    return UDR0;
}

int main(void)
{
    uart_init();

    while(1) {
        uart_puts("Hello World!\n");
        /* Implement some delay*/
    }
    return 0;

} /* End main() */

int main(void)
{
    uart_init();

    for (;;) {
        uart_puts("Testing\n");
        _delay_ms(500);
    }

    return 0;

} /* End main() */


uint8_t uart_getc(void)
{
	loop_until_bit_is_set(UCSR0A, RXC0);
	return UDR0;

} /* End uart_getc() */

void uart_putc(uint8_t data)
{
    /* Wait for empty transmit buffer */
    while (!(UCSR0A & (1 << UDRE0))) ;

    /* Put data into buffer, sends the data */
    UDR0 = data;

} /* End uart_putc() */

void uart_puts(const char *s)
{
	while (*s) uart_putc(*s++);

} /* End uart_puts() */

void uart_putc(uint8_t data)
{
	loop_until_bit_is_set(UCSR0A, UDRE0);
	UDR0 = data;
} /* uart_putc() */

void uart_puts(const char *s)
{
	while (*s) uart_putc(*s++);

} /* End uart_puts */
#endif

/* End main.c */

