/***************************************************************************
 * Utils Header File
 *
 * Created: 2022-02-19
 * Updated: 2022-02-19
 * Author: nlantau
 **************************************************************************/

/***************************************************************************
 *  Info:
 *
 **************************************************************************/

/***** Include guard ******************************************************/
#ifndef UTILS_H_
#define UTILS_H_

/***** Include section ****************************************************/
#include <avr/io.h>

/***** Macro Definitions **************************************************/
#define sbi(var, mask) ((var) |= (uint8_t)(1 << mask))
#define cbi(var, mask) ((var) &= (uint8_t)~(1 << mask))

/***** Function prototypes ************************************************/
extern void delay_ms(uint16_t x);


#endif /* UTILS_H_ */

