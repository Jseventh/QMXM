#ifndef _LCD1602_H_
#define _LCD1602_H_
//#include "LPC11XX.h"
//��ʼ����
#define LCD_RS_LOW 		LPC_GPIO2->DATA &= ~(1<<0)	//����״̬����
#define LCD_RS_HIGH		LPC_GPIO2->DATA |=  (1<<0)	//
#define LCD_RW_LOW		LPC_GPIO2->DATA &= ~(1<<1)	//��дʹ������
#define LCD_RW_HIGH		LPC_GPIO2->DATA |=  (1<<1)	//
#define LCD_E_LOW		LPC_GPIO2->DATA &= ~(1<<2)	//ʹ�ܶ�
#define LCD_E_HIGH		LPC_GPIO2->DATA |=  (1<<2)	//

#define LCD_DATAPORT	LPC_GPIO2->DATA	            //DB0��DB7���ݶ˿�
#define LCD_DATA_IN		LPC_GPIO2->DIR &= ~0xFFF	//���ö˿�Ϊ����
#define LCD_DATA_OUT	LPC_GPIO2->DIR |=  0xFFF	//���ö˿�Ϊ���

static volatile unsigned int ticks = 0;

void Delayms(uint16_t ms);
void SysTick_Handler(void);
uint8_t Busy_Check();
void LCD_WriteCommand(uint32_t cmd);
void LCD_WriteData(uint32_t dat);
uint8_t LCD_DisplayChar(uint8_t x, uint8_t y, uint8_t ch);
uint8_t LCD_DisplayStr(uint8_t x, uint8_t y, uint8_t *pStr);
uint8_t LCD_DisplayIntValue(uint8_t x,uint8_t y,int temp);
void LCD_IOInit(void);
void InitLCD();
#endif
