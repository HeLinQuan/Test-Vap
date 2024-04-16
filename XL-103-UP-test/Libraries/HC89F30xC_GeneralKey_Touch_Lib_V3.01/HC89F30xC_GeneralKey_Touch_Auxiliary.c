/******************* (C) COPYRIGHT 2009~2022 holychip **************************
* File Name          : HC89F30xC_GeneralKey_Touch_Auxiliary.c
* Author             : Touch Team�Z
* Version            : V3.0.1.1
* Date               : 2023/04/24
********************************************************************************

ע�����ļ��������û������޸ģ�

*******************************************************************************/
#include "HC89F30xC.h"
#include "HC89F30xC_GeneralKey_Touch_Lib_V3.01\HC89F30xC_GeneralKey_Touch_Lib.h"
#include "HC89F30xC_GeneralKey_Touch_Lib_V3.01\HC89F30xC_GeneralKey_Touch_Auxiliary.h"
#include "HC89F30xC_GeneralKey_Touch_Lib_V3.01\HC89F30xC_GeneralKey_Touch_Lib_CFG.h"
#include <string.h> 

//===================================================================================================
extern ux16	XDATA_RawData[];					//�˲���RawData
extern ux16	XDATA_RawDataBuf[];					//�ɼ�����RawData
extern sx16 XDATA_BaseLine[];					//Baseline
extern uc8  CODE_INTERNAL_INDEX[];				//��ӦIC��ͨ����
extern uc8  CODE_TK_CH_MAX;						//��ӦIC��ͨ������
extern ux8	XDATA_OpenChannel[];				//�򿪵�ͨ��

#if HCTouchLib_MULTIBUTTON	
unsigned char code nuc_CombinationKeyA_a[2] = HCTouchLib_COMBINATIONKEYA;
unsigned char code nuc_CombinationKeyB_a[2] = HCTouchLib_COMBINATIONKEYB;
unsigned char code nuc_CombinationKeyC_a[2] = HCTouchLib_COMBINATIONKEYC;
unsigned char code nuc_CombinationKeyD_a[2] = HCTouchLib_COMBINATIONKEYD;
#endif	

//===================================================================================================
#if HCTouchLib_FILTER_DEPTH	
ux16 XDATA_RawData_Filter[HCTouchLib_OPENED_TK_AMOUNT][HCTouchLib_FILTER_DEPTH];
#endif	



/***************************************************************************************
  * @˵��	�ఴ����󼰴δ����ݲ���
  *	@����	fi_ArrData_a  	  :����Differֵ
  *			fuc_ArrDataAddr_a :����ͨ��ֵ
  *			fuc_Len:�������鳤��
  * @����ֵ ��
  * @ע		��
***************************************************************************************/
#if HCTouchLib_MULTIBUTTON						
static void MultiButtonSearch(s16 fi_ArrData_a[], u8 fuc_ArrDataAddr_a[], u8 fuc_Len)
{
    s16 fi_MaxTemp;
	s16 fi_SecMaxTemp;
	u8	fuc_MaxAddr;
	u8	fuc_SecMaxAddr;
    u8 fuc_i;
    for (fuc_i=0; fuc_i<fuc_Len; fuc_i++)
	{
		if(fi_MaxTemp < fi_ArrData_a[fuc_i])
		{
			fi_SecMaxTemp = fi_MaxTemp;
			fi_MaxTemp = fi_ArrData_a[fuc_i];
			fuc_SecMaxAddr = fuc_MaxAddr;
			fuc_MaxAddr = fuc_ArrDataAddr_a[fuc_i];
		}
		else if(fi_SecMaxTemp < fi_ArrData_a[fuc_i])
		{
			fi_SecMaxTemp = fi_ArrData_a[fuc_i];
			fuc_SecMaxAddr = fuc_ArrDataAddr_a[fuc_i];
		}
	}	
	fuc_ArrDataAddr_a[0] = fuc_MaxAddr;
	fuc_ArrDataAddr_a[1] = fuc_SecMaxAddr;
}
#endif




/***************************************************************************************
  * @˵��  	��ϰ���������
  *	@����	��
  * @����ֵ ��
  * @ע		��
***************************************************************************************/
void TouchMultibuttonHandle(void)
{
#if HCTouchLib_MULTIBUTTON	
	u8  fuc_TouchKeyFlagNum;
	s16 fi_MultibuttonDiffer_a[HCTouchLib_OPENED_TK_AMOUNT];
	u8  fuc_BubbleSortChannel_a[HCTouchLib_OPENED_TK_AMOUNT];
	u8  fuc_i;
	//����ͬʱ�м���ͨ��ͬʱ��Ч
	fuc_TouchKeyFlagNum = (TouchKeyFlag>> 0 & 0x01L)+(TouchKeyFlag>> 1 & 0x01L)+(TouchKeyFlag>> 2 & 0x01L)+(TouchKeyFlag>> 3 & 0x01L)+\
						  (TouchKeyFlag>> 4 & 0x01L)+(TouchKeyFlag>> 5 & 0x01L)+(TouchKeyFlag>> 6 & 0x01L)+(TouchKeyFlag>> 7 & 0x01L)+\
						  (TouchKeyFlag>> 8 & 0x01L)+(TouchKeyFlag>> 9 & 0x01L)+(TouchKeyFlag>>10 & 0x01L)+(TouchKeyFlag>>11 & 0x01L)+\
						  (TouchKeyFlag>>12 & 0x01L)+(TouchKeyFlag>>13 & 0x01L)+(TouchKeyFlag>>14 & 0x01L)+(TouchKeyFlag>>15 & 0x01L)+\
						  (TouchKeyFlag>>16 & 0x01L)+(TouchKeyFlag>>17 & 0x01L)+(TouchKeyFlag>>18 & 0x01L)+(TouchKeyFlag>>19 & 0x01L)+\
						  (TouchKeyFlag>>20 & 0x01L);
	
	if(fuc_TouchKeyFlagNum >= 2)
	{
		for(fuc_i = 0;fuc_i < HCTouchLib_OPENED_TK_AMOUNT;fuc_i++)
		{
			fi_MultibuttonDiffer_a[fuc_i] = (s16)(XDATA_RawData[fuc_i] - XDATA_BaseLine[fuc_i]);
		}	
		memcpy(fuc_BubbleSortChannel_a,XDATA_OpenChannel,HCTouchLib_OPENED_TK_AMOUNT);
		//ÿ������ǰ�����¸���ͨ������		
		MultiButtonSearch(fi_MultibuttonDiffer_a,fuc_BubbleSortChannel_a,HCTouchLib_OPENED_TK_AMOUNT);
		//���򣬽�����ͨ���ŵ�fuc_BubbleSortChannel_a[0]�У��ڶ����ͨ���ŵ�fuc_BubbleSortChannel_a[1]��
#if   (HCTouchLib_MULTIBUTTON == 1)	
		TouchKeyFlag = 0x00;
		TouchKeyFlag |= 0x01L<<fuc_BubbleSortChannel_a[0];
#elif (HCTouchLib_MULTIBUTTON == 2)	
		if(fuc_TouchKeyFlagNum==2)
		{
			if((((TouchKeyFlag>>nuc_CombinationKeyA_a[0]) & 0x01L) == 1)&&(((TouchKeyFlag>>nuc_CombinationKeyA_a[1]) & 0x01L) == 1)){return;}
			else if((((TouchKeyFlag>>nuc_CombinationKeyB_a[0]) & 0x01L) == 1)&&(((TouchKeyFlag>>nuc_CombinationKeyB_a[1]) & 0x01L) == 1)){return;}
			else if((((TouchKeyFlag>>nuc_CombinationKeyC_a[0]) & 0x01L) == 1)&&(((TouchKeyFlag>>nuc_CombinationKeyC_a[1]) & 0x01L) == 1)){return;}
			else if((((TouchKeyFlag>>nuc_CombinationKeyD_a[0]) & 0x01L) == 1)&&(((TouchKeyFlag>>nuc_CombinationKeyD_a[1]) & 0x01L) == 1)){return;}			
			else
			{
				TouchKeyFlag = 0x00;
				TouchKeyFlag |= 0x01L<<fuc_BubbleSortChannel_a[0];		
			}		
		}//�������������ͬʱ��Ч��Ϊ�û����õ���ϰ������򰴼���Ч�����Ϊ���û����õ���ϰ��������ź���ǿ�İ�����Ч��
		else
		{
			TouchKeyFlag = 0x00;
			TouchKeyFlag |= 0x01L<<fuc_BubbleSortChannel_a[0];				
		}
		//���>=3��������Ч�����ź���ǿ�İ�����Ч��
#endif		
	}	
#endif		
}



/***************************************************************************************
  * @˵��  	�˲�ð������
  *	@����	fui_ArrData_a ����������
  *			fuc_Len���������鳤��
  * @����ֵ ��
  * @ע		��
***************************************************************************************/
#if HCTouchLib_FILTER_DEPTH			//ʹ���˲��򰴼�ģʽ
static void FilterBubbleSort(u16 fui_ArrData_a[], u8 fuc_Len)
{
    u16 fui_Temp = 0;
    u8 fuc_i = 0, fuc_j = 0;
    for (fuc_i=0; fuc_i<fuc_Len-1; fuc_i++)
	{
        for (fuc_j=0; fuc_j<fuc_Len-1-fuc_i; fuc_j++) 
		{ 
            if (fui_ArrData_a[fuc_j] > fui_ArrData_a[fuc_j+1]) 
			{ 
                fui_Temp = fui_ArrData_a[fuc_j];
                fui_ArrData_a[fuc_j] = fui_ArrData_a[fuc_j+1];
                fui_ArrData_a[fuc_j+1] = fui_Temp;
            }
        }	
	}
}
#endif	


/***************************************************************************************
  * @˵��  	�˲�����
  *	@����	��
  * @����ֵ ��
  * @ע		��
***************************************************************************************/
void TouchRawDataFilter(void)
{
#if HCTouchLib_FILTER_DEPTH		//ʹ���˲�				
	unsigned char fuc_i = 0, fuc_j = 0, fuc_z = 0;
	unsigned long xdata ful_Num[HCTouchLib_OPENED_TK_AMOUNT] = {0x00};

	for(fuc_i = 0; fuc_i < HCTouchLib_OPENED_TK_AMOUNT; fuc_i++)
	{
		XDATA_RawData_Filter[fuc_i][HCTouchLib_FILTER_DEPTH-1] = XDATA_RawDataBuf[fuc_i];
		for(fuc_j = 0; fuc_j<HCTouchLib_FILTER_DEPTH-1; fuc_j++)
		{
			XDATA_RawData_Filter[fuc_i][fuc_j] = XDATA_RawData_Filter[fuc_i][fuc_j+1];
		}
		FilterBubbleSort(XDATA_RawData_Filter[fuc_i],HCTouchLib_FILTER_DEPTH);
		for(fuc_z = 1; fuc_z<HCTouchLib_FILTER_DEPTH-1; fuc_z++)
		{
			ful_Num[fuc_i] += XDATA_RawData_Filter[fuc_i][fuc_z];
		}
		ful_Num[fuc_i] /=  (HCTouchLib_FILTER_DEPTH-2);
		XDATA_RawData[fuc_i] = (u16)(ful_Num[fuc_i]);	
	}
#else											//û��ʹ���˲�
	unsigned char fuc_i = 0;
	for(fuc_i = 0;fuc_i < HCTouchLib_OPENED_TK_AMOUNT;fuc_i++)
	{
		XDATA_RawData[fuc_i] = XDATA_RawDataBuf[fuc_i];
	}	
#endif
	
}

/******************************************************************************************************
 * Revision history:
 *
 * Revision 1.01  	2017/12/18 14:10 Taboo.Z�Z
 * Revision 1.0.2.0	2018/07/20 16:31 Jing.L�Z
 * Revision 1.0.3.0	2018/09/10 14:38 Jing.L�Z
 * Revision 1.0.4.0	2019/03/06 13:59 Touch Team
 * Revision 1.0.5.0	2019/09/17 19:23 Touch Team
 * Add: 1���״�����RawData�˲�����
 * Revision 3.0.0.0	2021/04/08 10:45 Touch Team
 * Add: 1���޸ĵ������Լ���ϰ����쳣����ʽ
 ******************************************************************************************************/
