/******************* (C) COPYRIGHT 2009~2017 holychip **************************
* File Name          : Buzzer_Driver.h
* Author             : Taboo.Z�Z
* Version            : V1.00
* Date               : 10/10/2017
********************************************************************************


*******************************************************************************/
#ifndef __Buzzer_Driver_H__
#define __Buzzer_Driver_H__

sbit    beep = P2^4 ;       //������

extern bit F_BEEP1,F_BEEP2,F_BEEP3,F_BEEP4,F_BEEP5;


//unsigned char   speek_dd,speekk,speek_pp,speek_countt;
extern unsigned char xdata  buz_on ; 
void    speek_manage0() ;
void    speek_dan0(u8 speek_d_tmp) ;//ʱ��Ϊ10MS*timers_20
//speek_p_tmp�����ڣ�speek_d_tmp�����ʱ�䣬speek_count_tmp�Ǵ���
void speek_duo(u8 speek_p_tmp,u8 speek_d_tmp,u8 speek_count_tmp);



#endif  /* __Buzzer_Driver_H__ */
