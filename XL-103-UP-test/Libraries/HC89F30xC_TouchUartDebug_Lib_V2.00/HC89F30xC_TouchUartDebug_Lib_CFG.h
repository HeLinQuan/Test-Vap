/******************* (C) COPYRIGHT 2009~2021 holychip **************************
* File Name          : HC89F30xC_TouchUartDebug_Lib_CFG.h
* Author             : Touch Team�Z
* Version            : V2.0.0.0
* Date               : 2020/05/29
********************************************************************************

ע������TouchUartDebugLib��ͷ�ĺ궨�壬�û����Ը���ʵ�ʵ�����Ҫ���޸ĺ��������

*******************************************************************************/
#ifndef __HC89F30xC_TouchUartDebug_Lib_CFG_H__
#define __HC89F30xC_TouchUartDebug_Lib_CFG_H__

//===================================================================================================
//�������Կ���  
//						0����ֹ����ʱ���ش������Գ��򣬴�������ȷ������ѡ��0��
//						1����������ʱ���ش������Գ��򣬴�ʱ����ͨ���������Թ��߼�����������ȡ�ڲ�������ݣ������û�����ʱ���Դ�������
#define	TouchUartDebugLib_SW				0

//===================================================================================================
//�������ڵ��Բ������趨���������޸ģ������޸�ʱ�����û�����ȷ�����貨�����Ƿ�����
#define TouchUartDebugLib_BAUDRATE  		1000000

// ѡ��������ͨ��ʱ���ݶ˿ڣ� ��ʽTouchUartDebugLib_TXD_Px_y���������궨��Ϊ��#define TouchUartDebugLib_TXD_P3_5" ��ʾ��������ͨ��ʱѡ��P3.5 Ϊ Touch_TXD�˿�
#define TouchUartDebugLib_TXD_P3_4     

//�������ģʽ�����������趨��һ�㲻��Ҫ�޸�
#define TouchUartDebugLib_TXD_PORT_Levelx    GPIO_Out_PP

#endif /*__HC89F30xC_TouchUartDebug_Lib_CFG_H__*/