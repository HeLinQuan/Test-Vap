#ifndef __ADC_TDS_H__ 
#define __ADC_TDS_H__ 

extern unsigned int TDS_RO , TDS_YS  , TDS_RO_SUM ,  TDS_YS_SUM , TDS_RO_avg, TDS_YS_avg  ;   // ´¿Ë®TDS  Ô­Ë®TDS


sbit  TDS1_IO1 = P2^3 ;  
sbit  TDS1_IO2 = P2^1 ;  
#define  TDS_RO_ADD  {TDS1_IO1 =1 ; TDS1_IO2 = 0 ;} ;
#define  TDS_RO_DOWN {TDS1_IO1 =0 ; TDS1_IO2 = 1 ;} ; 
#define  TDS_RO_STOP {TDS1_IO1 =0 ; TDS1_IO2 = 0 ;} ; 


sbit  TDS2_IO1 = P0^2 ;  
sbit  TDS2_IO2 = P2^5 ;  

#define  TDS_YS_ADD  {TDS2_IO1 =1 ; TDS2_IO2 = 0 ;} ;
#define  TDS_YS_DOWN {TDS2_IO1 =0 ; TDS2_IO2 = 1 ;} ; 
#define  TDS_YS_STOP {TDS2_IO1 =0 ; TDS2_IO2 = 0 ;} ; 

void TDS_RO_read(void)	;
void TDS_YS_read(void)	;
#endif
