/******************* (C) COPYRIGHT 2009~2017 holychip **************************
* File Name          : Fun_Handle.H
* Author             : Taboo.Z�Z
* Version            : V1.00
* Date               : 10/10/2017
********************************************************************************


*******************************************************************************/
#ifndef __Fun_Handle_H__
#define __Fun_Handle_H__

sbit    PUMP    = P1^1 ;    //ˮ��  ��ˮ��
#define SHUIBEN_OFF    PUMP = 0 ;
#define SHUIBEN_ON     PUMP = 1 ;

sbit    ChongXi = P1^2 ;    //  ��ϴ��
#define CXF_OFF        ChongXi = 0 ;
#define CXF_ON         ChongXi = 1 ;


sbit    yali_high_sw = P1^4 ;         //��ѹ����
sbit    yali_low_sw  = P1^5 ;         //��ѹ����

extern bit F_WashFirst_10S;
extern bit F_WaterProduction;
extern bit F_ZHISHUICHAOSHI;
extern bit F_QUESHUI;
extern bit F_LOUSHUI;
extern bit F_Wash;
extern bit F_SHUIBEN;
extern bit F_CXF;
extern unsigned char xdata CLEAN_TIME_SEC;
extern unsigned char xdata F_FilterOutTime;


void Fun_Handle(void);
void ParamInit(void);

#endif /* __Fun_Handle_H__ */
