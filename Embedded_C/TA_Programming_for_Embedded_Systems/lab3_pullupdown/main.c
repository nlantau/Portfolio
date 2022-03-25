/***************************************************************************
 * Lab 3 - Pull-up and pull-down
 *
 *
 * Created: 2022-03-25
 * Updated: 2022-03-25
 * Author : nlantau
 **************************************************************************/

/***** Include guard ******************************************************/
#define F_CPU 16000000UL

/***** Include section ****************************************************/
#include <stdio.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

/***** Macro Definitions **************************************************/
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1
#define DEBOUNCE_TIME 5               /* 50 works good for normal useage*/

/***** Function prototypes ************************************************/
inline static void uart_init(void);
static void uart_putc(uint8_t data);
static void uart_puts(const char *s);
inline static uint8_t debounce(uint8_t PORT, uint8_t PIN);

/***** Constants **********************************************************/

/***** Variables **********************************************************/
const uint8_t msg[17] PROGMEM = {"Button pressed: "};

/***** MAIN ***************************************************************/
int main(void)
{
    DDRD &= ~(1 << PIND3);
    PORTD |= (1 << PIND3);

    uart_init();
    uint8_t button_was_pressed = 0;
    char buff[20];
    uint8_t counter = 0;
    uint8_t letter, i;

    for (;;) {
        if (debounce(PIND, PIND3)) {
            if (!button_was_pressed) {

                i = 0;

                while ((letter = pgm_read_byte(&msg[i++]))) {
                    uart_putc(letter);
                }


                sprintf(buff, "%d", counter++);
                uart_puts(buff);
                uart_putc('\n');

                button_was_pressed = 1;
            } else {
                button_was_pressed = 0;
            }
        }
    }

	return 0;

} /* End main() */

#ifdef __GNUC__
__attribute__((always_inline)) 
#endif
inline static uint8_t debounce(uint8_t PORT, uint8_t PIN)
{
    if (bit_is_clear(PORT, PIN)) {
        _delay_ms(DEBOUNCE_TIME);
        if (bit_is_clear(PORT, PIN))
            return 1;
    }
    return 0;
}

#ifdef __GNUC__
__attribute__((always_inline)) 
#endif
inline static void uart_init(void)
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


static void uart_putc(uint8_t data)
{
    loop_until_bit_is_set(UCSR0A, UDRE0);
    UDR0 = data;

} /* uart_putc() */


static void uart_puts(const char *s)
{
    while (*s) uart_putc(*s++);

} /* End uart_puts */

/* End main.c */

