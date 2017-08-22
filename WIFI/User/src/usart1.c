#include "includes.h"

/******************************************************
* Name�� Usart1_Init() 
* Parameter��������
* Function��  ͨ��ģ���ʼ��
* Description�� PA10 PA9
* Author��  sun
******************************************************/
void Usart1_Init(int boand)
{
	 
	 float USARTDIV;  	//���벨���ʼĴ����е���ֵ
	 int OVER8=0;
   int DIV_Fraction; //��ʾUSARTDIV��С������
	 int DIV_Mantissa; //��ʾUSARTDIV����������
	/*****************************************************************************/
	
	/**��USART1��TX RX �ܽŵĸ�������**/
	
	 //��PA��ʱ����
	  RCC->AHB1ENR |=(0x1<<0);
	
		/**��USART1��TX PA9 ���ù�������**/
	
	//ģʽ�Ĵ�������
	 GPIOA->MODER &=~(0x3<<18); //����
	 GPIOA->MODER |=(0x2<<18);  // ���ù�������
	
	//����ĸ��ù�������
	 GPIOA->AFR[1] &=~(0xf<<4); //����
	 GPIOA->AFR[1] |= (0x7<<4); //���ó�USART_TX
	
		/*****************************************************************************/

		/**��USART1��TX PA10 ���ù�������**/
	
	//ģʽ�Ĵ�������
	 GPIOA->MODER &=~(0x3<<20); //����
	 GPIOA->MODER |=(0x2<<20);  // ���ù�������
	
	//����ĸ��ù�������
	 GPIOA->AFR[1] &=~(0xf<<8); //����
	 GPIOA->AFR[1] |= (0x7<<8); //���ó�USART_TX
	 
	 	/*****************************************************************************/
	 
		/**��USART1�ķ��ͽ��յĹ�������**/
		
		//��USART1������ʱ��
	    RCC->APB2ENR |=(0x1<<4);
		
		 //���ڷ���ʹ��λ����
		 USART1->CR1 |=(0x1<<13);
		
		 //��ֹ��żУ��
		 USART1->CR1 &=~(0x1<<10);
		 
		 //������ʹ��
		 USART1->CR1 |=(0x1<<3);
		 //������ʹ��
		 USART1->CR1 |=(0x1<<2);
		 
		 //�����Ͷ�·�ַ�
		 USART1->CR1 &=~(0x1<<0);
		 
#ifdef Usart1_OVER8  //16��
		 USART1->CR1 &=~(1<<15);
		 OVER8=0;
#else
     USART1->CR1 |=(0x1<<15);
     OVER8=1;
#endif

		 /*****************************************************************************/
		 
		 /**TX RX	����������**/
		 
		 USARTDIV=(float)84000000/(8*(2-OVER8)*boand);
		 DIV_Mantissa = USARTDIV;
		 DIV_Fraction = (USARTDIV-DIV_Mantissa)*8*(2-OVER8);
		 USART1->BRR = DIV_Mantissa<<4 |DIV_Fraction;
		 
	
}



/******************************************************
* Name�� Usart1_Sendbyte() 
* Parameter: �����ַ�
* Function��  usart1���ͺ���  u8 date 
* Description�� 
* Author��  sun
******************************************************/
void Usart1_Sendbyte(u8 date)
{
 //�ȴ��ϴε����ݷ������ // һ�㶼��״̬�Ĵ���
	while((USART1->SR &(0x1<<6))==0);
 //���͸�����
	USART1->DR = date;

}



/******************************************************
* Name�� Usart1_SendString() 
* Parameter: �ַ���
* Function��  usart1���ͺ���  u8 date 
* Description�� 
* Author��  sun
******************************************************/
void Usart1_SendString(char *buf)
{
	 while(*buf !='\0')
	 {
		  Usart1_Sendbyte(*buf);
		  buf++;
	 }
	 Usart1_Sendbyte('\r');
	 Usart1_Sendbyte('\n');
}

/******************************************************
* Name�� Usart1_Sendbyte() 
* Parameter: �����ַ�
* Function��  usart1���ͺ���  u8 date 
* Description�� 
* Author��  sun
******************************************************/
u8 Usart1_Receivebyte()
{
	u8 date;
 //�ȴ��ϴε����ݽ������ 
	while((USART1->SR &(0x1<<5))==0)
	;
	
 //���ո�����
    date	= USART1->DR;
	//���ؽ��յ�������
	return date;
}
/******************************************************
* Name�� Usart1_SendString() 
* Parameter: �ַ���
* Function��  usart1���ͺ���  u8 *buf 
* Description�� 
* Author��  sun
******************************************************/
void Usart1_Receivestring(char *buf)
{
	 u8 ch; 
	 while(1)
	 {
		  ch =Usart1_Receivebyte();
		 //�жϽ��յ����Ƿ��ǽ�����־
		 if(ch ==' ' || ch =='\r' || ch=='\n')
		 {
			 break;
		 }
		 *buf =ch;
		 buf++;
	 }
	 *buf ='\0';//���һ��������־ 
}

#pragma import(__use_no_semihosting_swi) //ȡ��������״̬

struct __FILE { int handle; /* Add whatever you need here */ };
FILE __stdout;

int fputc(int ch, FILE *f) {
	Usart1_Sendbyte(ch);
  return (ch);
}
int ferror(FILE *f) {
  /* Your implementation of ferror */
  return EOF;
}

void _ttywrch(int ch) {
  Usart1_Sendbyte(ch);
}



void Usart1_Exit_Init()
{
	RCC->APB2ENR |=(0x1<<14);
	USART1->CR1 |=(0x1<<5);
	My_NVIC_Init(7-2,2,3,USART1_IRQn);
}

void USART1_IRQHandler(void)
{
//  static char buf[30];
//	static int i=0;
//	USART1->SR &=~(0x1<<5);
//	buf[i]=USART1->DR;
//	if(buf[i]!='\r'||buf[i]!='\n')
//	{
//	  if(strcmp(buf,"abc")==0)
//		{
//		 LED2_ON;
//		}
//		i++;
//	}
	u8 date;
  //static u32 addr=0; // �洢���ֿ�Ŀ�ʼ��ַ
	static u32 addr=1046790; // �洢ASCLL�Ŀ�ʼ��ַ
	date = USART1->DR;
	W25Q64_Page_Program(addr++,date);
}
