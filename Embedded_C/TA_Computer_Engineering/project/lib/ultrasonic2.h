/***************************************************************************
 *  Ultrasonic 2 Header
 *
 *
 *  Created: 2022-02-20
 *  Updated: 2022-02-20
 *  Author : Mattias Ahle
 *  Updated: nlantau
 **************************************************************************/

/***** Include guard ******************************************************/

#ifndef ULTRASONIC_2_H_
#define ULTRASONIC_2_H_
#ifndef F_CPU
#define F_CPU 16000000UL
#endif

/***** Include section ****************************************************/
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>


/***** Macro Definitions **************************************************/
#define trig_pin PINB1
#define echo_pin PIND3

/***** Function prototypes ************************************************/
extern void hc_sr04_init(void);
extern uint16_t hc_sr04_distance(void);

#endif /* ULTRASONIC_2_H_ */

