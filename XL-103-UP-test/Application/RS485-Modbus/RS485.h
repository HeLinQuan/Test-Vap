#ifndef __RS485_H__ 
#define __RS485_H__ 
#include "define.h"

#define  USE_RS485  1
#define  USART_RX_MAX  64    //接收缓存最大值
extern u8      USART_RX_CNT;
extern u8 xdata USART_RX_BUF[USART_RX_MAX];

sbit RS485_MODE_Pin = P2^2 ;   //RS485模式控制引脚 设置为推挽输出
#define RS485_MODE_Sending  RS485_MODE_Pin = 1;  //发送模式
#define RS485_MODE_Receive  RS485_MODE_Pin = 0;  //接收模式

void UartRxMonitor(void);
unsigned int GetCRC16(unsigned char *pPtr,unsigned char ucLen);
#endif