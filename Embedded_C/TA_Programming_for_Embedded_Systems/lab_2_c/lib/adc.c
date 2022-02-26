/***************************************************************************
 * ADC Source File
 *
 * Created: 2022-02-19
 * Updated: 2022-02-19
 * Author: nlantau
 **************************************************************************/

/***************************************************************************
 *  Info: See adc.h
 *
 **************************************************************************/

/***** Include section ****************************************************/
#include "adc.h"


/***** Functions **********************************************************/
uint8_t adc_init(void)
{
    /* 5V reference */
    ADMUX |= (1 << REFS0);

    /* Prescaler 128 */
    ADCSRA |= (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2);

    /* Enable ADC */
    ADCSRA |= (1 << ADEN);

    return SUCCESS;

} /* End adc_init() */

uint8_t adc_read_to_array(uint8_t adc_channel, uint16_t *adc_arr, uint8_t arr_index)
{
    /* Select channel with safety mask */
    ADMUX = (ADMUX & 0xF0) | (adc_channel & 0x0F);

    /* Start conversion */
    ADCSRA |= (1 << ADSC);

    loop_until_bit_is_clear(ADCSRA, ADSC);

    if (ADC >= 0)
        adc_arr[arr_index] = ADC;
    else
        adc_arr[arr_index] = 0;

    return SUCCESS;

} /* End adc_read_to_array() */

uint16_t adc_read(uint8_t adc_channel)
{
    /* Select channel with safety mask */
    ADMUX = (ADMUX & 0xF0) | (adc_channel & 0x0F);

    /* Start conversion */
    ADCSRA |= (1 << ADSC);

    loop_until_bit_is_clear(ADCSRA, ADSC);

    return ADC;

} /* End adc_read() */

/* End adc.c */
