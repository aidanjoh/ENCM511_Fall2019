/*****************************************************************************
 * GP_Timer.h
 *****************************************************************************/

#ifndef __GP_TIMER_H__
#define __GP_TIMER_H__

typedef unsigned char GP_TIMER;
void Init_GP_Timer(GP_TIMER whichGPTimer);
void Start_GP_Timer(GP_TIMER whichGPTimer);

unsigned long int ReadWidth_GP_Timer(GP_TIMER whichGPTimer);
unsigned long int ReadPeriod_GP_Timer(GP_TIMER whichGPTimer);

bool IsReady_GP_Timer(GP_TIMER whichGPTimer);

#endif /* __GP_TIME_H__ */
