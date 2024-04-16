
#include "HC89F30xC.h"
#include "HC89F30xC_SYS.h"
#include "HC89F30xC_IO_INIT.h"

#include "HC89F30xC_PORT_MAP.h"

#include "define.h"

/**��ע��
���͹�����ѹ��5V
���нӿڣ�SDA�������ݴ���ͨ�ţ�UART��Э�飬֧�ֲ�����19200bps
one bit time 1/19200 = 52us
֧�ֹ����������ʾ
�Զȵ��ڵ�·��λռ�ձ�16���ɵ�������������8���ɵ���
**/ 


/**********************************************************
�������ƣ�TM1652GPIO_init
�������ܣ���ʼ��TM1652������������
������������
�������أ���
����������main
�������ڣ�2021��2��26��09:34:05
��    �ߣ�Vence
ע    �⣺PA.4��Ϊ���ڵ������������
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
unsigned char Tm1652_flag = 0;			//1652��ʾ�ӳٱ�־λ
unsigned char Tm1652_TimeCount = 0;*/			//1652��ʾʱ��
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

		TMSDA=0;   					  //��ʼλ
		delay_us(84);  
		for(i=0; i<8; i++)				  //��λ����λ
		{
				if(sdat & 0x01)
				{
					TMSDA=1;
					sfalg++;
				}else
				{
					TMSDA=0;
				}
				delay_us(84); 					 //������Ϊ19200����ÿ����һλ��ʱ52us
				sdat >>=1;
		}

		if(sfalg%2==0)			         //��У��λ     
		{
				TMSDA=1;
		}
		else			        
		{
				TMSDA=0;
		}
				delay_us(84);		
				TMSDA=1;  							//ֹͣλ
				delay_us(84);   
}

/**********************************************************
�������ƣ�Control_display
�������ܣ���ʾ���Ƶ���
����������ռ�ձ�(0-15)������������(1-8)����ʾģʽ(0-1)
�������أ���
����������TM1652GPIO_init
�������ڣ�2020/04/19  13��36
��    �ߣ�RJ
ע    �⣺��
**********************************************************/
void Control_display(void)
{
		unsigned char Ctr_duty;
		unsigned char Ctr_curr;
		unsigned char Ctr_mode;
		unsigned char Crdata;

		Ctr_duty = 0xf0 ;
		Ctr_curr = 0x0a ;       // 0a�䶯Ϊ0f 
		Ctr_mode = 0x01 ;				// ���� 7�� 6λ���

		Crdata = (Ctr_duty|Ctr_curr|Ctr_mode);
		tm1652_send_data(addr_Cr);				
		tm1652_send_data(Crdata);	
		Delay_1ms(3);
}


//=============================================================================



