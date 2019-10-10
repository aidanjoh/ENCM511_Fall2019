/*****************************************************************************
 * ADSP_BF609_Utilities_Library_Core0.h
 *****************************************************************************/

#ifndef __ADSP_BF609_UTILITIES_LIBRARY_H__
#define __ADSP_BF609_UTILITIES_LIBRARY_H__

#include <stdint.h>

unsigned long long int ReadCycles(void);
void SetBoardLED_SPI_ConfigSoftSwitches(void);
int32_t Smith_adi_initpinmux(void);

#endif /* __ADSP_BF609_UTILITIES_LIBRARY_H__ */
