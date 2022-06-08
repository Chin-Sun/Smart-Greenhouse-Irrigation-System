#include "uart.h"
#include "string.h"
#include "modbus.h"


bit rx_end = 0;

unsigned char rx_sta = 0;
unsigned char rx_len = 0;
unsigned char rx_buf[20] = 0;


void SendOneByte(unsigned char c)
{
    SBUF = c;
    while(!TI);
    TI = 0;
}

void SendString(char *s)
{
    while (*s)                  //检测字符串结束标志
    {
        SendOneByte(*s++);         //发送当前字符
    }
}

void InitUART(void)   //12M,4800bps
{
    TMOD = TMOD | 0x20;
    SCON = 0x50;
    TH1 = 0xF3;
    TL1 = TH1;
    PCON = 0x80;
    EA = 1;
    ES = 1;
    TR1 = 1;
		IP= IP | 0x10;
	
		modbus_init(1);
}

void UART_IDLE(void)
{
	if(rx_sta != 0)
	{
			rx_sta++;
		if(rx_sta >= 3)
		{
			rx_sta = 0;
			rx_end = 1;
		}
	}
	UART_handle();
}
void UART_handle(void)
{
	if(rx_end == 1)
	{
//		SendString(rx_buf);
		modbus_handle(rx_buf,rx_len);
		memset(rx_buf,0,rx_len);
		rx_len = 0;
		rx_end = 0;
	}
}

void UARTInterrupt(void) interrupt 4
{
    if(RI)
    {
      RI = 0;
			if(rx_end == 0)
			{
				rx_sta = 1;
				rx_buf[rx_len] = SBUF;
				rx_len++;
			}
    }
    else
        TI = 0;
}

