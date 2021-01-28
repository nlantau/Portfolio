/***************************************************************************
 *  UART Source file
 *
 *	Usage:
 *		Transmit:
 *				uart_sendString(_buf);
 *				uart_sendCharacter('\r');
 *		Recieve:
 *				uart_getAndCheckRecievedStringForNullBytes(_buf, bufSize);
 *
 *	Created: 2020-09-08
 *  Updated: 2020-10-06
 *  Author: nlantau
 **************************************************************************/

/***** Include section ****************************************************/

#include "uart.h"

/***** UART Initialize ****************************************************/

void uart_init(void)
{
    UBRR0H = (MYUBRR >> 8);                  /* Baud Rate Register High */
    UBRR0L = MYUBRR;                         /* Baud Rate Register Low */
    UCSR0B |= (1 << TXEN0) | (1 << RXEN0);   /* Enable TX and RX */
    UCSR0C |= (1 << UCSZ00) | (1 << UCSZ01); /* 8-bit */

} /* End uart_init() */

/***** UART Send **********************************************************/

void uart_sendCharacter(char data)
{
    while (!(UCSR0A & (1 << UDRE0))) /* Wait for transmit buffer to be empty */
    {
        ;
    }
    UDR0 = data; /* Load data into transmit register */

} /* End uart_putc */

void uart_sendString(char *s)
{
    while (*s)
    {
        uart_sendCharacter(*s++);
    }

} /* End uart_puts */

void uart_putint(uint8_t bufSize, uint8_t value)
{
    char _buffer[bufSize];
    itoa(value, _buffer, 10);
    uart_sendString(_buffer);

} /* End uart_putint */

/***** UART Receive *******************************************************/

unsigned char uart_getc(void)
{
    while (!(UCSR0A & (1 << RXC0))) /* Wait for data */
    {
        ;
    }
    return UDR0; /* Return data */

} /* End uart_getc */

void uart_getString(char *buf, uint8_t bufSize)
{
    uint8_t bufIndex = 0;
    char c;

    c = uart_getc();
    if (c == '\0') /* If UDR0 is NULL (nothing of interest) */
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

    if (_buf[0] != '\0') /* If first element is not NULL = string is OK */
    {
        for (uint8_t i = 0; i < bufSize; i++)
        {
            _buf[i] = '\0'; /* Clear the buffer */
        }
        uart_getString(_buf, bufSize); /* Recieve actual data and store in buffer */
    }
    else /* The first element is NULL = string NOT OK */
    {
        for (uint8_t i = 0; i < bufSize; i++)
        {
            (i == 0) ? (_buf[i] = '0') : (_buf[i] = '\0'); /* Put decimal 0 at first index to display 0 on OLED/display */
        }
    }

} /* End uart_gets_arr() */
