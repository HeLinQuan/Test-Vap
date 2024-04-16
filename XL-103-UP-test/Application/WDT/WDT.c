/******************* (C) COPYRIGHT 2009~2016 holychip **************************
* File Name          : WDT.c
* Author             : Taboo.Z�Z
* Version            : V1.00
* Date               : 9/12/2017
********************************************************************************


*******************************************************************************/
//#include "HC89F303.h"
#include "WDT.h"
#include "HC89F30xC.h"

//===============================================================================
void WDT_INIT(void)
{
	WDTCCR = WDTCCR_DF;
	WDTC =   bmWDTCLR | bmWDTPS1 | bmWDTPS0; 	//PS 011  64  MAX64K    MIN 256MS
}
