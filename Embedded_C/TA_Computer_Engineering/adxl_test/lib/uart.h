/*
 * uart.h
 *
 *	Created: 2020-09-08 22:11:05
 *  Author: nlantau
 */

/***************************************************************************
 * UART
 *
 *	Enables UART RX and TX
 *	Functions for RX/TX char, char *, int
 *
 **************************************************************************/

/***** Include guard ******************************************************/

#ifndef UART_H_
#define UART_H_
#ifndef F_CPU
#define F_CPU 16000000UL
#endif

/***** Include section ****************************************************/

#include <avr/io.h>
#include <stdlib.h>

/***** Macro Definitions **************************************************/

#define BaudRate 9600
#define MYUBRR (F_CPU / 16 / BaudRate) - 1

/***** Function prototypes ************************************************/

void uart_init(void);
void uart_putc(unsigned char data);
void uart_sendString(char *s);
void uart_putint(int bufSize, uint8_t value);
unsigned char uart_getc(void);
void uart_getString(char *buf, uint8_t bufSize);
void uart_flush(void);
void uart_getAndCheckRecievedStringForNullBytes(char *_buf, uint8_t bufSize);

#endif /* UART_H_ */