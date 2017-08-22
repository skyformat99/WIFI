#include "includes.h"
/******************************************************
* Name�� Usart2_Init() 
* Parameter�������� int boand
* Function��  ͨ��ģ���ʼ��
* Description�� PA2 PA3
* Author��  sun
******************************************************/

void Usart2_Init(int boand)
{
	  float USARTDIV;     //���벨���ʼĴ����е�ֵ
	  int DIV_Fraction; //����������С������
    int DIV_Mantissa; //������������������
	  int OVER8=0;
	
	
   /**��PA��ʱ����**/
	 RCC->AHB1ENR |=(0x1<<0);
	 
	/**����USART2��PA2,PA3 TX RX�ĸ��ù�������**/
	  
	  // XX XX XX XX  GPIOA
	  // 11 11 00 00  0xf<<4
  	// 00 00 11 11 ~(0xf<<4);
	  // 00 00 XX XX  &
    // 10 10 00 00  OxA<<4
	  // 10 10 XX XX
	 
		/**����PA2��PA3��TX����**/
	
	   //ģʽ�Ĵ��� 1010 // 10 =a
	
//	  GPIOA->MODER &=~(0xf<<4);
//	  GPIOA->MODER |=(0xa<<4); 

		GPIOA->MODER &=~(0x3<<4);
		GPIOA->MODER |=(0x2<<4); 
		

		GPIOA->AFR[0] &=~(0xf<<8);
		GPIOA->AFR[0] |=(0x7<<8); //0111
	
	
		
		GPIOA->MODER &=~(0x3<<6);
		GPIOA->MODER |=(0x2<<6);	//������ͼĴ���
		
	 
	  // 0111 0111  1+2+4
  	
		//���ù�������
	
//   	GPIOA->AFR[0] &=~(0xff<<8);
//  	GPIOA->AFR[0] |=(0x77<<8);

		

		GPIOA->AFR[0] &=~(0xf<<12);
		GPIOA->AFR[0] |=(0x7<<12);

	
	/**��UASRT2�Ľ��շ��͹�������**/
	
	   //��USART2������ʱ��
		 RCC->APB1ENR |=(0x1<<17);
		 
		 //���ڷ���ʹ��λ����
		 USART2->CR1 |=(0x1<<13);
		 
		 //��ֹ��żУ��
		 USART2->CR1 &=~(0x1<<10);
		 
		 //������ʹ��
		 USART2->CR1 |=(0x1<<3);
		 
		 //������ʹ��
		 USART2->CR1 |=(0x1<<2);
		 
		 //�����Ͷ�·�ַ� ��0
		 
		 USART2->CR1 &=~(0x1<<0);
		 
		 
#ifdef Usart2_OVER8  //16��
		 USART2->CR1 &=~(0x1<<15);
		 OVER8=0;
#else
     USART2->CR1 |=(0x1<<15);
     OVER8=1;
#endif
		 
		 /**���ò�����**/
		 		 
		 
		 USARTDIV=(float)(42000000/(8*(2-OVER8)*boand));
		 DIV_Mantissa = USARTDIV;
		 DIV_Fraction = (USARTDIV-DIV_Mantissa)*8*(2-OVER8);
     USART2->BRR = DIV_Mantissa<<4 | DIV_Fraction;
}   

/******************************************************
* Name�� Usart2_Sendbyte() 
* Parameter: �ַ���
* Function��  usart2���ͺ���  u8 date 
* Description�� 
* Author��  sun
******************************************************/
void Usart2_Sendbyte(u8 date)
{
 //�ȴ��ϴε�������ɷ���
	while((USART2->SR & (0x1<<6)) == 0);
	  USART2->DR = date;

}


/*****************************
��������USART1_Sendstring
����������
u8  *buf : �ַ�ָ�룬
     ��ʾҪ�����ַ������׵�ַ
��������ֵ����
�������ܣ�ʵ�ִ���1����һ���ַ���
����������
*****************************/
void Usart2_SendString(u8 *buf)
{
	 while(*buf !='\0')
	 {
		  Usart2_Sendbyte(*buf);
		  buf++;
	 }
	 Usart2_Sendbyte('\r');
	 Usart2_Sendbyte('\n');
}


/******************************************************
* Name�� Usart2_Sendbyte() 
* Parameter: �����ַ�
* Function��  usart2���ͺ���  u8 date 
* Description�� 
* Author��  sun
******************************************************/
u8 Usart2_Receivebyte()
{
	u8 date;
 //�ȴ��ϴε����ݽ������ 
	while((USART2->SR &(0x1<<5))==0)
	;
	
 //���ո�����
    date	= USART2->DR;
	//���ؽ��յ�������
	return date;
}

/****************************
��������USART2_Receivestring
����������char *str :���յ����ַ����׵�ַ

��������ֵ����
�������ܣ�ʵ��USART2�ַ�������
����������
   �Զ�����ս�����־
   #   led_on#
  ���� �ո� \r \n
*****************************/
void Usart2_Receivestring(char *str)
{
	char date;
	while(1)
	{
		//����һ���ַ�
		date= Usart2_Receivebyte();
		//�ж��Ƿ��ǽ�����־
		if(date ==' '|| date =='\r'|| date=='\n')
		{
			break;
		}
		else
		{
			*str =date;
			str++;
		}			
	}
	*str='\0';
}

void Usart2_Exit_Init()
{
  Usart2_Init(9600);
	RCC->APB2ENR |=(0x1<<14);
	USART2->CR1 |=(0x1<<5);
	My_NVIC_Init(7-2,2,3,USART2_IRQn);
}

void USART2_IRQHandler(void)
{
  static char buf[30];
	static int i=0;
	USART2->SR &=~(0x1<<5);

	buf[i]=USART2->DR;
	if(buf[i]!='\r'||buf[i]!='\n')
	{
	  if(strcmp(buf,"abc")==0)
		{
			LED1_ON;
		 
		}
		if(strcmp(buf,"bcd")==0)
		{
		  LED1_OFF;
		}
		i++;
	}
}

