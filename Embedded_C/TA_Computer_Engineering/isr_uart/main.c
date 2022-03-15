/***************************************************************************
 * ISR UART RX & TX
 *
 * Created: 2022-03-15
 * Updated: 2022-03-15
 * Author : nlantau
 **************************************************************************/

/***** Include guard ******************************************************/
#define F_CPU 16000000UL

/***** Include section ****************************************************/
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

/***** Macro Definitions **************************************************/
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1
#define UART_RX_INT 1

/***** Function prototypes ************************************************/
void uart_init(void);
uint8_t uart_getc(void);
void uart_putc(uint8_t data);
void uart_puts(const char *s);
int uart_putchar_stream(char c, FILE *stream);

/***** Constants **********************************************************/
static FILE mystdout = FDEV_SETUP_STREAM(uart_putchar_stream, NULL, _FDEV_SETUP_WRITE);
/***** Variables **********************************************************/

/***** MAIN ***************************************************************/
int main(void)
{
    stdout = &mystdout;
    uart_init();

    for (;;) {
        _delay_ms(500);
    }

    return 0;

} /* End main() */

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

ISR(USART_RX_vect, ISR_BLOCK)
{
    /* Check for frame error */
    if (!(UCSR0A & (1 << FE0))) {
        volatile uint8_t data = UDR0;
        printf("\r>Received: [%c]\n", data);
    } else {
        /* Must read UDR0 to clear interrupt flag */
        volatile uint8_t data __attribute__((unused)) = UDR0;
    }
}


int uart_putchar_stream(char c, FILE *stream)
{
    if (c == '\n') uart_putchar_stream('\r', stream);

    loop_until_bit_is_set(UCSR0A, UDRE0);
    UDR0 = c;

    return 0;

} /* End uart_putchar_stream() */


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

