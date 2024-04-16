/******************* (C) COPYRIGHT 2009~2017 holychip **************************
* File Name          : TIMER.c
* Author             : Taboo.Z
* Version            : V1.00
* Date               : 9/12/2017
********************************************************************************


*******************************************************************************/
#include "define.h"


unsigned char xdata TIMER_1MS=0, TIMER_10MS=0, TIMER_100MS=0, TIMER_500MS=0, TIMER_1SEC=0, TIMER_1MIN=0, TIMER_1HOUR=0;

unsigned char xdata work_10min ; 
unsigned int xdata  work1_hour , work2_hour,work3_hour , work4_hour, work5_hour;

bit F_1MS; 
bit F_10MS;
bit F_100MS; 
bit F_500MS;
bit F_1SEC; 
bit F_1MIN;
bit F_1HOUR;

bit F_PN_500MS;
//===============================================================================
void ParamTimtInit(void)
{
    F_1MS    = 0 ; 
    F_10MS   = 0 ;
    F_100MS  = 0 ; 
    F_500MS  = 0 ;
    F_1SEC   = 0 ; 
    F_1MIN   = 0 ;
    F_1HOUR  = 0 ;
    F_PN_500MS = 0;
}

void TIMER0_Init(void)
{
	TIMER0_DIS;
	CLR_TIMER0_TF0;
	TCON1 |= bmT0X12;		    //1FP
	TMOD &= ~(bmBIT1 | bmBIT0);			//FS0
	TIMER0_COUNT_INIT;
	ET0 = 1;
	TIMER0_EN;
}


void TIMER1_Init(void)
{
 /**********************************TIM1配置初始化**************************************/
	TCON1 = 0x00;						//T1定时器时钟为Fosc
	TMOD = 0x00;						//16位重装载定时器/计数器

	//Tim1计算时间 	= (65536 - 0xFACB) * (1 / (Fosc /Timer分频系数))
	//				= 1333 / (16000000 / 12)
	//				= 1 ms

	//定时1ms
	//反推初值 	= 65536 - ((1/1000) / (1/(Fosc / Timer分频系数)))
	//		   	= 65536 - ((1/1000) / (1/(16000000 / 12)))
	//			= 65536 - 166
	//			= 0xFF5A
	
	TH1 = 0xFF;
	TL1 = 0x5A;
	IE |= 0x08;							//打开T1中断
	TCON |= 0x40;						//使能T1
	EA = 1;								//打开总中断
 }

void delay_us( unsigned char  count)
{
	unsigned char   i ;
	for(i=0 ; i<count ; i++)
	{
		  ;
	}
}
void delay_ms( unsigned char  count)
{
	unsigned char   i ;
	for(i=0 ; i<count ; i++)
	{
     	 delay_us( 100)	 ;	 	
		 CLR_WDT;
	}
}

void TIMR0_ISR_Handle()
{
   /*Nothing*/
}

/*============125us===========*/
void TIMR1_ISR_Handle()
{	  
  	if(buz_on)
    {       
        beep =~beep; 
    }
    else
    {    
        beep =1;
    }
    
    TIMER_1MS++ ; 
	TIMER_10MS++;
}


void TIMER_SCAN(void)
{  
	if(TIMER_1MS>=8) //1ms
	{
		TIMER_1MS=0;
	    F_1MS=1;
	}
    
    if(TIMER_10MS>=80)  //10ms
	{
		TIMER_10MS=0;
	    F_10MS=1;
        
        if(++TIMER_100MS>=10) //100ms
        {
            TIMER_100MS = 0;
            F_100MS = 1;
            
            if(++TIMER_500MS>=5) //500ms
            {
                TIMER_500MS = 0;
                F_500MS = 1;
                
                F_PN_500MS =~ F_PN_500MS;
                
                if(++TIMER_1SEC>=2)   //1s
                {
                    TIMER_1SEC = 0;
                    F_1SEC = 1;
                    
                    if(++TIMER_1MIN>=60) //1min
                    {
                        TIMER_1MIN = 0;
                        F_1MIN = 1;
                        
                        if(++TIMER_1HOUR>=60) //1h
                        {
                            TIMER_1HOUR = 0;
                            F_1HOUR = 1;
                        }
                    }
                }
            }
        }
	}
    
}


/*********************************END OF FILE************************************/
/******************* (C) COPYRIGHT 2009~2017 holychip ***************************/
