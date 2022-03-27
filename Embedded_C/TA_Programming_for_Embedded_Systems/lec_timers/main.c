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
#define BAUD             9600
#define MYUBRR           F_CPU/16/BAUD-1
#define TIMER1_CTC_VALUE 15625

/***** Function prototypes ************************************************/
inline static void uart_init(void);
static void uart_putc(uint8_t data);
static void uart_puts(const char *s);
static void timer0_init(void);
static void timer1_init(void);
static void timer2_init(void);

/***** Constants **********************************************************/

/***** Variables **********************************************************/
static volatile uint8_t timer0_ovf_counter;
static volatile uint8_t timer0_seconds;
static volatile char timer0_buffer[5] = { 0 };

/* Using 8-bit counter un purpose */
static volatile uint8_t timer1_seconds;
static volatile char timer1_buffer[6] = { 0 };

static volatile uint8_t timer2_ovf_counter;
static volatile uint8_t timer2_seconds;
static volatile char timer2_buffer[5] = { 0 };

/***** MAIN ***************************************************************/
int main(void)
{
    uart_init();
    timer0_init();
    timer1_init();
    timer2_init();

    OCR1A = TIMER1_CTC_VALUE;

    /* LEDs */
    DDRD |= (1 << PIND3) | (1 << PIND6);
    DDRB |= (1 << PINB1);

    PORTD &= ~(1 << PIND3);
    PORTD &= ~(1 << PIND6);
    PORTB &= ~(1 << PINB1);


    for (;;)
        asm volatile ("nop");

	return 0;

} /* End main() */

/***** TIMER0 *************************************************************/
ISR(TIMER0_OVF_vect, ISR_BLOCK)
{
    /* TOV0 is cleared by hw when ISR executes */
    timer0_ovf_counter++;

    if (timer0_ovf_counter == 61) {

        /* Critical section. Save SREG and disable ISR */
        uint8_t volatile _sreg = SREG;
        cli();

        timer0_ovf_counter = 0;
        timer0_seconds++;
        PORTD ^= (1 << PIND3);
        sprintf(timer0_buffer, "%d", timer0_seconds);

        uart_puts(timer0_buffer);
        uart_putc('\n');

        /* Re-enable interrupts */
        SREG = _sreg;
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

/***** TIMER1 *************************************************************/
ISR(TIMER1_COMPA_vect, ISR_BLOCK)
{
    /* Critical section. Save SREG and disable ISR */
    uint8_t volatile _sreg = SREG;
    cli();

    PORTD ^= (1 << PIND6);
    timer1_seconds++;
    sprintf(timer1_buffer, "%d", timer1_seconds);
    uart_putc('\t');
    uart_puts(timer1_buffer);
    uart_putc('\n');

    /* Re-enable interrupts */
    SREG = _sreg;
}


static void timer1_init(void)
{
    /* CTC Mode - Clear Timer on Compare Match
     *
     * 16-bit, prescaler: f_cpu/1024 => 15625 timer ticks / seconds.
     * This fits fine in 16 bits (>= 2^16 - 1 = 65535)
     *
     * OCR1A or ICR1 are used to manipulate the counter resolution.
     * Counter is cleared to zero when the counter value (TCNT1) matches
     * either the OCR1A or the ICR1.
     *
     */

    /* f_cpu/1024 prescaler */
    TCCR1B = (1 << CS12) | (1 << CS10);

    /* CTC Mode. Top: OCR1A */
    TCCR1B |= (1 << WGM12);

    /* Compare A Match Interrupt Enable */
    TIMSK1 |= (1 << OCIE1A);

    sei();
}

/***** TIMER2 *************************************************************/
ISR(TIMER2_OVF_vect, ISR_BLOCK)
{
    /* TOV0 is cleared by hw when ISR executes */
    timer2_ovf_counter++;

    if (timer2_ovf_counter == 61) {

        /* Critical section. Save SREG and disable ISR */
        uint8_t volatile _sreg = SREG;
        cli();

        timer2_ovf_counter = 0;
        timer2_seconds++;

        PORTB ^= (1 << PINB1);
        sprintf(timer2_buffer, "%d", timer2_seconds);

        uart_putc('\t');
        uart_putc('\t');
        uart_puts(timer2_buffer);
        uart_putc('\n');

        /* Re-enable interrupts */
        SREG = _sreg;
    }
}

static void timer2_init(void)
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
    TCCR2B = (1 << CS22) | (1 << CS21) | (1 << CS20);

    /* Overflow Interrupt Enable*/
    TIMSK2 = (1 << TOIE2);

    sei();
}

/***** USART0 *************************************************************/
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

