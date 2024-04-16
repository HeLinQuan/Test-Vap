/******************* (C) COPYRIGHT 2009~2022 holychip **************************
* File Name          : HC89F30xC_GeneralKey_Touch_Auxiliary.c
* Author             : Touch Team
* Version            : V3.0.1.1
* Date               : 2023/04/24
********************************************************************************

注：本文件不建议用户自行修改！

*******************************************************************************/
#include "HC89F30xC.h"
#include "HC89F30xC_GeneralKey_Touch_Lib_V3.01\HC89F30xC_GeneralKey_Touch_Lib.h"
#include "HC89F30xC_GeneralKey_Touch_Lib_V3.01\HC89F30xC_GeneralKey_Touch_Auxiliary.h"
#include "HC89F30xC_GeneralKey_Touch_Lib_V3.01\HC89F30xC_GeneralKey_Touch_Lib_CFG.h"
#include <string.h> 

//===================================================================================================
extern ux16	XDATA_RawData[];					//滤波后RawData
extern ux16	XDATA_RawDataBuf[];					//采集所得RawData
extern sx16 XDATA_BaseLine[];					//Baseline
extern uc8  CODE_INTERNAL_INDEX[];				//对应IC的通道号
extern uc8  CODE_TK_CH_MAX;						//对应IC的通道总数
extern ux8	XDATA_OpenChannel[];				//打开的通道

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
  * @说明	多按键最大及次大数据查找
  *	@参数	fi_ArrData_a  	  :传入Differ值
  *			fuc_ArrDataAddr_a :传入通道值
  *			fuc_Len:排序数组长度
  * @返回值 无
  * @注		无
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
  * @说明  	组合按键处理函数
  *	@参数	无
  * @返回值 无
  * @注		无
***************************************************************************************/
void TouchMultibuttonHandle(void)
{
#if HCTouchLib_MULTIBUTTON	
	u8  fuc_TouchKeyFlagNum;
	s16 fi_MultibuttonDiffer_a[HCTouchLib_OPENED_TK_AMOUNT];
	u8  fuc_BubbleSortChannel_a[HCTouchLib_OPENED_TK_AMOUNT];
	u8  fuc_i;
	//计算同时有几个通道同时有效
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
		//每次排序前都重新更新通道排序		
		MultiButtonSearch(fi_MultibuttonDiffer_a,fuc_BubbleSortChannel_a,HCTouchLib_OPENED_TK_AMOUNT);
		//排序，将最大的通道放到fuc_BubbleSortChannel_a[0]中，第二大的通道放到fuc_BubbleSortChannel_a[1]中
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
		}//如果是两个按键同时生效且为用户设置的组合按键，则按键生效。如果为非用户设置的组合按键，则信号最强的按键生效。
		else
		{
			TouchKeyFlag = 0x00;
			TouchKeyFlag |= 0x01L<<fuc_BubbleSortChannel_a[0];				
		}
		//如果>=3个按键生效，则信号最强的按键生效。
#endif		
	}	
#endif		
}



/***************************************************************************************
  * @说明  	滤波冒泡排序
  *	@参数	fui_ArrData_a ：排序数组
  *			fuc_Len：排序数组长度
  * @返回值 无
  * @注		无
***************************************************************************************/
#if HCTouchLib_FILTER_DEPTH			//使能滤波或按键模式
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
  * @说明  	滤波函数
  *	@参数	无
  * @返回值 无
  * @注		无
***************************************************************************************/
void TouchRawDataFilter(void)
{
#if HCTouchLib_FILTER_DEPTH		//使能滤波				
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
#else											//没有使能滤波
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
 * Revision 1.01  	2017/12/18 14:10 Taboo.Z
 * Revision 1.0.2.0	2018/07/20 16:31 Jing.L
 * Revision 1.0.3.0	2018/09/10 14:38 Jing.L
 * Revision 1.0.4.0	2019/03/06 13:59 Touch Team
 * Revision 1.0.5.0	2019/09/17 19:23 Touch Team
 * Add: 1、首次增加RawData滤波功能
 * Revision 3.0.0.0	2021/04/08 10:45 Touch Team
 * Add: 1、修改单按键以及组合按键异常处理方式
 ******************************************************************************************************/
