#include<reg51.h>	//加载头文件


extern bit rx_end;
extern unsigned char rx_sta;
extern unsigned char rx_len;
extern unsigned char rx_buf[20];


void InitUART(void);
void SendOneByte(unsigned char c);
void SendString(char *s);
void UART_IDLE(void);
void UART_handle(void);




