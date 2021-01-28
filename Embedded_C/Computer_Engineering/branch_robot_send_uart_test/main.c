/***************************************************************************
 *  Robot UART Prototype Source File
 *  
 *  FOR UART TESTING PURPOSE ONLY
 *  RX two ADC values and sets motor speed on Left and Right motor
 *  Kills Robot if collision is detected (simulated by button press)
 *
 *	Created: 2020-10-13
 *  Updated: 2020-10-16
 *  Author: nlantau
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

/***** Macro Definitions **************************************************/

#define ROBOT_KILL 1

/***** Function prototypes ************************************************/

void set_pullup_on_PIND2(void);
void poll_collision_detection(void);
void poll_ADC_values(void);
void pwm_init(void);
void adjust_received_adc(char *int_buf, char *buf);
void adjust_motor_speed(char dir, char *rx_adc_buf, char *int_buf);

/***** Constants **********************************************************/

static const int BUFSIZE = 10;

/***** MAIN ***************************************************************/

int main(void)
{
    uart_init();
    pwm_init();
    //set_pullup_on_PIND2();

    DDRD |= (1 << PIND2);
    DDRD |= (1 << PIND4);

    DDRD |= (1 << PIND7);
    DDRB |= (1 << PINB0);

    PORTD |= (1 << PIND4);
    PORTD |= (1 << PIND7);

    PORTD &= ~(1 << PIND2);
    PORTB &= ~(1 << PINB0);

    while (1)
    {
        poll_ADC_values();
        // poll_collision_detection();

        //OCR0A = 150;
        //OCR0B = 150;
    }
}

/***** Pull down PIND2 simulates collision ********************************/

void set_pullup_on_PIND2(void)
{
    DDRD &= ~(1 << PIND2);
    PORTD |= (1 << PIND2);

} /* End set_pullup_on_PIND2() */

void poll_collision_detection(void)
{
    if (!(PIND & (1 << PIND2)))
    {
        UCSR0B |= (1 << TXEN0);
        UDR0 = '1';
        _delay_ms(10);
        UCSR0B &= ~(1 << TXEN0);
/* Collision kills robot */
#if ROBOT_KILL
        while (1)
        {
            OCR0A = 0;
            OCR0B = 0;
        }
#endif
    }

} /* End poll_collision_detection() */

void poll_ADC_values(void)
{
    char buf[BUFSIZE];
    char int_buf[BUFSIZE];

    char direction = uart_getc();
    if (direction == 'X')
    {
        adjust_motor_speed(direction, buf, int_buf);
    }
    else if (direction == 'Y')
    {
        adjust_motor_speed(direction, buf, int_buf);
    }
    else
    {
        // Empty
    }

} /* End poll_ADC_values() */

/***** Adjust - Motors ***************************************************/

void adjust_motor_speed(char dir, char *rx_adc_buf, char *int_buf)
{
    int motor_speed;

    uart_getString(rx_adc_buf, BUFSIZE);
    adjust_received_adc(int_buf, rx_adc_buf);

    /* Parse char arr to integer */
    motor_speed = atoi(int_buf);

    /* ADC is modified in Remote:
     * ADC_X += 3000
     * ADC_Y += 1000
     * This is to make it easier to separate the values */
    (dir == 'X') ? (motor_speed -= 3000) : (motor_speed -= 1000);

    /* map 10-bit to 8-bit */
    motor_speed /= 4;

    /* Set OCR0A or OCR0B */
    (dir == 'X') ? (OCR0A = motor_speed) : (OCR0B = motor_speed);

} /* End adjust_motor_speed() */

/***** Manipulate buffers ************************************************/

void adjust_received_adc(char *int_buf, char *buf)
{
    if (buf[0] != '\0')
        for (size_t i = 0; i < 5; i++)
        {
            int_buf[i] = buf[i];
        }
    int_buf[5] = '\0';

} /* End adjust_received_adc() */

/***** Initialize PWM for motors *****************************************/

void pwm_init(void)
{
    /* Output on PIND5, PIND6 */
    DDRD |= (1 << PIND5) | (1 << PIND6);

    /* Clear OC0A and OC0B on compare match, fast PWM */
    TCCR0A = (1 << COM0B1) | (1 << COM0A1) | (1 << WGM01) | (1 << WGM00);

    /* 1024 prescaler */
    TCCR0B = (1 << CS00) | (1 << CS02);

} /* End pwm_init() */
