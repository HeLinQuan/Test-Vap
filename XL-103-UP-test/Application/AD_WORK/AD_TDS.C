#include "define.h"
unsigned char xdata ERR_CODE; 

unsigned int TDS_RO=0 , TDS_YS=0  , TDS_RO_SUM=0 ,  TDS_YS_SUM=0 , TDS_RO_avg=0, TDS_YS_avg=0  ;   // 纯水TDS  原水TDS


unsigned int AD_SUM  , AD_DC1 ,AD_DC2;

unsigned int xdata TEMP_BUFF[10] ; 

unsigned int xdata TEMP_BUFFYS[20] ;  

unsigned char ad_cnt ,ad_cnt2; 
void TDS_YS_read(void)
{
	  unsigned char  j , i ; 
	  unsigned int temp_wd2 ; 
	  unsigned int temp_tt ;  
	  TDS_YS_ADD ;      //IO正向AD转换
	  for(i=0 ;i<10 ;i++)
	  {
				ADCC1 = 0x02;						//选择外部通道 2
				ADCC0 |= 0x40;					//启动ADC转换
				while(!(ADCC0&0x20));		//等待ADC转换结束
				ADCC0 &=~ 0x20;					//清除标志位	
				AD_SUM+= ADCR;			    //获取ADC的值	
    }			
	  AD_DC1 = AD_SUM/100 ; 
	  AD_SUM = 0 ; 	
		TDS_YS_DOWN ;     //IO反向转换  
    for(i=0 ;i<10 ;i++)
	  {
				ADCC1 = 0x02;						//选择外部通道2
				ADCC0 |= 0x40;					//启动ADC转换
				while(!(ADCC0&0x20));		//等待ADC转换结束
				ADCC0 &=~ 0x20;					//清除标志位	
				AD_SUM+= ADCR;			    //获取ADC的值	
    }			
	  AD_DC2 = AD_SUM/100 ; 
	  AD_SUM = 0 ; 

		
    TDS_YS_STOP;     //IO停止
		
		TEMP_BUFFYS[ad_cnt2]	 = AD_DC1 ; //320ms 更新一次 	真实温度值 	
		if(++ad_cnt2>10)
		{
				ad_cnt2 = 0 ;	
				for(j=0 ;j<9 ; j++)    
				{
								for(i= 0 ; i<(10-j) ; i++)
								{
											if(TEMP_BUFFYS[i]>TEMP_BUFFYS[i+1])
											{
													temp_wd2 = TEMP_BUFFYS[i] ; 
													TEMP_BUFFYS[i]=TEMP_BUFFYS[i+1] ;
													TEMP_BUFFYS[i+1] = temp_wd2  ;
											}
								}
				}   
				for(i=2 ; i<9 ; i++)
				{
						temp_tt+= TEMP_BUFFYS[i] ;
				}
				TDS_YS=(temp_tt/8)*1.25 ;
				if(TDS_YS<30)
				{
					  TDS_YS=TDS_YS;
				}
				else if(TDS_YS<45)
				{
					  TDS_YS=TDS_YS+TDS_YS*0.15 ;
				}
			  else if(TDS_YS<60)
				{
					  TDS_YS=TDS_YS+TDS_YS*0.2 ;
				}
				else if(TDS_YS<75)
				{
					  TDS_YS=TDS_YS+TDS_YS*0.25 ;
				}
				else if(TDS_YS<90)
				{
					  TDS_YS=TDS_YS+TDS_YS*0.3 ;
				}	
				else if(TDS_YS<105)
				{
					  TDS_YS=TDS_YS+TDS_YS*0.35 ;
				}
				else if(TDS_YS<120)
				{
					  TDS_YS=TDS_YS+TDS_YS*0.4 ;
				}	
				else if(TDS_YS<135)
				{
					  TDS_YS=TDS_YS+TDS_YS*0.45;
				}
				else if(TDS_YS<150)
				{
					  TDS_YS=TDS_YS+TDS_YS*0.5 ;
				}	
				else if(TDS_YS<165)
				{
					  TDS_YS=TDS_YS+TDS_YS*0.55 ;
				}
				else if(TDS_YS<180)
				{
					  TDS_YS=TDS_YS+TDS_YS*0.6 ;
				}	
				else if(TDS_YS<195)
				{
					  TDS_YS=TDS_YS+TDS_YS*0.7 ;
				}
			  else if(TDS_YS<210)
				{
					  TDS_YS=TDS_YS+TDS_YS*0.8 ;
				}	
				else if(TDS_YS<225)
				{
					  TDS_YS=TDS_YS+TDS_YS*0.85 ;
				}
				else if(TDS_YS<240)
				{
					  TDS_YS=TDS_YS+TDS_YS*0.9 ;
				}	
				else if(TDS_YS<250)
				{
					  TDS_YS=TDS_YS+TDS_YS*1.0 ;
				}
				else if(TDS_YS<260)
				{
					  TDS_YS=TDS_YS+TDS_YS*1.1 ;
				}
				else if(TDS_YS<270)
				{
					  TDS_YS=TDS_YS+TDS_YS*1.2 ;
				}
				else if(TDS_YS<280)
				{
					  TDS_YS=TDS_YS+TDS_YS*1.3 ;
				}	
				else if(TDS_YS<285)
				{
					  TDS_YS=TDS_YS+TDS_YS*1.4 ;
				}
				else if(TDS_YS<290)
				{
					  TDS_YS=TDS_YS+TDS_YS*1.5 ;
				}	
				else if(TDS_YS<295)
				{
					  TDS_YS=TDS_YS+TDS_YS*1.65 ;
				}
				else if(TDS_YS<300)
				{
					  TDS_YS=TDS_YS+TDS_YS*1.8 ;
				}
				else if(TDS_YS<305)
				{
					  TDS_YS=TDS_YS+TDS_YS*1.95 ;
				}
				else if(TDS_YS<310)
				{
					  TDS_YS=TDS_YS+TDS_YS*2.2 ;
				}
				else if(TDS_YS<315)
				{
					  TDS_YS=TDS_YS+TDS_YS*2.35 ;
				}
				else if(TDS_YS<320)
				{
					  TDS_YS=TDS_YS+TDS_YS*2.5 ;
				}
				else if(TDS_YS<325)
				{
					  TDS_YS=TDS_YS+TDS_YS*2.8 ;
				}
				else //if(TDS_YS<700)
				{
					  TDS_YS=TDS_YS+TDS_YS*3;
				}	
				if(TDS_YS>=999) TDS_YS=999;
 				temp_tt = 0 ; 	 
		} 
}
	

void TDS_RO_read(void)
{
	  unsigned char  j , i ; 
	  unsigned int temp_wd ; 
	  unsigned int temp_ttt ;  
	  TDS_RO_ADD ;      //IO正向AD转换
	  for(i=0 ;i<10 ;i++)
	  {
				ADCC1 = 0x0B;						//选择外部通道11
				ADCC0 |= 0x40;					//启动ADC转换
				while(!(ADCC0&0x20));		//等待ADC转换结束
				ADCC0 &=~ 0x20;					//清除标志位	
				AD_SUM+= ADCR;			    //获取ADC的值	
    }			
	  AD_DC1 = AD_SUM/100 ; 
	  AD_SUM = 0 ; 	
		TDS_RO_DOWN ;     //IO反向转换  
    for(i=0 ;i<10 ;i++)
	  {
				ADCC1 = 0x0B;						//选择外部通道11
				ADCC0 |= 0x40;					//启动ADC转换
				while(!(ADCC0&0x20));		//等待ADC转换结束
				ADCC0 &=~ 0x20;					//清除标志位	
				AD_SUM+= ADCR;			    //获取ADC的值	
    }			
	  AD_DC2 = AD_SUM/10 ; 
	  AD_SUM = 0 ; 	
    TDS_RO_STOP;     //IO停止
		
		TEMP_BUFF[ad_cnt]	 = AD_DC1 ; //320ms 更新一次 	真实温度值 	
		if(++ad_cnt>10)
		{
				ad_cnt = 0 ;	
				for(j=0 ;j<9 ; j++)    
				{
								for(i= 0 ; i<(10-j) ; i++)
								{
											if(TEMP_BUFF[i]>TEMP_BUFF[i+1])
											{
													temp_wd = TEMP_BUFF[i] ; 
													TEMP_BUFF[i]=TEMP_BUFF[i+1] ;
													TEMP_BUFF[i+1] = temp_wd  ;
											}
								}
				}   
				for(i=2 ; i<10 ; i++)
				{
								temp_ttt+= TEMP_BUFF[i] ;
				}
				TDS_RO=((temp_ttt/8)*1.1) ;
				if(TDS_RO>=99)
				{
					  TDS_RO = 99 ; 
				}
 				temp_ttt = 0 ; 	 
		} 
}		  
