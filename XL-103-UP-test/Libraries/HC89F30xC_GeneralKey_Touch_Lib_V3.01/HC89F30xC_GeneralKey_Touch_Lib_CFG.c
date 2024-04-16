/******************* (C) COPYRIGHT 2009~2022 holychip **************************
* File Name          : HC89F30xC_GeneralKey_Touch_Lib_CFG.c
* Author             : Touch Team�Z
* Version            : V3.0.1.0
* Date               : 2022/08/08
********************************************************************************

ע�����ļ��������û������޸ģ�

*******************************************************************************/
//===================================================================================================
#include "HC_DEFINE.H"
#include "HC89F30xC_GeneralKey_Touch_Lib_V3.01\HC89F30xC_GeneralKey_Touch_Lib_CFG.h"
#include "HC89F30xC_GeneralKey_Touch_Lib_V3.01\HC89F30xC_GeneralKey_Touch_Auxiliary.h"
#include "HC89F30xC_GeneralKey_Touch_Lib_V3.01\HC89F30xC_GeneralKey_Touch_Lib_Build_Message.h"

//===================================================================================================

#define TK_CH_MAX  		21
uc8 CODE_INTERNAL_INDEX[TK_CH_MAX] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};

//===================================================================================================
uc8  	CODE_TK_CH_MASK[21]             = HCTouchLib_TK_CH_MASK;
uc8  	CODE_TK_LONGKEY[21]             = HCTouchLib_TK_LONGKEY;
uc8		CODE_CHANNEL_CALIBRATE_SW       = 1;
uc8		CODE_CALIBRATE_DEFLECTED_AREA   = 100;
uc16	CODE_CALIBRATE_TARGET_LINE      = 0;
uc8		CODE_DSCR                       = HCTouchLib_DSCR;
uc8		CODE_CTKDS_PRSDIV               = (0 << 4) | (1 << 3) | 0;
uc8		CODE_VD_RV                      = (HCTouchLib_VD << 4) | 0;
uc8		CODE_RBS                        = (0 << 7) | HCTouchLib_RBS;
uc8		CODE_VD							= HCTouchLib_VD;
uc8		CODE_RBSEL						= HCTouchLib_RBS;
uc16	CODE_OVERLOW_TIME               = HCTouchLib_OVERLOW_TIME;
uc8		CODE_CONFIRM_TOUCH_TIME         = HCTouchLib_CONFIRM_TOUCH_TIME;
uc8		CODE_CONFIRM_NOTOUCH_TIME       = HCTouchLib_CONFIRM_NOTOUCH_TIME;
uc8		CODE_LIMIT_FACTOR               = HCTouchLib_LIMIT_FACTOR;
uc16	CODE_FINGER_THRESHOLD[21]       = HCTouchLib_FINGER_THRESHOLD;
uc8		CODE_OPENED_TK_AMOUNT           = HCTouchLib_OPENED_TK_AMOUNT;
uc8 	CODE_TK_CH_MAX                  = TK_CH_MAX;
uc8		CODE_FILTER_DEPTH				= HCTouchLib_FILTER_DEPTH;
uc16	CODE_RAWDATA_FULL				= ((HCTouchLib_DSCR+1)*256-1);
//===================================================================================================
ux16	XDATA_RawData		[HCTouchLib_OPENED_TK_AMOUNT];
ux16	XDATA_RawDataBuf	[HCTouchLib_OPENED_TK_AMOUNT];
sx16 	XDATA_BaseLine		[HCTouchLib_OPENED_TK_AMOUNT];
ux8 	XDATA_TouchCnt		[HCTouchLib_OPENED_TK_AMOUNT];
ux8 	XDATA_NoTouchCnt	[HCTouchLib_OPENED_TK_AMOUNT];
ux16	XDATA_LongRstCnt	[HCTouchLib_OPENED_TK_AMOUNT];
ux16	XDATA_OverZeroCnt	[HCTouchLib_OPENED_TK_AMOUNT];
ux8 	XDATA_OverLowCnt	[HCTouchLib_OPENED_TK_AMOUNT];
ux8		XDATA_OpenChannel	[HCTouchLib_OPENED_TK_AMOUNT];
ux16	XDATA_ConfirmLongTouchTime	= HCTouchLib_CONFIRM_LONGTOUCH_TIME;
ux16	XDATA_ConfirmShortTouchTime	= HCTouchLib_CONFIRM_SHORTTOUCH_TIME;
ux16	XDATA_OverZeroTime	    	= HCTouchLib_OVERZERO_TIME;
ux16	XDATA_ConfirmTouchRadio 	= HCTouchLib_CONFIRM_TOUCH_RATIO;
ux16	XDATA_ConfirmNoTouchRadio 	= HCTouchLib_CONFIRM_NOTOUCH_RATIO;
/******************************************************************************************************
 * Revision history:
 *
 * Revision 1.01  	2017/12/18 14:10 Taboo.Z�Z
 * Revision 1.0.2.0	2018/07/20 16:31 Jing.L�Z
 * Revision 1.0.3.0	2018/09/10 14:38 Jing.L�Z
 * Add: 1�����ӳ����Լ������Զ���λ����
 *		2���̶��˲��ֲ�������
 * Revision 1.0.4.0	2019/03/06 13:59 Touch Team
 * Add: 1���������Чʱ������п�������
 *		2�����Ӳ��ֺ����ڲ�ʹ�ò���
 *		3������һ��16λ��LONGTOBIN����������TKͨ��ʹ��
 * Revision 1.0.5.0	2019/09/17 19:11 Touch Team 
 *	    1��������ֵ��������
 *		2��������ֵ����
 *		3����������Ͱ��������
 * Revision 2.0.0.0	2020/05/29 15:29 HA Team 
 *      1������IO�����������ѡ��
 *      2�����Ӷ̰�����Чʱ������
 * Revision 3.0.0.0	2021/04/07 14:06 HA Team 
 *      1��ɾ����ͬ�ͺŵ�ͨ��ѡ��
 *      2�����Ӷ̰�����Чʱ������
 *
*******************************************************************************************************/ 