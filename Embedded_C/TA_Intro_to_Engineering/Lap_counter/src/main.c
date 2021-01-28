/***************************************************************************
 *  Lap Counter DT1010C
 *  
 * 
 *  Created: 2020-10-23
 *  Updated: 2020-10-25
 *   Author: nlantau
 **************************************************************************/

/***** Include guard ******************************************************/

#ifndef F_CPU
#define F_CPU 16000000UL
#endif /* F_CPU */

/***** Include section ****************************************************/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include "lib/ultrasonic.h"
#include "lib/font.h"
#include "lib/i2cmaster.h"
#include "lib/lcd.h"

/***** Macro Definitions **************************************************/

/***** Function prototypes ************************************************/

void init_pullup_pinD2(void);
void printer_puts(char *s, uint8_t x, uint8_t y);
void printer_putc(unsigned char p, uint8_t x, uint8_t y);
void timer0_init(void);
void print_pic(const unsigned char *arr);

/***** Constants **********************************************************/
const uint8_t ONE_SEC = 7500;
const uint8_t SENSOR_DIST = 14;

/***** Variables **********************************************************/

volatile uint8_t overflow_count = 0;
volatile uint8_t millis = 0;
volatile uint8_t seconds = 0;
volatile uint8_t minutes = 0;
volatile uint8_t lap_counter = 0;
volatile uint8_t counter = 0;

/***** MAIN ***************************************************************/

int main(void)
{
    lcd_init(0xAF);
    lcd_clrscr();
    ultrasonic_initINT0();
    ultrasonic_initTrigEcho();
    ultrasonic_initTimer2();
    timer0_init();
    sei();

    DDRD &= ~(1 << PIND4);
    PORTD |= (1 << PIND4);

    while (1)
    {
        switch (counter)
        {
        case 0:
            print_pic(&niklas_lantau);
            break;
        case 1:
            print_pic(&hkr_logo_two);
            break;
        case 2:
            print_pic(&slak_2020);
            break;
        case 3:
            print_pic(&got_one);
            break;
        case 4:
            print_pic(&BR);
            break;
        case 5:
            print_pic(&python_one);
            break;
        case 6:
            print_pic(&nazila);
            break;
        case 7:
            print_pic(&collision_one);
            break;
        case 8:
            print_pic(&team_one);
            break;
        case 9:
            print_pic(&kungen);
            break;
        }

        if (!(PIND & (1 << PIND4)))
        {
            _delay_ms(80);
            counter++;
        }
        if (counter > 9)
        {
            counter = 0;
        }

        char buf[20];
        sprintf(buf, "T: %2d:%2d:%2d", minutes, seconds, millis);

        printer_puts("Niklas Lantau", 0, 0);
        printer_puts(buf, 0, 2);
        do
        {
            ultrasonic_sendTrigPulse();
            printer_puts("Niklas Lantau", 0, 0);
            printer_puts(buf, 0, 2);

            if (result < SENSOR_DIST)
            {

                printer_puts("Lap 1", 0, 6);
                if (lap_counter == 0)
                {
                    millis = 0;
                    seconds = 0;
                    minutes = 0;
                    overflow_count = 0;
                }

                lap_counter++;

                if (lap_counter == 1)
                    _delay_ms(2000);

                while (lap_counter == 2)
                {
                    printer_puts("Finished      ", 0, 0);
                    printer_puts("      ", 0, 6);
                    printer_puts(buf, 0, 2);
                }
            }

        } while (lap_counter == 0);
    }
} /* End main() */

void print_pic(const unsigned char *arr)
{
    int counter = 0;
    for (uint8_t a = 0; a < 8; a++)
    {
        lcd_gotoxy(0, a);
        i2c_start(LCD_I2C_ADR << 1);
        i2c_write(0x40);

        for (uint8_t b = 0; b < 128; b++)
        {
            i2c_write(pgm_read_byte(&arr[counter]));
            counter++;
        }

        i2c_stop();
    }
}
/***** TIMER **************************************************************/

void timer0_init(void)
{
    /* Timer Overflow Interrupt Enable  */
    TIMSK0 |= (1 << TOIE0);

    /* Timer Overflow Flag */
    TIFR0 |= (1 << TOV0);

    /* 1024 prescaler */
    TCCR0B |= (1 << CS01);

} /* End pwm_init() */

ISR(TIMER0_OVF_vect)
{

    overflow_count++;
    if (overflow_count == ONE_SEC)
    {
        millis++;
        overflow_count = 0;
        if (millis == 100)
        {
            millis = 0;
            seconds++;
            counter++;
        }
        if (seconds == 60)
        {
            seconds = 0;
            minutes++;
        }
    }

} /* End ISR() */

/***** OLED ***************************************************************/

void printer_putc(unsigned char p, uint8_t x, uint8_t y)
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

void printer_puts(char *s, uint8_t x, uint8_t y)
{
    while (*s)
    {
        printer_putc(*s++, x++, y);
    }

} /* End printer_puts() */
