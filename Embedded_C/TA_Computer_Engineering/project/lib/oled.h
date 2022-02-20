/***************************************************************************
 * OLED Header File
 *
 * Created: 2022-02-20
 * Updated: 2022-02-20
 * Author: nlantau
 **************************************************************************/

/***************************************************************************
 *  Info: 
 *
 **************************************************************************/

/***** Include guard ******************************************************/
#ifndef OLED_S_H_
#define OLED_S_H_

/***** Include section ****************************************************/
#include "lcd.h"
#include "font.h"
#include <avr/io.h>

/***** Macro Definitions **************************************************/

/***** Function prototypes ************************************************/
extern void oled_puts(char *s, uint8_t x, uint8_t y);
extern void oled_putc(unsigned char p, uint8_t x, uint8_t y);

#endif /* OLED_S_H_ */

