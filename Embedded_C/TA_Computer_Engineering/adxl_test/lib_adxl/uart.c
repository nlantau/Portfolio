/*
 * uart.c
 *
 *	Created: 2020-09-13 13:36:29
 *  Author: nlantau
 */

/***************************************************************************
 * UART
 *
 *	Enables UART RX and TX
 *	Functions for RX/TX char, char *, int
 *
 **************************************************************************/

/***** Include section ****************************************************/

#include "uart.h"

/***** UART Initialize ****************************************************/

void uart_init(void)
{
	/* Baud Rate Register High */
	UBRR0H = (MYUBRR >> 8);

	/* Baud Rate Register Low */
	UBRR0L = MYUBRR;

	/* Enable TX and RX */
	UCSR0B |= (1 << TXEN0) | (1 << RXEN0);

	/* 8-bit */
	UCSR0C |= (1 << UCSZ00) | (1 << UCSZ01);

} /* End uart_init() */

/***** UART Send **********************************************************/

void uart_putc(unsigned char data)
{
	/* Wait for transmit buffer to be empty */
	while (!(UCSR0A & (1 << UDRE0)))
		;

	/* Load data into transmit register */
	UDR0 = data;

} /* End uart_putc */

void uart_sendString(char *s)
{
	while (*s)
		uart_putc(*s++);

} /* End uart_puts */

void uart_putint(int bufSize, uint8_t value)
{
	/* _buffer */
	char _buffer[bufSize];

	/* Convert value to char arr */
	itoa(value, _buffer, 10);

	/* Transmit char arr buffer */
	uart_sendString(_buffer);

} /* End uart_putint */

/***** UART Receive *******************************************************/

unsigned char uart_getc(void)
{
	/* Wait for data */
	while (!(UCSR0A & (1 << RXC0)))
		;

	/* Return data */
	return UDR0;

} /* End uart_getc */

void uart_getString(char *buf, uint8_t bufSize)
{
	uint8_t bufIndex = 0;
	unsigned char c;

	c = uart_getc();

	/* If UDR0 is NULL (nothing of interest) */

	if (c == '\0')
	{
		buf[0] = '\0';
		return;
	}

	while (1)
	{
		if ((c == '\r'))
		{
			buf[bufIndex] = 0;
			break;
		}
		else
		{
			buf[bufIndex] = c;
			bufIndex++;
		}
		c = uart_getc();
	}

} /* End uart_gets() */

void uart_getAndCheckRecievedStringForNullBytes(char *_buf, uint8_t bufSize)
{
	uart_getString(_buf, bufSize);

	if (_buf[0] != '\0')
	{
		for (int i = 0; i < bufSize; i++)
		{
			_buf[i] = '\0';
		}
		uart_getString(_buf, bufSize);
	}
	else
	{
		for (int i = 0; i < bufSize; i++)
		{
			(i == 0) ? (_buf[i] = '0') : (_buf[i] = '\0');
		}
	}
}

void uart_flush(void)
{
	unsigned char dummy;
	while (UCSR0A & (1 << RXC0))
		dummy = UDR0;
}