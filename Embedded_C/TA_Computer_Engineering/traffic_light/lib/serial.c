/***************************************************************************
 *  Serial source file
 * 
 *
 *  Created: 2013
 *  Updated: 2021-10-02 by Niklas Lantau
 *  Author : Tomasz Wisniewski
 **************************************************************************/

/***** Include section ****************************************************/

#include "serial.h"
#include <avr/io.h>
#include <avr/power.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>


/* I HAVE DECLARED DESSA FÖR TESTA */
static volatile uint64_t counter = 0x00;
static volatile unsigned char msg[64] = {0};
static volatile uint8_t is_start_delim = 0;

/***** ISR ****************************************************************/

#if SERIAL_IMPLEMENT_RX_INT == 1

/**
 * @brief receive USART interrupt
 *
 * Data is received in this ISR and placed in the RX ring buffer - if there is still space available.
 *
 * @param USART_RX_vect
 */
ISR(USART_RX_vect, ISR_BLOCK) {

	// no frame error
	// UCSR0A must be read before UDR0 !!!
	if (bit_is_clear(UCSR0A, FE0)) {
		/// must read the data in order to clear the interrupt flag
		volatile unsigned char data = UDR0;

		/// calculate the next available ring buffer data bucket index
		volatile unsigned char next =
		   	((g_rx_buff.u.r.head + 1) % SERIAL_RX_RING_SIZE);


		/* FROM HERE I HAVE KLADDAT */
		uint16_t length = 0x1234;

		if (data == 0x7E) {
			is_start_delim = 1;
			serial_poll_sendc(START_DELIMITER);		// Start delim
			serial_poll_sendc(length >> 8);			// Length (16 bit), send MSB
			serial_poll_sendc(length);			// Length (16 bit), send LSB
			serial_poll_sendc(TRANSMIT_REQUEST_FRAME);	// 8 bit
			serial_poll_sendc(FRAME_ID);			// 8 bit
			for (int8_t i = 56; i>= 0; i -= 8)
				serial_poll_sendc(ID_1051C >> i);	// 64 bit
		}

		serial_flush();


		/*if (counter > 16) {
			serial_poll_send(msg, 17);

			// Clear msg and flush UART
			counter = 0;
			memset(msg, '\0', SERIAL_RX_RING_SIZE);
			serial_flush();
		}
		*/

		/* TO HERE I HAVE KLADDAT */

		/// do not overflow the buffer
		if (next != g_rx_buff.u.r.tail) {
			g_rx_buff.u.r.ring[g_rx_buff.u.r.head] = data;
			g_rx_buff.u.r.head = next;			
		}
		else {
			;
		}
	}
	else {
		/// must read the data in order to clear the interrupt flag
		volatile unsigned char data __attribute__((unused)) = UDR0;
	}
}
#endif


#if SERIAL_IMPLEMENT_TX_INT == 1

/**
 * @brief transmission complete interrupt
 *
 * @param USART_TX_vect
 * @param ISR_BLOCK
 */
ISR(USART_UDRE_vect, ISR_BLOCK) {
	
	// proceed if there still is data to be send
	if (g_tx_buff.u.r.head != g_tx_buff.u.r.tail) {
		UDR0 = g_tx_buff.u.r.ring[g_tx_buff.u.r.tail];
		g_tx_buff.u.r.tail = (g_tx_buff.u.r.tail + 1) % SERIAL_TX_RING_SIZE;

	}
	else {
		// mask the interrupt everything has been send
		UCSR0B &= ~_BV(UDRIE0);
	}
}
#endif


/***** UART Initialization ************************************************/

e_return serial_init(uint32_t a_speed) {
	
	// baud value
	uint16_t baud_value = 0x00;

	// enable power
	power_usart0_enable();	

	// double mode disabled
	UCSR0A = 0x00;

	// choose predefined value or calculate
	switch (a_speed) { 

#if F_CPU == 16000000UL
		case E_BAUD_2400:
			UCSR0A |= _BV(U2X0);
			baud_value = 832;
			break;

		case E_BAUD_4800:
			baud_value = 207;
			break;

		case E_BAUD_9600:
			baud_value = 103;
			break;

		case E_BAUD_14400:
			baud_value = 68;
			break;

		case E_BAUD_19200:
			baud_value = 51;
			break;

		case E_BAUD_28800:
			baud_value = 34;
			break;

		case E_BAUD_38400:
			baud_value = 25;
			break;

		case E_BAUD_57600:
			UCSR0A |= _BV(U2X0);
			baud_value = 34;
			break;

		case E_BAUD_76800:
			baud_value = 12;
			break;

		case E_BAUD_115200:
			UCSR0A |= _BV(U2X0);
			baud_value = 16;
			break;

#endif

		default:
			// manual calculation
			{
				int8_t use_double = 1;

				do {
					if (use_double) {
						UCSR0A |= _BV(U2X0);
						baud_value = (F_CPU / 4 / a_speed - 1) / 2;
					} else {
						UCSR0A = 0x00;
						baud_value = (F_CPU / 8 / a_speed - 1) / 2;
					}

				} while (baud_value > 4095 && use_double--);
			}
			break;
	} // switch

	UBRR0H = (baud_value >> 8) & 0xff;
	UBRR0L = baud_value & 0xff;

#if SERIAL_IMPLEMENT_RX_INT == 1
	// clear the ring, reuse the bad_value variable
	baud_value = sizeof(g_rx_buff);
	common_zero_mem(&g_rx_buff, baud_value);
#endif

#if SERIAL_IMPLEMENT_TX_INT == 1
	// reuse the bad_value variable 
	baud_value = sizeof(g_tx_buff);
	common_zero_mem(&g_tx_buff, baud_value);
#endif

	// asynchronous, 8N1 mode
	UCSR0C |= 0x06;
	
	// rx/tx enable
	UCSR0B |= _BV(RXEN0);
	UCSR0B |= _BV(TXEN0);

	serial_flush();
	return RET_OK;
}


void serial_install_interrupts(e_serial_flags a_flags) {

	// disable transmission complete interrupt
	UCSR0B &= ~_BV(TXCIE0);

#if SERIAL_IMPLEMENT_RX_INT == 1
	if (a_flags & E_FLAGS_SERIAL_RX_INTERRUPT) {
		// enable receive interrupt
		UCSR0B |= _BV(RXCIE0);
	}
#endif

#if SERIAL_IMPLEMENT_TX_INT == 1
	if (a_flags & E_FLAGS_SERIAL_TX_INTERRUPT) {
		// do nothing, the interrupt will be enable whenever the characters are
		// queued to send
	}
#endif

	// enable global interrupts
	sei();
}



#if SERIAL_IMPLEMENT_RX_INT == 1
//inline 
unsigned char serial_available() {
	return (SERIAL_RX_RING_SIZE + g_rx_buff.u.r.head - g_rx_buff.u.r.tail) % SERIAL_RX_RING_SIZE;
}


unsigned char serial_peek(void *a_data, unsigned char a_size) {
	unsigned char read = serial_available();
	if (read > a_size)
		read = a_size;

	for (unsigned char i = 0; i<read; i++) {
		((unsigned char *)a_data)[i] =
			g_rx_buff.u.r.ring[ (g_rx_buff.u.r.tail + i) % SERIAL_RX_RING_SIZE ];
	}

	return read;
}


unsigned int serial_recv(void *a_data, unsigned int a_size, unsigned char a_waitall) {
	unsigned int read = 0x00;

	if (!a_waitall && g_rx_buff.u.r.head == g_rx_buff.u.r.tail) {
		return 0;
	}

	while ( read < a_size ) {

		while (serial_available() && (read < a_size)) 
		{
			((unsigned char *)a_data)[read] = g_rx_buff.u.r.ring[ g_rx_buff.u.r.tail ];
			g_rx_buff.u.r.tail = (g_rx_buff.u.r.tail + 1) % SERIAL_RX_RING_SIZE;
			read++;
		}

		if (!a_waitall)
			break;
	}
	
	return read;
}


unsigned char serial_getc(unsigned char *a_data) {
	
	if (g_rx_buff.u.r.head == g_rx_buff.u.r.tail)
		return 0;

	*a_data = g_rx_buff.u.r.ring[g_rx_buff.u.r.tail];
	g_rx_buff.u.r.tail = (g_rx_buff.u.r.tail + 1) % SERIAL_RX_RING_SIZE;
	return 1;
}
#endif


unsigned char serial_poll_recv(unsigned char *a_data, unsigned int a_size) {
	unsigned int cnt = a_size;

	while (a_size) {
		/* Wait for data to be received */
		while ( !(UCSR0A & (1<<RXC0)) );

		/* Get and return received data from buffer */
		*a_data = UDR0;
		a_data++;
		a_size--;
	}

	return cnt;
}


unsigned char serial_poll_getc(unsigned char *a_data) {
	return serial_poll_recv(a_data, 1);
}


#if SERIAL_IMPLEMENT_TX_INT == 1
unsigned char serial_send(void *a_data, unsigned int a_size, unsigned char a_waitall) {
	uint8_t n = 0x00;
	uint8_t *data = (uint8_t *)a_data;
	uint8_t initiated = 0x00;

	while (a_size) {
		volatile unsigned char next =
		   	((g_tx_buff.u.r.head + 1) % SERIAL_TX_RING_SIZE);

		/// do not overflow the buffer
		if (next != g_tx_buff.u.r.tail) {
			g_tx_buff.u.r.ring[g_tx_buff.u.r.head] = *data;
			g_tx_buff.u.r.head = next;			
		}
		else {
			if (a_waitall) {
				if (!initiated) {
					initiated = 0x01;

					// enable data register empty interrupt
					UCSR0B |= _BV(UDRIE0);
				}
				continue;
			}
			else
				break;
		}

		a_size--;
		n++;
		data++;
	}

	if (!a_waitall || !initiated) {
		initiated = 0x01;
		// enable data register empty interrupt
		UCSR0B |= _BV(UDRIE0);
	}

	return n;
}


unsigned char serial_sendc(unsigned char a_data) {

	uint8_t n = 0x00;
	uint8_t next =
		((g_tx_buff.u.r.head + 1) % SERIAL_TX_RING_SIZE);

	/// do not overflow the buffer
	if (next != g_tx_buff.u.r.tail) {
		g_tx_buff.u.r.ring[g_tx_buff.u.r.head] = a_data;
		g_tx_buff.u.r.head = next;
		n = 1;

		// enable data register empty interrupt
		UCSR0B |= _BV(UDRIE0);
	}

	return n;
}
#endif


unsigned int serial_poll_send(void *data, unsigned int a_size) {
	unsigned int i = 0x00;
	while (i < a_size) {
		// wait until usart buffer is empty
		while ( bit_is_clear(UCSR0A, UDRE0) );

		// send the data
		UDR0 = ((unsigned char *)data)[i++];
	}

	return i;
}


unsigned int serial_poll_sendc(unsigned char a_char) {
	return serial_poll_send((void *)&a_char, 1);
}


void serial_flush() {
	unsigned char dummy __attribute__((unused)) = 0x00;

#if SERIAL_IMPLEMENT_RX_INT == 1
	g_rx_buff.u.r.tail = g_rx_buff.u.r.head = 0x00;
#endif

	// flush the input fifo
	while ( UCSR0A & (1<<RXC0) ) dummy = UDR0;
}


#if SERIAL_IMPLEMENT_RX_INT == 1
volatile t_buffer* serial_get_rx_state() {
	return &g_rx_buff;
}
#endif


#if SERIAL_IMPLEMENT_TX_INT == 1
volatile t_buffer* serial_get_tx_state() {
	return &g_tx_buff;
}
#endif

