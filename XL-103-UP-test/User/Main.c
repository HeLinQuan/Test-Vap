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
	SystemInit();						//时钟初始化函数(默认Fosc=32M，Fcpu=16M)
	IO_Init();							//所有CTK口必须设置为模拟输入口
    TM1652_init();
    
    EEPROM_INIT();
    ParamInit();                        //全局变量初始化函数
    TIMER0_Init();
	TIMER1_Init();
    
    
    AD_INIT() ;
    
	EA = 1;								//CTK初始化之前必须打开EA
	CTK_Init();							//CTK初始化中未清狗，建议将WDT初始化放到CTK初始化之后	
	
    
    WDT_INIT();
    
    speek_dan0(30);
    
#if TouchUartDebugLib_SW
	CTK_TouchUartDebug_Init();			//触摸串口调试初始化
#endif

	UartInit();
    
	while(1)
	{
		if(OneCycleScanDone)
		{
			Touch_Signal_Handle();
			OneCycleScanDone = 0;

#if TouchUartDebugLib_SW
	ECTK = 0; 							//触摸串口调试发送数据前，必需现关ECTK，后再打开
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
//		if(TouchKeyFlag == TK0){;}		//判断单按键有效	
//		if(TouchKeyFlag == TK2|TK3){;}	//判断多个按键同时有效
	}
}

/*********************************END OF FILE************************************/
/******************* (C) COPYRIGHT 2009~2023 holychip ***************************/
