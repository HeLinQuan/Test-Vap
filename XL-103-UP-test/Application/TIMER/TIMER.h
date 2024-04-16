/******************* (C) COPYRIGHT 2009~2017 holychip **************************
* File Name          : TIMER.h
* Author             : Taboo.Z¤Z
* Version            : V1.00
* Date               : 9/12/2017
********************************************************************************


*******************************************************************************/
#ifndef __TIMER_H__
#define __TIMER_H__
#include "define.h"


#define	T0_MS                1  //ms max 2.048ms
#define	T0_XMS			        (u16)(65536-(SYSCLK_FOSC/1000*T0_MS))

#define TH0_DF         	0XFA	//	(T0_XMS/256)
#define TL0_DF         	0XCB	//	(T0_XMS%256)
#define	TIMER0_COUNT_INIT		TH0=TH0_DF ; TL0=TL0_DF

#define TIMER0_EN       	(TR0 = 1)
#define TIMER0_DIS 		 		(TR0 = 0)
#define CLR_TIMER0_TF0 		(TF0 = 0)


extern bit F_1MS; 
extern bit F_10MS;
extern bit F_100MS; 
extern bit F_500MS;
extern bit F_1SEC; 
extern bit F_1MIN;
extern bit F_1HOUR;

extern bit F_PN_500MS;

extern unsigned char xdata work_10min ; 
extern unsigned int xdata  work1_hour , work2_hour,work3_hour , work4_hour, work5_hour;
//===============================================================================


void TIMR1_ISR_Handle();
void TIMER0_Init(void);
void TIMER1_Init(void);

void delay_us( unsigned char  count);
void delay_ms( unsigned char  count);
void TIMER_SCAN(void);
void ParamTimtInit(void);
#endif /* __TIMER_H__ */
