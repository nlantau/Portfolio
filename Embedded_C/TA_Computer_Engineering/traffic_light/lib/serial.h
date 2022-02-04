/***************************************************************************
 *  Serial header file
 * 
 *
 *  Created: 2013
 *  Updated: 2021-10-02 by Niklas Lantau
 *  Author : Tomasz Wisniewski
 **************************************************************************/



/***** Include guard ******************************************************/

#ifndef ALL_UART_
#define ALL_UART_

#ifndef F_CPU
#define F_CPU 16000000UL
#endif /* F_CPU */

/***** Include section ****************************************************/

#include <avr/io.h>
#include <avr/power.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdint.h>

/***** Type definitions ***************************************************/

typedef volatile int8_t vint8_t;
typedef volatile uint8_t vuint8_t;
typedef volatile int16_t vint16_t;
typedef volatile uint16_t vuint16_t;
typedef volatile int32_t vint32_t;
typedef volatile uint32_t vuint32_t;
typedef volatile int64_t vint64_t;
typedef volatile uint64_t vuint64_t;


/***** Macro Definitions **************************************************/

#define SERIAL_COLLECT_STATS 0
#define SERIAL_IMPLEMENT_RX_INT 1
#define SERIAL_IMPLEMENT_TX_INT 0
//#define SERIAL_SUPPORT_HIGH_SPEEDS 1
#define SERIAL_STDIN_POLL 0
#define SERIAL_STDOUT_POLL 1
#define SERIAL_RX_RING_SIZE 64
#define SERIAL_TX_RING_SIZE 64
#define common_zero_mem(__ptr, __len) while (__len--) (*(char *)(__ptr)) = 0x00

/* Define Required XBee Frame Type and Responses */
#define START_DELIMITER				0x7E
#define AT_COMMAND_FRAME			0x08
#define TRANSMIT_REQUEST_FRAME			0x10
#define REMOTE_AT_COMMAND_FRAME			0x17
#define IO_DATA_SAMPLE_FRAME			0x92
#define AT_COMMAND_RESPONSE_FRAME		0x88
#define REMOTE_AT_COMMAND_RESPONSE_FRAME	0x97
#define RECEIVE_PACKET_FRAME			0x90
#define TRANSMIT_STATUS_FRAME			0x8B
#define FRAME_ID				0x01
#define REMOTE_AT_COMMAND_OPT			0x02
#define TRANSMIT_REQUEST_OPT			0x00
#define TRANSMIT_REQUEST_BROADCAST_RADIUS	0x00

#define LONG_ADDRESS				0x1122334455667788

#define Read					0
#define Write					1

#define Vref					1.2


#define BUFFER_SIZE				100
#define DIGITAL_BUFFER_SIZE			16
#define ANALOG_BUFFER_SIZE			8

/***** Structs Definitions ************************************************/

typedef struct _ring_buffer {
	volatile unsigned char head;
	volatile unsigned char tail;
	/// data storage space for the ring buffer
	volatile unsigned char ring[1];
} ring_buffer;

#define RING_SIZE (sizeof(ring_buffer) - 1)

typedef struct _t_buffer {
	/// data storage space for the ring buffer
	union {
		volatile uint8_t raw[SERIAL_RX_RING_SIZE + RING_SIZE];
		volatile ring_buffer r;
	} u;

} t_buffer;

/***** Enum Definitions **************************************************/

typedef enum _e_serial_flags {
	E_FLAGS_SERIAL_RX_INTERRUPT = 0x01,
	E_FLAGS_SERIAL_TX_INTERRUPT,
} e_serial_flags;

typedef enum _e_serial_speed {
	E_BAUD_2400 = 2400,
	E_BAUD_4800 = 4800,
	E_BAUD_9600 = 9600,
	E_BAUD_14400 = 14400,
	E_BAUD_19200 = 19200,
	E_BAUD_28800 = 28800,
	E_BAUD_38400 = 38400,
	E_BAUD_57600 = 57600,
	E_BAUD_76800 = 76800,
	E_BAUD_115200 = 115200,
	E_BAUD_LAST
} e_serial_speed;

typedef enum _MAC_addr {
	ID_1051C = 0x0013A20041B77594,
	ID_1053C = 0x0013A20041B77597,
	ID_1051R = 0x0013A20041B77570,
	ID_1053R = 0x0013A20041B77578,
} MAC_addr;

typedef enum _e_return {
	RET_OK = 0x00,
	RET_ERROR = 0x80,
	RET_ERROR_PARAMETER,
	RET_ERROR_RESOURCES
} e_return;

/***** Function Prototypes ***********************************************/

e_return serial_init(uint32_t a_speed);
void serial_install_interrupts(e_serial_flags a_flags);

#if SERIAL_IMPLEMENT_RX_INT == 1
unsigned char serial_available();
unsigned char serial_peek(void *a_data, unsigned char a_size);
unsigned int serial_recv(void *a_data, unsigned int a_size, unsigned char a_waitall);
unsigned char serial_getc(unsigned char *a_data);
#endif

unsigned char serial_poll_recv(unsigned char *a_data, unsigned int a_size);
unsigned char serial_poll_getc(unsigned char *a_data);

#if SERIAL_IMPLEMENT_TX_INT == 1
unsigned char serial_send(void *a_data, unsigned int a_size, unsigned char a_waitall);
unsigned char serial_sendc(unsigned char a_data);
#endif

unsigned int serial_poll_send(void *a_data, unsigned int a_size);
unsigned int serial_poll_sendc(unsigned char a_char);

#if SERIAL_IMPLEMENT_RX_INT == 1
volatile t_buffer* serial_get_rx_state();
#endif

#if SERIAL_IMPLEMENT_TX_INT == 1
volatile t_buffer* serial_get_tx_state();
#endif

void serial_flush();


/***** Declarations *******************************************************/

#if SERIAL_IMPLEMENT_RX_INT == 1
static volatile t_buffer g_rx_buff;
#endif

#if SERIAL_IMPLEMENT_TX_INT == 1
static volatile t_buffer g_tx_buff;
#endif

#endif /* UART_H_ */
