/******************* (C) COPYRIGHT 2009~2021 holychip **************************
* File Name          : HC89F30xC_GeneralKey_Touch_Lib.h
* Author             : Touch Team�Z
* Version            : V3.0.0.0
* Date               : 2021/04/08
********************************************************************************

ע�����ļ��û������޸ģ�

*******************************************************************************/
#ifndef __HC89F30xC_GeneralKey_Touch_Lib_H__
#define __HC89F30xC_GeneralKey_Touch_Lib_H__

//===================================================================================================
extern void CTK_Init(void);			    //���ô˳���ǰ�����ȴ����ж��ܿ��أ�EA=1������ΪCTK��ʼ��ʱ����ҪCTK�ж����
extern void CTK_ISR_Handle(void);       //�˺���������CTK�ж�����е���
extern void Touch_Signal_Handle(void);  //����ɨ�����һ�ֺ󣬵���һ��
extern void Scan_Pause(void);           //CTKɨ����ͣ
extern void Scan_Continue(void);        //CTKɨ�����
extern void BaseLineReset(void);        //��λ����ͨ������

//===================================================================================================
extern bit  OneCycleScanDone;           //ɨ��һ����λһ�Σ�һ��ʱ�� �� ����ͨ��ɨ��ʱ�� * �����ļ��ͨ������
extern ux32 TouchKeyFlag;               //������Ӧ��־��ÿ1BIT ��Ӧһ��ͨ����BIT��Ӧλ��HCTouchLib_TK_CH_MASK���Ӧ
extern ux16	XDATA_CONFIRM_LONGTOUCH_TIME;//���ó�������Ч�ʱ��
extern ux16	XDATA_CONFIRM_SHORTTOUCH_TIME;//���ö̰�����Ч�ʱ��
extern ux16	XDATA_OverZeroTime; 		//��ֵ����¼���ֵ
extern ux16	XDATA_ConfirmTouchRadio;	//����ȷ�ϰ�����Чֵ����
extern ux16	XDATA_ConfirmNoTouchRadio;	//����ȷ�ϰ�����Чֵ����
extern uc8  TOUCH_LIB_VERSION[];       	//������汾���


#define TK0		0x000001
#define TK1		0x000002
#define TK2		0x000004
#define TK3		0x000008
#define TK4		0x000010
#define TK5		0x000020
#define TK6		0x000040
#define TK7		0x000080
#define TK8		0x000100
#define TK9		0x000200
#define TK10	0x000400
#define TK11	0x000800
#define TK12	0x001000
#define TK13	0x002000
#define TK14	0x004000
#define TK15	0x008000
#define TK16	0x010000
#define TK17	0x020000
#define TK18	0x040000
#define TK19	0x080000
#define TK20	0x100000


#endif /*__HC89F30xC_GeneralKey_Touch_Lib_H__*/
