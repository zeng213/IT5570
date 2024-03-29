/*-----------------------------------------------------------------------------
 * TITLE: CORE_MAIN.H
 * 
 * Copyright (c) 1983-2007, Insyde Software Corporation. All Rights Reserved.
 *
 * You may not reproduce, distribute, publish, display, perform, modify, adapt,
 * transmit, broadcast, present, recite, release, license or otherwise exploit
 * any part of this publication in any form, by any means, without the prior
 * written permission of Insyde Software Corporation.
 *---------------------------------------------------------------------------*/
 
#ifndef CORE_MAIN_H
#define CORE_MAIN_H 

#define Only_Timer1msEvent  0x01
#define All_TimerEvent      0x00

#define Normal_MainService  0xFF
 
extern void main(void);
extern void main_service(void);
extern void service_unlock(void);
extern void service_Low_LVEvent(void);

extern void service_1mS(void); 
extern void Timer1msEvent(void);
extern void Timer5msEvent(void);
extern void Timer10msEventA(void);
extern void Timer10msEventB(void);
extern void Timer50msEventA(void);
extern void Timer50msEventB(void);
extern void Timer50msEventC(void);
extern void Timer100msEventA(void);
extern void Timer100msEventB(void);
extern void Timer100msEventC(void);
extern void Timer500msEventA(void);
extern void Timer500msEventB(void);
extern void Timer500msEventC(void);
extern void Timer1SecEventA(void);
extern void Timer1SecEventB(void);
extern void Timer1SecEventC(void);
extern void Timer1MinEvent(void);

#endif  

