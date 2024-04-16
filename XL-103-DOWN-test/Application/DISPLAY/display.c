#include "define.h"
unsigned char  dis_code[6] =     {0x00,0x00,0x00,0x00,0x00,0x00};
unsigned char  dis_code_lock[6] ={0x00,0x00,0x00,0x00,0x00,0x00};
unsigned char  num_shi,num_ge,num_bai ;
volatile unsigned char addrtable[6] = {addr_gr2,addr_gr1,addr_gr3,addr_gr5,addr_gr4,addr_gr6};			//显示地址,换成const unsigned char code就不可以
//volatile unsigned char led_buffer[11]={0x77,0x14,0x6d,0x3d,0x1e,0x3b,0x7b,0x15,0x7F,0x3F,0x00};     //数码管字库
volatile unsigned char  LED_font[11]={0x3f,0x06,0x5B,0x4f,0x66,0x6d,0x7d,0x07,0x7F,0x6F,0x00};       //数码管字库
//                                      0    1    2    3    4     5    6    7    8    9  "空白"
//==============================================================================

//==============================================================================
void DIS_MANAGE (void)  
{
    DIS_ON_ALL
    if(F_Power == 0)
    {
        DIS_OFF_ALL
    }
    else
    {   
        
        
        num_ge    =(TDS_RO_avg%10) ; 		
        num_shi   = (TDS_RO_avg/10);
        num_bai   =0;//((TDS_RO_avg%100)%10);  
        dis_code[0] = LED_font[num_bai];
        dis_code[1] = LED_font[num_shi];
        dis_code[2] = LED_font[num_ge];

        
        if(F_FilterSet == 1)
        {
            if(F_PN_500MS)
            {
                if(Filter_SetMode == 1)
                {
                    DIS_OFF_LX1
                }
                else if(Filter_SetMode == 2)
                {
                    DIS_OFF_LX2
                }
                else if(Filter_SetMode == 3)
                {
                    DIS_OFF_LX3
                }else if(Filter_SetMode == 4)
                {
                    DIS_OFF_LX4
                }
            }
        }
        else
        {
            if(F_PN_500MS)
            {
                if(F_FilterOutTime == 1)
                {
                    DIS_OFF_LX1
                }
                else if(F_FilterOutTime == 2)
                {
                    DIS_OFF_LX2
                }
                else if(F_FilterOutTime == 3)
                {
                    DIS_OFF_LX3
                }else if(F_FilterOutTime == 4)
                {
                    DIS_OFF_LX4
                }
            }
        }
        
    }
}

//=============================================================================
void display (void) 
{	
	      if((dis_code[0]!=dis_code_lock[0])||(dis_code[1]!=dis_code_lock[1])||(dis_code[2]!=dis_code_lock[2])||(dis_code[3]!=dis_code_lock[3])||(dis_code[4]!=dis_code_lock[4]))//||(dis_code[5]!=dis_code_lock[5]))
				{
					  dis_code_lock[0]=dis_code[0];
					  dis_code_lock[1]=dis_code[1];
					  dis_code_lock[2]=dis_code[2];
					  dis_code_lock[3]=dis_code[3];
					  dis_code_lock[4]=dis_code[4];
				//		EA = 0;    	     
						tm1652_send_data(0x08);	
						tm1652_send_data(dis_code[0]);     
						tm1652_send_data(dis_code[1]);     	
						tm1652_send_data(dis_code[2]);     
						tm1652_send_data(dis_code[3]&~(1<<0)&~(1<<1));  //&~(1<<0)&~(1<<1)
						tm1652_send_data(dis_code[4]&~(1<<0));     
						Delay_1ms(5);  
						Control_display();	    
				//		EA = 1;
	      }
	     
	     	
}



/******************************************************************************/