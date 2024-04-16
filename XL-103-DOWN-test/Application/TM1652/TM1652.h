#ifndef _TM1652_H_
#define _TM1652_H_

#define   SEG1   0X01				//"h"
#define   SEG2   0X02               //"��Դ"
#define   SEG3   0X40				//ͯ��
#define   SEG4   0X08			    //��ʱ
#define   SEG5   0X10			    //��+��
#define   SEG6   0X20				//����
#define   SEG7   0X04				//����
#define   SEG8   0X80			    
//TM1652
/***************定义显示地址******************************/ 
#define addr_gr1	0x08			// GR1地址
#define addr_gr2	0x88			// GR2地址
#define addr_gr3	0x48			// GR3地址
#define addr_gr4	0xc8			// GR4地址
#define addr_gr5	0x28			// GR5地址
#define addr_gr6	0xa8			// GR6地址(这里八段无位)

#define addr_Cr     0x18			// 控制调节

sbit    TMSDA   = P3^4 ;    //(TM1652ͨѶ��)

void Control_display(void) ;
void specified_flood_led_data(void);

void tm1652_send_data(unsigned char sdat);
void TM1652_init(void);
void Delay_1us(unsigned char d_us);
void Delay_1ms(unsigned char d_ms);
#endif