#include "define.h"

/*******ȫ�ֱ���*******/
bit F_WashFirst_10S;
bit F_ZHISHUICHAOSHI;
bit F_QUESHUI;
bit F_LOUSHUI;
bit F_WaterProduction;
bit F_Wash;
bit F_SHUIBEN;
bit F_CXF;

unsigned char xdata CLEAN_TIME_SEC;
unsigned char xdata F_FilterOutTime;


/*******�ֲ�����*******/
unsigned char DIS_CNT = 0;
bit F_WashAccumulateFull_4h = 0;
bit F_WashAccumulateWork_10min = 0;
bit F_WashFull = 0;
unsigned char xdata F_WaterFull_CNT = 0;
unsigned char xdata F_WaterProduction_CNT1 = 0;
unsigned char xdata F_WaterProduction_CNT2 = 0;
unsigned char xdata xSEC_FilterOutTime_CNT = 0;
bit  F_yali_low = 1 , F_yali_high = 0; 
unsigned int low_count = 1000, high_count = 0; 
unsigned int Tim_cnt=0;
bit F_WashFull_Flag = 1;
unsigned char TDS_CNT = 0 ;
unsigned int TDS_CHECK_CNT = 0;
static void ParamHandleInit(void)
{
    F_WashFirst_10S = 1;  //�����ϵ��ϴ��־λ�� 1
    CLEAN_TIME_SEC = 0;
    
    F_WaterProduction = 0;  //��ˮ��־
    F_ZHISHUICHAOSHI = 0;  //��ˮ��ʱ��־λ��0
    F_QUESHUI = 0;         //ȱˮ��־λ��0
    F_LOUSHUI = 0;        //©ˮ��־λ��0
    
    F_Wash = 1;  //��ϴ��־λ��0
    
    F_SHUIBEN = 0; //ˮ�ñ�־λ��0
    F_CXF = 0;   //��ϴ����־λ��0
    
    F_FilterOutTime = 0;  //��о���ڱ�־λ
}

/****������ʼ��****/
void ParamInit(void)
{ 
      ParamTimtInit();
      ParamHandleInit();
      ParamKeyInit(); 
//    ParamAdworkInit();
}
/*************************************************************************
ѹ�����ؼ��  10msɨ��һ��  
*************************************************************************/
void yali_sw_check (void)    //���򣺽�ͨΪ0  �Ͽ�Ϊ1
{
    if(yali_low_sw==0)	  //��ˮ 
    {  
        low_count+=50 ;
        if(low_count>=1000)   //10�� 
        {
            low_count = 1000 ; 							 
            F_yali_low = 1 ;   //��ѹ���رպ� 
        }
    }
	else		    //��ˮ 
	{
        if(--low_count<=1)
        {
            low_count = 1 ;
            F_yali_low = 0 ;     //��ѹ���ضϿ�  ȱˮ  
        }
	 }
	
     
    if(yali_high_sw==0)   //��ѹ���� ���տ���   ��Ϊ1 �� �Ͽ�  0Ϊ�պ�
    {
        if(++high_count>=50)
        {
            high_count = 50 ;
            F_yali_high = 0 ;  //��ѹ���رպ�
        }
    }
    else   //ˮ��
    {
        if(--high_count<=1)
        {
                high_count = 1 ;
                F_yali_high = 1 ;   //��ѹ���ضϿ� 
        }
    }
}

void RO_SIGN_chuli(void)
{
	if(F_yali_low==0) //ȱˮ
	{  
		if(F_QUESHUI==0)
		{
			speek_duo(150,50,10);
		}
		F_QUESHUI = 1 ; //ȱˮ 
	}
	else 
	{
		F_QUESHUI = 0 ;   //��ȱˮ 		 
		if(F_yali_high==0) 
		{ 
			F_WaterProduction = 1 ; //��ˮ���� 
            if(F_WashFull_Flag == 0)
            {
                F_WashFull_Flag = 1;
            }
		}
         else
		{
			F_WaterProduction = 0 ; //��ˮ��� ��ˮ��
            if(F_WashFull_Flag == 1)
            {
                F_WashFull_Flag = 0;
                F_WashFull = 1;
            }
		}					  
	}			 
}
/**************************************************************************
ROϵͳ��ˮ����  //100MS ɨ��һ�� 
**************************************************************************/
void RO_SYS_WORK(void)
{  
	if((F_ZHISHUICHAOSHI==1)||(F_QUESHUI == 1)||(F_LOUSHUI == 1)||(F_Power == 0)) //�����رշ��š���
	 { 
            F_SHUIBEN = 0;
            F_CXF = 0;
	 }
	 else
	 {
		  if(F_Wash == 1)  //��ϴ
		  {
				 if(CLEAN_TIME_SEC>0)
				 {
						F_SHUIBEN = 1;
                        F_CXF = 1;  
				 }
				 else 
				 {
						 F_Wash = 0 ; 
                         F_SHUIBEN = 0;
                         F_CXF = 0; 
				 }	
		  }
          else
          {
                if(F_WaterProduction == 1)   //��ˮ
                {
                    F_SHUIBEN = 1;
                    F_CXF = 0;
                }
                else                        //ˮ��
                { 
                    F_SHUIBEN = 0;
                    F_CXF = 0;
                }
          }
      }
}

/**********************************************************
��ϴģʽ  10ms 
***********************************************************/
void RO_CLEAN_check(void)
{
   if(F_WashFirst_10S==1)  //�ϵ��ϴ30s
    {
        CLEAN_TIME_SEC = 30;  
        F_Wash = 1 ; 
        F_WashFirst_10S = 0;  //
    }
    else if(F_WashAccumulateFull_4h == 1)   //��������ˮ��״̬�ۼ�4h����ϴ20s
    {
        CLEAN_TIME_SEC = 20;  
        F_Wash =1 ;
        F_WashAccumulateFull_4h = 0;
    }
    else if((F_WashAccumulateWork_10min == 1)&&(F_WaterProduction == 1))   //�����ۼ���ˮ10min��ˮ�����ϴ10s
    {
        CLEAN_TIME_SEC = 10;  
        F_Wash =1 ; 
        F_WashAccumulateWork_10min = 0;
    }
    else if(F_WashFull == 1)    //ˮ����ϴ 10s
    {
        CLEAN_TIME_SEC = 10;  
        F_Wash =1 ; 
        F_WashFull = 0;
    }
}

/**********************************************************
���š��ü�⺯��  100ms 
***********************************************************/
void WorkPro(void)
{	 
    if(F_SHUIBEN == 1)
    {
        SHUIBEN_ON
    }
    else
    {
        SHUIBEN_OFF
    }
    
    if(F_CXF == 1)
    {
        CXF_ON
    }
    else
    {
        CXF_OFF
    }
}


/*********************************************
TDS ���   1ms ɨ�� 1�� 
//  TDS ��� 
**********************************************/
void TDS_CHECK(void)
{
    if(F_WaterProduction==1)  //��ˮ��־			
    {
        if(++TDS_CHECK_CNT>=15000)
        {
            TDS_CHECK_CNT = 15000;
            TDS_YS_read() ;   //��ԭˮTDS 		 
            TDS_RO_read() ;   //��ȡ��ˮ TDS 
        }
    }
    else
    { 
        TDS_YS_STOP;     //IOֹͣ 
        TDS_RO_STOP;     //IOֹͣ
        TDS_CHECK_CNT = 0;
    } 	
}

static void Scan_1ms(void)
{
    if(F_1MS==1)
	{
        F_1MS = 0;
        SingReceive();
        TDS_CHECK();
    }
}

static void Scan_10ms(void)
{
    if(F_10MS==1)
	  {
	      F_10MS = 0; 
          speek_manage0();
          KEY_Handle(KEY_TEMP);  //������������
          yali_sw_check();
          
          Check_Leak();   //©ˮ���
          RO_SYS_WORK();
	  }
}

static void Scan_100ms(void)
{
    if(F_100MS == 1)
    {
       F_100MS =0;
        
        if(++DIS_CNT>=2)
        {
            DIS_CNT = 0;
            
            DIS_MANAGE();    /*��ʾ��������*/
			if(buz_on==0)
            {
                display();	
            }
        }
        
        WorkPro();
        RO_CLEAN_check();
        RO_SIGN_chuli();
    }
}

static void Scan_500ms(void)
{
    if(F_500MS == 1)
    {
       F_500MS = 0;
       
//        if(F_WaterProduction == 1)
//        {
//        
//        }
        TDS_RO_SUM += TDS_RO ;
        TDS_YS_SUM += TDS_YS ;
        if(++TDS_CNT>=10)
        {
            TDS_CNT = 0 ; 
            TDS_RO_avg = TDS_RO_SUM/10 ;
            TDS_YS_avg = TDS_YS_SUM/10 ;
            TDS_RO_SUM = 0 ;
            TDS_YS_SUM = 0 ;
        }
    }
}

static void Scan_xSEC(void)
{
    if(F_1SEC == 1)
    {
        F_1SEC = 0;
         DIS_TO_MAIN_SEND();
        if(CLEAN_TIME_SEC>0)  //��ϴʱ���Լ�
        {
             CLEAN_TIME_SEC--;
        }
        else
        {
             CLEAN_TIME_SEC=0 ;   
        }
        
        if(++xSEC_FilterOutTime_CNT>=10)  //ÿ10sɨ��һ�� �Ƿ�����о����
        {
            xSEC_FilterOutTime_CNT = 0;
            if(work1_hour>=SET_WORK1_HOUR)//��һ����о
            {
                F_FilterOutTime = 1;
            }
            if(work2_hour>=SET_WORK2_HOUR)//�ڶ�����о
            {
                F_FilterOutTime = 2;
            }
            if(work3_hour>=SET_WORK3_HOUR)//��һ����о
            {
                F_FilterOutTime = 3;
            }
            if(work4_hour>=SET_WORK4_HOUR)//�ڶ�����о
            {
                F_FilterOutTime = 4;
            }
            
            if(F_FilterOutTime != 0)
            {
                if(F_BEEP2 == 0)
                {
                    F_BEEP2 = 1;
                    speek_duo(150,50,10);
                }
            }
            else
            {
                F_BEEP2 = 0;
            }
        }
        
        if(F_FilterSet == 1)
        {
            if(++xSCE_SetWait_CNT>=15) //15s  ������о��λģʽʱ������ȴ�15s�޲������Զ��˳�
            {
                F_FilterSet = 0;
            }
        }
        else
        {
            xSCE_SetWait_CNT = 0;
        }
    }
}

static void Scan_xMIN(void)
{
    if(F_1MIN == 1)
    {
        F_1MIN = 0;
        
        if(F_WaterProduction == 1)
        {
            if(++F_WaterProduction_CNT1>=10)
            {
                F_WaterProduction_CNT1 = 0;
                F_WashAccumulateWork_10min = 1;
            }
            
            if(++F_WaterProduction_CNT2>=120)
            {
                F_WaterProduction_CNT2 = 0;
                F_ZHISHUICHAOSHI = 1;
                speek_duo(150,50,5);
            }
            
            if(++work_10min>=10)  //ÿ10min�洢1����о����ʱ��
            {
                work_10min = 0;
                if(++work_10min>=6)
                {
                    work_10min = 0; 
                    work1_hour++ ;
                    work2_hour++ ; 
                    work3_hour++ ;
                    work4_hour++ ;
                } 
                EEPROM_WRITE() ; 
            }
                
        }
        else
        {
            F_WaterProduction_CNT2 = 0;
        }
    }
}


static void Scan_xHour(void)
{
    if(F_1HOUR == 1)
    {
        F_1HOUR = 0;
        if(F_WaterProduction == 0)
        {
            if(++F_WaterFull_CNT>=4)
            {
                F_WaterFull_CNT = 0;
                F_WashAccumulateFull_4h = 1;
            }
        }
        
    }
}


void Check_Leak(void)//©ˮ��� 10ms����һ��
{
    
       if(P0_3 == 0)
       {
           if(++Tim_cnt>=500)
            {
                Tim_cnt=500;
                F_LOUSHUI=1;
                
                if(F_BEEP1 == 0)
                {
                    F_BEEP1 = 1;
                    speek_duo(150,50,5);
                }

            }
       }
       else
		{
			Tim_cnt=0;
            F_BEEP1 = 0;
		}
}
//===============================================================================
void Fun_Handle(void)
{
    CLR_WDT;
    TIMER_SCAN();  //��ʱ���������ֳ� 1ms��10ms��100ms��500ms��1s��1min��1h
    JudgeOneStringEnd();
    
    Scan_1ms();
    Scan_10ms();
    Scan_100ms();
    Scan_500ms();
    Scan_xSEC();
    Scan_xMIN();
    Scan_xHour();
}