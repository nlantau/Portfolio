/***************************************************************************
 * Lec 19 - Timers
 *
 *
 * Created: 2022-03-26
 * Updated: 2022-03-27
 * Author : nlantau
 **************************************************************************/

/***** Include guard ******************************************************/
#define F_CPU 16000000UL

/***** Include section ****************************************************/
#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>

/***** Macro Definitions **************************************************/
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1

/***** Function prototypes ************************************************/
inline static void uart_init(void);
static void uart_putc(uint8_t data);
static void uart_puts(const char *s);
static void timer0_init(void);

/***** Constants **********************************************************/

/***** Variables **********************************************************/
static volatile uint8_t timer0_ovf_counter;
static volatile uint8_t seconds;
static volatile char buff[5] = { 0 };

/***** MAIN ***************************************************************/
int main(void)
{
    uart_init();
    timer0_init();

    DDRD |= (1 << PIND3);
    PORTD &= ~(1 << PIND3);


    for (;;) {
        asm volatile ("nop");

    }

	return 0;

} /* End main() */

ISR(TIMER0_OVF_vect, ISR_BLOCK)
{
    /* TOV0 is cleared by hw when ISR executes */
    timer0_ovf_counter++;

    if (timer0_ovf_counter == 61) {
        timer0_ovf_counter = 0;
        seconds++;
        PORTD ^= (1 << PIND3);
        sprintf(buff, "%d", seconds);

        uart_puts(buff);
        uart_putc('\n');

    }

}

static void timer0_init(void)
{
    /* Normal Mode
     *
     * 8-bit, prescaler: f_cpu/1024 => 15625 timer ticks / second.
     * This requires 61 (9 ticks remainder) overflows of 8-bit register.
     *   -> 61 * 256 = 15616. 15625 - 15625 = 9.
     *
     * So, with a prescaler of f_cpu/1024 we have 1/15625 periods. 
     *   -> 1/15625 = 64 * 10^-6 = 64 µs/period
     *
     * Each 8-bit timer "second" is therefore 64 * 9 = 576 µs = 0.5 ms
     * faster than a real-time second.
     * 
     */

    /* f_cpu/1024 prescaler */
    TCCR0B = (1 << CS02) | (1 << CS00);

    /* Overflow Interrupt Enable*/
    TIMSK0 = (1 << TOIE0);

    sei();
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
#endif /* UART_RX_INT */

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

