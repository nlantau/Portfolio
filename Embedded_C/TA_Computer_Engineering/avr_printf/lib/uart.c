/***************************************************************************
 * UART Source File
 *
 * Created: 2022-02-19
 * Updated: 2022-02-19
 * Author: nlantau
 **************************************************************************/

/***************************************************************************
 *  Info: See uart.h
 *
 **************************************************************************/

/***** Include section ****************************************************/
#include "uart.h"

static FILE mystdout = FDEV_SETUP_STREAM(uart_putchar_stream, NULL, _FDEV_SETUP_WRITE);

/***** Functions **********************************************************/

uint8_t stdout_init(void)
{
	/* Redirects stdout for printf() to UART */
	stdout = &mystdout;

	return SUCCESS;
}

uint8_t uart_init(void)
{
	/* Sets BAUD to 9600 */
	UBRR0H = MYUBRR >> 8;
	UBRR0L = MYUBRR;

	/* Enable RX and TX */
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);

	return SUCCESS;

} /* End uart_init() */

int uart_putchar_stream(char c, FILE *stream)
{
	if (c == '\n') uart_putchar_stream('\r', stream);

	loop_until_bit_is_set(UCSR0A, UDRE0);
	UDR0 = c;

	return 0;

} /* End uart_putchar_stream() */

/* End uart.c */
