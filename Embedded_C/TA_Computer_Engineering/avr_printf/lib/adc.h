/***************************************************************************
 * ADC Header File
 *
 * Created: 2022-02-19
 * Updated: 2022-02-19
 * Author: nlantau
 **************************************************************************/

/***************************************************************************
 *  Info: Prescaler 128
 *        Reference 5.0V
 *        10-bit ADC
 *  TODO: Implement function that reads all ADC and stores in array
 *
 **************************************************************************/

/***** Include guard ******************************************************/
#ifndef ADC_H_
#define ADC_H_

/***** Include section ****************************************************/
#include <avr/io.h>

/***** Macro Definitions **************************************************/
#define SUCCESS 1

/***** Function prototypes ************************************************/
extern uint8_t adc_init(void);
extern uint16_t adc_read(uint8_t adc_channel);
extern uint8_t adc_read_to_array(uint8_t adc_channel, uint16_t *adc_arr);

#endif /* ADC_H_ */

