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
		P0M2 = GPIO_In_AN;    //TDS1����V
		P0M3 = GPIO_In_FLOATING;    //©ˮ���
		
		P0M4 = GPIO_Out_PP  ;  //  
		P0M5 = GPIO_Out_PP  ;  //  
		P0M6 = GPIO_Out_PP  ;  //  
		P0M7 = GPIO_In_AN  ;  //  

	P1 = 0X00; 
		P1M0 = GPIO_Out_PP;  
		P1M1 = GPIO_Out_PP; //ˮ��
		P1M2 = GPIO_Out_PP; //��ϴ
		P1M3 = GPIO_In_AN;  //TK11 ��λ��  
		P1M4 = GPIO_In_PU; //��ѹ
		P1M5 = GPIO_In_PU;  //��ѹ
		P1M6 = GPIO_In_PU;  //rx���� 
		P1M7 = GPIO_Out_PP; //TX����

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
		P3M5 = GPIO_Out_PP; // ������
}

void AD_INIT(void)
{
  /************************************ADC��ʼ��****************************************/	
	  P0M2 = GPIO_In_AN;
      P0M3 = GPIO_In_FLOATING;  //
      P2M3 = GPIO_In_AN;
	  ADCC0 = 0x80;						//��ADCת����Դ
	  delay_us(20);						//��ʱ20us��ȷ��ADCϵͳ�ȶ�
//	  ADCC1 = 0x02;						//ѡ���ⲿͨ��
//      ADCC1 = 0x03;						//ѡ���ⲿͨ��
//      ADCC1 = 0x0B;						//ѡ���ⲿͨ��
	  ADCC2 = 0x4B;						//ת�����12λ���ݣ������Ҷ��룬ADCʱ��16��Ƶ
}

/*********************************END OF FILE************************************/
