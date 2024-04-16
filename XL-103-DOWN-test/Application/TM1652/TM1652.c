
#include "HC89F30xC.h"
#include "HC89F30xC_SYS.h"
#include "HC89F30xC_IO_INIT.h"

#include "HC89F30xC_PORT_MAP.h"

#include "define.h"

/**备注：
典型工作电压：5V
串行接口（SDA），兼容串口通信（UART）协议，支持波特率19200bps
one bit time 1/19200 = 52us
支持共阴数码管显示
辉度调节电路（位占空比16级可调、段驱动电流8级可调）
**/ 


/**********************************************************
函数名称：TM1652GPIO_init
函数功能：初始化TM1652数据输入引脚
函数参数：无
函数返回：无
函数隶属：main
创建日期：2021年2月26日09:34:05
作    者：Vence
注    解：PA.4作为串口的数据输出引脚
**********************************************************/



void Delay_1ms(unsigned char d_ms)
{
		unsigned char i ; 
		for(i=0 ; i<d_ms ; i++)
		{
			CLR_WDT;
			delay_us(160)	 ;		
			delay_us(160)	 ;		
			delay_us(160)	 ;		
			delay_us(160)	 ;	
			delay_us(160)	 ;		
			delay_us(160)	 ;	 	 		 	 	 	 	
		}
	
}	


/*unsigned char K = 0;
unsigned char Tm1652_flag = 0;			//1652显示延迟标志位
unsigned char Tm1652_TimeCount = 0;*/			//1652显示时间
void TM1652_init(void)
{
	  EA = 0; 
        tm1652_send_data(0x08);
		tm1652_send_data(0xff);
		tm1652_send_data(0xff);
		tm1652_send_data(0xff);
		tm1652_send_data(0xff&~(1<<0)&~(1<<1));  //&~(1<<0)&~(1<<1)
		tm1652_send_data(0xff&~(1<<0));
		tm1652_send_data(0xff);
		Delay_1ms(3);  
		Control_display() ;
	  EA = 1; 
}

void tm1652_send_data(unsigned char sdat)
{
		unsigned char i=0, sfalg=0;

		TMSDA=0;   					  //起始位
		delay_us(84);  
		for(i=0; i<8; i++)				  //八位数据位
		{
				if(sdat & 0x01)
				{
					TMSDA=1;
					sfalg++;
				}else
				{
					TMSDA=0;
				}
				delay_us(84); 					 //波特率为19200，故每发送一位延时52us
				sdat >>=1;
		}

		if(sfalg%2==0)			         //奇校验位     
		{
				TMSDA=1;
		}
		else			        
		{
				TMSDA=0;
		}
				delay_us(84);		
				TMSDA=1;  							//停止位
				delay_us(84);   
}

/**********************************************************
函数名称：Control_display
函数功能：显示控制调节
函数参数：占空比(0-15)，段驱动电流(1-8)，显示模式(0-1)
函数返回：无
函数隶属：TM1652GPIO_init
创建日期：2020/04/19  13：36
作    者：RJ
注    解：无
**********************************************************/
void Control_display(void)
{
		unsigned char Ctr_duty;
		unsigned char Ctr_curr;
		unsigned char Ctr_mode;
		unsigned char Crdata;

		Ctr_duty = 0xf0 ;
		Ctr_curr = 0x0a ;       // 0a变动为0f 
		Ctr_mode = 0x01 ;				// 设置 7段 6位输出

		Crdata = (Ctr_duty|Ctr_curr|Ctr_mode);
		tm1652_send_data(addr_Cr);				
		tm1652_send_data(Crdata);	
		Delay_1ms(3);
}


//=============================================================================



