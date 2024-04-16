/******************* (C) COPYRIGHT 2009~2021 holychip **************************
* File Name          : HC89F30xC_GeneralKey_Touch_Auxiliary.h
* Author             : HA Team
* Version            : V3.0.0.0    
* Date               : 2021/04/07
********************************************************************************

注：凡是HCTouchLib开头的宏定义，用户可以根据实际调试需要，修改后面的数据

*******************************************************************************/
#ifndef __HC89F30xC_GeneralKey_Touch_Auxiliary_H__
#define __HC89F30xC_GeneralKey_Touch_Auxiliary_H__


/****************************************************************************************************/
void TouchRawDataFilter(void);			//触摸RawData滤波函数，此函数必须添加在main.c中，否则程序无法正常运行
void TouchMultibuttonHandle(void);		//组合按键处理，一共三种模式
/****************************************************************************************************/

// 设置RawData滤波深度，打开后系统会对RawData采用递推中位值平均滤波，即对递推数组进行排序后去除最高值和最低值，然后对剩余数据计算平均值
//			0：关闭滤波功能
//			3->15：设置滤波数组长度，如设置为5，则对RawData数据进行排序，然后去除最高值和最低值，剩余的3个数据计算平均得到最终值
#define HCTouchLib_FILTER_DEPTH			0
/****************************************************************************************************/

/****************************************************************************************************/

// 设置按键模式选择
//			0：多按键模式，支持多个按键同时有效			
//			1：单按键模式，超过一个按键有效时，本轮所有按键无效
//			2：双按键模式，同一时间内最多有两个按键有效，且必须为用户设置的组合按键，否则所有按键无效
#define HCTouchLib_MULTIBUTTON 			0


// 设置双按键组成元素，最多提供两组组合按键，必须配合双按键模式使用
//			举例：如果TK0和TK1作为组合按键则在{}填入0,1，如不需使用，填入两个相同值即可
#define HCTouchLib_COMBINATIONKEYA      {2,7}
#define HCTouchLib_COMBINATIONKEYB      {13,14}
#define HCTouchLib_COMBINATIONKEYC      {2,7}
#define HCTouchLib_COMBINATIONKEYD      {13,14}

#endif

/******************************************************************************************************
 * Revision history:
 *
 * Revision 1.01  	2017/12/18 14:10 Taboo.Z
 * Revision 1.0.2.0	2018/07/20 16:31 Jing.L
 * Revision 1.0.3.0	2018/09/10 14:38 Jing.L
 * Revision 1.0.4.0	2019/03/06 13:59 Touch Team
 * Revision 1.0.5.0	2019/09/17 19:23 Touch Team
 * Add: 1、首次增加RawData滤波功能
 * Revision 2.0.0.0	2020/05/29 14:59 HA Team
 * Add: 1、最强按键修改，分为三种模式
 * Revision 3.0.0.0	2021/04/08 08:47 HA Team
 * Add: 1、修改单按键模式以及双按键模式，超过设定要求后所有按键无效
 ******************************************************************************************************/