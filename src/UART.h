#ifndef _UART_H_
#define _UART_H_
#define UART_BPS 115200
void UART_Init(void);
void UART_SendByte(uint8_t ucDat);
void UART_SendStr(char *pucStr);
#endif
