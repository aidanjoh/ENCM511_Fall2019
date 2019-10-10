/*
 * FrontPanel_LEDS_Switches.h
 *
 *  Created on: Aug 7, 2018
 *      Author: smithmr
 */

#ifndef FRONTPANEL_LEDS_SWITCHES_H_
#define FRONTPANEL_LEDS_SWITCHES_H_

typedef unsigned char FRONTPANEL_SWITCH_5BIT_VALUE;
void Init_GPIO_FrontPanelSwitches(void);
FRONTPANEL_SWITCH_5BIT_VALUE Read_GPIO_FrontPanelSwitches(void);

typedef unsigned char FRONTPANEL_LED_8BIT_VALUE;
void Init_GPIO_FrontPanelLEDS(void);
void Write_GPIO_FrontPanelLEDS(FRONTPANEL_LED_8BIT_VALUE frontPanelLEDvalue);
FRONTPANEL_LED_8BIT_VALUE Read_GPIO_FrontPanelLEDS(void);

#endif /* FRONTPANEL_LEDS_SWITCHES_H_ */
