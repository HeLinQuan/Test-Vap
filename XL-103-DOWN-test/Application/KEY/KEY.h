/******************* (C) COPYRIGHT 2009~2017 holychip **************************
* File Name          : KEY.h
* Author             : Taboo.Z¤Z
* Version            : V1.00
* Date               : 10/10/2017
********************************************************************************


*******************************************************************************/
#ifndef __KEY_H__
#define __KEY_H__
//===============================================================================
#define KEY_L           TK7 				
#define KEY_R			TK11 


extern u32 KEY_TEMP;
extern u8  KEY_CNT;
extern u32 KEY_TEMP;
extern u8  KEY_CNT;
extern bit F_Power; 
extern bit F_FilterSet;
extern unsigned char Filter_SetMode;
extern unsigned char xSCE_SetWait_CNT;

/*************************************************/

void KEY_Handle(u32 key_flag);
void ParamKeyInit(void);
void ColseAllWater(void);
#endif /* __KEY_H__ */
