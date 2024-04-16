/******************* (C) COPYRIGHT 2009~2021 holychip **************************
* File Name          : HC89F30xC_SYS.c
********************************************************************************


*******************************************************************************/
#include	"HC89F30xC.h"
#include	"HC89F30xC_SYS.h"

/****************************************************************************
* Function Name  :
* Description    :
* Input          : None
* Output         : None
* Return         : None
****************************************************************************/
void SystemInit(void)
{
	//SYS CLOCK
	CLKSWR = (SYSCLK_SEL << 4) | SYSCLK_HSRC_DIV;
	CLKDIV = SYSCLK_FCPU_DIV;

	//BOR
	RSTDBC = 0xFF; 			//Timer = RSTDBC*8*Tcpu + 2Tcpu
	BORC = 0xC0 | BOR_SET_2V4 ; 		
}

/*********************************END OF FILE************************************/
/******************* (C) COPYRIGHT 2009~2021 holychip ***************************/
