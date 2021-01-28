/***************************************************************************
 *  UART Header
 * 
 *
 *	Created: 2020-09-08
 *  Updated: 2020-10-06
 *  Author: nlantau
 **************************************************************************/

/***** Include guard ******************************************************/

#ifndef UART_H_
#define UART_H_
#ifndef F_CPU
#define F_CPU 16000000UL

#endif /* F_CPU */
/***** Include section ****************************************************/

#include <avr/io.h>
#include <stdlib.h>

/***** Macro Definitions **************************************************/

#define BaudRate 9600
#define MYUBRR (F_CPU / 16 / BaudRate) - 1

/***** Function prototypes ************************************************/

void uart_init(void);
void uart_sendCharacter(char data);
void uart_sendString(char *s);
void uart_putint(uint8_t bufSize, uint8_t value);
unsigned char uart_getc(void);
void uart_getString(char *buf, uint8_t bufSize);
void uart_getAndCheckRecievedStringForNullBytes(char *_buf, uint8_t bufSize);

#endif /* UART_H_ */

/*** end of file ***/