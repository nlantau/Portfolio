/***************************************************************************
 *  Lab 5 - Sensor Interface with Arduino Uno
 *  
 *
 *  Created: 2021-05-16
 *  Updated: 2021-05-16
 *  Author : nlantau
 **************************************************************************/

/***** Include guard ******************************************************/

#ifndef F_CPU
#define F_CPU 16000000UL

/***** Include section ****************************************************/

#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>
#include "lib_adxl/adxl345.h"
#include "lib_adxl/i2cmaster.h"
#include "lib_adxl/uart.h"

#endif /* F_CPU */
/***** Macro Definitions **************************************************/

/***** Function prototypes ************************************************/

/***** Constants **********************************************************/

/***** MAIN ***************************************************************/

int main(void)
{
	double ax = 0;
	double ay = 0;
	double az = 0;
	
	char itmp[10];
	
	uart_init();
	
	adxl345_init();
	
	
	while (1) {
		adxl345_getdata(&ax, &ay, &az);
		
		dtostrf(ax, 3, 5, itmp); uart_sendString(itmp); uart_putc(' ');
		dtostrf(ay, 3, 5, itmp); uart_sendString(itmp); uart_putc(' ');
		dtostrf(az, 3, 5, itmp); uart_sendString(itmp); uart_putc(' ');
		
		uart_sendString("\r\n");
		_delay_ms(100);
	
	}





}

