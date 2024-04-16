/******************* (C) COPYRIGHT 2009~2017 holychip **************************
* File Name          : Buzzer_Driver.c
* Author             : Taboo.Z�Z
* Version            : V1.00
* Date               : 10/10/2017
********************************************************************************


*******************************************************************************/
#include "define.h"
bit F_BEEP1=0,F_BEEP2=0,F_BEEP3=0,F_BEEP4=0,F_BEEP5=0;
unsigned char xdata  speek_dd,speekk,speek_pp,speek_countt;
unsigned char xdata  buz_on ;  
//***************************************************************/
/*ģ �� ��: speek_manage            �����ͺţ�����                      */
/*�ļ�����: �����������                                                    */
/*�� �� �ˣ��� ��                   ��      �ڣ�2011-12-20                  */
/*�� �� �ˣ�                        ��      �ڣ�                                */
/*����������speek_pΪ�������ڣ�speek_dΪ���ʱ�䣬                  */
/*speek_countΪ���ʱ��                                                     */
/*����˵����                                                                    */
/*��    ����                                                                        */
//***************************************************************/

void    speek_manage0()
{
    if(speek_dd>speekk)
    {
        buz_on=2;                   //��ʼ��
    }//
    else
    {
        buz_on=0;
        if(speekk>speek_pp)       //�����ڽ���
        {
           if(speek_countt>0)
           {
                speek_countt-=1;
                speekk=0;
           }
           else
           {
                speek_pp=0;
                speek_dd=0;
           }
        }
    }//
    if(++speekk>250)
     {
        speekk=250;
     }//
}//


void speek_dan0(u8 speek_d_tmp)//ʱ��Ϊ10MS*timers_20
{
    if(speekk>speek_d_tmp)
    {
        speekk=0;
    }
    speek_dd=speek_d_tmp;
    speek_pp=0;                      //���ΰ�����Чȥ����ΰ�����Ч��
    speek_countt=0;
}
//speek_p_tmp�����ڣ�speek_d_tmp�����ʱ�䣬speek_count_tmp�Ǵ���
void speek_duo(u8 speek_p_tmp,u8 speek_d_tmp,u8 speek_count_tmp)
{
    if(speekk>speek_p_tmp)
    {
        speekk=0;
    }
    speek_dd=speek_d_tmp;
    speek_pp=speek_p_tmp;
    speek_countt=speek_count_tmp-1;
}

/*********************************END OF FILE************************************/
/******************* (C) COPYRIGHT 2009~2017 holychip ***************************/