/*****************************************************************************
 * Lab4_BF609_Core0.h
 *****************************************************************************/

#ifndef __LAB4_BF609_CORE0_H__
#define __LAB4_BF609_CORE0_H__

/* Add your custom header content here */
#include <stdint.h>
#include "../../ENCM511_SpecificFiles/ENCM511_include/REB_SPI_Library.h"
#include "../../ENCM511_SpecificFiles/ENCM511_include/GP_Timer_Library.h"
#include <stdio.h>

void SetBoardLED_SPI_ConfigSoftSwitches(void);
int32_t Smith_adi_initpinmux(void);
void startLab4(void);

#endif /* __LAB4_BF609_CORE0_H__ */
