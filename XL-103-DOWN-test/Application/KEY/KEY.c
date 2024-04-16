/*******************************************************************************/
#include "define.h"
//===============================================================================
void KEY_TIG_INIT(void);
//===============================================================================
/******ȫ�ֱ���*********/
u32 KEY_TEMP;
u8  KEY_CNT;
bit F_Power;
bit F_FilterSet;
unsigned char Filter_SetMode;
unsigned char xSCE_SetWait_CNT;
/******�ֲ�����*********/
ux32 OLD_KEY = 0;
unsigned  int xdata KEY_LONG_CNT1 = 0;
unsigned  int xdata KEY_LONG_CNT2 = 0;
bit KEY_LONG = 0;

void ParamKeyInit(void)
{
    KEY_TEMP  = 0;
    KEY_CNT = 0;
    F_Power = 1;  //��Դ����ʼ��Ϊ1
    xSCE_SetWait_CNT = 0;
    F_FilterSet = 0;
    Filter_SetMode = 1;
}



//===============================================================================
void KEY_Handle(u32 key_flag)  //10msɨ��һ��
{
    if((key_flag != OLD_KEY) && (KEY_CNT >3))   //�̰�
    {	
        if((OLD_KEY == KEY_L)&&(KEY_LONG == 0))      //�����о��λ�� 
        {
            KEY_LONG = 1;
            
            if(F_FilterSet == 1)
             {
                speek_dan0(20);
                if(++Filter_SetMode>=5)
                {
                    Filter_SetMode = 1;
                }
                xSCE_SetWait_CNT = 0;   //����˳���о15s�ĵȴ�ʱ��
             }
        }
        else if((OLD_KEY == KEY_R)&&(KEY_LONG == 0)) //�Ҽ���ϴ�� ����Դ��
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
    else//����
    {
         if(key_flag == KEY_L) //  ������о��λģʽ
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
         
         if(key_flag == KEY_R) //  �����ϴģʽ���ػ�״̬
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
