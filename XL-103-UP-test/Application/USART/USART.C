#include "define.h"
unsigned char xdata SendOutData[16] = {0x55,0xAA,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
unsigned char xdata ReceivebeBuffer[16] = {0x00,0x00,0x00,0x00};		//���ջ�����
unsigned char Receiveflag = 0;								//���ձ�־λ
unsigned char Receietime = 0;									//����ʱ��
unsigned char Receivenum = 0;									//������Ŀ

bit F_WORK;
unsigned char F_BUZ;

volatile unsigned char xdata ReceiveLimitFlag = 0;							//�������Ʊ�־λ
volatile unsigned int xdata ReceiveLimitCount = 0;							//�������Ƽ���


unsigned char WENBIAO_value ,START_value  , WORK_value  ,YURE_value; 


//unsigned int  xdata KAOLU_temp,KEY_VALUE,F_OVER;
//unsigned int  xdata F_30min,beep=0,beep1=0,beep2=0;


void UartInit()			//uart��ʼ��
{
	/**********************************UART���ó�ʼ��**************************************/
    
//    P1M6 =  GPIO_In_PU;      //  RXD      ����Ϊ��������
//	P1M7 =  GPIO_Out_PP;    // TXD	    ����Ϊ�������
//	
//	TXD_MAP = 0x17;							//TXDӳ��P
//	RXD_MAP = 0x16;							//RXDӳ��P
	
    P1M6 = GPIO_Out_PP ;      //  RXD      ����Ϊ��������
	P1M7 = GPIO_In_PU ;    // TXD	    ����Ϊ�������
	
	TXD_MAP =0x16 ;							//TXDӳ��P
	RXD_MAP =0x17 ;							//RXDӳ��P




	
	T4CON = 0x06;								//T4����ģʽ��UART1�����ʷ�����
	//�����ʼ���
	//������ = 1/16 * (T4ʱ��ԴƵ�� / ��ʱ��4Ԥ��Ƶ��) / (65536 - 0xFF98)
	//       = 1/16 * ((16000000 / 1) / 104)
	//		 = 9615.38(���0.16%)

	//������9600
	//���Ƴ�ֵ = (65536 - ((T4ʱ��ԴƵ�� / ��ʱ��4Ԥ��Ƶ��) * (1 / 16)) / ������)
	//		   = (65536 - (16000000 * (1 / 16) / 9600))
	//		   = (65536 - 104.167)
	//         = FF98
    TH4 = 0xFF;
	TL4 = 0x98;							//������9600
	SCON2 = 0x02;						//8λUART�������ʿɱ�
	SCON = 0x10;						//�������н���
	IE |= 0x10;							//ʹ�ܴ����ж�
	EA = 1;								  //ʹ�����ж�
}


//����һ���ֽ�
void UART_SendChar(unsigned char UART_da)
{
	  SBUF = UART_da;						//����8λ��������
		while(!(SCON & 0x02));
		SCON &=~ 0x02;						//��������жϱ�־λ
}

void  UART_SendData(  unsigned char  len0)
{
    unsigned char i;
		for(i=0;i<len0;i++)
		{
				UART_SendChar(SendOutData[i]);	
		}
}


 void JudgeOneStringEnd()		  			//�ж�һ֡���ݽ���
{
	if(Receiveflag == 1 && Receietime == 3)		//3		
	{ 
			JudgeTheReceiveData(ReceivebeBuffer,Receivenum);
			ClearBuffer();
	}
}

unsigned char JudgeTheReceiveData(unsigned char *da,unsigned char num)			//�жϽ��յ������Ƿ���ȷ
{
		unsigned char  num_data, i ;
	  num_data = num;
		num_data = 0 ;
		for(i=2 ; i<11 ; i++)
		{
			 num_data += *(da+i);
		}

		if((*da == 0X55) &&(*(da+1) == 0XAA)&&(num_data == *(da+11)))//ͷ�롢У������ȷ
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

void ClearBuffer()													//��ջ�����
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

if(Receiveflag == 1)	//���ڽ���һ֡�����ж�
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