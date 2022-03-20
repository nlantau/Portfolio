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

void uart_init(void)
{
    /* Enable RX and TX */
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);

    /* Disable transmission complete interrupt */
    UCSR0B &= ~(1 << TXCIE0);

    /* 8-bit character size */
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);

    /* Sets BAUD to 9600 */
    UBRR0H = MYUBRR >> 8;
    UBRR0L = MYUBRR;

#if UART_RX_INT == 1
    /* Enable RX interrupt */
    UCSR0B |= (1 << RXCIE0);

    sei();
#endif

} /* End uart_init() */

uint8_t uart_getc(void)
{
    loop_until_bit_is_set(UCSR0A, RXC0);
    return UDR0;

} /* End uart_getc() */

int uart_putchar_stream(char c, FILE *stream)
{
    if (c == '\n') uart_putchar_stream('\r', stream);

    loop_until_bit_is_set(UCSR0A, UDRE0);
    UDR0 = c;

    return 0;

} /* End uart_putchar_stream() */

void uart_putc(uint8_t data)
{
    loop_until_bit_is_set(UCSR0A, UDRE0);
    UDR0 = data;

} /* uart_putc() */

void uart_puts(const char *s)
{
    while (*s) uart_putc(*s++);

} /* End uart_puts */


/* End uart.c */
