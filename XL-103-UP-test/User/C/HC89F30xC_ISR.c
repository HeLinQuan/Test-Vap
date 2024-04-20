/******************* (C) COPYRIGHT 2009~2021 holychip **************************
* File Name          : HC89F30xC_ISR.c
********************************************************************************


*******************************************************************************/
#include "define.h"


//================================================================================
extern void CTK_ISR_Handle(void);

/****************************************************************************
* Function Name  : ISR_CTK
* Description    : CTK interrupt request
* Input          : None
* Output         : None
* Return         : None
****************************************************************************/

void ISR_CTK(void)      interrupt CTK_VECTOR
{
		CTK_ISR_Handle();
}
/****************************************************************************
* Function Name  : ISR_Timer0
* Description    : Timer0 interrupt request
* Input          : None
* Output         : None
* Return         : None
****************************************************************************/
void ISR_Timer0(void)     interrupt TIMER0_VECTOR
{
    //TIMR0_ISR_Handle();
}
/****************************************************************************
* Function Name  : ISR_Timer1
* Description    : Timer1 interrupt request
* Input          : None
* Output         : None
* Return         : None
****************************************************************************/
void ISR_Timer1(void)     interrupt TIMER1_VECTOR
{
    TIMR1_ISR_Handle();
}
//---------------------------------------------------------------------------
void UART1_Rpt(void) interrupt UART1_VECTOR
{
	if(SCON&0x01)						//�жϽ����жϱ�־λ
	{
			SCON &=~ 0x01;					//��������жϱ�־λ
            if(USE_RS485 == 0)
            {
                Receiveflag = 1;
                Receietime = 0;
                ReceivebeBuffer[Receivenum] = SBUF;
                Receivenum++;
            }
            else
            {
                if(USART_RX_CNT < USART_RX_MAX)  //���յ����ֽ� С�� ���õ���󻺴���
                {
                    USART_RX_CNT++;
                    USART_RX_BUF[USART_RX_CNT] = SBUF;
                }
            }
			
	}	
}


/*********************************END OF FILE************************************/
/******************* (C) COPYRIGHT 2009~2021 holychip ***************************/
