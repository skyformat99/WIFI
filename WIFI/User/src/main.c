	#include "includes.h"
	/******************************************************
	* Name： main函数
	* Function：  子模块具体实现
	* Description： 
	* Author：  sun
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
			
		//串口接收数据	
		Usart2_Receivestring(data);
		
		//串口发送数据
		Usart1_SendString((char *)data);
		
		
	}

	}
					 




