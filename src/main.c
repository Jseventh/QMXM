#include "LPC11xx.h"                    // Device header
#include "config.h"
#define UART_BPS 115200
char GcRcvBuf[20];
char GcRcvBuf_LCD[20];
uint16_t table[9]={0xff,0x7f,0x3f,0x1f,0x0f,0x07,0x03,0x01,0x00};

void Delay(uint32_t ulTime)
{
	uint32_t i;
	i=0;
	while(ulTime--)
	{
		for(i=0;i<5000;i++);
	}
}
void delay_mine(void)
{
	uint16_t i=4000;
	while(i--);
}
void LEDInit(void)
{
	LPC_GPIO2->DIR = 0xFF;
}
void LED_ON(ucBuf)
{
		LPC_GPIO2->DATA &=~(0xff);
		LPC_GPIO2->DATA |= table[ucBuf/410];
		delay_mine();
}
/*
*********************************************************************************************************
*   ? ? ?: CaculTwoPoint
*   ????: ??2?????,??Y?
*   ?    ?:  2??????x???
*   ? ? ?: x???y?
*********************************************************************************************************
*/
int32_t  CaculTwoPoint(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x)
{
    return y1 + ((int64_t)(y2 - y1) * (x - x1)) / (x2 - x1);
}
int main(void)
{
	uint32_t i;
	uint32_t ulADCData;
	uint32_t ulADCBuf;
	uint32_t voltage,temp_r,current;//定义电压，热敏电阻的阻滞，电流;
	int times;
	UART_Init();
	ADC_Init();
	LEDInit();
	LCD_IOInit();
	InitLCD();
	while(1)
	{
		ulADCData=0;
		for(i=0;i<10;i++)
		{
			LPC_ADC->CR|=(1<<24);
			while((LPC_ADC->DR[7]&0x80000000)==0);
			LPC_ADC->CR|=(1<<24);
			while((LPC_ADC->DR[7]&0x80000000)==0);
			ulADCBuf=LPC_ADC->DR[7];
			ulADCBuf=(ulADCBuf>>6)&0x3ff;
			ulADCData+=ulADCBuf;
		}
		ulADCData=ulADCData/10;
		ulADCData=(ulADCData*3300)/1024;
		voltage=3300-ulADCData;
		current=voltage/10000;
		temp_r=ulADCData/current;
		sprintf(GcRcvBuf_LCD,"%4d",temp_r);
		LCD_DisplayStr(1,1,GcRcvBuf_LCD);
		sprintf(GcRcvBuf,"VINO=%4d mv\r\n",ulADCData);
		UART_SendStr(GcRcvBuf);
		LED_ON(ulADCData);
		Delay(200);
	}
}