#ifndef _USART_H_
#define _USART_H_

//uart
#define Success 1
#define Fail  0


//uart
extern unsigned char xdata ReceiveLimitFlag;							//�������Ʊ�־λ
extern unsigned int  xdata ReceiveLimitCount;							//�������Ƽ���
extern unsigned char xdata SendOutData[16];
extern unsigned char xdata ReceivebeBuffer[16];		//���ջ�����
extern unsigned char Receiveflag;									//���ձ�־λ
extern unsigned char Receietime;									//����ʱ��
extern unsigned char Receivenum;									//������Ŀ



void UartInit(void);												//uart��ʼ��
void SendData(unsigned char da);	//��������
void JudgeOneStringEnd();									//�ж�һ֡���ݽ���
unsigned char JudgeTheReceiveData(unsigned char *da,unsigned char num);			//�жϽ��յ������Ƿ���ȷ
void ClearBuffer(void);										//��ջ�����

void DIS_TO_MAIN_SEND(void) ; 
void SingReceive(void);
void  UART_SendData(  unsigned char  len0) ;

extern  unsigned int  xdata   cnt_temp;



#endif