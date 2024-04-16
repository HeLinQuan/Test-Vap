/******************* (C) COPYRIGHT 2009~2023 holychip **************************
* File Name          : Main.c
* Author             : HA Team
* Version            : V3.0.1.3
* Date               : 2023/04/24
********************************************************************************/

//================================================================================
#define  ALLOCATE_EXTERN
#include "define.h"
//================================================================================

void main()
{
	SystemInit();						//ʱ�ӳ�ʼ������(Ĭ��Fosc=32M��Fcpu=16M)
	IO_Init();							//����CTK�ڱ�������Ϊģ�������
    TM1652_init();
    
    EEPROM_INIT();
    ParamInit();                        //ȫ�ֱ�����ʼ������
    TIMER0_Init();
	TIMER1_Init();
    
    
    AD_INIT() ;
    
	EA = 1;								//CTK��ʼ��֮ǰ�����EA
	CTK_Init();							//CTK��ʼ����δ�幷�����齫WDT��ʼ���ŵ�CTK��ʼ��֮��	
	
    
    WDT_INIT();
    
    speek_dan0(30);
    
#if TouchUartDebugLib_SW
	CTK_TouchUartDebug_Init();			//�������ڵ��Գ�ʼ��
#endif

	UartInit();
    
	while(1)
	{
		if(OneCycleScanDone)
		{
			Touch_Signal_Handle();
			OneCycleScanDone = 0;

#if TouchUartDebugLib_SW
	ECTK = 0; 							//�������ڵ��Է�������ǰ�������ֹ�ECTK�����ٴ�
	CTK_TouchUartDebug();
	ECTK = 1;
#endif
            
            if((TouchKeyFlag)!= KEY_TEMP)
            {
                    KEY_TEMP = TouchKeyFlag;
                    KEY_CNT = 0;
            }
            else
            {
                    KEY_CNT++;
                    if(KEY_CNT>=10) KEY_CNT = 10 ; 
            }
		}
        CLR_WDT;
		Fun_Handle(); 
//		if(TouchKeyFlag == TK0){;}		//�жϵ�������Ч	
//		if(TouchKeyFlag == TK2|TK3){;}	//�ж϶������ͬʱ��Ч
	}
}

/*********************************END OF FILE************************************/
/******************* (C) COPYRIGHT 2009~2023 holychip ***************************/
