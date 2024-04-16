/******************* (C) COPYRIGHT 2009~2017 holychip **************************
* File Name          : Buzzer_Driver.c
* Author             : Taboo.Z
* Version            : V1.00
* Date               : 10/10/2017
********************************************************************************


*******************************************************************************/
#include "define.h"
bit F_BEEP1=0,F_BEEP2=0,F_BEEP3=0,F_BEEP4=0,F_BEEP5=0;
unsigned char xdata  speek_dd,speekk,speek_pp,speek_countt;
unsigned char xdata  buz_on ;  
//***************************************************************/
/*模 块 名: speek_manage            驱动型号：海尔                      */
/*文件名称: 声音处理程序                                                    */
/*创 建 人：张 铸                   日      期：2011-12-20                  */
/*修 改 人：                        日      期：                                */
/*功能描述：speek_p为声音周期，speek_d为响的时间，                  */
/*speek_count为响的时间                                                     */
/*其他说明：                                                                    */
/*版    本：                                                                        */
//***************************************************************/

void    speek_manage0()
{
    if(speek_dd>speekk)
    {
        buz_on=2;                   //开始响
    }//
    else
    {
        buz_on=0;
        if(speekk>speek_pp)       //本周期结束
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


void speek_dan0(u8 speek_d_tmp)//时间为10MS*timers_20
{
    if(speekk>speek_d_tmp)
    {
        speekk=0;
    }
    speek_dd=speek_d_tmp;
    speek_pp=0;                      //单次按键有效去掉多次按键有效。
    speek_countt=0;
}
//speek_p_tmp是周期，speek_d_tmp是响的时间，speek_count_tmp是次数
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