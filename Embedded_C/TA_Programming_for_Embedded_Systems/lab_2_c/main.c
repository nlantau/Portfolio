/***************************************************************************
 * Lab 2 - Timers and Counter
 *
 * Modified to use 5 IR-sensors that toggle 5 LEDs if value of 
 * IR-sensor is greater than a threshold. Play time with my son.
 *
 * python -m serial.tools.miniterm
 *
 * Created: 2022-02-22
 * Updated: 2022-02-24
 * Author : nlantau
 **************************************************************************/

/***** Include guard ******************************************************/
#define F_CPU 16000000UL

/***** Include section ****************************************************/
#include "lib/adc.h"
#include "lib/uart.h"
#include "lib/utils.h"
#include "lib/font.h"
#include "lib/oled.h"
#include "lib/i2cmaster.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>

/***** Macro Definitions **************************************************/
#define LAB2 0
#define PLAYTIME 1

/***** Function prototypes ************************************************/
void timer0_init(void);
void led_init(void);
void led_toggle(void);

/***** Constants **********************************************************/
static const uint16_t ONE_SEC = 7500;
static const uint8_t THRESHOLD = 200;

/***** Variables **********************************************************/
/* Since overflow_count is 16 bit, perhaps an atomic block is in order? */
static volatile uint16_t overflow_count = 0;


/***** MAIN ***************************************************************/
int main(void)
{
    stdout_init();
    uart_init();
    led_init();

#if PLAYTIME
    uint8_t i, j, adc_ports[5] = {0x00, 0x01, 0x02, 0x06, 0x07};
    uint16_t adc_value[5] = {0};
    char buff[10] = {0}, oled_buff[30] = {0};
    adc_init();
    lcd_init(0xAF);
    lcd_clrscr();

#endif /* PLAYTIME */

#if LAB2
    timer0_init();
    sei();
    printf("Start\n");
#endif /* LAB2 */

    for (;;) {
        asm volatile ("nop");
#if PLAYTIME

        for (i = 0; i < 5; ++i) {
            adc_read_to_array(adc_ports[i], adc_value, i);

            sprintf(buff, "%d", adc_value[i]);
            uart_puts(buff);
            uart_putc('\t');

            memset(buff, 0, 10);

        }
        uart_putc('\n');

        sprintf(oled_buff, "%3d,%3d,%3d,%3d,%3d", adc_value[0], adc_value[1], adc_value[2], adc_value[3], adc_value[4]);

        oled_puts("Niklas Lantau", 0, 0);
        oled_puts(oled_buff, 0, 2);
        _delay_ms(50);

#endif /* PLAYTIME */
    }

    return 0;

} /* End main() */


void led_init(void)
{
    DDRD |= (1 << PIND2) | (1 << PIND3) | (1 << PIND4) | (1 << PIND5) | (1 << PIND6);
    PORTD &= ~((1 << PIND2) | (1 << PIND3) | (1 << PIND4) | (1 << PIND5) | (1 << PIND6));

} /* End led_init() */

void led_toggle(void)
{
#if LAB2
    int i;
    printf("> Toggling LED: %s\n", PINB & (1 << PINB1) ? "Off" : "On");
    for (i = 0; i < 40; ++i) {
        printf("%c", uart_getc());
    }
    printf("\n");
#endif
    PORTD ^= (1 << PIND2) | (1 << PIND3) | (1 << PIND4) | (1 << PIND5) | (1 << PIND6);

} /* End led_toggle() */

void timer0_init(void)
{
    /* Timer/Counter0 Overflow Flag */
    TIFR0 |= (1 << TOV0);

    /* clk/8 prescaler */
    TCCR0B |= (1 << CS01);

    /* Timer/Counter 0 Overflow Interrupt Enable  */
    TIMSK0 |= (1 << TOIE0);

} /* End timer0_init() */

ISR(TIMER0_OVF_vect)
{

    overflow_count++;
    if (overflow_count == ONE_SEC) {
        led_toggle();
        overflow_count = 0;
    }

} /* End ISR() */

/* End main.c */

