/***************************************************************************
 *  Ultrasonice Source File
 *
 *
 *	Created: 2020-09-21
 *  Updated: 2020-10-06
 *  Author: nlantau
 **************************************************************************/

/***** Include section ****************************************************/

#include "ultrasonic.h"

/***** Global Variables ***************************************************/

volatile int timerOverflow = 0;

/***** Functions **********************************************************/

void ultrasonic_initTrigEcho(void)
{
    DDRD |= (1 << trigPin);  /* Output trig */
    DDRD &= ~(1 << echoPin); /* Input echo */

} /* End ultrasonic_init_trig_echo() */

void ultrasonic_initINT0(void)
{
    EICRA |= (1 << ISC00); /* Any logical change */
    EIMSK |= (1 << INT0);  /* INT0 enable */

} /* End ultrasonic_init_INT0() */

void ultrasonic_initTimer2(void)
{
    TIMSK2 |= (1 << TOIE2); /* Timer overflow interrupt */
    TCCR2B |= (1 << CS21);  /* prescaler clk 8 */

} /* End ultrasonic_init_timer2() */

void ultrasonic_sendTrigPulse(void)
{
    PORTD &= ~(1 << trigPin);
    _delay_ms(1);

    PORTD |= (1 << trigPin);
    _delay_us(10);
    PORTD &= ~(1 << trigPin);

} /* End ultrasonic_trigger() */

/***** Interrupt Service Routines *****************************************/

ISR(TIMER2_OVF_vect)
{
    /* 7,812 overflows == 1 second */
    timerOverflow++;

} /* End ISR() */

ISR(INT0_vect)
{
    /*************************************************
	* ISR() executes on any logical change to INT0
	*	 -> first call: from 0-5V
	*					- echoPin is high
	*	 -> second call: from 5-0V
	*					- echoPin is low
	*************************************************/
    if (PIND & (1 << echoPin))
    {
        TCNT2 = 0;
        timerOverflow = 0;
    }
    else if (!(PIND & (1 << echoPin)))
    {

        (timerOverflow <= 1) ? (timerOverflow = 1) : (timerOverflow = timerOverflow);
        stop = timerOverflow * 128 + TCNT2 / 2;

        if (timerOverflow < 2) /* ~ < 5 cm */
        {
            result = timerOverflow;
        }
        else if (timerOverflow >= 2)
        {
            result = stop / 58.0;
        }
        else
        {
        }

        timerOverflow = 0;
        TCNT2 = 0;
    }

} /* End ISR() */
