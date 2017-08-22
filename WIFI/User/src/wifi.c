#include "includes.h"


 char str[100];
 u8 str0[]="AT";
 u8 str1[] = "AT+RST";//复位
 u8 str2[] = "AT+CIFSR";//查询本机地址
 u8 str3[] = "AT+CWMODE=2";//设置wifi为2
	/*1： 代表是 Station 模式；
	2： 代表是 AP 模式；
	3： 代表是 AP 兼容 Station 模式。*/	
	
	
 u8 str4[] = "AT+CWSAP?";//查询当前 AP 的参数。
 u8 str5[] =" AT+CIPMUX=1";//开启多连接
 u8 str6[] = "AT+RESTORE";  //恢复出厂设置
 u8 str7[]="AT+CIPSERVER=1,8080";
void WIFI_Init(void)
{	
	int i=5;
	LED4_ON;
	//发送AT指令
	Usart2_SendString(str0);
	Usart2_Receivestring(str);
	Delay_ms(500);
	Usart1_SendString((char *)str);
	
	//发送查询本机地址命令
	Usart2_SendString(str2);
	Usart2_Receivestring(str);
	Delay_ms(500);
	Usart1_SendString((char *)str);
	
	//设置wifi为2
	Usart2_SendString(str3);
	Usart2_Receivestring(str);
	Delay_ms(500);
	Usart1_SendString((char *)str);

	

//	//WIFI 复位
//	USART2_Sendstring(str1);
//	while(i--)
//	{
//		Delay_ms(500);
//	}
	
//	//查询当前 AP 的参数。
//	USART2_Sendstring(str4);
//	while(i--)
//	{
//		Delay_ms(500);
//	}

	//开启多连接
	Usart2_SendString(str5);

	Usart2_Receivestring(str);
	Delay_ms(500);
	Usart1_SendString((char *)str);
		
	//发送管口
	Usart2_SendString(str7);

	Usart2_Receivestring(str);
	Delay_ms(500);
	Usart1_SendString((char *)str);
	LED4_OFF;
	
}