/***************************************************************************
 * UART Header File
 *
 * Created: 2022-02-19
 * Updated: 2022-02-19
 * Author: nlantau
 **************************************************************************/

/***************************************************************************
 *  Info: Very basic for now. Using FDEV_SETUP_STREAM to set stdout to
 *        UART, which makes it possible to use printf() from stdio.h to
 *        send FILE stream of characters to a PC serial monitor.
 *  TODO: Implement 'uart_getc()' 
 *
 **************************************************************************/

/***** Include guard ******************************************************/
#ifndef UART_S_H_
#define UART_S_H_

#ifndef F_CPU
#define F_CPU        16000000UL
#endif /* F_CPU */

/***** Include section ****************************************************/
#include <stdio.h>
#include <avr/io.h>

/***** Macro Definitions **************************************************/
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1
#define SUCCESS 1

/***** Function prototypes ************************************************/

/* Must return 'int' according to the definition of 
 * FDEV_SETUP_STREAM() in stdio.h
 */
extern int uart_putchar_stream(char c, FILE *stream);
extern void uart_init(void);
extern uint8_t stdout_init(void);
extern void uart_putc(uint8_t data);
extern uint8_t uart_getc(void);
extern void uart_puts(const char *s);

#endif /* UART_S_H_ */

