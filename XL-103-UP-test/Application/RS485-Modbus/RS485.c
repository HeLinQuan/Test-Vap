/*
使用说明
1：配合该工程下的串口初始化
void UartInit()			//uart初始化
{
    P1M6 = GPIO_Out_PP ;      //RXD      设置为上拉输入
	P1M7 = GPIO_In_PU ;    // TXD	    设置为推挽输出
	
	TXD_MAP =0x16 ;							//TXD映射P
	RXD_MAP =0x17 ;							//RXD映射P
    
	T4CON = 0x06;								//T4工作模式：UART1波特率发生器

    TH4 = 0xFF;
	TL4 = 0x98;							//波特率9600
	SCON2 = 0x02;						//8位UART，波特率可变
	SCON = 0x10;						//允许串行接收
	IE |= 0x10;							//使能串口中断
	EA = 1;								  //使能总中断
}

2：在串口中断中接收传回的数据
void UART1_Rpt(void) interrupt UART1_VECTOR
{
	if(SCON&0x01)						//判断接收中断标志位
	{
			SCON &=~ 0x01;					//清除接收中断标志位
            if(USE_RS485 == 0)
            {
                Receiveflag = 1;
                Receietime = 0;
                ReceivebeBuffer[Receivenum] = SBUF;
                Receivenum++;
            }
            else
            {
                if(USART_RX_CNT < USART_RX_MAX)  //接收到的字节 小于 设置的最大缓存区
                {
                    USART_RX_CNT++;
                    USART_RX_BUF[USART_RX_CNT] = SBUF;
                }
            }
			
	}	
}

3：定时器扫描，一帧结束判断函数
static void Scan_1ms(void)
{
    if(F_1MS==1)
	{
        F_1MS = 0;
        UartRxMonitor();
    }
}


*/
#include "define.h"

u8       USART_RX_CNT = 0;             //串口中断接收到数据的长度变量
u8 xdata USART_RX_BUF[USART_RX_MAX];   //串口中断接收到数据保存的缓冲区
bit      F_ReceiveOk = 0;              //标识串口接收数据包完成标志

bit RS485Busy = 0;  //通信标识 主机发送数据后置1 接收到应答后清零
u8 xdata RS485_RX_BUF[64];  //接收缓冲区 64字节
u16 ReadDateVal = 0;  //用于保存读命令获得的数据
u8 RegGroup[5];       //Modbus寄存器数组，地址为 0X00--0X04

void RS485_Init(void)   //485串口初始化
{
    /*使用通用串口 USART 中的 RXD 与 TXD 在此处不用初始化*/
    
    RS485_MODE_Receive     //默认位接收模式
}

/****************************************************************************************************
 * 函数名称： void RS485_SendData(u8 *buf,u8 len)
 * 入口参数：u8 *buf u8 len
 * 返回  值：无
 * 功能说明：串口发送数据
 * 			 buf:发送区首地址
 *			 len:发送的字节数(为了和本代码的接收匹配,这里建议不要超过64个字节)
 ***************************************************************************************************/
void RS485_SendData(u8 *buf,u8 len)
{
	u8 t;
	RS485_MODE_Sending			//设置为发送模式
	delay_ms(1);
	for(t=0;t<len;t++)	    	//循环发送数据
	{	
        SBUF = *(buf+t);
		while(!TI);
        TI = 0;
	}	 
	delay_ms(1);	     		//IO转换稍作延时
	USART_RX_CNT=0;	  
	RS485_MODE_Receive			//设置为接收模式	
}
/****************************************************************************************************
 * 函数名称：u8 RS485_ReadData(u8 *buf, u8 len) 
 * 入口参数：u8 *buf u8 len
 * 返回  值：u8
 * 功能说明：计算接收的数据长度，并且将数据放到*buf数组中
 ***************************************************************************************************/             
u8 RS485_ReadData(u8 *buf, u8 len)    //USART_RX_CNT 、 len 有bug
{
	u8 i;
	if(len > USART_RX_CNT)  		//指定读取长度大于实际接收到的数据长度时
	{
		len = USART_RX_CNT; 		//读取长度设置为实际接收到的数据长度
	}
	
	for(i = 0;i < len;i ++)  		//拷贝接收到的数据到接收指针中
	{
		*buf = USART_RX_BUF[i];  	//将数据复制到buf中
		buf  ++;
	}
	USART_RX_CNT=0;              	//接收计数器清零
	return len;                   	//返回实际读取长度
}

/****************************************************************************************************
 * 函数名称：void UartRxMonitor(void)
 * 入口参数：void
 * 返回  值：无
 * 功能说明：在定时器中调用，用于监控数据接收  1ms 扫描一次
 ***************************************************************************************************/   
void UartRxMonitor(void) 					
{
	static u8 USART_RX_BKP = 0;  			//定义USART2_RC_BKP暂时存储诗句长度与实际长度比较
	static u8 idletmr      = 0;        		//定义监控时间
	
	if(USART_RX_CNT > 0)					//接收计数器大于零时，监控总线空闲时间
	{
		if(USART_RX_BKP != USART_RX_CNT) 	//接收计数器改变，即刚接收到数据时，清零空闲计时
		{
			USART_RX_BKP = USART_RX_CNT;  	//赋值操作，将实际长度给USART2_RX_BKP
			idletmr      = 0;               //将监控时间清零
		}
		else                              	//接收计数器未改变，即总线空闲时，累计空闲时间
		{
											//如果在一帧数据完成之前有超过3--5个字节时间的停顿，接收设备将刷新当前的消息并假定下一个字节是一个新的数据帧的开始
			if(idletmr < 3)                 //空闲时间小于3ms时，持续累加
			{
				idletmr++;
				if(idletmr >= 5)            //空闲时间达到5ms时，即判定为1帧接收完毕
				{
					F_ReceiveOk = 1;			//设置命令到达标志，帧接收完毕标志
				}
			}
		}
	}
	else
	{
		USART_RX_BKP = 0;
	}
}

/****************************************************************************************************
 * 函数名称：void UartRxMonitor(u8 ms)
 * 入口参数：u8 ms
 * 返回  值：无
 * 功能说明：串口驱动函数，检测数据帧的接收，调度功能函数，需在主循环中调用
 *           这里是从机，需要对主机发来的报文进行对应的处理，并返回应答
 *			 从机不主动发送数据，一切操作都是为了响应主机的报文
 ***************************************************************************************************/   
void UartDriver(void)
{
	unsigned char xdata i;
	unsigned char xdata cnt;
	
	unsigned int xdata crc;
	unsigned char xdata crch,crcl;
	static unsigned char xdata len;
	static unsigned char xdata buf[USART_RX_MAX];
	if (F_ReceiveOk)            									//帧接收完成标志，即接收到一帧新数据
	{
		F_ReceiveOk = 0;           								//帧接收完成标志清零
		len = RS485_ReadData(buf,USART_RX_CNT);   				//将接收到的命令读到缓冲区中
		crc = GetCRC16(buf,len-2);       					//计算CRC校验值，除去CRC校验值
		crch=crc  >> 8;    										//crc高位
		crcl=crc  &  0xFF;										//crc低位
		if((buf[len-2] == crch) && (buf[len-1] == crcl))  		//判断CRC校验是否正确
		{
			/* 在点对多点的应用中，这里还需要加上一条，判断报文的地址是否和本机地址一致，否则不作处理 */
			/* 可设置不同从机为不同地址，用以区分报文是发给谁的，相同则处理，不同则不作处理 */
			switch (buf[1])  									//按功能码执行操作
			{
				case 0x03:     									//读数据
					if((buf[2] == 0x00) && (buf[3] <= 0x05))  	//寄存器地址支持0x0000~0x0005
					{
						if(buf[3] <= 0x04) 
						{
							i      = buf[3];					//提取寄存器地址
							cnt    = buf[5];  					//提取待读取的寄存器数量
							buf[2] = cnt*2;  					//读取数据的字节数，为寄存器*2，因modbus定义的寄存器为16位
							len    = 3;							//响应帧第4个字节开始为数据
							while(cnt --)
							{
								buf[len ++] = 0x00;				//寄存器高字节补0
								buf[len ++] = RegGroup[i++];	//低字节
							}
						}
						break;
					}
					else  										//寄存器地址不被支持时，返回错误码
					{   
						buf[1] = 0x83;  						//功能码最高位置1
						buf[2] = 0x02;  						//设置异常码为02-无效地址
						len    = 3;
						break;
					}
				case 0x06:           							//写入单个寄存器
					if((buf[2] == 0x00) && (buf[3] <= 0x05))   	//寄存器地址支持0x0000-0x0005
					{
						if(buf[3] <= 0x04)
						{
							i           = buf[3];				//提取寄存器地址
							RegGroup[i] = buf[5];				//保存寄存器数据
						}
						len -= 2;                				//长度-2以重新计算CRC并返回原报文
						break;
					}
					else  
					{											//寄存器地址不被支持，返回错误码
						buf[1] = 0x86;           				//功能码最高位置1
						buf[2] = 0x02;          				//设置异常码为02-无效地址
						len    = 3;
						break;
					}
				default:   						 				//其他不支持的功能码
					buf[1] = 0x80;     							//功能码最高位置1
					buf[2] = 0x01;     							//设置异常码为01—无效功能
					len    = 3;
					break;
			}
			crc = GetCRC16(buf,len);           					//计算CRC校验值
			buf[len ++] = crc >> 8;           					//CRC高字节
			buf[len ++] = crc & 0xff;        					//CRC低字节
			RS485_SendData(buf,len); 			 					//发送响应帧
		}
		//else	/* 如果校验值错误，执行错误处理函数 这里用串口1打印一条提示信息 也可自定义共它处理函数 */
			//printf("接收错误\r\n");
	}
}




