/***************************************************************************
 * Playground - Using UART and ADC
 *
 * Created: 2022-02-18
 * Updated: 2022-02-19
 * Author : nlantau
 **************************************************************************/

/***** Include guard ******************************************************/

/***** Include section ****************************************************/
#include "lib/utils.h"
#include "lib/uart.h"
#include "lib/adc.h"
#include <avr/io.h>

/***** Macro Definitions **************************************************/

/***** Function prototypes ************************************************/

/***** Constants **********************************************************/

/***** Variables **********************************************************/

/***** MAIN ***************************************************************/
int main(void)
{
	uint8_t x = 0;
	uint16_t adc_value[5] = {0};
	uart_init();
	stdout_init();
	adc_init();

	for (;;) {
		x++;
		adc_read_to_array(MUX0, adc_value);
		adc_read_to_array(MUX1, adc_value);
		printf("Testing: x = %d, adc-value[0] = %d, adc-value[1] = %d \n", x, adc_value[0], adc_value[1]);
		delay_ms(500);
	}

	return 0;

} /* End main() */


/* End main.c */

