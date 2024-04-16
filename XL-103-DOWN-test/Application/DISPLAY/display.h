#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#define DIS_OFF_YS       {dis_code[4] = ~0x01;}
#define DIS_OFF_CS       {dis_code[4] = ~0x02;}

#define DIS_OFF_SHUMAN   {dis_code[4] = ~0x10;dis_code[3] = ~0x10;}
#define DIS_OFF_ZHISHUI  {dis_code[4] = ~0x08;dis_code[3] = ~0x08;}
#define DIS_OFF_QUESHUI  {dis_code[4] = ~0x04;dis_code[3] = ~0x04;}
#define DIS_OFF_CHONGXI  {dis_code[4] = ~0x40;dis_code[3] = ~0x40;}

#define DIS_OFF_GONGNENG {dis_code[4] = ~0x5C;dis_code[3] = ~0x5C;}

#define DIS_OFF_LX1      {dis_code[4] = ~0x10;dis_code[3] = ~0x10;}
#define DIS_OFF_LX2      {dis_code[4] = ~0x08;dis_code[3] = ~0x08;}
#define DIS_OFF_LX3      {dis_code[4] = ~0x04;dis_code[3] = ~0x04;}
#define DIS_OFF_LX4      {dis_code[4] = ~0x40;dis_code[3] = ~0x40;}

#define DIS_OFF_ALL      {dis_code[0] = 0x00;dis_code[1] = 0x00;dis_code[2] = 0x00;dis_code[3] = 0x00;dis_code[4] = 0x00;}
#define DIS_ON_ALL       {dis_code[3] = 0xff;dis_code[4] = 0xff;}
    
#define DIS_OFF_KEY_L    {dis_code[3] = ~0x01;}
#define DIS_OFF_KEY_R    {dis_code[3] = ~0x02;}

#define DIS_ON_KEY_R     {dis_code[3] = 0x02;}

void DIS_MANAGE (void);
void display (void);
#endif /* __DISPLAY_H__ */