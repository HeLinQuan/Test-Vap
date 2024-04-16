/******************* (C) COPYRIGHT 2009~2021 holychip **************************
* File Name          : HC89F30xC_GeneralKey_Touch_Lib_Build_Message.h
* Author             : Touch Team�Z
* Version            : V3.0.0.0
* Date               : 2021/04/08
********************************************************************************

ע�����ļ��������û������޸ģ�

*******************************************************************************/
#ifndef __HC89F30xC_GeneralKey_Touch_Lib_Build_Message_H__
#define __HC89F30xC_GeneralKey_Touch_Lib_Build_Message_H__

//================================================================================

//================================================================================
#if (HCTouchLib_DSCR > 255)
#error	"Error��Please setting HCTouchLib_DSCR < 256"
#endif

//================================================================================
#if (HCTouchLib_VD > 3)
#error 	"Error��Please setting 0 <= HCTouchLib_VD <= 3"
#elif (HCTouchLib_VD ==0)
#pragma message "CTK����Դ��ѹ��2V"
#elif (HCTouchLib_VD ==1)
#pragma message "CTK����Դ��ѹ��2.5V"
#elif (HCTouchLib_VD ==2)
#pragma message "CTK����Դ��ѹ��3V"
#elif (HCTouchLib_VD ==3)
#pragma message "CTK����Դ��ѹ��4V"
#endif

//================================================================================
#pragma message "CTK����Ƶ�ʣ�Fosc/2"
#pragma message "CTK��ŵ�Ƶ�ʣ�Fosc/2"
#pragma message "CTK��ŵ�α�������"
#pragma message "CTK�ο���ѹ��0.60V"

//================================================================================
#if (HCTouchLib_RBS > 6)|(HCTouchLib_RBS < 3)
#error 	"Error��Please setting 3 <= HCTouchLib_RBS <= 6"
#elif (HCTouchLib_RBS ==3)
#pragma message "CTK�ŵ���裺4"
#elif (HCTouchLib_RBS ==4)
#pragma message "CTK�ŵ���裺8"
#elif (HCTouchLib_RBS ==5)
#pragma message "CTK�ŵ���裺16"
#elif (HCTouchLib_RBS ==6)
#pragma message "CTK�ŵ���裺32"
#endif

//================================================================================
#if (HCTouchLib_OPENED_TK_AMOUNT > 21)
#error	"Error��Please setting HCTouchLib_OPENED_TK_AMOUNT <= 21"
#endif

//================================================================================
#if (HCTouchLib_CONFIRM_TOUCH_RATIO < 40)|(HCTouchLib_CONFIRM_TOUCH_RATIO > 1000)|(HCTouchLib_CONFIRM_TOUCH_RATIO < HCTouchLib_CONFIRM_NOTOUCH_RATIO)
#error 	"Error��Please setting 40 <= HCTouchLib_CONFIRM_TOUCH_RATIO <= 1000 && HCTouchLib_CONFIRM_NOTOUCH_RATIO < HCTouchLib_CONFIRM_TOUCH_RATIO"
#endif

//================================================================================
#if (HCTouchLib_CONFIRM_NOTOUCH_RATIO < 20)|(HCTouchLib_CONFIRM_NOTOUCH_RATIO > 1000)
#error 	"Error��Please setting 20 <= HCTouchLib_CONFIRM_NOTOUCH_RATIO <= 1000"
#endif

//================================================================================
#if ((HCTouchLib_LIMIT_FACTOR == 1)|(HCTouchLib_LIMIT_FACTOR > 256))
#error 	"Error��Please setting 1 < HCTouchLib_LIMIT_FACTOR < 256"
#endif

//================================================================================
#if ((HCTouchLib_CONFIRM_TOUCH_TIME == 0)|(HCTouchLib_CONFIRM_TOUCH_TIME > 255))
#error	"Error��Please setting 0 < HCTouchLib_CONFIRM_TOUCH_TIME < 256"
#endif

//================================================================================
#if ((HCTouchLib_CONFIRM_NOTOUCH_TIME == 0)|(HCTouchLib_CONFIRM_NOTOUCH_TIME > 255))
#error 	"Error��Please setting 0 < HCTouchLib_CONFIRM_NOTOUCH_TIME < 256"
#endif

//================================================================================
#if (((0 < HCTouchLib_CONFIRM_SHORTTOUCH_TIME)&&(HCTouchLib_CONFIRM_SHORTTOUCH_TIME <= HCTouchLib_CONFIRM_TOUCH_TIME))|(HCTouchLib_CONFIRM_SHORTTOUCH_TIME > 2000))
#error 	"Error��Please setting HCTouchLib_CONFIRM_LONGTOUCH_TIME = 0 or HCTouchLib_CONFIRM_TOUCH_TIME < HCTouchLib_CONFIRM_SHORTTOUCH_TIME < 2000"
#endif

//================================================================================
#if (((0 < HCTouchLib_CONFIRM_LONGTOUCH_TIME)&&(HCTouchLib_CONFIRM_LONGTOUCH_TIME <= HCTouchLib_CONFIRM_SHORTTOUCH_TIME))|(HCTouchLib_CONFIRM_LONGTOUCH_TIME > 65535))
#error 	"Error��Please setting HCTouchLib_CONFIRM_LONGTOUCH_TIME = 0 or HCTouchLib_CONFIRM_SHORTTOUCH_TIME < HCTouchLib_CONFIRM_LONGTOUCH_TIME < 65536"
#endif

//================================================================================
#if (HCTouchLib_OVERZERO_TIME > 65535)
#error 	"Error��Please setting HCTouchLib_OVERZERO_TIME < 65535"
#endif

//================================================================================
#if ((HCTouchLib_OVERLOW_TIME > 255)|(HCTouchLib_OVERLOW_TIME < HCTouchLib_CONFIRM_NOTOUCH_TIME))
#error 	"Error��Please setting HCTouchLib_CONFIRM_NOTOUCH_TIME < HCTouchLib_OVERLOW_TIME < 256"
#endif

//================================================================================
#if (HCTouchLib_FILTER_DEPTH == 0)
#pragma message "CTK RawData������λֵƽ���˲�: �ر�"
#elif ((HCTouchLib_FILTER_DEPTH >= 3)&&(HCTouchLib_FILTER_DEPTH <= 15))
#pragma message "CTK RawData������λֵƽ���˲�: ��"
#else
#error 	"Error��Please setting 3 <= HCTouchLib_FILTER_DEPTH <= 15"
#endif

//================================================================================
#if (HCTouchLib_MULTIBUTTON == 0)
#pragma message "CTK��ϰ�������: �ఴ��ģʽ"
#elif (HCTouchLib_MULTIBUTTON == 1)
#pragma message "CTK��ϰ�������: ������ģʽ"
#elif (HCTouchLib_MULTIBUTTON == 2)
#pragma message "CTK��ϰ�������: ˫����ģʽ"
#else
#error 	"Error��Please setting HCTouchLib_MULTIBUTTON = 0 or HCTouchLib_MULTIBUTTON = 1 or HCTouchLib_MULTIBUTTON = 2"
#endif

#endif /* __HC89F30xC_GeneralKey_Touch_Lib_Build_Message_H__ */

/******************************************************************************************************
 * Revision history:
 *
 * Revision 1.01	2017/12/18 14:10 Taboo.Z�Z
 * Revision 1.0.2.0	2018/07/20 16:26 Jing.L�Z
 * Revision 1.0.3.0	2018/09/10 14:26 Jing.L�Z
 * Add: 1�����ӳ�����ʾ���
 *		2��ɾ���˲��ֲ������
 * Revision 1.0.4.0	2019/03/06 14:33 Touch Team
 * Add: 1���޸Ĳ��ִ���
 * Revision 1.0.5.0	2019/09/17 19:16 Touch Team
 * Add: 1��ɾ�����ֲ������
 *		2������RawData�˲�ʹ�������ʾ
 *		3��������ǿ����ʹ�������ʾ
 * Revision 3.0.0.0	2021/04/08 10:40 Touch Team
 * Add: 1��ɾ�����ֲ������
 *		2�����Ӱ�����Ч��ֵ������Ч��ֵ����
 *
 ******************************************************************************************************/

