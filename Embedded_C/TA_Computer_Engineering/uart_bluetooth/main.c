/***************************************************************************
 *  OLED Arduino Slave Unit 
 *
 *  Rx command via UART connected to Xbee
 *
 *  Created: 2021-10-02
 *  Updated: 2021-10-03
 *  Author : nlantau
 **************************************************************************/
/***** Include guard ******************************************************/

#ifndef F_CPU
#define F_CPU 16000000UL
#endif /* F_CPU */

/***** Include section ****************************************************/

#include "lib/serial.h"
#include <util/delay.h>

/***** Macro Definitions **************************************************/

/***** Constants **********************************************************/

//static const uint8_t start_delim = 0x7E;
//static const char *master_src_adr = "0013A20041B7597";
//static const uint8_t rf_opt = 0xC1;
//static const uint8_t BUF_SIZE = 32;

/***** Function prototypes ************************************************/

/***** MAIN ***************************************************************/


int main(void)
{
	DDRD |= (1 << PIND3);
	PORTD &= ~(1 << PIND3);


	uint8_t c = 0x00;

	serial_init(E_BAUD_9600);
	serial_install_interrupts(E_FLAGS_SERIAL_RX_INTERRUPT);
	serial_flush();

	while (1) {


	}

	return 0;

} /* End main() */

/* End main.c */
