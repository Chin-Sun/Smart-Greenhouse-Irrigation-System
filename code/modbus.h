#include<reg51.h>	//加载头文件

#define ADDR_ERR 1
#define CRC_ERR 2

extern unsigned char s1,s2,w1,w2;

typedef unsigned char uint8_t;
typedef unsigned int uint16_t;

extern uint8_t addr;

void modbus_init(uint8_t addr);
void modbus_handle(uint8_t* rx,uint8_t len);

uint16_t crc16bitbybit(uint8_t *ptr, uint16_t len);
uint16_t crc16table(uint8_t *ptr, uint16_t len);
uint16_t crc16tablefast(uint8_t *ptr, uint16_t len);

void modbus_send(uint8_t* rxbuf,uint8_t len);



