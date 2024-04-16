/******************* (C) COPYRIGHT 2009~2021 holychip **************************
* File Name          : HC88T6xx1_IO_INIT.c
********************************************************************************


*******************************************************************************/
#include "define.h"


/****************************************************************************
* Function Name  :
* Description    :
* Input          : None
* Output         : None
* Return         : None
****************************************************************************/
void IO_Init(void)
{
	P0 = 0X00;
		P0M0 = GPIO_Out_PP;    //
		P0M1 = GPIO_Out_PP;    // 
		P0M2 = GPIO_In_AN;    //TDS1——V
		P0M3 = GPIO_In_FLOATING;    //漏水检测
		
		P0M4 = GPIO_Out_PP  ;  //  
		P0M5 = GPIO_Out_PP  ;  //  
		P0M6 = GPIO_Out_PP  ;  //  
		P0M7 = GPIO_In_AN  ;  //  

	P1 = 0X00; 
		P1M0 = GPIO_Out_PP;  
		P1M1 = GPIO_Out_PP; //水泵
		P1M2 = GPIO_Out_PP; //冲洗
		P1M3 = GPIO_In_AN;  //TK11 复位键  
		P1M4 = GPIO_In_PU; //高压
		P1M5 = GPIO_In_PU;  //低压
		P1M6 = GPIO_In_PU;  //rx接受 
		P1M7 = GPIO_Out_PP; //TX发送

    P2 = 0X00;
		P2M0 = GPIO_Out_PP;  
		P2M1 = GPIO_Out_PP;  // 
		P2M2 = GPIO_Out_PP; //
		P2M3 = GPIO_In_AN; // 
		P2M4 = GPIO_Out_PP; // 
		P2M5 = GPIO_Out_PP;  //AD 
		
		P2M6 = GPIO_Out_PP; // 
		P2M7 = GPIO_Out_PP; //

	P3 = 0X00;
		P3M4 = GPIO_Out_PP;  // 1652SDA
		P3M5 = GPIO_Out_PP; // 蜂鸣器
}

void AD_INIT(void)
{
  /************************************ADC初始化****************************************/	
	  P0M2 = GPIO_In_AN;
      P0M3 = GPIO_In_FLOATING;  //
      P2M3 = GPIO_In_AN;
	  ADCC0 = 0x80;						//打开ADC转换电源
	  delay_us(20);						//延时20us，确保ADC系统稳定
//	  ADCC1 = 0x02;						//选择外部通道
//      ADCC1 = 0x03;						//选择外部通道
//      ADCC1 = 0x0B;						//选择外部通道
	  ADCC2 = 0x4B;						//转换结果12位数据，数据右对齐，ADC时钟16分频
}

/*********************************END OF FILE************************************/
