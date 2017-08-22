#include "includes.h"
	/******************************************************
	* Name�� KEY_Init
	* Function��  ʵ�ֿ������Ӧ��KEY�����빦������
	* Description�� PA0 PE2 PE3 PE4
	* Author��  sun
	******************************************************/
	void KEY_Init()
	{

		/**��GPIOA�ܽŵ�ʱ��**/
		 RCC->AHB1ENR |=(0x1<<0);
		
		/**��GPIOE�ܽŵ�ʱ��**/
		 RCC->AHB1ENR |=(0x1<<4);
		
		/**����PA0�˿ڵ�����ģʽ**/

		GPIOA->MODER &=~(0x3<<0); // ����
	// 	GPIOA->MODER |= (0x0<<0); //��������ģʽ
		
		/**����PA0�˿ڵ���������ģʽ**/
		
		GPIOA->PUPDR &=~(0x3<<0); // ���� 
	//	GPIOA->PUPDR |=(0x0<<0); // ������������ 
		
		
		
		/**����PE2�˿ڵ�����ģʽ**/
		GPIOE->MODER &=~(0x3<<4); // ����
	//	GPIOE->MODER |= (0x0<<4);  //��������ģʽ
		
		/**����PF2�˿ڵ���������ģʽ**/
		
		GPIOE->PUPDR &=~(0x3<<4);// ����
	//	GPIOE->PUPDR |=(0x0<<4); // ������������ 



			/**����PE3�˿ڵ�����ģʽ**/
		GPIOE->MODER &=~(0x3<<6);// ����
  //GPIOE->MODER |= (0x0<<6);  //��������ģʽ 
		
		/**����PE3�˿ڵ���������ģʽ**/
		
		GPIOE->PUPDR &=~(0x3<<6); // ����
	//GPIOE->PUPDR |=(0x0<<6); // ������������  



			/**����P4�˿ڵ�����ģʽ**/
		GPIOE->MODER &=~(0x3<<8);// ����
		//GPIOE->MODER |= (0x0<<8);  //��������ģʽ 
		
		/**����PE4�˿ڵ���������ģʽ**/
		
		GPIOE->PUPDR &=~(0x3<<8); // ����
		//GPIOE->PUPDR |=(0x0<<8); //������������   
		
	}
	
		/******************************************************
	* Name�� Get_Value
	* Function��  �õ���Ӧ�İ���ֵ
	* Description�� KEY1 KEY2 KEY3 KEY4
	* Author��  sun
	******************************************************/
	int Get_Value()
	{
		if(KEY1_ON ==1)
			return 1;
		else if(KEY2_ON == 0)
			return 2;
		else if(KEY3_ON == 0)
			return 3;
		else if(KEY4_ON == 0)
			return 4;
		return 0;

	
	}
		
	
	/******************************************************
	* Name�� 
	* Function��  ����EXTI���ⲿ�жϴ������
	* Description��  PA0 PE2 PE3 PE4
	* Author��  sun
	******************************************************/
	
	
	/**
	 ���ò��裺
	1���Ѱ�����Ӧ��IO�����ó�����ģʽ
	��SYSCFG������ʱ��
	***********************************
	---- PA0 
	
		1��ѡ��PA0��ΪEXTIO�Ĵ����ܽ� -- �����ش���
		2������EXTI0�ϴ����ж�
		3��EXTI0��NVIC����
	 	
	******************************** **/
	void Key_EXTI_Init()
	{
		// ������ʼ��
	  KEY_Init();
		
		// ��SYSCFG������ʱ��
	  RCC->APB2ENR |=(0x1<<14);
		
		
		/************����PA0**************/
	   
		//ѡ��PA0��ΪEXTI0�Ĵ����ܽ�
		SYSCFG->EXTICR[0] &=~(0xf<<0); 
		
		// ��EXTI0����Ϊ�����ش���
		EXTI->RTSR |=(0x1<<0);
		
		//����EXTI0���жϴ���
		EXTI->IMR |=(0x1<<0);
		
		//EXTI0��NVIC����
	  My_NVIC_Init(7-2,3,1,EXTI0_IRQn);
		
		
			/************����PE2**************/
	   
		//ѡ��PE2��ΪEXTI2�Ĵ����ܽ�
		SYSCFG->EXTICR[0] &=~(0xf<<8);
	  SYSCFG->EXTICR[0] |=(0x4<<8);
		
		// ��EXTI2����Ϊ�½��ش���
		EXTI->FTSR |=(0x1<<2);
		
		//����EXTI2���жϴ���
		EXTI->IMR |=(0x1<<2);
		
		//EXTI0��NVIC����
	  My_NVIC_Init(7-2,2,1,EXTI2_IRQn);
		
		
		
			/************����PE3**************/
	   
		//ѡ��PE3��ΪEXTI2�Ĵ�����
		SYSCFG->EXTICR[0] &=~(0xf<<12);
	  SYSCFG->EXTICR[0] |=(0x4<<12);
		
		// ��EXTI3����Ϊ�½��ش���
		EXTI->FTSR |=(0x1<<3);
		
		//����EXTI3���жϴ���
		EXTI->IMR |=(0x1<<3);
		
		//EXTI3��NVIC����
	  My_NVIC_Init(7-2,1,1,EXTI3_IRQn);
		
		
		
			/************����PE4**************/
	   
		//ѡ��PE4��ΪEXTI0�Ĵ����ܽ�
		SYSCFG->EXTICR[1] &=~(0xf<<0);
	  SYSCFG->EXTICR[1] |=(0x4<<0);
		
		// ��EXTI4����Ϊ�½��ش���
		EXTI->FTSR |=(0x1<<4);
		
		//����EXTI4���жϴ���
		EXTI->IMR |=(0x1<<4);
		
		//EXTI4��NVIC����
	  My_NVIC_Init(7-2,0,1,EXTI4_IRQn);
		
	}
	void  EXTI0_IRQHandler(void)
	{
		//����жϱ�־
		EXTI->PR|=(0x1<<0);
    LED1_ON;
		
 	}
	void  EXTI2_IRQHandler(void)
	{
		EXTI->PR|=(0x1<<2);
		LED1_OFF;
	
 	}
		void  EXTI3_IRQHandler(void)
	{
		 EXTI->PR|=(0x1<<3);
		 LED_ALLON();
	
 	}

		void  EXTI4_IRQHandler(void)
	{
		EXTI->PR|=(0x1<<4);
		LED_ALLOFF();

 	}
	
	void WJ_Exit_Init()
	{
	 /**
		 ��PF��ʱ����
		**/
		RCC->AHB1ENR |=(0x1<<5);
		
		
		
		//��SYSCFG��ʱ����
				
		RCC->APB2ENR |=(0x1<<14);
		
		 
		/**PF14 PF15 PF7**/
		
		
		
			/************����PF7**************/
		
		//����PF7������ģʽ
		GPIOF->MODER &=~(0x3<<14);
		GPIOF->MODER |=(0x0<<14);
		
		//����PF7��������ģʽ
		
		GPIOF->PUPDR &=~(0x3<<14);
		GPIOF->PUPDR |=(0x2<<14); // ����Ϊ����ģʽ
	   
		//ѡ��PF7��ΪEXTI7�Ĵ����ܽ�
		SYSCFG->EXTICR[1] &=~(0xf<<12);
    SYSCFG->EXTICR[1] |=(0x5<<12);		
		
		// ��EXTI7����Ϊ�����ش���
		EXTI->RTSR |=(0x1<<7);
		
		//����EXTI7���жϴ���
		EXTI->IMR |=(0x1<<7);
		
		//EXTI7��NVIC����
	  My_NVIC_Init(7-2,3,1,EXTI9_5_IRQn);
		
	
		
		/************����PF14**************/
		
			
		//����PF14������ģʽ
		GPIOF->MODER &=~(0x3<<28);
		GPIOF->MODER |=(0x0<<28);
		
		//����PF14��������ģʽ
		
		GPIOF->PUPDR &=~(0x3<<28);
		GPIOF->PUPDR |=(0x2<<28); // ����Ϊ����ģʽ
	   
		//ѡ��PF14��ΪEXTI14�Ĵ����ܽ�
		SYSCFG->EXTICR[3] &=~(0xf<<8);
    SYSCFG->EXTICR[3] |=(0x5<<8);		
		
		// ��EXTI14����Ϊ�½��ش���
		EXTI->RTSR |=(0x1<<14);
		
		//����EXTI14���жϴ���
		EXTI->IMR |=(0x1<<14);
		
		//EXTI14��NVIC����
	  My_NVIC_Init(7-2,2,1,EXTI15_10_IRQn);
		
		
		/************����PF15**************/
		
		
		
		//����PF15������ģʽ
		
		GPIOF->MODER &=~((unsigned int)0x3<<30);
		GPIOF->MODER |=((unsigned int)0x0<<30);
		
		//����PF15��������ģʽ
		
		GPIOF->PUPDR &=~((unsigned int)0x3<<2*15);
		GPIOF->PUPDR |=((unsigned int)0x2<<2*15); 
		
		// ����Ϊ����ģʽ
		
		
	   
		//ѡ��PF15��ΪEXTI15�Ĵ����ܽ�
		SYSCFG->EXTICR[3] &=~(0xf<<12);
    SYSCFG->EXTICR[3] |=(0x5<<12);		
		
		// ��EXTI15����Ϊ���ش���
		EXTI->RTSR |=(0x1<<15);
		
		//����EXTI15���жϴ���
		EXTI->IMR |=(0x1<<15);
		
		//EXTI15��NVIC����
	  My_NVIC_Init(7-2,1,1,EXTI15_10_IRQn);
		
	}
void EXTI9_5_IRQHandler(void)
{
 
	//ִ��PE7���ж������־
	if(EXTI->PR & (1<<7))
	{
	EXTI->PR |=(0x1<<7);
	LED1_OFF;
	}

}

void EXTI15_10_IRQHandler(void)
{
 
	//ִ��PE14���ж������־
	if(EXTI->PR & (1<<14))
	{
	EXTI->PR |=(0x1<<14);
	LED2_OFF;
	}
	
	else if(EXTI->PR & (1<<15))
	{
	EXTI->PR |=(0x1<<15);
	LED3_OFF;
	LED4_OFF;
	}

}

