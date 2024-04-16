#ifndef _TM1652_H_
#define _TM1652_H_

#define   SEG1   0X01				//"h"
#define   SEG2   0X02               //"电源"
#define   SEG3   0X40				//童锁
#define   SEG4   0X08			    //定时
#define   SEG5   0X10			    //“+”
#define   SEG6   0X20				//加热
#define   SEG7   0X04				//无线
#define   SEG8   0X80			    
//TM1652
/***************瀹氫箟鏄剧ず鍦板潃******************************/ 
#define addr_gr1	0x08			// GR1鍦板潃
#define addr_gr2	0x88			// GR2鍦板潃
#define addr_gr3	0x48			// GR3鍦板潃
#define addr_gr4	0xc8			// GR4鍦板潃
#define addr_gr5	0x28			// GR5鍦板潃
#define addr_gr6	0xa8			// GR6鍦板潃(杩欓噷鍏鏃犱綅)

#define addr_Cr     0x18			// 鎺у埗璋冭妭

sbit    TMSDA   = P3^4 ;    //(TM1652通讯口)

void Control_display(void) ;
void specified_flood_led_data(void);

void tm1652_send_data(unsigned char sdat);
void TM1652_init(void);
void Delay_1us(unsigned char d_us);
void Delay_1ms(unsigned char d_ms);
#endif