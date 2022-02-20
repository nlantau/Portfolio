/***************************************************************************
 * OLED Source File
 *
 * Created: 2022-02-20
 * Updated: 2022-02-20
 * Author: nlantau
 **************************************************************************/

/***************************************************************************
 *  Info: See oled.h
 *
 **************************************************************************/

/***** Include section ****************************************************/
#include "oled.h"

/***** Functions **********************************************************/
void oled_putc(unsigned char p, uint8_t x, uint8_t y)
{
	lcd_gotoxy(x, y);
	i2c_start(LCD_I2C_ADR << 1);
	i2c_write(0x40);
	for (uint8_t i = 0; i < 7; i++)
		i2c_write(pgm_read_byte(&(FONT[(p - 65) + 33][i])));
	i2c_stop();

} /* End printer_putc() */

void oled_puts(char *s, uint8_t x, uint8_t y)
{
	while (*s)
		oled_putc(*s++, x++, y);

} /* End printer_puts() */

/* End oled.c */
