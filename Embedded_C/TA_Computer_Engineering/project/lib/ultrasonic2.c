/***************************************************************************
 *  Ultrasonic 2 Source File
 *
 *
 *  Created: 2020-02-20
 *  Updated: 2022-02-20
 *  Author : Mattias Ahle
 *  Updated: nlantau
 **************************************************************************/

/***************************************************************************
 *  Info: Static prototypes need to reside inside source file.
 *        HC-SR04
 *        Prescaler 64
 *        INT1   - ISR INT1_vect
 *        TIMER1 - ISR TIMER1_OVR_vect
 *
 *        hc_sr04_distance() returns distance in millimeters.
 *        
 *
 **************************************************************************/

/***** Include section ****************************************************/
#include "ultrasonic2.h"

/***** Static variables ***************************************************/
static uint16_t distance = 0;
static const uint8_t PRESCALER = 64;
static const uint8_t CLOCKS_PER_MICRO = F_CPU / 1000000;
static const uint32_t MAX_COUNTS_COUNTER_REGISTER = 65536;
static volatile uint64_t overflow_count = 0;

/***** Static prototypes **************************************************/
static void int1_init(void);
static void timer1_init(void);
static void timer1_start(void);
static void timer1_stop(void);
static void timer1_start(void);
static void timer1_reset(void);
static uint64_t timer1_micros(void);
static void send_trig_signal(void);

/***** INT1 ***************************************************************/
static void int1_init(void)
{
    /* Any logical change */
    EICRA |= (1 << ISC10);

    /* INT1 enable */
    EIMSK |= (1 << INT1);
}


/***** TIMER1 *************************************************************/
static void timer1_init(void)
{
    /* Timer/Counter1 counting register init to zero */
    TCNT1 = 0;

    /* Timer/Counter1, Overflow Interrrupt Enable */
    TIMSK1 |= (1 << TOIE1);

    /* Clear Timer/Counter1, Overflow flag*/
    TIFR1 |= (1 << TOV0);

} /* End timer1_init() */

static void timer1_start(void)
{
    /* Prescaler 64 */
    TCCR1B |= (1 << CS10) | (1 << CS11);

} /* End timer1_start() */

static void timer1_stop(void)
{
    TCCR1B &= ~(1 << CS10);
    TCCR1B &= ~(1 << CS11);
    TCCR1B &= ~(1 << CS12);

} /* End timer1_stop() */

static void timer1_reset(void)
{
    timer1_stop();
    overflow_count = 0;
    TCNT1 = 0;

} /* End timer1_reset() */

static uint64_t timer1_micros(void)
{
    static const uint8_t MICROS_PER_TCNT1 = PRESCALER / CLOCKS_PER_MICRO;
    static const uint32_t MICROS_PER_OVERFLOW = MICROS_PER_TCNT1 * MAX_COUNTS_COUNTER_REGISTER;

    return overflow_count * MICROS_PER_OVERFLOW + TCNT1 * MICROS_PER_TCNT1;

} /* End timer1_micros() */


/***** HC-SR04 ************************************************************/
void hc_sr04_init(void)
{
    DDRB |= (1 << trig_pin);
    DDRD &= ~(1 << echo_pin);

    timer1_init();
    int1_init();

} /* End hc_sr04_init() */

static void send_trig_signal(void)
{
    PORTB &= ~(1 << trig_pin);
    _delay_us(2);
    PORTB |= (1 << trig_pin);
    _delay_ms(10);
    PORTB &= ~(1 << trig_pin);

} /* End send_trig_signal() */

uint16_t hc_sr04_distance(void)
{
    send_trig_signal();
    distance = (uint16_t) ((timer1_micros() * 17) / 100);
    timer1_reset();

    return distance;

} /* hc_sr04_distance() */


/***** Interrupt Service Routines *****************************************/
ISR(TIMER1_OVF_vect)
{
    overflow_count++;

} /* End ISR() */

ISR(INT1_vect)
{
    if (PIND & (1 << echo_pin))
        timer1_start();
    else
        timer1_stop();

} /* End ISR() */


