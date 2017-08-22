#include "includes.h"


/******************** LCD���ų�ʼ������ *******************
LCD��ʾ��Ӳ���ܽŶ�Ӧ��ϵ��
�����ߣ�
DB0---PD14	DB1---PD15	DB2---PD0	DB3---PD1
DB4---PE7	DB5---PE8	DB6---PE9	DB7---PE10
DB8---PE11	DB9---PE12	DB10---PE13	DB11---PE14
DB12---PE15	DB13---PD8	DB14---PD9	DB15---PD10
�����ߣ�
WR---PD5	RD---PD4	CS---PG12	RS---PF12	BL--PB15
**********************************************************/
void LCD_Port_Init(void)
{
	 /* ʹ��LCDӲ���ܽ�ʱ�� */
	RCC->AHB1ENR |= (1<<3);//��PD
	RCC->AHB1ENR |= (1<<4);//��PE
	RCC->AHB1ENR |= (1<<6);//��PG
	RCC->AHB1ENR |= (1<<1);//��PB
	RCC->AHB1ENR |= (1<<5);//��PF
	
	
	/* ����LCDӲ���ܽ�ģʽ */
	/* DB0~DB15�����ߣ��������  ʱ��50M */
	GPIOD->MODER |=(0X1<<(2*14))|(0X1<<(2*15));   //���ó�ͨ�����  
	GPIOD->OSPEEDR |=(0X2<<(2*14))|(0X2ul<<(2*15)); //���ó��������50M 		
	
	GPIOD->MODER |=(0X1<<(2*0))|(0X1<<(2*1));     //���ó�ͨ�����  
	GPIOD->OSPEEDR |=(0X2<<(2*0))|(0X2<<(2*1));   //���ó��������50M
	
	GPIOE->MODER |=0x55554000;                    //���ó�ͨ�����  
	GPIOE->OTYPER |= 0;                           //���ó��������
	GPIOE->OSPEEDR |=0x55554000;                  //���ó��������50M

	GPIOD->MODER |=(0X1<<(2*8))|(0X1<<(2*9))|(0X1<<(2*10));  //���ó�ͨ�����  
	GPIOD->OSPEEDR |=(0X2<<(2*1))|(0X2<<(2*1))|(0X2<<(2*1));   //���ó��������50M
	
	/* �����ߣ��������  ʱ��50M ����Ϊ�ߵ�ƽ */
	GPIOD->MODER |=(0X1<<(2*4))|(0X1<<(2*5));  //���ó�ͨ�����  
	GPIOD->OSPEEDR |=(0X2<<(2*4))|(0X2<<(2*5));
	GPIOD->ODR |= (1<<4)|(1<<5);
	
	GPIOG->MODER |=(0X1<<(2*12));              //���ó�ͨ�����  
	GPIOG->OSPEEDR |=(0X2<<(2*12));
	GPIOG->ODR |= (1<<12);

	GPIOF->MODER |=(0X1<<(2*12));              //���ó�ͨ�����  
	GPIOF->OSPEEDR |=(0X2<<(2*12));
	GPIOF->ODR |= (1<<12);
	
	GPIOB->MODER |=(0X1<<(2*15));               //���ó�ͨ�����  
	GPIOB->OSPEEDR |=(0X2ul<<(2*15));
	GPIOB->ODR &= ~(1<<15);                     //�رձ��⣬��LCD��ʼ������ٴ�                
}

/******************* LCDд����� *********************************
��������Ҫ���������
********************************************************************/
void LCD_ILI9486_CMD(u16 common)
{	
	GPIOF->ODR &= ~(1 << 12);    //D/C����
	GPIOG->ODR &= ~(1 << 12);    //CS����
	GPIOD->ODR &= ~(1 << 5);     //WR����

	/* ������͵��������� */
	if(common&(1<<0))   GPIOD->BSRRL = (1<<14); else GPIOD->BSRRH = (1<<14);
	if(common&(1<<1))   GPIOD->BSRRL = (1<<15); else GPIOD->BSRRH = (1<<15);
	if(common&(1<<2))   GPIOD->BSRRL = (1<<0);  else GPIOD->BSRRH = (1<<0);
	if(common&0x08)   GPIOD->BSRRL = (1<<1);  else GPIOD->BSRRH = (1<<1);
	if(common&0x10)   GPIOE->BSRRL = (1<<7);  else GPIOE->BSRRH = (1<<7);
	if(common&0x20)   GPIOE->BSRRL = (1<<8);  else GPIOE->BSRRH = (1<<8);
	if(common&0x40)   GPIOE->BSRRL = (1<<9);  else GPIOE->BSRRH = (1<<9);
	if(common&0x80)   GPIOE->BSRRL = (1<<10); else GPIOE->BSRRH = (1<<10);
	if(common&0x0100) GPIOE->BSRRL = (1<<11); else GPIOE->BSRRH = (1<<11);
	if(common&0x0200) GPIOE->BSRRL = (1<<12); else GPIOE->BSRRH = (1<<12);
	if(common&0x0400) GPIOE->BSRRL = (1<<13); else GPIOE->BSRRH = (1<<13);
	if(common&0x0800) GPIOE->BSRRL = (1<<14); else GPIOE->BSRRH = (1<<14);
	if(common&0x1000) GPIOE->BSRRL = (1<<15); else GPIOE->BSRRH = (1<<15);
	if(common&0x2000) GPIOD->BSRRL = (1<<8);  else GPIOD->BSRRH = (1<<8);
	if(common&0x4000) GPIOD->BSRRL = (1<<9);  else GPIOD->BSRRH = (1<<9);
	if(common&(1<<15)) GPIOD->BSRRL = (1<<10); else GPIOD->BSRRH = (1<<10);
	GPIOD->ODR |= 1 << 5;        //WR����
	GPIOG->ODR |= 1 << 12;       //����CS
}

/******************* LCDд���ݺ��� *********************************
��������Ҫ���������
********************************************************************/
void LCD_ILI9486_Parameter(u16 data)
{
	GPIOF->ODR |= 1 << 12;       //D/C����
	GPIOG->ODR &= ~(1 << 12);    //CS����	
	GPIOD->ODR &= ~(1 << 5);     //WR����
	/* �����ݷ��͵��������� */
	if(data&0x01)   GPIOD->BSRRL = (1<<14); else GPIOD->BSRRH = (1<<14);
	if(data&0x02)   GPIOD->BSRRL = (1<<15); else GPIOD->BSRRH = (1<<15);
	if(data&0x04)   GPIOD->BSRRL = (1<<0);  else GPIOD->BSRRH = (1<<0);
	if(data&0x08)   GPIOD->BSRRL = (1<<1);  else GPIOD->BSRRH = (1<<1);
	if(data&0x10)   GPIOE->BSRRL = (1<<7);  else GPIOE->BSRRH = (1<<7);
	if(data&0x20)   GPIOE->BSRRL = (1<<8);  else GPIOE->BSRRH = (1<<8);
	if(data&0x40)   GPIOE->BSRRL = (1<<9);  else GPIOE->BSRRH = (1<<9);
	if(data&0x80)   GPIOE->BSRRL = (1<<10); else GPIOE->BSRRH = (1<<10);
	if(data&0x0100) GPIOE->BSRRL = (1<<11); else GPIOE->BSRRH = (1<<11);
	if(data&0x0200) GPIOE->BSRRL = (1<<12); else GPIOE->BSRRH = (1<<12);
	if(data&0x0400) GPIOE->BSRRL = (1<<13); else GPIOE->BSRRH = (1<<13);
	if(data&0x0800) GPIOE->BSRRL = (1<<14); else GPIOE->BSRRH = (1<<14);
	if(data&0x1000) GPIOE->BSRRL = (1<<15); else GPIOE->BSRRH = (1<<15);
	if(data&0x2000) GPIOD->BSRRL = (1<<8);  else GPIOD->BSRRH = (1<<8);
	if(data&0x4000) GPIOD->BSRRL = (1<<9);  else GPIOD->BSRRH = (1<<9);
	if(data&0x8000) GPIOD->BSRRL = (1<<10); else GPIOD->BSRRH = (1<<10);
	GPIOD->ODR |= 1 << 5;        //WR����
	GPIOG->ODR |= 1 << 12;       //����CS
}

/********************** LCD�������� ******************************************
������
SX��EX��X�����ʼ����ͽ�������
SY��EY��Y�����ʼ����ͽ�������
Color�� ��Ļ��ɫ
******************************************************************************/
void LCD_Clear(u16 SX, u16 EX, u16 SY, u16 EY, u16 Color)
{
	u32 i;
	
	LCD_ILI9486_CMD(0x2A);                      //����0x2A�������X������
	LCD_ILI9486_Parameter((SX & 0xff00) >> 8);  //����X����ʼ����ĸ�8λ
	LCD_ILI9486_Parameter((SX & 0x00ff));       //����X����ʼ����ĵ�8λ
	LCD_ILI9486_Parameter((EX & 0xff00) >> 8);  //����X���������ĸ�8λ
	LCD_ILI9486_Parameter((EX & 0x00ff));       //����X���������ĵ�8λ
	
	LCD_ILI9486_CMD(0x2B);                      //����0x2B�������Y������
	LCD_ILI9486_Parameter((SY & 0xff00) >> 8);  //����Y����ʼ����ĸ�8λ
	LCD_ILI9486_Parameter((SY & 0x00ff));       //����Y����ʼ����ĵ�8λ
	LCD_ILI9486_Parameter((EY & 0xff00) >> 8);  //����Y���������ĸ�8λ
	LCD_ILI9486_Parameter((EY & 0x00ff));       //����Y���������ĵ�8λ
	
	LCD_ILI9486_CMD(0x2C);                      //����0x2A�������LCD��ʾ��ɫ
	for(i = 0; i < (EX - SX + 1) * (EY - SY + 1); i++)  //ѭ�����������ÿһ�����ص�
	{
		LCD_ILI9486_Parameter(Color);
	}
}

/********************** LCD��ʼ������ *******************************************/
void LCD_Init(void)
{
	LCD_Port_Init();
	//************* Reset LCD Driver ****************//
	Delay_ms(120); // Delay 120 ms
	//************* Start Initial Sequence **********//
	LCD_ILI9486_CMD(0XF2);
	LCD_ILI9486_Parameter(0x18);
	LCD_ILI9486_Parameter(0xA3);
	LCD_ILI9486_Parameter(0x12);
	LCD_ILI9486_Parameter(0x02);
	LCD_ILI9486_Parameter(0XB2);
	LCD_ILI9486_Parameter(0x12);
	LCD_ILI9486_Parameter(0xFF);
	LCD_ILI9486_Parameter(0x10);
	LCD_ILI9486_Parameter(0x00);
	LCD_ILI9486_CMD(0XF8);
	LCD_ILI9486_Parameter(0x21);
	LCD_ILI9486_Parameter(0x04);
	LCD_ILI9486_CMD(0XF9);
	LCD_ILI9486_Parameter(0x00);
	LCD_ILI9486_Parameter(0x08);
	LCD_ILI9486_CMD(0x36);
	LCD_ILI9486_Parameter(0x08);  
	LCD_ILI9486_CMD(0x3A);
	LCD_ILI9486_Parameter(0x55);   //����16λBPP
	LCD_ILI9486_CMD(0xB4);
	LCD_ILI9486_Parameter(0x01);//0x00
	LCD_ILI9486_CMD(0xB6);
	LCD_ILI9486_Parameter(0x02);
	LCD_ILI9486_Parameter(0x22);
	LCD_ILI9486_CMD(0xC1);
	LCD_ILI9486_Parameter(0x41);
	LCD_ILI9486_CMD(0xC5);
	LCD_ILI9486_Parameter(0x00);
	LCD_ILI9486_Parameter(0x07);//0X18
	LCD_ILI9486_CMD(0xE0);
	LCD_ILI9486_Parameter(0x0F);
	LCD_ILI9486_Parameter(0x1F);
	LCD_ILI9486_Parameter(0x1C);
	LCD_ILI9486_Parameter(0x0C);
	LCD_ILI9486_Parameter(0x0F);
	LCD_ILI9486_Parameter(0x08);
	LCD_ILI9486_Parameter(0x48);
	LCD_ILI9486_Parameter(0x98);
	LCD_ILI9486_Parameter(0x37);
	LCD_ILI9486_Parameter(0x0A);
	LCD_ILI9486_Parameter(0x13);
	LCD_ILI9486_Parameter(0x04);
	LCD_ILI9486_Parameter(0x11);
	LCD_ILI9486_Parameter(0x0D);
	LCD_ILI9486_Parameter(0x00);
	LCD_ILI9486_CMD(0xE1);
	LCD_ILI9486_Parameter(0x0F);
	LCD_ILI9486_Parameter(0x32);
	LCD_ILI9486_Parameter(0x2E);
	LCD_ILI9486_Parameter(0x0B);
	LCD_ILI9486_Parameter(0x0D);
	LCD_ILI9486_Parameter(0x05);
	LCD_ILI9486_Parameter(0x47);
	LCD_ILI9486_Parameter(0x75);
	LCD_ILI9486_Parameter(0x37);
	LCD_ILI9486_Parameter(0x06);
	LCD_ILI9486_Parameter(0x10);
	LCD_ILI9486_Parameter(0x03);
	LCD_ILI9486_Parameter(0x24);
	LCD_ILI9486_Parameter(0x20);
	LCD_ILI9486_Parameter(0x00);
	LCD_ILI9486_CMD(0x11);   //�˳�˯��
	Delay_ms(120);
	LCD_ILI9486_CMD(0x29);   //������ʾ
	
	/* �������û���ʵ�ʱ�д */
	LCD_Clear(0,319,0,479,WHITE);  //����Ļ��ɫλ��ɫ
	GPIOB->ODR |= 1 << 15;          //��LCD�����
}


/*****************************
��������LCD_Draw_Point
����������
u16 x   u16 y   u16 color
������  ������   ��ɫ

��������ֵ����
�������ܣ���LCD����ʾһ����
����������

*****************************/
void LCD_Draw_Point(u16 x ,u16 y ,u16 color)
{
	LCD_ILI9486_CMD(0x2A);                      //����0x2A�������X������
	LCD_ILI9486_Parameter((x & 0xff00) >> 8);  //����X����ʼ����ĸ�8λ
	LCD_ILI9486_Parameter((x & 0x00ff));       //����X����ʼ����ĵ�8λ
	LCD_ILI9486_Parameter((x & 0xff00) >> 8);  //����X���������ĸ�8λ
	LCD_ILI9486_Parameter((x & 0x00ff));       //����X���������ĵ�8λ
	
	LCD_ILI9486_CMD(0x2B);                      //����0x2B�������Y������
	LCD_ILI9486_Parameter((y & 0xff00) >> 8);  //����Y����ʼ����ĸ�8λ
	LCD_ILI9486_Parameter((y & 0x00ff));       //����Y����ʼ����ĵ�8λ
	LCD_ILI9486_Parameter((y & 0xff00) >> 8);  //����Y���������ĸ�8λ
	LCD_ILI9486_Parameter((y & 0x00ff));       //����Y���������ĵ�8λ
	
	LCD_ILI9486_CMD(0x2C);
	LCD_ILI9486_Parameter(color);
}



/*****************************
��������LCD_Draw
����������
u16 x_start   u16 y_start    u16 x_end  u16 y_end  u16 color
��ʼ������  ��ʼ������   ��ɫ  �յ������  �յ�������  ��ɫ

��������ֵ����
�������ܣ���LCD����ĳ���������ĳ����ɫ
����������
*****************************/
void LCD_Draw(u16 x_start ,u16 y_start,u16 x_end ,u16 y_end ,u16 color)
{
	u16 i;
	//ȷ��Ҫ��ʾ����Ŀ�ȷ�Χ
	LCD_ILI9486_CMD(0x2A); 
	LCD_ILI9486_Parameter(x_start>>8);//��ʼλ�õĸ�8λ��Ҫͨ����8λ�������ߴ���
	LCD_ILI9486_Parameter(x_start);//��ʼλ�õĵ�8λ
	LCD_ILI9486_Parameter(x_end>>8);//����λ�õĸ�8λ��Ҫͨ����8λ�������ߴ���
	LCD_ILI9486_Parameter(x_end);//����λ�õĵ�8λ
	
	//ȷ��Ҫ��ʾ����ĸ߶ȷ�Χ
	LCD_ILI9486_CMD(0x2B); 
	LCD_ILI9486_Parameter(y_start>>8);//��ʼλ�õĸ�8λ��Ҫͨ����8λ�������ߴ���
	LCD_ILI9486_Parameter(y_start);//��ʼλ�õĵ�8λ
	LCD_ILI9486_Parameter(y_end>>8);//����λ�õĸ�8λ��Ҫͨ����8λ�������ߴ���
	LCD_ILI9486_Parameter(y_end);//����λ�õĵ�8λ
	
	//��ȷ���ķ�Χ�������ɫ
	LCD_ILI9486_CMD(0x2C); 
	for(i=0;i<(x_end -x_start)*(y_end -y_start);i++)
	{
		LCD_ILI9486_Parameter(color);
	}
}


/***************************************
��������LCD_Dis16hz
����������
u16 x  u16 y  u16 color  u16 backcolor  u8 *buf
  ��ʼλ��     ������ɫ   ������ɫ       ��������
��������ֵ����
�������ܣ���LCD��ʾ16*16 ��С�ĺ���
***************************************/
void LCD_Dis16hz(u16 x,u16 y,u16 color,u16 backcolor,u8 *buf)
{
	u16 i,j;
	u16 temp;
	//ȷ��Ҫ��ʾ����Ŀ�ȷ�Χ
	LCD_ILI9486_CMD(0x2A); 
	LCD_ILI9486_Parameter(x>>8);//��ʼλ�õĸ�8λ��Ҫͨ����8λ�������ߴ���
	LCD_ILI9486_Parameter(x);//��ʼλ�õĵ�8λ
	LCD_ILI9486_Parameter((x+15)>>8);//����λ�õĸ�8λ��Ҫͨ����8λ�������ߴ���
	LCD_ILI9486_Parameter(x+15);//����λ�õĵ�8λ
	
	//ȷ��Ҫ��ʾ����ĸ߶ȷ�Χ
	LCD_ILI9486_CMD(0x2B); 
	LCD_ILI9486_Parameter(y>>8);//��ʼλ�õĸ�8λ��Ҫͨ����8λ�������ߴ���
	LCD_ILI9486_Parameter(y);//��ʼλ�õĵ�8λ
	LCD_ILI9486_Parameter((y+15)>>8);//����λ�õĸ�8λ��Ҫͨ����8λ�������ߴ���
	LCD_ILI9486_Parameter(y+15);//����λ�õĵ�8λ
	
	//��ȷ���ķ�Χ�������ɫ
	LCD_ILI9486_CMD(0x2C); 
	for(i=0;i<16;i++)//��
	{
		//�õ�ÿһ�е�����
		temp = buf[2*i]<<8 |buf[2*i+1];
		for(j=0;j<16;j++)//��
		{
			 if(temp &(0x8000>>j))//����
			 {
				 LCD_ILI9486_Parameter(color);
			 }
			 else //����
			 {
				 LCD_ILI9486_Parameter(backcolor);
			 }
		}
	}
}


/***************************************
��������LCD_Dis32hz
����������
u16 x  u16 y  u16 color  u16 backcolor  u8 *buf
  ��ʼλ��     ������ɫ   ������ɫ       ��������
��������ֵ����
�������ܣ���LCD��ʾ32*32 ��С�ĺ���
***************************************/
void LCD_Dis32hz(u16 x,u16 y,u16 color, const u8 *pic,u8 *buf)
{
	u16 i,j;
	u32 temp;
	u16 backcolor;
	//ȷ��Ҫ��ʾ����Ŀ�ȷ�Χ
	LCD_ILI9486_CMD(0x2A); 
	LCD_ILI9486_Parameter(x>>8);//��ʼλ�õĸ�8λ��Ҫͨ����8λ�������ߴ���
	LCD_ILI9486_Parameter(x);//��ʼλ�õĵ�8λ
	LCD_ILI9486_Parameter((x+31)>>8);//����λ�õĸ�8λ��Ҫͨ����8λ�������ߴ���
	LCD_ILI9486_Parameter(x+31);//����λ�õĵ�8λ
	
	//ȷ��Ҫ��ʾ����ĸ߶ȷ�Χ
	LCD_ILI9486_CMD(0x2B); 
	LCD_ILI9486_Parameter(y>>8);//��ʼλ�õĸ�8λ��Ҫͨ����8λ�������ߴ���
	LCD_ILI9486_Parameter(y);//��ʼλ�õĵ�8λ
	LCD_ILI9486_Parameter((y+31)>>8);//����λ�õĸ�8λ��Ҫͨ����8λ�������ߴ���
	LCD_ILI9486_Parameter(y+31);//����λ�õĵ�8λ
	
	//��ȷ���ķ�Χ�������ɫ
	LCD_ILI9486_CMD(0x2C); 
	for(i=0;i<32;i++)//��
	{
		//�õ�ÿһ�е�����
		temp = buf[4*i]<<24 |buf[4*i+1]<<16 |buf[4*i +2]<<8 |buf[4*i+3];
		for(j=0;j<32;j++)//��
		{
			 if(temp &(0x80000000>>j))//����
			 {
				 LCD_ILI9486_Parameter(color);
			 }
			 else //����
			 {
				 backcolor =pic[(i+y)*320*2 +(j+x)*2]<<8 |pic[(i+y)*320*2 +(j+x)*2+1];
				 LCD_ILI9486_Parameter(backcolor);
			 }
		}
	}
}
void LCD_Dishz(u16 x,u16 y,u16 color,	u16 backcolor,u8 *buf)
{
	u16 i,j;
	u32 temp;

	//ȷ��Ҫ��ʾ����Ŀ�ȷ�Χ
	LCD_ILI9486_CMD(0x2A); 
	LCD_ILI9486_Parameter(x>>8);//��ʼλ�õĸ�8λ��Ҫͨ����8λ�������ߴ���
	LCD_ILI9486_Parameter(x);//��ʼλ�õĵ�8λ
	LCD_ILI9486_Parameter((x+31)>>8);//����λ�õĸ�8λ��Ҫͨ����8λ�������ߴ���
	LCD_ILI9486_Parameter(x+31);//����λ�õĵ�8λ
	
	//ȷ��Ҫ��ʾ����ĸ߶ȷ�Χ
	LCD_ILI9486_CMD(0x2B); 
	LCD_ILI9486_Parameter(y>>8);//��ʼλ�õĸ�8λ��Ҫͨ����8λ�������ߴ���
	LCD_ILI9486_Parameter(y);//��ʼλ�õĵ�8λ
	LCD_ILI9486_Parameter((y+31)>>8);//����λ�õĸ�8λ��Ҫͨ����8λ�������ߴ���
	LCD_ILI9486_Parameter(y+31);//����λ�õĵ�8λ
	
	//��ȷ���ķ�Χ�������ɫ
	LCD_ILI9486_CMD(0x2C); 
	for(i=0;i<32;i++)//��
	{
		//�õ�ÿһ�е�����
		temp = buf[4*i]<<24 |buf[4*i+1]<<16 |buf[4*i +2]<<8 |buf[4*i+3];
		for(j=0;j<32;j++)//��
		{
			 if(temp &(0x80000000>>j))//����
			 {
				 LCD_ILI9486_Parameter(color);
			 }
			 else //����
			 {
				// backcolor =pic[(i+y)*320*2 +(j+x)*2]<<8 |pic[(i+y)*320*2 +(j+x)*2+1];
				 LCD_ILI9486_Parameter(backcolor);
			 }
		}
	}
}
/***************************************
��������LCD_Disanyhz
����������
u16 x  u16 y  u16 width  u16 high u16 color  u16 backcolor  u8 *buf
  ��ʼλ��      ���ֿ��    ���ָ߶�  ������ɫ   ������ɫ       ��������
��������ֵ����
�������ܣ���LCD��ʾ�����С�ĺ���
***************************************/
void LCD_Disanyhz(u16 x,u16 y,u16 width,u16 high,u16 color,u16 backcolor,u8 *buf)
{
	u16 i,j,k;
	//ȷ��Ҫ��ʾ����Ŀ�ȷ�Χ
	LCD_ILI9486_CMD(0x2A); 
	LCD_ILI9486_Parameter(x>>8);//��ʼλ�õĸ�8λ��Ҫͨ����8λ�������ߴ���
	LCD_ILI9486_Parameter(x);//��ʼλ�õĵ�8λ
	LCD_ILI9486_Parameter((x+width-1)>>8);//����λ�õĸ�8λ��Ҫͨ����8λ�������ߴ���
	LCD_ILI9486_Parameter(x+width-1);//����λ�õĵ�8λ
	
	//ȷ��Ҫ��ʾ����ĸ߶ȷ�Χ
	LCD_ILI9486_CMD(0x2B); 
	LCD_ILI9486_Parameter(y>>8);//��ʼλ�õĸ�8λ��Ҫͨ����8λ�������ߴ���
	LCD_ILI9486_Parameter(y);//��ʼλ�õĵ�8λ
	LCD_ILI9486_Parameter((y+high-1)>>8);//����λ�õĸ�8λ��Ҫͨ����8λ�������ߴ���
	LCD_ILI9486_Parameter(y+high-1);//����λ�õĵ�8λ
	
	//��ȷ���ķ�Χ�������ɫ
	LCD_ILI9486_CMD(0x2C); 
	for(i=0;i<high;i++)//��
	{
		//��һ�в�ֳ�n��8λ
		for(k=0;k<width/8;k++)
		{
			 //8λ����
			for(j=0;j<8;j++)//��
			{
				 if(*buf &(0x80>>j))//����
				 {
					 LCD_ILI9486_Parameter(color);
				 }
				 else //����
				 {
					 LCD_ILI9486_Parameter(backcolor);
				 }
			}
			buf++;
		}
		
	}
}


/***************************************
��������LCD_Dispic
����������
u16 x  u16 y  u16 width  u16 high        u8 *buf
  ��ʼλ��      ͼƬ���    ͼƬ�߶�      ��������
��������ֵ����
�������ܣ���LCD��ʾ�����С��ͼƬ
***************************************/
void LCD_Dispic(u16 x,u16 y,u16 width,u16 high ,const u8 *buf)
{
	u16 i,j;
	u16 color;
	//ȷ��Ҫ��ʾ����Ŀ�ȷ�Χ
	LCD_ILI9486_CMD(0x2A); 
	LCD_ILI9486_Parameter(x>>8);//��ʼλ�õĸ�8λ��Ҫͨ����8λ�������ߴ���
	LCD_ILI9486_Parameter(x);//��ʼλ�õĵ�8λ
	LCD_ILI9486_Parameter((x+width-1)>>8);//����λ�õĸ�8λ��Ҫͨ����8λ�������ߴ���
	LCD_ILI9486_Parameter(x+width-1);//����λ�õĵ�8λ
	
	//ȷ��Ҫ��ʾ����ĸ߶ȷ�Χ
	LCD_ILI9486_CMD(0x2B); 
	LCD_ILI9486_Parameter(y>>8);//��ʼλ�õĸ�8λ��Ҫͨ����8λ�������ߴ���
	LCD_ILI9486_Parameter(y);//��ʼλ�õĵ�8λ
	LCD_ILI9486_Parameter((y+high-1)>>8);//����λ�õĸ�8λ��Ҫͨ����8λ�������ߴ���
	LCD_ILI9486_Parameter(y+high-1);//����λ�õĵ�8λ
	
	//��ȷ���ķ�Χ�������ɫ
	LCD_ILI9486_CMD(0x2C); 
	for(i=0;i<high;i++)//��
	{
		for(j=0;j<width;j++)//��
		{
			//�õ�ͼƬ��ÿһ����ɫֵ
			color = buf[i*width*2 +j*2] <<8 |buf[i*width*2 +j*2+1];
			LCD_ILI9486_Parameter(color);
		}
	}
	
}


/***************************************
��������LCD_Dispic1
����������
 struct PIC pic ��ͼƬ��Ϣ�ṹ�����
��������ֵ����
�������ܣ���LCD��ʾ�����С��ͼƬ
***************************************/
void LCD_Dispic1(struct PIC pic)
{
	u16 i,j;
	u16 color;
	//ȷ��Ҫ��ʾ����Ŀ�ȷ�Χ
	LCD_ILI9486_CMD(0x2A); 
	LCD_ILI9486_Parameter(pic.x>>8);//��ʼλ�õĸ�8λ��Ҫͨ����8λ�������ߴ���
	LCD_ILI9486_Parameter(pic.x);//��ʼλ�õĵ�8λ
	LCD_ILI9486_Parameter((pic.x+pic.width-1)>>8);//����λ�õĸ�8λ��Ҫͨ����8λ�������ߴ���
	LCD_ILI9486_Parameter(pic.x+pic.width-1);//����λ�õĵ�8λ
	
	//ȷ��Ҫ��ʾ����ĸ߶ȷ�Χ
	LCD_ILI9486_CMD(0x2B); 
	LCD_ILI9486_Parameter(pic.y>>8);//��ʼλ�õĸ�8λ��Ҫͨ����8λ�������ߴ���
	LCD_ILI9486_Parameter(pic.y);//��ʼλ�õĵ�8λ
	LCD_ILI9486_Parameter((pic.y+pic.high-1)>>8);//����λ�õĸ�8λ��Ҫͨ����8λ�������ߴ���
	LCD_ILI9486_Parameter(pic.y+pic.high-1);//����λ�õĵ�8λ
	
	//��ȷ���ķ�Χ�������ɫ
	LCD_ILI9486_CMD(0x2C); 
	for(i=0;i<pic.high;i++)//��
	{
		for(j=0;j<pic.width;j++)//��
		{
			//�õ�ͼƬ��ÿһ����ɫֵ
			color = pic.buf[i*pic.width*2 +j*2] <<8 |pic.buf[i*pic.width*2 +j*2+1];
			LCD_ILI9486_Parameter(color);
		}
	}
	
}

/***************************************
��������LCD_Dispic2
����������
u16 x  u16 y         u8 *buf
  ��ʼλ��          ��������
��������ֵ����
�������ܣ���LCD��ʾ�����С��ͼƬ
  ��ѡ ����ͼ��ͷ��Ϣ
***************************************/
void LCD_Dispic2(u16 x,u16 y,const u8 *buf)
{
	u16 i,j;
	u16 color;
	u16 width;
	u16 high ;
	width =buf[2]<<8 |buf[3];
	high =buf[4]<<8 |buf[5];
	//ȷ��Ҫ��ʾ����Ŀ�ȷ�Χ
	LCD_ILI9486_CMD(0x2A); 
	LCD_ILI9486_Parameter(x>>8);//��ʼλ�õĸ�8λ��Ҫͨ����8λ�������ߴ���
	LCD_ILI9486_Parameter(x);//��ʼλ�õĵ�8λ
	LCD_ILI9486_Parameter((x+width-1)>>8);//����λ�õĸ�8λ��Ҫͨ����8λ�������ߴ���
	LCD_ILI9486_Parameter(x+width-1);//����λ�õĵ�8λ
	
	//ȷ��Ҫ��ʾ����ĸ߶ȷ�Χ
	LCD_ILI9486_CMD(0x2B); 
	LCD_ILI9486_Parameter(y>>8);//��ʼλ�õĸ�8λ��Ҫͨ����8λ�������ߴ���
	LCD_ILI9486_Parameter(y);//��ʼλ�õĵ�8λ
	LCD_ILI9486_Parameter((y+high-1)>>8);//����λ�õĸ�8λ��Ҫͨ����8λ�������ߴ���
	LCD_ILI9486_Parameter(y+high-1);//����λ�õĵ�8λ
	
	//��ȷ���ķ�Χ�������ɫ
	LCD_ILI9486_CMD(0x2C); 
	for(i=0;i<high;i++)//��
	{
		for(j=0;j<width;j++)//��
		{
			//�õ�ͼƬ��ÿһ����ɫֵ
			color = buf[i*width*2 +j*2+8] <<8 |buf[i*width*2 +j*2+1+8];
			LCD_ILI9486_Parameter(color);
		}
	}
	
}

/***************************************
��������LCD_Dis32ch
����������
u16 x  u16 y  u16 color  u16 backcolor  u8 *buf
  ��ʼλ��     ������ɫ   ������ɫ       ��������
��������ֵ����
�������ܣ���LCD��ʾ32*32 ��С���ַ�
***************************************/
void LCD_Dis32ch(u16 x,u16 y,u16 color,const u8 *pic,u8 *buf)
{
	u16 i,j;
	u32 temp;
	u16 backcolor;
	//ȷ��Ҫ��ʾ����Ŀ�ȷ�Χ
	LCD_ILI9486_CMD(0x2A); 
	LCD_ILI9486_Parameter(x>>8);//��ʼλ�õĸ�8λ��Ҫͨ����8λ�������ߴ���
	LCD_ILI9486_Parameter(x);//��ʼλ�õĵ�8λ
	LCD_ILI9486_Parameter((x+15)>>8);//����λ�õĸ�8λ��Ҫͨ����8λ�������ߴ���
	LCD_ILI9486_Parameter(x+15);//����λ�õĵ�8λ
	
	//ȷ��Ҫ��ʾ����ĸ߶ȷ�Χ
	LCD_ILI9486_CMD(0x2B); 
	LCD_ILI9486_Parameter(y>>8);//��ʼλ�õĸ�8λ��Ҫͨ����8λ�������ߴ���
	LCD_ILI9486_Parameter(y);//��ʼλ�õĵ�8λ
	LCD_ILI9486_Parameter((y+31)>>8);//����λ�õĸ�8λ��Ҫͨ����8λ�������ߴ���
	LCD_ILI9486_Parameter(y+31);//����λ�õĵ�8λ
	
	//��ȷ���ķ�Χ�������ɫ
	LCD_ILI9486_CMD(0x2C); 
	for(i=0;i<32;i++)//��
	{
		//�õ�ÿһ�е�����
		temp = buf[2*i]<<8 |buf[2*i+1];
		for(j=0;j<16;j++)//��
		{
			 if(temp &(0x8000>>j))//����
			 {
				 LCD_ILI9486_Parameter(color);
			 }
			 else //����
			 {
				  backcolor =pic[(i+y)*320*2 +(j+x)*2]<<8 |pic[(i+y)*320*2 +(j+x)*2+1];
				 LCD_ILI9486_Parameter(backcolor);
			 }
		}
	}
}
void LCD_Diszf(u16 x,u16 y,u16 color,	u16 backcolor,u8 *buf)
{
	u16 i,j;
	u32 temp;

	//ȷ��Ҫ��ʾ����Ŀ�ȷ�Χ
	LCD_ILI9486_CMD(0x2A); 
	LCD_ILI9486_Parameter(x>>8);//��ʼλ�õĸ�8λ��Ҫͨ����8λ�������ߴ���
	LCD_ILI9486_Parameter(x);//��ʼλ�õĵ�8λ
	LCD_ILI9486_Parameter((x+15)>>8);//����λ�õĸ�8λ��Ҫͨ����8λ�������ߴ���
	LCD_ILI9486_Parameter(x+15);//����λ�õĵ�8λ
	
	//ȷ��Ҫ��ʾ����ĸ߶ȷ�Χ
	LCD_ILI9486_CMD(0x2B); 
	LCD_ILI9486_Parameter(y>>8);//��ʼλ�õĸ�8λ��Ҫͨ����8λ�������ߴ���
	LCD_ILI9486_Parameter(y);//��ʼλ�õĵ�8λ
	LCD_ILI9486_Parameter((y+31)>>8);//����λ�õĸ�8λ��Ҫͨ����8λ�������ߴ���
	LCD_ILI9486_Parameter(y+31);//����λ�õĵ�8λ
	
	//��ȷ���ķ�Χ�������ɫ
	LCD_ILI9486_CMD(0x2C); 
	for(i=0;i<32;i++)//��
	{
		//�õ�ÿһ�е�����
		temp = buf[2*i]<<8 |buf[2*i+1];
		for(j=0;j<16;j++)//��
		{
			 if(temp &(0x8000>>j))//����
			 {
				 LCD_ILI9486_Parameter(color);
			 }
			 else //����
			 {
				 // backcolor =pic[(i+y)*320*2 +(j+x)*2]<<8 |pic[(i+y)*320*2 +(j+x)*2+1];
				 LCD_ILI9486_Parameter(backcolor);
			 }
		}
	}
}

/***************************************
��������LCD_DisString
����������
u16 x  u16 y   u16 color  u16 backcolor  u8 *buf
  ��ʼλ��      ������ɫ   ������ɫ       �ַ�������
��������ֵ����
�������ܣ���LCD��ʾ�ַ���

u8 *buf="��a��bc��2017��/07/31";
***************************************/
void LCD_DisString(u16 x,u16 y ,u16 color,const u8 *pic, u8 *buf)
{
	u32 AB ; //����
	u32 CD ; //λ��
	u32 addr; 
	u8 str[128];
	u8 ch[64];
	 while(*buf !='\0')//�ַ�����������Ҫ��ʾ������
	 {
		 if(*buf>0xa0 && *(buf+1)>0xa0)//Ҫ��ʾ���Ǻ���
		 {
			 //��GB2312���ֿ����ҵ�Ҫ��ʾ�ĺ���
			 AB = (*buf-0xa1) *94; //�������ڵ���
			 CD = *(buf+1)-0xa1;   //������������ռ��λ
			 addr =(AB+CD)*128 ;   //�������ֿ��ļ��еĵ�ַ
			 addr +=0;            //�ֿ��ڴ洢оƬ�еĿ�ʼλ��
				//�Ӵ洢оƬ�ж�������
       W25Q64_Read_DateFromZK(addr,128,str);
					 //��ȡ������ʾ����
			 LCD_Dis32hz(x,y,color,pic,str);
			
			  buf +=2;
				  x +=32; //ˮƽ��ʾ�ַ���
			 
		 }
		
		 else if(*buf >=' ' && *buf <='~')//Ҫ��ʾ�����ַ�
		 {
			 //��ASCLL�ַ������ҵ�Ҫ��ʾ���ַ�
			 addr = (*buf-32) *64 ;//�ַ����ֿ��ļ��еĵ�ַ
			 addr += 1046790 ;   //���ٺ��ֿ��ڴ洢оƬ�е�ƫ��
			 //�Ӵ洢оƬ�ж�������
	       W25Q64_Read_DateFromZK(addr,64,ch);
				 //��ȡ�ַ���ʾ����
				 LCD_Dis32ch(x,y,color,pic,ch);
	
			 buf++;
			 x +=16;
			 
		 }
	 }
}



/***************************************
��������LCD_DisString
����������
u16 x  u16 y   u16 color  u16 backcolor  u8 *buf
  ��ʼλ��      ������ɫ   ������ɫ       �ַ�������
��������ֵ����
�������ܣ���LCD��ʾ�ַ���

u8 *buf="��a��bc��2017��/07/31";
***************************************/
void LCD_ShowString(u16 x,u16 y ,u16 color, u16 back, u8 *buf)
{
	 u8 i;
	u32 AB ; //����
	u32 CD ; //λ��
	u32 addr; 
	u8 str[128];
	u8 ch[64];
	 while(*buf !='\0')//�ַ�����������Ҫ��ʾ������
	 {
		 if(*buf>0xa0 && *(buf+1)>0xa0)//Ҫ��ʾ���Ǻ���
		 {
			 //��GB2312���ֿ����ҵ�Ҫ��ʾ�ĺ���
			 AB = (*buf-0xa1) *94; //�������ڵ���
			 CD = *(buf+1)-0xa1;   //������������ռ��λ
			 addr =(AB+CD)*128 ;   //�������ֿ��ļ��еĵ�ַ
			 addr +=0;            //�ֿ��ڴ洢оƬ�еĿ�ʼλ��
				//�Ӵ洢оƬ�ж�������
       W25Q64_Read_DateFromZK(addr,128,str);
					 //��ȡ������ʾ����
			 LCD_Dishz(x,y,color,back,str);
			
			  buf +=2;
				  x +=32; //ˮƽ��ʾ�ַ���
			 
		 }
		
		 else if(*buf >=' ' && *buf <='~')//Ҫ��ʾ�����ַ�
		 {
			 //��ASCLL�ַ������ҵ�Ҫ��ʾ���ַ�
			 addr = (*buf-32) *64 ;//�ַ����ֿ��ļ��еĵ�ַ
			 addr += 1046790 ;   //���ٺ��ֿ��ڴ洢оƬ�е�ƫ��
			 //�Ӵ洢оƬ�ж�������
	       W25Q64_Read_DateFromZK(addr,64,ch);
				 //��ȡ�ַ���ʾ����
				 LCD_Diszf(x,y,color,back,ch);
			 buf++;
			 x +=16;
			 
		 }
	 }
}












