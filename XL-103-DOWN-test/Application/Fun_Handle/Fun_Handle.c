#include "define.h"

/*******全局变量*******/
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


/*******局部变量*******/
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

bit F_WashFull_Flag = 1;

static void ParamHandleInit(void)
{
    F_WashFirst_10S = 1;  //机器上电冲洗标志位置 1
    CLEAN_TIME_SEC = 0;
    
    F_WaterProduction = 0;  //制水标志
    F_ZHISHUICHAOSHI = 0;  //制水超时标志位置0
    F_QUESHUI = 0;         //缺水标志位置0
    F_LOUSHUI = 0;        //漏水标志位置0
    
    F_Wash = 1;  //冲洗标志位置0
    
    F_SHUIBEN = 0; //水泵标志位置0
    F_CXF = 0;   //冲洗阀标志位置0
    
    F_FilterOutTime = 0;  //滤芯到期标志位
}

/****变量初始化****/
void ParamInit(void)
{ 
      ParamTimtInit();
      ParamHandleInit();
      ParamKeyInit(); 
//    ParamAdworkInit();
}
/*************************************************************************
压力开关检测  10ms扫描一次  
*************************************************************************/
void yali_sw_check (void)    //浮球：接通为0  断开为1
{
    if(yali_low_sw==0)	  //有水 
    {  
        low_count+=50 ;
        if(low_count>=1000)   //10秒 
        {
            low_count = 1000 ; 							 
            F_yali_low = 1 ;   //低压开关闭合 
        }
    }
	else		    //无水 
	{
        if(--low_count<=1)
        {
            low_count = 1 ;
            F_yali_low = 0 ;     //低压开关断开  缺水  
        }
	 }
	
     
    if(yali_high_sw==0)   //高压开关 常闭开关   ，为1 是 断开  0为闭合
    {
        if(++high_count>=50)
        {
            high_count = 50 ;
            F_yali_high = 0 ;  //高压开关闭合
        }
    }
    else   //水满
    {
        if(--high_count<=1)
        {
                high_count = 1 ;
                F_yali_high = 1 ;   //高压开关断开 
        }
    }
}

void RO_SIGN_chuli(void)
{
	if(F_yali_low==0) //缺水
	{  
		if(F_QUESHUI==0)
		{
			speek_duo(150,50,10);
		}
		F_QUESHUI = 1 ; //缺水 
	}
	else 
	{
		F_QUESHUI = 0 ;   //不缺水 		 
		if(F_yali_high==0) 
		{ 
			F_WaterProduction = 1 ; //制水工作 
            if(F_WashFull_Flag == 0)
            {
                F_WashFull_Flag = 1;
            }
		}
         else
		{
			F_WaterProduction = 0 ; //制水完成 ，水满
            if(F_WashFull_Flag == 1)
            {
                F_WashFull_Flag = 0;
                F_WashFull = 1;
            }
		}					  
	}			 
}
/**************************************************************************
RO系统制水工作  //100MS 扫描一次 
**************************************************************************/
void RO_SYS_WORK(void)
{  
	if((F_ZHISHUICHAOSHI==1)||(F_QUESHUI == 1)||(F_LOUSHUI == 1)||(F_Power == 0)) //出错后关闭阀门、泵
	 { 
            F_SHUIBEN = 0;
            F_CXF = 0;
	 }
	 else
	 {
		  if(F_Wash == 1)  //冲洗
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
                if(F_WaterProduction == 1)   //制水
                {
                    F_SHUIBEN = 1;
                    F_CXF = 0;
                }
                else                        //水满
                { 
                    F_SHUIBEN = 0;
                    F_CXF = 0;
                }
          }
      }
}

/**********************************************************
冲洗模式  10ms 
***********************************************************/
void RO_CLEAN_check(void)
{
   if(F_WashFirst_10S==1)  //上电冲洗30s
    {
        CLEAN_TIME_SEC = 30;  
        F_Wash = 1 ; 
        F_WashFirst_10S = 0;  //
    }
    else if(F_WashAccumulateFull_4h == 1)   //机器处于水满状态累计4h，冲洗20s
    {
        CLEAN_TIME_SEC = 20;  
        F_Wash =1 ;
        F_WashAccumulateFull_4h = 0;
    }
    else if((F_WashAccumulateWork_10min == 1)&&(F_WaterProduction == 1))   //机器累计制水10min，水满后冲洗10s
    {
        CLEAN_TIME_SEC = 10;  
        F_Wash =1 ; 
        F_WashAccumulateWork_10min = 0;
    }
    else if(F_WashFull == 1)    //水满冲洗 10s
    {
        CLEAN_TIME_SEC = 10;  
        F_Wash =1 ; 
        F_WashFull = 0;
    }
}

/**********************************************************
阀门、泵检测函数  100ms 
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


static void Scan_10ms(void)
{
    if(F_10MS==1)
	  {
	      F_10MS = 0; 
          //speek_manage0();
          //KEY_Handle(KEY_TEMP);  //按键函数调用
          yali_sw_check();
          
          Check_Leak();   //漏水检测
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
            if(buz_on==0)
		{
             display();	
        }
            
			  
        }
        
        DIS_MANAGE();
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
			//  DIS_TO_MAIN_SEND();
        
    }
}

static void Scan_xSEC(void)
{
    if(F_1SEC == 1)
    {
        F_1SEC = 0;
       
        if(CLEAN_TIME_SEC>0)  //冲洗时间自减
        {
             CLEAN_TIME_SEC--;
        }
        else
        {
             CLEAN_TIME_SEC=0 ;   
        }
        
//        if(++xSEC_FilterOutTime_CNT>=10)  //每10s扫描一次 是否有滤芯到期
//        {
//            xSEC_FilterOutTime_CNT = 0;
//            if(work1_hour>=SET_WORK1_HOUR)//第一组滤芯
//            {
//                F_FilterOutTime = 1;
//            }
//            if(work2_hour>=SET_WORK2_HOUR)//第二组滤芯
//            {
//                F_FilterOutTime = 2;
//            }
//            if(work3_hour>=SET_WORK3_HOUR)//第一组滤芯
//            {
//                F_FilterOutTime = 3;
//            }
//            if(work4_hour>=SET_WORK4_HOUR)//第二组滤芯
//            {
//                F_FilterOutTime = 4;
//            }
//            
//            if(F_FilterOutTime != 0)
//            {
//                if(F_BEEP2 == 0)
//                {
//                    F_BEEP2 = 1;
//                    speek_duo(150,50,10);
//                }
//            }
//            else
//            {
//                F_BEEP2 = 0;
//            }
//        }
        
        
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
            
            if(++work_10min>=10)  //每10min存储1次滤芯寿命时间
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
//===============================================================================
void Fun_Handle(void)
{
    CLR_WDT;
    TIMER_SCAN();  //定时器基数，分出 1ms、10ms、100ms、500ms、1s、1min、1h
    JudgeOneStringEnd();
    
    Scan_10ms();
    Scan_100ms();
    Scan_500ms();
    Scan_xSEC();
    Scan_xMIN();
    Scan_xHour();
}