/***************************************************************************
 *  Test of MOSFET with 9V motor
 *  
 * 
 *  Created: 2020-10-31
 *  Updated: 2020-10-31
 *   Author: nlantau
 **************************************************************************/

/***** Include guard ******************************************************/

#ifndef F_CPU
#define F_CPU 16000000UL
#endif /* F_CPU */

/***** Include section ****************************************************/

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

/***** Macro Definitions **************************************************/

/***** Function prototypes ************************************************/

void timer0_init(void);
void adc_init(void);
unsigned char adc_read_(uint8_t ADCchannel);
long map(long x, long in_min, long in_max, long out_min, long out_max);

/***** Constants **********************************************************/

/***** Variables **********************************************************/

/***** MAIN ***************************************************************/

int main(void)
{
    timer0_init();
    adc_init();

    while (1)
    {
        OCR0B = adc_read_(0);
    }

} /* End main() */

/***** TIMER **************************************************************/

void timer0_init(void)
{
    /* Output on PIND5, PIND6 */
    DDRD |= (1 << PIND5);

    /* Clear OC0A and OC0B on compare match, fast PWM */
    TCCR0A = (1 << COM0B1) | (1 << WGM01) | (1 << WGM00);

    /* 1024 prescaler */
    TCCR0B = (1 << CS00) | (1 << CS02);

} /* End pwm_init() */

/***** ADC ***************************************************************/

void adc_init(void)
{
    /* 5V reference, 8-bit */
    ADMUX |= (1 << REFS0) | (1 << ADLAR);

    /* prescaler 128 */
    ADCSRA |= (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2);

    /* Enable ADC */
    ADCSRA |= (1 << ADEN);

} /* End adc_init() */

/***** ADC Read **********************************************************/

unsigned char adc_read_(uint8_t ADCchannel)
{
    /* Select channel with safety mask */
    ADMUX = (ADMUX & 0xF0) | (ADCchannel & 0x0F);

    /* Enable ADC, Start conversion */
    ADCSRA |= (1 << ADSC);

    /* Let conversion take its time */
    while ((ADCSRA & (1 << ADSC)))
    {
        ;
    }

    return ADCH;
} /* End adc_read() */

/***** Map ***************************************************************/

long map(long x, long in_min, long in_max, long out_min, long out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;

} /* End map() */