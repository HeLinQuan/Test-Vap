/*******************************************************************************/
#include "define.h"
//===============================================================================
void KEY_TIG_INIT(void);
//===============================================================================
/******全局变量*********/
u32 KEY_TEMP;
u8  KEY_CNT;
bit F_Power;
bit F_FilterSet;
unsigned char Filter_SetMode;
unsigned char xSCE_SetWait_CNT;
/******局部变量*********/
ux32 OLD_KEY = 0;
unsigned  int xdata KEY_LONG_CNT1 = 0;
unsigned  int xdata KEY_LONG_CNT2 = 0;
bit KEY_LONG = 0;

void ParamKeyInit(void)
{
    KEY_TEMP  = 0;
    KEY_CNT = 0;
    F_Power = 1;  //电源键初始化为1
    xSCE_SetWait_CNT = 0;
    F_FilterSet = 0;
    Filter_SetMode = 1;
}



//===============================================================================
void KEY_Handle(u32 key_flag)  //10ms扫描一次
{
    if((key_flag != OLD_KEY) && (KEY_CNT >3))   //短按
    {	
        if((OLD_KEY == KEY_L)&&(KEY_LONG == 0))      //左键滤芯复位键 
        {
            KEY_LONG = 1;
            
            if(F_FilterSet == 1)
             {
                speek_dan0(20);
                if(++Filter_SetMode>=5)
                {
                    Filter_SetMode = 1;
                }
                xSCE_SetWait_CNT = 0;   //清掉退出滤芯15s的等待时间
             }
        }
        else if((OLD_KEY == KEY_R)&&(KEY_LONG == 0)) //右键冲洗键 、电源键
        {
            speek_dan0(20); 
            KEY_LONG = 1;
            
            if(F_Power == 0)
            {
                F_Power = 1;
                F_WashFirst_10S = 1;
            }
            else
            {
                if(F_Wash == 1)
                {
                    CLEAN_TIME_SEC = 0;
                    F_Wash = 0;
                }
                else
                {
                    F_WashFirst_10S = 1;
                }
                
            }
        }
        
        OLD_KEY = key_flag; 
        KEY_LONG = 0;
    }
    else//长按
    {
         if(key_flag == KEY_L) //  进入滤芯复位模式
         {	
             if(++KEY_LONG_CNT1>=300) // 10*300 = 3000ms = 3s
            { 
                KEY_LONG_CNT1 = 0;
                
                if(F_FilterSet==0)
                {
                    speek_dan0(20);
                    KEY_LONG = 1;
                    
                    F_FilterSet=1 ; 
                    Filter_SetMode=1 ;            								
                }
                else
                {
                    speek_dan0(20);
                    KEY_LONG = 1;
                    
                    F_FilterSet=0 ; 
                    Filter_SetMode=0;            								
                }
            }    
         }
         else
         {
            KEY_LONG_CNT1 = 0;
         }
         
         if(key_flag == KEY_R) //  进入冲洗模式、关机状态
         {	
             if(++KEY_LONG_CNT2>=300) // 110*300 = 3000ms = 3s
            { 
                KEY_LONG_CNT2 = 0;
                
                if(F_Power == 1)
                {
                    speek_dan0(20); 
                    F_Power = 0;
                    KEY_LONG = 1;
                }
            }    
         }
         else
         {
            KEY_LONG_CNT2 = 0;
         }
     }
	
}
/*********************************END OF FILE************************************/
