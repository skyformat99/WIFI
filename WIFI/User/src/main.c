	#include "includes.h"
	/******************************************************
	* Name�� main����
	* Function��  ��ģ�����ʵ��
	* Description�� 
	* Author��  sun
	******************************************************/	

	int main()
	{
  char data[500];
	LED_Init();
	Usart1_Init(115200);
	Usart2_Init(115200);
	WIFI_Init();
	while(1)
	{
			
		//���ڽ�������	
		Usart2_Receivestring(data);
		
		//���ڷ�������
		Usart1_SendString((char *)data);
		
		
	}

	}
					 




