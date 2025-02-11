#include "stm32f10x.h"                  // Device header
void SX1278_Init(void);
uint8_t SX1278_SwapByte(uint8_t sendbyte);
void SX1278_WriteReg(uint8_t addr,uint8_t data);
void SX1278_Read_Tx_Buffer(uint8_t len);//读取发送数据缓冲区，LORA上
void SX1278_Write_Tx_Buffer(uint8_t len);//写入LoRa上的数据发送缓冲区
int Send_Data(int len);
void SX1278_Basic_Setting();
void Get_Basic_Setting(void);