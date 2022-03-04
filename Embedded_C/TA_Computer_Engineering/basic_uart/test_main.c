/*************************************************************************
 * Basic UART RX & TX - TEST
 *
 * Used for testing on PC. No cross-compilation for this file.
 *
 * Created: 2022-03-03
 * Updated: 2022-03-03
 * Author : nlantau
 **************************************************************************/

/***** Include guard ******************************************************/
#define F_CPU 16000000UL

/***** Include section ****************************************************/
#include <stdio.h>
#include <stdint.h>

/***** Macro Definitions **************************************************/
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1

#define AS_INT 0
#define AS_CHAR 1

/***** Function prototypes ************************************************/

/***** Constants **********************************************************/

/***** Variables **********************************************************/

/***** MAIN ***************************************************************/
int main(void)
{
    printf("/***** TEST - UART ****************************************/");
    printf("\n\n\n> using: ");

#if AS_INT
    printf("uint8_t\n\n");
    uint8_t UBRR0H_test = MYUBRR >> 8;
    uint8_t UBRR0L_test = MYUBRR;
#elif AS_CHAR
    printf("unsigned char\n\n");
    unsigned char UBRR0H_test = MYUBRR >> 8;
    unsigned char UBRR0L_test = MYUBRR;
#endif

    printf("UBRR0H_test: %d\n", UBRR0H_test);
    printf("UBRR0L_test: %d\n", UBRR0L_test);
    printf("UBRR0L_test: %c\n", UBRR0L_test);

    printf("\n\n\n");
    printf("/***** TEST - UART ****************************************/\n");


    return 0;

} /* End main() */

#if 0
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
#endif

/* End main.c */

