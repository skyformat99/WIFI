#include "includes.h"


 char str[100];
 u8 str0[]="AT";
 u8 str1[] = "AT+RST";//��λ
 u8 str2[] = "AT+CIFSR";//��ѯ������ַ
 u8 str3[] = "AT+CWMODE=2";//����wifiΪ2
	/*1�� ������ Station ģʽ��
	2�� ������ AP ģʽ��
	3�� ������ AP ���� Station ģʽ��*/	
	
	
 u8 str4[] = "AT+CWSAP?";//��ѯ��ǰ AP �Ĳ�����
 u8 str5[] =" AT+CIPMUX=1";//����������
 u8 str6[] = "AT+RESTORE";  //�ָ���������
 u8 str7[]="AT+CIPSERVER=1,8080";
void WIFI_Init(void)
{	
	int i=5;
	LED4_ON;
	//����ATָ��
	Usart2_SendString(str0);
	Usart2_Receivestring(str);
	Delay_ms(500);
	Usart1_SendString((char *)str);
	
	//���Ͳ�ѯ������ַ����
	Usart2_SendString(str2);
	Usart2_Receivestring(str);
	Delay_ms(500);
	Usart1_SendString((char *)str);
	
	//����wifiΪ2
	Usart2_SendString(str3);
	Usart2_Receivestring(str);
	Delay_ms(500);
	Usart1_SendString((char *)str);

	

//	//WIFI ��λ
//	USART2_Sendstring(str1);
//	while(i--)
//	{
//		Delay_ms(500);
//	}
	
//	//��ѯ��ǰ AP �Ĳ�����
//	USART2_Sendstring(str4);
//	while(i--)
//	{
//		Delay_ms(500);
//	}

	//����������
	Usart2_SendString(str5);

	Usart2_Receivestring(str);
	Delay_ms(500);
	Usart1_SendString((char *)str);
		
	//���͹ܿ�
	Usart2_SendString(str7);

	Usart2_Receivestring(str);
	Delay_ms(500);
	Usart1_SendString((char *)str);
	LED4_OFF;
	
}