/*
 * adc.h
 *
 * Created: 2020-09-10 16:20:02
 *  Author: nlantau
 */

/***************************************************************************
 * ADC
 *
 *	Prescaler 128
 *	Reference 5.0V
 *	adc_read() masks out all but wanted ADC-channel
 *
 **************************************************************************/

/***** Include guard ******************************************************/

#ifndef ADC_H_
#define ADC_H_

/***** Include section ****************************************************/

#include <avr/io.h>

/***** Function prototypes ************************************************/

void adc_init(void);
unsigned char adc_read_(uint8_t ADCchannel);
void adc_read(uint8_t ADCchannel);

#endif /* ADC_H_ */