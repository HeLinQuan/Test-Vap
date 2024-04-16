#ifndef __HC_EEPROM_H__
#define __HC_EEPROM_H__

void  EEPROM_WRITE(void ); 
void  EEPROM_INIT(void);

void Flash_EraseBlock(unsigned int fui_Address);//扇区擦除
void FLASH_WriteData(unsigned char fui_Address, unsigned int fuc_SaveData);//写入一个数据
void Flash_WriteArr(unsigned int fui_Address,unsigned char fuc_Length,unsigned char *fucp_SaveArr);//写入任意长度数据
void Flash_ReadArr1(unsigned int fui_Address,unsigned char fuc_Length,unsigned char *fucp_SaveArr);//读取任意长度数据


#define   EE_WORK1_HOUR_L        0X00
#define   EE_WORK1_HOUR_H        0X01 

#define   EE_WORK2_HOUR_L        0X02
#define   EE_WORK2_HOUR_H        0X03 

#define   EE_WORK3_HOUR_L        0X04
#define   EE_WORK3_HOUR_H        0X05 

#define   EE_WORK4_HOUR_L        0X06
#define   EE_WORK4_HOUR_H        0X07 

#define   EE_WORK5_HOUR_L        0X08
#define   EE_WORK5_HOUR_H        0X09 


#define   EE_FRIST        0X0A 

#define   EE_WORK_MIN     0X0C

#define SET_WORK1_HOUR   360
#define SET_WORK2_HOUR   360
#define SET_WORK3_HOUR   720
#define SET_WORK4_HOUR   360
#define SET_WORK5_HOUR   1800


#endif