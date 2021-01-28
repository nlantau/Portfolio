/***************************************************************************
 *  Remote UART 8 bit Prototype Source File
 *  
 *  Test module for UART 8-bit
 *    + Testing ADCH 8-bit ADC values as char
 * 
 *  Created: 2020-10-17
 *  Updated: 2020-10-17
 *   Author: nlantau
 **************************************************************************/

/***** Include guard ******************************************************/

#ifndef F_CPU
#define F_CPU 16000000UL
#endif /* F_CPU */

/***** Include section ****************************************************/

#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>
#include <stdlib.h>
#include "lib/adc.h"
#include "lib/uart.h"
#include "lib/font.h"
#include "lib/i2cmaster.h"
#include "lib/lcd.h"

/***** Macro Definitions **************************************************/

/***** Function prototypes ************************************************/

void pwm_algo_config_0_0_1(unsigned char *right_motor, unsigned char *left_motor);
void transmit_motor_values(unsigned char *right_motor, unsigned char *left_motor);
static void printer_puts(char *s, uint8_t x, uint8_t y);
static void printer_putc(unsigned char p, uint8_t x, uint8_t y);
static void init_pullup_pinD2(void);
//static void establish_remote_connection(void);

/***** Constants **********************************************************/

static const uint8_t MOTOR_DIR = 1;
static const uint8_t MOTOR_CHOICE = 0;
static const uint8_t HANDSHAKE_BYTE = 0xFF;

/***** TODO ****************************************************************
 * 
 * 
 * ************************************************************************/

/***** MAIN ***************************************************************/

int main(void)
{
    uart_init();
    adc_init();
    lcd_init(0xAF);
    lcd_clrscr();
    init_pullup_pinD2();

    while (1)
    {
        unsigned char adc_x = adc_read_(0);
        unsigned char adc_y = adc_read_(1);

        /* Handshake byte */
        if (PIND & (1 << PIND2))
        {
            UDR0 = HANDSHAKE_BYTE;
            _delay_ms(200);
            DDRB |= (1 << PINB2);
            PORTB |= (1 << PINB2);
        }
        else if (!(PIND & (1 << PIND2)))
        {
            PORTB &= ~(1 << PIND2);
        }


        /* Print x- and y-values on OLED */
        printer_puts("X: ", 0, 0);
        printer_puts("Y: ", 0, 0);

        /* Modify bytes to transmit */
        pwm_algo_config_0_0_1(&adc_x, &adc_y);

        /* Transmit motor values */
        transmit_motor_values(&adc_x, &adc_y);
    }
}

void transmit_motor_values(unsigned char *right_motor, unsigned char *left_motor)
{
    UDR0 = *right_motor;
    _delay_ms(10);
    UDR0 = *left_motor;
    _delay_ms(10);
}

/***** Information *********************************************************
 *  function:  pwm_algo_config_0_0_1()
 *  called by: main()
 *  param 1:   pointer to adc_x
 *  param 2:   pointer to adc_y
 *  returns:   void
 *  
 *  Description
 *  - Motor direction:
 *  + Sets bit 1 if motor direction should be forwards
 *  + Unsets bit 1 if motor direction should be backwards
 *
 *  - Motor choice: 
 *  + Sets LSB for Left motor
 *  + Unsets LSB for Right motor
 *  +
 * 
 *  This function should be used as a template for creating
 *  the final differential steering algorithm
 * ************************************************************************/
void pwm_algo_config_0_0_1(unsigned char *right_motor, unsigned char *left_motor)
{
    /* Check if y > 127 = set fw else set bw */
    if (*left_motor > 115)
    {
        /* Set forward y-axis */
        *left_motor |= (1 << MOTOR_DIR);
    }
    else if (*left_motor < 115)
    {
        /* Set backward y-axis */
        *left_motor &= ~(1 << MOTOR_DIR);
    }

    if (*right_motor > 115)
    {
        /* Set forward x-axis */
        *right_motor |= (1 << MOTOR_DIR);
    }
    else if (*right_motor < 115)
    {
        /* Set backward x-axis */
        *right_motor &= ~(1 << MOTOR_DIR);
    }

    /* Set Left or Right (LSB: Left = 1, Right = 0) */
    *right_motor = (*right_motor & 0xFE);
    *right_motor &= ~(1 << MOTOR_CHOICE);

    *left_motor = (*left_motor & 0xFE);
    *left_motor |= (1 << MOTOR_CHOICE);
}

/***** OLED ***************************************************************/

static void printer_putc(unsigned char p, uint8_t x, uint8_t y)
{
    lcd_gotoxy(x, y);
    i2c_start(LCD_I2C_ADR << 1);
    i2c_write(0x40);
    for (uint8_t i = 0; i < 7; i++)
    {
        i2c_write(pgm_read_byte(&(FONT[(p - 65) + 33][i])));
    }
    i2c_stop();

} /* End printer_putc() */

static void printer_puts(char *s, uint8_t x, uint8_t y)
{
    while (*s)
    {
        printer_putc(*s++, x++, y);
    }

} /* End printer_puts() */

/***** REMOTE CONNECTION **************************************************/

#if 0 /* Might be useful */
static void establish_remote_connection(void)
{
    do
    {

    } while (!(UDR0 & HANDSHAKE_BYTE));

} /* End establish_remote_connection() */
#endif

static void init_pullup_pinD2(void)
{
    DDRD &= ~(1 << PIND2);
    PORTD |= (1 << PIND2);

} /* End init_pullup_pind2() */