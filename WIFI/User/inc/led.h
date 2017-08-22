#ifndef  LED_H
#define  LED_H
//PF6
#define LED1_ON   GPIOF->ODR &=~(0x1<<6)
#define LED1_OFF  GPIOF->ODR |=(0x1<<6)
//PF9
#define LED2_ON   GPIOF->ODR &=~(0x1<<9)
#define LED2_OFF  GPIOF->ODR |=(0x1<<9)
//PF10
#define LED3_ON   GPIOF->ODR &=~(0x1<<10)
#define LED3_OFF  GPIOF->ODR |=(0x1<<10)
//PC0
#define LED4_ON   GPIOC->ODR &=~(0x1<<0)
#define LED4_OFF  GPIOC->ODR |=(0x1<<0)

void LED_Init(void);  
/**LED��ʼ��**/

void LED_ALLON(void); 
/**LEDȫ��**/

void LED_ALLOFF(void); 
/**LEDȫ��**/

void LED_Twinkle(void); 
/**��˸**/

void LED_Water(void); 
/**��ˮ��**/

void LED_HX(void);
#endif

