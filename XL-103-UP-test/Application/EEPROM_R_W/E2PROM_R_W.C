#include "define.h"
#define EEPROM_ADDR   0X3C00  //地址
unsigned char xdata guc_Write_a[16] = {0x00,0x00,0x00,0x00,0x00};	//写入数据
unsigned char xdata guc_Read_a[16] = {0x00};			//用于存放读取的数据


void  EEPROM_WRITE(void )
{
    guc_Write_a[EE_WORK1_HOUR_H] = work1_hour/256 ;	 //存储模式 
    guc_Write_a[EE_WORK1_HOUR_L] = work1_hour%256 ;

    guc_Write_a[EE_WORK2_HOUR_H] = work2_hour/256 ;	 //存储模式 
    guc_Write_a[EE_WORK2_HOUR_L] = work2_hour%256 ;

    guc_Write_a[EE_WORK3_HOUR_H] = work3_hour/256 ;	 //存储模式 
    guc_Write_a[EE_WORK3_HOUR_L] = work3_hour%256 ;

    guc_Write_a[EE_WORK4_HOUR_H] = work4_hour/256 ;	 //存储模式 
    guc_Write_a[EE_WORK4_HOUR_L] = work4_hour%256 ;

    guc_Write_a[EE_WORK5_HOUR_H] = work5_hour/256 ;	 //存储模式 
    guc_Write_a[EE_WORK5_HOUR_L] = work5_hour%256 ;

    guc_Write_a[EE_FRIST] = 0X5A ;

    guc_Write_a[EE_WORK_MIN] =  work_10min ;   //20分钟存储1次 

    Flash_EraseBlock(EEPROM_ADDR);			 //擦除地址0x3C00所在扇区
    Flash_WriteArr(EEPROM_ADDR,16,guc_Write_a);  //在地址0x3C00写入数据
}

/**
  * @说明  	扇区擦除，约消耗5ms的时间
  * @参数  	fui_Address ：被擦除的扇区内的任意一个地址
  * @返回值 无
  * @注		只要操作扇区里面的任意一个地址，就可以擦除此扇区
  */
#pragma disable						//确保擦除时不会进中断导致擦除失败
void Flash_EraseBlock(unsigned int fui_Address)
{
	IAP_CMD = 0xF00F;				//Flash解锁
	IAP_ADDR = fui_Address;			//写入擦除地址
	IAP_CMD = 0xD22D;				//选择操作方式， 扇区擦除
	IAP_CMD = 0xE11E; 				//触发后IAP_ADDRL&IAP_ADDRH指向0xFF，同时自动锁定
}

/**
  * @说明  	写入一个字节数据到Flash里面
  * @参数  	fui_Address ：FLASH地址
  *	@参数	fucp_SaveData：写入的数据
  * @返回值 无
  * @注		写之前必须先对操作的扇区进行擦除
  */
#pragma disable						//确保写入时不会进中断导致写入失败
void FLASH_WriteData(unsigned char fuc_SaveData, unsigned int fui_Address)
{
	IAP_DATA = fuc_SaveData;
	IAP_CMD=0xF00F;					//Flash解锁
	IAP_ADDR = fui_Address;
	IAP_CMD=0xB44B;					//字节编程
	IAP_CMD=0xE11E;					//触发一次操作
}

/**
  * @说明  	写入任意长度的数据到FLASH里面
  * @参数  	fui_Address ：FLASH起始地址
  *	@参数	fuc_Length ： 写入数据长度
  *			取值范围：0x00-0xFF
  *	@参数	*fucp_SaveArr：写入的数据存放区域的首地址
  * @返回值 无
  * @注		写之前必须先对操作的扇区进行擦除
  */
#pragma disable						//确保写入时不会进中断导致写入失败
void Flash_WriteArr(unsigned int fui_Address,unsigned char fuc_Length,unsigned char *fucp_SaveArr)
{
	unsigned char fui_i = 0;
	for(fui_i=0;fui_i<fuc_Length;fui_i++)
	{
	   	FLASH_WriteData(*(fucp_SaveArr++), fui_Address++); 
	}
}

/**
  * @说明  	从FLASH里面读取任意长度的数据
  * @参数  	fui_Address ：FLASH起始地址
  *	@参数	fuc_Length ：读取数据长度
  *			取值范围：0x00-0xFF
  *	@参数	*fucp_SaveArr：读取数据存放的区域首地址
  * @返回值 无
  * @注		无
  */
void Flash_ReadArr1(unsigned int fui_Address,unsigned char fuc_Length,unsigned char *fucp_SaveArr)
{
	while(fuc_Length--)
	*(fucp_SaveArr++)=*((unsigned char code *)(fui_Address++));//读取数据
}




void  EEPROM_INIT(void)
{
	
	FREQ_CLK = 0x10;					//指明当前系统时钟
    
	Flash_ReadArr1(EEPROM_ADDR,16,guc_Read_a);	//读取地址0x3C00所在扇区
	
	if(guc_Read_a[EE_FRIST]!= 0X5a)
    {
        work1_hour  = 0 ;       //读取开机时间	
        work2_hour  = 0 ;  
        work3_hour  = 3 ;       //work3_hour、work4_hour 用来存储加热与制冷的 H、M、L  默认温度设置都为3-H
        work4_hour  = 3 ;    
        work5_hour  = 3 ;       //work4_hour 用来存储出水量1：180ml、2:250ml、3:500ml、4:1000ml 默认为500ml
        work_10min  = 0 ; 
        EEPROM_WRITE( ) ;
    }		//存储模式 
	else
	{
        work_10min  =  guc_Read_a[EE_WORK_MIN ] ; 
        work1_hour  = (unsigned int)((guc_Read_a[EE_WORK1_HOUR_H]<<8)|guc_Read_a[EE_WORK1_HOUR_L]) ;       //读取开机时间	
        work2_hour  = (unsigned int)((guc_Read_a[EE_WORK2_HOUR_H]<<8)|guc_Read_a[EE_WORK2_HOUR_L]) ;  
        work3_hour  = (unsigned int)((guc_Read_a[EE_WORK3_HOUR_H]<<8)|guc_Read_a[EE_WORK3_HOUR_L]) ;       //读取开机时间	
        work4_hour  = (unsigned int)((guc_Read_a[EE_WORK4_HOUR_H]<<8)|guc_Read_a[EE_WORK4_HOUR_L]) ;  
        work5_hour  = (unsigned int)((guc_Read_a[EE_WORK5_HOUR_H]<<8)|guc_Read_a[EE_WORK5_HOUR_L]) ;  
	}
}