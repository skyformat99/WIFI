#ifndef   LCD_H
#define   LCD_H

#include "stm32f4xx.h" 


//������ɫ
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE         	 0x001F  
#define BRED             0XF81F
#define GRED 			 0XFFE0
#define GBLUE			 0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			 0XBC40 //��ɫ
#define BRRED 			 0XFC07 //�غ�ɫ
#define GRAY  			 0X8430 //��ɫ
//GUI��ɫ

#define DARKBLUE      	 0X01CF	//����ɫ
#define LIGHTBLUE      	 0X7D7C	//ǳ��ɫ  
#define GRAYBLUE       	 0X5458 //����ɫ
//������ɫΪPANEL����ɫ 
 
#define LIGHTGREEN     	 0X841F //ǳ��ɫ
//#define LIGHTGRAY        0XEF5B //ǳ��ɫ(PANNEL)
#define LGRAY 			 0XC618 //ǳ��ɫ(PANNEL),���屳��ɫ

#define LGRAYBLUE        0XA651 //ǳ����ɫ(�м����ɫ)
#define LBBLUE           0X2B12 //ǳ����ɫ(ѡ����Ŀ�ķ�ɫ)


//����ͼƬ��Ϣ�ṹ��
struct PIC
{
	u16 x;//��ʼ������
	u16 y;//��ʼ������
	u16 width ; //ͼƬʵ�ʿ��
	u16 high ; //ͼƬʵ�ʸ߶�
	const u8 *buf ;//ͼƬ��ɫ������
};

extern u8 hz_index[];
extern u8 hz_table[];
extern u8 ch_index[];
extern u8 ch_table[];

extern const unsigned char gImage_pic1[307200];
extern const unsigned char gImage_pic2[307208];
//���㺯��
void LCD_Draw_Point(u16 x ,u16 y ,u16 color);


void LCD_Init(void);
void LCD_Clear(u16 SX, u16 EX, u16 SY, u16 EY, u16 Color);
void LCD_ILI9486_Parameter(u16 data);
void LCD_ILI9486_CMD(u16 common);
void LCD_Port_Init(void);

void LCD_Draw(u16 x_start ,u16 y_start,u16 x_end ,u16 y_end ,u16 color);


//������ʾ��غ���
void LCD_Dis16hz(u16 x,u16 y,u16 color,u16 backcolor,u8 *buf);

void LCD_Disanyhz(u16 x,u16 y,u16 width,u16 high,u16 color,u16 backcolor,u8 *buf);
void LCD_Dis32hz(u16 x,u16 y,u16 color, const u8 *pic,u8 *buf);

//�ַ���ʾ��غ���
void LCD_Dis32ch(u16 x,u16 y,u16 color,const u8 *pic,u8 *buf);
void LCD_Diszf(u16 x,u16 y,u16 color,	u16 backcolor,u8 *buf);
void LCD_Dishz(u16 x,u16 y,u16 color,	u16 backcolor,u8 *buf);

//�ַ�����ʾ��غ���
void LCD_DisString(u16 x,u16 y ,u16 color,const u8 *pic, u8 *buf);

void LCD_ShowString(u16 x,u16 y ,u16 color, u16 back, u8 *buf);

//ͼƬ��ʾ��غ���
void LCD_Dispic(u16 x,u16 y,u16 width,u16 high ,const u8 *buf);
void LCD_Dispic1(struct PIC pic);
void LCD_Dispic2(u16 x,u16 y,const u8 *buf);
#endif
