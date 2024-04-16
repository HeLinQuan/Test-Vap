#include "define.h"
unsigned char xdata SendOutData[16] = {0x55,0xAA,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
unsigned char xdata ReceivebeBuffer[16] = {0x00,0x00,0x00,0x00};		//接收缓存器
unsigned char Receiveflag = 0;								//接收标志位
unsigned char Receietime = 0;									//接收时间
unsigned char Receivenum = 0;									//接收数目

bit F_WORK;
unsigned char F_BUZ;

volatile unsigned char xdata ReceiveLimitFlag = 0;							//接收限制标志位
volatile unsigned int xdata ReceiveLimitCount = 0;							//接收限制计数


unsigned char WENBIAO_value ,START_value  , WORK_value  ,YURE_value; 


//unsigned int  xdata KAOLU_temp,KEY_VALUE,F_OVER;
//unsigned int  xdata F_30min,beep=0,beep1=0,beep2=0;


void UartInit()			//uart初始化
{
	/**********************************UART配置初始化**************************************/
    
//    P1M6 =  GPIO_In_PU;      //  RXD      设置为上拉输入
//	P1M7 =  GPIO_Out_PP;    // TXD	    设置为推挽输出
//	
//	TXD_MAP = 0x17;							//TXD映射P
//	RXD_MAP = 0x16;							//RXD映射P
	
    P1M6 = GPIO_Out_PP ;      //  RXD      设置为上拉输入
	P1M7 = GPIO_In_PU ;    // TXD	    设置为推挽输出
	
	TXD_MAP =0x16 ;							//TXD映射P
	RXD_MAP =0x17 ;							//RXD映射P




	
	T4CON = 0x06;								//T4工作模式：UART1波特率发生器
	//波特率计算
	//波特率 = 1/16 * (T4时钟源频率 / 定时器4预分频比) / (65536 - 0xFF98)
	//       = 1/16 * ((16000000 / 1) / 104)
	//		 = 9615.38(误差0.16%)

	//波特率9600
	//反推初值 = (65536 - ((T4时钟源频率 / 定时器4预分频比) * (1 / 16)) / 波特率)
	//		   = (65536 - (16000000 * (1 / 16) / 9600))
	//		   = (65536 - 104.167)
	//         = FF98
    TH4 = 0xFF;
	TL4 = 0x98;							//波特率9600
	SCON2 = 0x02;						//8位UART，波特率可变
	SCON = 0x10;						//允许串行接收
	IE |= 0x10;							//使能串口中断
	EA = 1;								  //使能总中断
}


//发送一个字节
void UART_SendChar(unsigned char UART_da)
{
	  SBUF = UART_da;						//发送8位串口数据
		while(!(SCON & 0x02));
		SCON &=~ 0x02;						//清除发送中断标志位
}

void  UART_SendData(  unsigned char  len0)
{
    unsigned char i;
		for(i=0;i<len0;i++)
		{
				UART_SendChar(SendOutData[i]);	
		}
}


 void JudgeOneStringEnd()		  			//判断一帧数据结束
{
	if(Receiveflag == 1 && Receietime == 3)		//3		
	{ 
			JudgeTheReceiveData(ReceivebeBuffer,Receivenum);
			ClearBuffer();
	}
}

unsigned char JudgeTheReceiveData(unsigned char *da,unsigned char num)			//判断接收的数据是否正确
{
		unsigned char  num_data, i ;
	  num_data = num;
		num_data = 0 ;
		for(i=2 ; i<11 ; i++)
		{
			 num_data += *(da+i);
		}

		if((*da == 0X55) &&(*(da+1) == 0XAA)&&(num_data == *(da+11)))//头码、校验码正确
		{
              F_FilterSet= (*(da+2)) ;
              Filter_SetMode = (*(da+3));
              F_Power = (*(da+6));
              return Success;
		}
		else
		{
			 return Fail;
		}
}

void ClearBuffer()													//清空缓存器
{
	unsigned char i = 0;
	for(i=0; i<50; i++)
	{ 	
		ReceivebeBuffer[i] = 0;
	}
	Receiveflag = 0;
	Receietime  = 0;
	Receivenum  = 0;
}
void DIS_TO_MAIN_SEND(void)
{
	  unsigned char x , num_data ;  
		SendOutData[0] = 0X55 ; 
		SendOutData[1] = 0XAA ;  									
	    SendOutData[2] = F_FilterSet; 
		SendOutData[3] = Filter_SetMode; 
		SendOutData[4] = 0X00;
		SendOutData[5] = TDS_RO_avg;
		SendOutData[6] = F_Power; 
		SendOutData[7] = F_FilterOutTime;
		SendOutData[8] = 0X00 ;
	    SendOutData[9] = 0X00 ;
		SendOutData[10]= 0X00 ;
		num_data = 0 ; 
		for(x=2 ; x<11 ; x++)
		{
			num_data += SendOutData[x] ;
		}
		SendOutData[11]= num_data ; 
		UART_SendData(12) ;
}

void SingReceive(void)
{
if(ReceiveLimitFlag == 1)
{
        ReceiveLimitCount++;
        if(ReceiveLimitCount==100)
        {
            ReceiveLimitFlag = 0;
            ReceiveLimitCount = 0;
        }
}

if(Receiveflag == 1)	//串口接收一帧数据判断
{
        Receietime++;
        if(Receietime>=6)
        {
            ReceiveLimitFlag = 1;
            Receietime = 6;
        }
}
}






/*


*/
