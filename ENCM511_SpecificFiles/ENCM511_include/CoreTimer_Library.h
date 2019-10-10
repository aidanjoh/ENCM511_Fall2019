/*****************************************************************************
 * CoreTimer_Library.h
 *****************************************************************************/

#ifndef __CORETIMER_LIBRARY_H__
#define __CORETIMER_LIBRARY_H__

/* Add your custom header content here */

void Init_CoreTimer(unsigned long int period, unsigned long int count);

void Control_CoreTimer(unsigned short int cntrl_value) ;

bool Completed_CoreTimer(void);

void TimedWaitOnCoreTimer(void) ;

#endif /* __CORETIMER_LIBRARY_CORE0_H__ */
