#include "stm32f10x.h"                  // Device header
void SX1278_Init(void);
uint8_t SX1278_SwapByte(uint8_t sendbyte);
void SX1278_WriteReg(uint8_t addr,uint8_t data);
void SX1278_Read_Tx_Buffer(uint8_t len);//��ȡ�������ݻ�������LORA��
void SX1278_Write_Tx_Buffer(uint8_t len);//д��LoRa�ϵ����ݷ��ͻ�����
int Send_Data(int len);
void SX1278_Basic_Setting();
void Get_Basic_Setting(void);