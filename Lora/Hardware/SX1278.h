#ifndef __SX1278_h
#define __SX1278_h

void SX1278_Init(void);
uint8_t SX1278_SwapByte(uint8_t sendbyte);
void SX1278_WriteReg(uint8_t addr,uint8_t data);
void SX1278_Read_Tx_Buffer(uint8_t len);//读取发送数据缓冲区，LORA上
void SX1278_Write_Tx_Buffer(uint8_t len);//写入LoRa上的数据发送缓冲区
int Send_Data(int len);
int Recieve_Data(void);
void Get_Basic_Setting(void);
void SX1278_Basic_Setting(uint8_t len);

#endif
