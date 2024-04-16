/******************* (C) COPYRIGHT 2009~2021 holychip **************************
* File Name          : HC89F30xC_GeneralKey_Touch_Lib.h
* Author             : Touch Team
* Version            : V3.0.0.0
* Date               : 2021/04/08
********************************************************************************

注：本文件用户不可修改！

*******************************************************************************/
#ifndef __HC89F30xC_GeneralKey_Touch_Lib_H__
#define __HC89F30xC_GeneralKey_Touch_Lib_H__

//===================================================================================================
extern void CTK_Init(void);			    //调用此程序前必须先打开总中断总开关（EA=1），因为CTK初始化时，需要CTK中断配合
extern void CTK_ISR_Handle(void);       //此函数必须在CTK中断入口中调用
extern void Touch_Signal_Handle(void);  //建议扫描完成一轮后，调用一次
extern void Scan_Pause(void);           //CTK扫描暂停
extern void Scan_Continue(void);        //CTK扫描继续
extern void BaseLineReset(void);        //复位所有通道基线

//===================================================================================================
extern bit  OneCycleScanDone;           //扫描一轮置位一次，一轮时间 ≈ 单个通道扫描时间 * 开启的检测通道个数
extern ux32 TouchKeyFlag;               //按键响应标志，每1BIT 对应一个通道，BIT对应位与HCTouchLib_TK_CH_MASK相对应
extern ux16	XDATA_CONFIRM_LONGTOUCH_TIME;//设置长按键生效最长时间
extern ux16	XDATA_CONFIRM_SHORTTOUCH_TIME;//设置短按键生效最长时间
extern ux16	XDATA_OverZeroTime; 		//阈值零更新计数值
extern ux16	XDATA_ConfirmTouchRadio;	//触摸确认按键有效值比例
extern ux16	XDATA_ConfirmNoTouchRadio;	//触摸确认按键无效值比例
extern uc8  TOUCH_LIB_VERSION[];       	//触摸库版本编号


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
