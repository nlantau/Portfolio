/***************************************************************************
 * Main Header
 *
 * Module information:
 *	- ADC for input of JoyStick data
 *	- UART for sending converted ADC value to a receiving unit
 *	  PWM values in receiving unit
 *
 *  Created: 2020-09-13
 *  Updated: 2020-10-16
 *  Author  nlantau
 **************************************************************************/

/***** Include guard ******************************************************/

#ifndef MAIN_TX_H_
#define MAIN_TX_H_
#ifndef F_CPU
#define F_CPU 16000000UL

/***** Include section ****************************************************/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include "lib/adc.h"
#include "lib/manipulateArray.h"

#if LCD
#include "lib/lcd.h"
#include "lib/i2cmaster.h"
#include "lib/font.h"
#include "lib/uart.h"
#endif /* LCD */

/***** Function prototypes ************************************************/

void collision_detected(void);
void send_adc(char direction, int analogport);
void reset_collision_detected(void);
void poll_collision_detected(void);

#if LCD
void printer_puts(char *text, int x, int y);
void printer_putc(unsigned char p, int x, int y);
void print_button_pressed(void);
void update_oled_joystick(char direction, int analogport);
void oled_putc(unsigned char p, int x, int y);
void oled_puts(char *s, int x, int y);
#endif /* LCD */
#endif /* F_CPU */
#endif /* MAIN_TX_H_ */