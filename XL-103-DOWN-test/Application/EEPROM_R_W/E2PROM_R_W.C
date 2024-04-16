#include "define.h"
#define EEPROM_ADDR   0X3C00  //��ַ
unsigned char xdata guc_Write_a[16] = {0x00,0x00,0x00,0x00,0x00};	//д������
unsigned char xdata guc_Read_a[16] = {0x00};			//���ڴ�Ŷ�ȡ������


void  EEPROM_WRITE(void )
{
    guc_Write_a[EE_WORK1_HOUR_H] = work1_hour/256 ;	 //�洢ģʽ 
    guc_Write_a[EE_WORK1_HOUR_L] = work1_hour%256 ;

    guc_Write_a[EE_WORK2_HOUR_H] = work2_hour/256 ;	 //�洢ģʽ 
    guc_Write_a[EE_WORK2_HOUR_L] = work2_hour%256 ;

    guc_Write_a[EE_WORK3_HOUR_H] = work3_hour/256 ;	 //�洢ģʽ 
    guc_Write_a[EE_WORK3_HOUR_L] = work3_hour%256 ;

    guc_Write_a[EE_WORK4_HOUR_H] = work4_hour/256 ;	 //�洢ģʽ 
    guc_Write_a[EE_WORK4_HOUR_L] = work4_hour%256 ;

    guc_Write_a[EE_WORK5_HOUR_H] = work5_hour/256 ;	 //�洢ģʽ 
    guc_Write_a[EE_WORK5_HOUR_L] = work5_hour%256 ;

    guc_Write_a[EE_FRIST] = 0X5A ;

    guc_Write_a[EE_WORK_MIN] =  work_10min ;   //20���Ӵ洢1�� 

    Flash_EraseBlock(EEPROM_ADDR);			 //������ַ0x3C00��������
    Flash_WriteArr(EEPROM_ADDR,16,guc_Write_a);  //�ڵ�ַ0x3C00д������
}

/**
  * @˵��  	����������Լ����5ms��ʱ��
  * @����  	fui_Address ���������������ڵ�����һ����ַ
  * @����ֵ ��
  * @ע		ֻҪ�����������������һ����ַ���Ϳ��Բ���������
  */
#pragma disable						//ȷ������ʱ������жϵ��²���ʧ��
void Flash_EraseBlock(unsigned int fui_Address)
{
	IAP_CMD = 0xF00F;				//Flash����
	IAP_ADDR = fui_Address;			//д�������ַ
	IAP_CMD = 0xD22D;				//ѡ�������ʽ�� ��������
	IAP_CMD = 0xE11E; 				//������IAP_ADDRL&IAP_ADDRHָ��0xFF��ͬʱ�Զ�����
}

/**
  * @˵��  	д��һ���ֽ����ݵ�Flash����
  * @����  	fui_Address ��FLASH��ַ
  *	@����	fucp_SaveData��д�������
  * @����ֵ ��
  * @ע		д֮ǰ�����ȶԲ������������в���
  */
#pragma disable						//ȷ��д��ʱ������жϵ���д��ʧ��
void FLASH_WriteData(unsigned char fuc_SaveData, unsigned int fui_Address)
{
	IAP_DATA = fuc_SaveData;
	IAP_CMD=0xF00F;					//Flash����
	IAP_ADDR = fui_Address;
	IAP_CMD=0xB44B;					//�ֽڱ��
	IAP_CMD=0xE11E;					//����һ�β���
}

/**
  * @˵��  	д�����ⳤ�ȵ����ݵ�FLASH����
  * @����  	fui_Address ��FLASH��ʼ��ַ
  *	@����	fuc_Length �� д�����ݳ���
  *			ȡֵ��Χ��0x00-0xFF
  *	@����	*fucp_SaveArr��д������ݴ��������׵�ַ
  * @����ֵ ��
  * @ע		д֮ǰ�����ȶԲ������������в���
  */
#pragma disable						//ȷ��д��ʱ������жϵ���д��ʧ��
void Flash_WriteArr(unsigned int fui_Address,unsigned char fuc_Length,unsigned char *fucp_SaveArr)
{
	unsigned char fui_i = 0;
	for(fui_i=0;fui_i<fuc_Length;fui_i++)
	{
	   	FLASH_WriteData(*(fucp_SaveArr++), fui_Address++); 
	}
}

/**
  * @˵��  	��FLASH�����ȡ���ⳤ�ȵ�����
  * @����  	fui_Address ��FLASH��ʼ��ַ
  *	@����	fuc_Length ����ȡ���ݳ���
  *			ȡֵ��Χ��0x00-0xFF
  *	@����	*fucp_SaveArr����ȡ���ݴ�ŵ������׵�ַ
  * @����ֵ ��
  * @ע		��
  */
void Flash_ReadArr1(unsigned int fui_Address,unsigned char fuc_Length,unsigned char *fucp_SaveArr)
{
	while(fuc_Length--)
	*(fucp_SaveArr++)=*((unsigned char code *)(fui_Address++));//��ȡ����
}




void  EEPROM_INIT(void)
{
	
	FREQ_CLK = 0x10;					//ָ����ǰϵͳʱ��
    
	Flash_ReadArr1(EEPROM_ADDR,16,guc_Read_a);	//��ȡ��ַ0x3C00��������
	
	if(guc_Read_a[EE_FRIST]!= 0X5a)
    {
        work1_hour  = 0 ;       //��ȡ����ʱ��	
        work2_hour  = 0 ;  
        work3_hour  = 3 ;       //work3_hour��work4_hour �����洢����������� H��M��L  Ĭ���¶����ö�Ϊ3-H
        work4_hour  = 3 ;    
        work5_hour  = 3 ;       //work4_hour �����洢��ˮ��1��180ml��2:250ml��3:500ml��4:1000ml Ĭ��Ϊ500ml
        work_10min  = 0 ; 
        EEPROM_WRITE( ) ;
    }		//�洢ģʽ 
	else
	{
        work_10min  =  guc_Read_a[EE_WORK_MIN ] ; 
        work1_hour  = (unsigned int)((guc_Read_a[EE_WORK1_HOUR_H]<<8)|guc_Read_a[EE_WORK1_HOUR_L]) ;       //��ȡ����ʱ��	
        work2_hour  = (unsigned int)((guc_Read_a[EE_WORK2_HOUR_H]<<8)|guc_Read_a[EE_WORK2_HOUR_L]) ;  
        work3_hour  = (unsigned int)((guc_Read_a[EE_WORK3_HOUR_H]<<8)|guc_Read_a[EE_WORK3_HOUR_L]) ;       //��ȡ����ʱ��	
        work4_hour  = (unsigned int)((guc_Read_a[EE_WORK4_HOUR_H]<<8)|guc_Read_a[EE_WORK4_HOUR_L]) ;  
        work5_hour  = (unsigned int)((guc_Read_a[EE_WORK5_HOUR_H]<<8)|guc_Read_a[EE_WORK5_HOUR_L]) ;  
	}
}