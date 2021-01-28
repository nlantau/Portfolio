/***************************************************************************
 * Remote UART Prototype Source File
 *
 * Module information: Testing remote prototype
 *  TX two ADC values to Robot
 *  ADC_X is modified -> ADC += 3000
 *  ADC_Y is modified -> ADC += 1000
 *      Easier to separate values in Robot
 *
 *  RX '1' == LED on Remote turns on (collision sent by Robot)
 **************************************************************************/

/***** Macro Definitions **************************************************/

#define LCD 0 /* Needs to be first due to usage in main.h */

/***** Include section ****************************************************/

#include "main.h"

/***** Constants **********************************************************/

static const int BUFSIZE = 10;

/***** Entry point ********************************************************/

int main(void)
{
#if LCD
    lcd_init(0xAF);
    lcd_clrscr();
#endif

    adc_init();
    uart_init();

    while (1)
    {
        /* Transmit ADC values */
        send_adc('X', 0);
        send_adc('Y', 1);

        /* Poll collision-detected */
        poll_collision_detected();

        /* Button press - resets LED */
        if (PIND & (1 << PIND2))
        {
            reset_collision_detected();
        }

    } /* end of while(1) */

} /* End main() */

/***** TEST - Collision detected ******************************************/

void poll_collision_detected(void)
{
    char rx = UDR0;
    if (rx == '1')
    {
        UCSR0B &= ~(1 << RXEN0);

        collision_detected();

        UCSR0B |= (1 << RXEN0);
    }
}
void collision_detected(void)
{
    _delay_ms(200);
    DDRB |= (1 << PINB2);
    PORTB |= (1 << PINB2);

} /* End collision_detected() */

void reset_collision_detected(void)
{
    _delay_ms(200);
    DDRB |= (1 << PINB2);
    PORTB &= ~(1 << PINB2);

} /* End reset_collision_detected() */

void send_adc(char direction, int analogport)
{
    int modADC = adc_read_(analogport);
    if (direction == 'X')
    {
        modADC += 3000;
        uart_sendCharacter('X'); // This took too long to figure out
    }
    else if (direction == 'Y')
    {
        uart_sendCharacter('Y');
        modADC += 1000;
    }

    char _buffer[BUFSIZE]; /* _buffer will have the converted ADC string */
    snprintf(_buffer, BUFSIZE, "%d", modADC);
    manipulateArray_digitsToStringFillEmptyWithSpace(BUFSIZE, _buffer);

    uart_sendString(_buffer);
    uart_sendCharacter('\r');

} /* End send_adc() */

#if LCD
/***** OLED ***************************************************************/

void print_button_pressed(void)
{
    _delay_ms(50);

    lcd_clrscr();
    printer_puts("Button Pressed!", 2, 4);

    _delay_ms(1000);
    lcd_clrscr();

} /* End print_button_pressed() */

/***** OLED ***************************************************************/

void printer_putc(unsigned char p, int x, int y)
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

void printer_puts(char *s, int x, int y)
{
    while (*s)
        printer_putc(*s++, x++, y);

} /* End printer_puts() */

/***** Update OLED ********************************************************/

void update_oled_joystick(char direction, int analogport)
{
    int modADC = adc_read_(analogport);
    char _buf[BUFSIZE]; /* _buffer will have the converted ADC string */
    snprintf(_buf, BUFSIZE, "%d", modADC);
    manipulateArray_digitsToStringFillEmptyWithSpace(BUFSIZE, _buf);

    (direction == 'X') ? printer_puts(_buf, 2, 0) : printer_puts(_buf, 2, 1);

} /* End update_oled_joystick() */
#endif /* LCD */