/***************************************************************************
 * Playground - OLED, HC-SR04, IR-sensors, ADXL345
 *
 * Created: 2022-02-18
 * Updated: 2022-02-20
 * Author : nlantau
 **************************************************************************/

/***** Include guard ******************************************************/
#ifndef F_CPU
#define F_CPU 16000000UL
#endif /* F_CPU */

/***** Include section ****************************************************/
#include "lib/adxl345.h"
#include "lib/adc.h"
#include "lib/font.h"
#include "lib/i2cmaster.h"
#include "lib/lcd.h"
#include "lib/oled.h"
#include "lib/uart.h"
#include "lib/ultrasonic2.h"
#include "lib/utils.h"
#include <avr/io.h>
#include <stdlib.h>
#include <string.h>

/***** Macro Definitions **************************************************/

/***** Function prototypes ************************************************/

/***** Constants **********************************************************/

/***** Variables **********************************************************/

/***** MAIN ***************************************************************/
int main(void)
{
	uint8_t i, adc_ports[5] = {0x00, 0x01, 0x02, 0x03, 0x04};
	uint16_t adc_value[5] = {0}, distance = 0;
	double ax = 0, ay = 0, az = 0;
	char itmpx[10], itmpy[10], itmpz[10];
	char buff[8], oled_buff[30], acc_buff[30], dist_buff[20];

	uart_init();
	stdout_init();
	adc_init();
	adxl345_init();
	lcd_init(0xAF);
	lcd_clrscr();
	hc_sr04_init();
	sei();

	for (;;) {

		for (i = 0; i < 4; ++i) {
			adc_read_to_array(adc_ports[i], adc_value);
			sprintf(buff, "%d", adc_value[i]);

			uart_puts(buff);
			uart_putc('\t');

			memset(buff, 0, 8);
		}


		/* ADXL345 */
		adxl345_getdata(&ax, &ay, &az);
		dtostrf(ax, 3, 5, itmpx); uart_puts(itmpx); uart_putc(' ');
		dtostrf(ay, 3, 5, itmpy); uart_puts(itmpy); uart_putc(' ');
		dtostrf(az, 3, 5, itmpz); uart_puts(itmpz); uart_putc(' ');

		/* Parse to numbers to  string */
		memset(dist_buff, 0, 10); 
		sprintf(oled_buff, "IR %3d,%3d,%3d,%3d", adc_value[0], adc_value[1], adc_value[2], adc_value[3]);
		sprintf(acc_buff, "ACC %.4s,%.4s,%.4s", itmpx, itmpy, itmpz);
		sprintf(dist_buff, "D: %5d mm", distance); 

		/* HC-SR04 */
		distance = hc_sr04_distance();
		uart_puts(dist_buff);

		/* Print on OLED */
		oled_puts("Niklas Lantau", 0, 0);
		oled_puts(oled_buff, 0, 2);
		oled_puts(acc_buff, 0, 4);
		oled_puts(dist_buff, 0, 6);

		/* Newline on terminal + 100ms delay */
		uart_putc('\n');
		delay_ms(100);
	}

	return 0;

} /* End main() */


/* End main.c */

