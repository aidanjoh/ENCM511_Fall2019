/*****************************************************************************
 * Lab0_BF533_MOCKEDLEDandSwitches.h
 *****************************************************************************/

#ifndef __LAB0_BF533_MOCKEDLEDANDSWITCHES_H__
#define __LAB0_BF533_MOCKEDLEDANDSWITCHES_H__

/* Add your custom header content here */

//Prototypes

void Start_Lab0(void);
void My_Init_LEDInterface(void);
unsigned char My_ReadLED(void);
void My_Init_SwitchInterface(void);
unsigned char My_ReadSwitches(void);
void My_WriteLED(unsigned char);
void charToBinary(unsigned char, unsigned char*);


#endif /* __LAB0_BF533_MOCKEDLEDANDSWITCHES_H__ */
