/*
 * Board_LEDS_Switches.h
 *
 *  Created on: Aug 7, 2018
 *      Author: smithmr
 */

#ifndef BOARD_LEDS_SWITCHES_H_
#define BOARD_LEDS_SWITCHES_H_

typedef unsigned char BOARD_SWITCH_2BIT_VALUE;
void Init_GPIO_BoardSwitches(void);
BOARD_SWITCH_2BIT_VALUE Read_GPIO_BoardSwitches(void);

typedef unsigned char BOARD_LED_4BIT_VALUE;
void Init_GPIO_BoardLEDS(void);
void Write_GPIO_BoardLEDS(BOARD_LED_4BIT_VALUE boardLEDValue);
BOARD_LED_4BIT_VALUE Read_GPIO_BoardLEDS(void);

#endif /* BOARD_LEDS_SWITCHES_H_ */
