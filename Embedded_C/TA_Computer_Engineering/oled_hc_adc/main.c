/***************************************************************************
 *  Lap Counter DT1010C
 *  - Modified for menu-system (based on ADC-value)
 *  - Menu option for displaying pictures
 *  - Menu option for Lap Counter
 *  
 * 
 *  Created: 2020-10-23
 *  Updated: 2020-06-11
 *   Author: nlantau
 **************************************************************************/

/***** Include guard ******************************************************/

#ifndef F_CPU
#define F_CPU 16000000UL
#endif /* F_CPU */

/***** Include section ****************************************************/

#include "lib/ultrasonic.h"
#include "lib/font.h"
#include "lib/i2cmaster.h"
#include "lib/lcd.h"
#include "lib/adc.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>

/***** Macro Definitions **************************************************/

/***** Function prototypes ************************************************/

void init_pullup_pinD2(void);
void printer_puts(char *s, uint8_t x, uint8_t y);
void printer_putc(unsigned char p, uint8_t x, uint8_t y);
void timer0_init(void);
void print_pic(const unsigned char *arr);
void print_pic_switch(void);
void lap_counter_mode(void);
void print_kg(void);
void print_hkr(void);


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
    ultrasonic_init_INT0();
    ultrasonic_init_trig_echo();
    ultrasonic_init_timer2();
    timer0_init();
    adc_init();
    sei();

    DDRD &= ~(1 << PIND4);
    PORTD |= (1 << PIND4);

    unsigned char adc_val;


    while (1)
    {
        /*
        Implement a menu. Switch menu option with switches
        that are connected to ADC. 

        2-bit R-2R ladder (2 switches -> 4 different voltages),
        depending on Vin to ADC -> change menu option

        Voltage  10-bit ADC value
        0.00V -> 000 ADC
        1.29V -> 264 ADC
        2.58V -> 528 ADC
        3.87V -> 792 ADC

        */
        adc_val = adc_read_(0);

        //printer_putc(adc_val, 0, 0);

        //print_pic(&black);
        switch(adc_val)
        {
            case 0 ... 55:
                print_kg();
                break;
            case 56 ... 126:
                lap_counter_mode();
                break;
            case 127 ... 190:
                print_pic_switch();
                break;
            case 191 ... 255:
                print_hkr();
                break;

        }

    }
} /* End main() */

void print_kg(void)
{
    print_pic(&black);
    while (adc_read_(0) < 60)
        print_pic(&kg);
}

void print_hkr(void)
{
    print_pic(&black);
    while ( (adc_read_(0) < 256) && (adc_read_(0) > 190))
        print_pic(&hkr_logo_two);
}

void lap_counter_mode(void)
{
    print_pic(&black);
    millis = 0;
    seconds = 0;
    minutes = 0;
    overflow_count = 0;
    lap_counter = 0;
    while((adc_read_(0) < 127) && (adc_read_(0) > 60))
    {

        char buf[20];
        sprintf(buf, "T: %2d:%2d:%2d", minutes, seconds, millis);

        printer_puts("Niklas Lantau", 0, 0);
        printer_puts(buf, 0, 2);
        do
        {
            ultrasonic_sendTrigPulse();
            printer_puts("Niklas Lantau", 0, 0);
            printer_puts(buf, 0, 2);

            if (resulter < SENSOR_DIST)
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

                if (lap_counter == 2)
                {
                    printer_puts("Finished      ", 0, 0);
                    printer_puts("      ", 0, 6);
                    printer_puts(buf, 0, 2);

                    _delay_ms(2000);

                    /* Restore counters */
                    millis = 0;
                    seconds = 0;
                    minutes = 0;
                    overflow_count = 0;
                    lap_counter = 0;

                    while((adc_read_(0) < 127) && (adc_read_(0) > 60))
                    {
                    print_pic(&beer);
                    _delay_ms(200);
                    print_pic(&beer2);
                    _delay_ms(200);
                    print_pic(&beer3);
                    _delay_ms(200);
                    print_pic(&beer4);
                    _delay_ms(200);
                    print_pic(&kg);
                    _delay_ms(2000);

                    }

                }
            }

        } while ((lap_counter == 0) && (adc_read_(0) < 127) && (adc_read_(0) > 60));
    }
    print_pic(&black);
    millis = 0;
    seconds = 0;
    minutes = 0;
    overflow_count = 0;
    lap_counter = 0;
}


void print_pic_switch(void) 
{
    print_pic(&black);
    while ((adc_read_(0) < 191) && (adc_read_(0) > 126))
    {
        switch (counter)
        {
        case 0:
            print_pic(&BR);
            break;
        case 1:
            print_pic(&beer);
            break;
        case 2:
            print_pic(&beer2);
            break;
        case 3:
            print_pic(&beer3);
            break;
        case 4:
            print_pic(&beer4);
            break;
        case 5:
            print_pic(&beer3);
            break;
        case 6:
            print_pic(&beer2);
            break;
        case 7:
            print_pic(&beer);
            break;
        case 8:
            print_pic(&kg);
            break;
        case 9:
            print_pic(&HKR_logo);
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
    }
}

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
