#ifndef _USART_H_
#define _USART_H_

//uart
#define Success 1
#define Fail  0


//uart
extern unsigned char xdata ReceiveLimitFlag;							//接收限制标志位
extern unsigned int  xdata ReceiveLimitCount;							//接收限制计数
extern unsigned char xdata SendOutData[50];
extern unsigned char xdata ReceivebeBuffer[50];		//接收缓存器
extern unsigned char Receiveflag;									//接收标志位
extern unsigned char Receietime;									//接收时间
extern unsigned char Receivenum;									//接收数目



void UartInit(void);												//uart初始化
void SendData(unsigned char da);	//发送数据
void JudgeOneStringEnd();									//判断一帧数据结束
unsigned char JudgeTheReceiveData(unsigned char *da,unsigned char num);			//判断接收的数据是否正确
void ClearBuffer(void);										//清空缓存器

void DIS_TO_MAIN_SEND(void) ; 

void  UART_SendData(  unsigned char  len0) ;

extern  unsigned int  xdata   cnt_temp;



#endif
