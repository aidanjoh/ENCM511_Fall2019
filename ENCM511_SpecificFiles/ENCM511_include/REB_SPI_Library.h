/*****************************************************************************
 * REB_SPI_Library.h
 *****************************************************************************/

#ifndef __REB_SPI_LIBRARY_H__
#define __REB_SPI_LIBRARY_H__

/* Add your custom header content here */
// #include "H:\ENCM511_Fall2018\ADSP_BF609_Utilities_Library_Core0\src\ADSP_BF609_Utilities_Library_Core0.h"

#include "../../ADSP_BF609_Utilities_Library/src/ADSP_BF609_Utilities_Library.h"

void SetBoardLED_SPI_ConfigSoftSwitches(void);
void Init_REB_SPI(void);
void Start_REB_SPI(void);
void Stop_REB_SPI(void);
bool REB_SPI_Ready(void);

void REB_Write_SPI(unsigned long int writeSPIValue);
unsigned long int REB_Read_SPI(void);

#endif /* __REB_SPI_LIBRARY_H__ */
