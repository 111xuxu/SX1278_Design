#include "stm32f10x.h"                  // Device header
#include "My_spi.h"  
#include "SX1278_Reg_Define_Table.h"
#include "serial.h"
#include "OLED.h"
#include <string.h>
/*extern char Write_Buffer[256];
extern char Read_Buffer[256];*/
void SX1278_Init(void)
{
		MySPI_Init();
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
		GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;

		GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_ResetBits(GPIOA,GPIO_Pin_8);
	Delay_ms(10);
		GPIO_SetBits(GPIOA,GPIO_Pin_8);
	Delay_ms(10);
	
	
	
}


uint8_t SX1278_SwapByte(uint8_t sendbyte)
{
	uint8_t temp;
	MySPI_Start();
	MySPI_SwapByte(sendbyte);
	temp=MySPI_SwapByte(0x00);
	MySPI_Stop();
return temp;
}


uint8_t SX1278_ReadReg(uint8_t addr)
{


uint8_t temp;
	MySPI_Start();
	MySPI_SwapByte(addr&0x7f);
	temp=MySPI_SwapByte(0x00);
	MySPI_Stop();
return temp;
	


}


void SX1278_WriteReg(uint8_t addr,uint8_t data)
	
{
MySPI_Start();
	MySPI_SwapByte(addr|0x80);
	MySPI_SwapByte(data);
MySPI_Stop();
}



/*void SX1278_Write_Tx_Buffer(uint8_t len)
	
{
	
SX1278_WriteReg(0x0D,0x80);

for(uint8_t i=0;i<len;i++)
	{
		SX1278_WriteReg(0x00,Write_Buffer[i]);
	}
}

void SX1278_Read_Tx_Buffer(uint8_t len)
{

SX1278_WriteReg(0x0D,0x80);
for(uint8_t i=0;i<len;i++)
	{
		Read_Buffer[i]=SX1278_ReadReg(0x00);
	}
	
	


}

*/



int Send_Data(len)
{

SX1278_WriteReg(Mode,StandByMode);
	SX1278_WriteReg(0x22,len);//有效负载长度（信息长度）
SX1278_WriteReg(FIFO_Pointer,Send_Buffer_Start);
SX1278_WriteReg(Mode,SendMode);

 while ((SX1278_ReadReg(0x12) & 0x08) == 0);
	 SX1278_WriteReg(0x12, 0x08);

	
return 1;
	
	
}



void SX1278_Basic_Setting(void)
{
	SX1278_WriteReg(Mode,SleepMode);
	SX1278_WriteReg(Send_BasePointer,Send_Buffer_Start);//FIFO中发送区的指针基地址，从该指针向后进行写入
	SX1278_WriteReg(Recieve_BasePointer,Recieve_Buffer_Start);//FIFO中接收区基地址指向0x00
	SX1278_WriteReg(FIFO_Pointer,Send_Buffer_Start);//数据缓冲区FIFO中的指针地址
	SX1278_WriteReg(0x1D,0x66);//带宽，纠错编码率，报头选择
	SX1278_WriteReg(0x1E,0xB4);
	SX1278_WriteReg(0x22,0x80);
	SX1278_WriteReg(0x09,0xFF);//Transmit Power
}


void Get_Basic_Setting(void)
{
	char BW[]="0.0";
	char CR[]="0/0";
	char Head[]="ON";
	char temp;
	
	temp=SX1278_ReadReg(0x1D);
	switch(temp>>4){
		case 0:
			strcpy(BW,"7.8");
					break;
		case 1:
			strcpy(BW,"10.4");
					break;
		case 2:
			strcpy(BW,"15.6");
					break;
		case 3:
			strcpy(BW,"20.8");
					break;
		case 4:
			strcpy(BW,"31.25");
					break;
		case 5:
			strcpy(BW,"41.7");
					break;
		case 6:
			strcpy(BW,"62.5");
					break;
		case 7:
			strcpy(BW,"125");
					break;
		case 8:
			strcpy(BW,"250");
					break;
		case 9:
			strcpy(BW,"500");
					break;
	}
	OLED_ShowString(1,1,"BW:");
	
OLED_ShowString(1,4,BW);
	switch((temp>>1)&0x07){
		case 1:
			strcpy(CR,"4/5");
			break;
		case 2:
			strcpy(CR,"4/6");
			break;
		case 3:
			strcpy(CR,"4/7");
			break;
		case 4:
			strcpy(CR,"4/8");
			break;
	}
OLED_ShowString(1,9,"CR:");
OLED_ShowString(1,12,CR);
	
	if(temp&1==1)
	strcpy(Head,"OFF");
	else
		strcpy(Head,"ON");
	OLED_ShowString(2,1,"Head:");
	OLED_ShowString(2,6,Head);
}
	