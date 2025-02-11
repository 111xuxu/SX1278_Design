#include "stm32f10x.h"                  // Device header
#include "My_spi.h"  
#include "SX1278_Reg_Define_Table.h"
#include "delay.h"
#include <string.h>
#include "OLED.h"
#include "Key.h"
	
		
	


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
SX1278_WriteReg(FIFO_Pointer,Send_Buffer_Start);
SX1278_WriteReg(Mode,SendMode);
 while ((SX1278_ReadReg(0x12) & 0x08) == 0); 
	SX1278_WriteReg(0x12, 0x08);
return 1;
	
	
}




int Recieve_Data()
{
	int times;
	loop:
	
	SX1278_WriteReg(0x12, 0xFF);
SX1278_WriteReg(Mode,StandByMode);
	SX1278_WriteReg(Recieve_BasePointer,Recieve_Buffer_Start);
	SX1278_WriteReg(FIFO_Pointer,Recieve_Buffer_Start);
	
	SX1278_WriteReg(Mode,Continue_Recieve);
	
	while ((SX1278_ReadReg(0x12) & 0x40) == 0);
	
	SX1278_WriteReg(0x12, 0xFF);
	/*SX1278_WriteReg(FIFO_Pointer,Recieve_Buffer_Start);
	OLED_ShowHexNum(3,1,SX1278_ReadReg(0x00),2);
	OLED_ShowHexNum(3,4,SX1278_ReadReg(0x00),2);
	OLED_ShowHexNum(3,7,SX1278_ReadReg(0x00),2);*/
   SX1278_WriteReg(FIFO_Pointer,Recieve_Buffer_Start);
	if(SX1278_ReadReg(0x00)!=0x12|SX1278_ReadReg(0x00)!=0x34|SX1278_ReadReg(0x00)!=0x56)
	{
		SX1278_WriteReg(FIFO_Pointer,Recieve_Buffer_Start);
		times++;
		if(times==10)
		{OLED_Clear();
		OLED_ShowString(1,1,"pack error");
			OLED_ShowString(2,1,"please check");
			return 0;
		}
			goto loop;
	}
	
	
	return 1;
	//OLED_ShowString(4,1,"recieved");
return 1;

}

void SX1278_Basic_Setting(uint8_t len)
{
	SX1278_WriteReg(Mode,SleepMode);
	SX1278_WriteReg(Send_BasePointer,Send_Buffer_Start);//FIFO中发送区的指针基地址，从该指针向后进行写入
	SX1278_WriteReg(Recieve_BasePointer,Recieve_Buffer_Start);//FIFO中接收区基地址指向0x00
	SX1278_WriteReg(FIFO_Pointer,Send_Buffer_Start);//数据缓冲区FIFO中的指针地址
	SX1278_WriteReg(0x1D,0x66);//带宽，纠错编码率，报头选择
	SX1278_WriteReg(0x1E, 0xB4);
	SX1278_WriteReg(0x22,len);//有效负载长度
	SX1278_WriteReg(0x09,0xF8);//Transmit Power
}


void Get_Basic_Setting(void)
{
	char BW[]="";
	char cr[]="";
	char Head[]="";
	char Power[]="";
	char temp;
	char power=SX1278_ReadReg(0x09);
	if(SX1278_ReadReg(0x42)!=0x12)
	{
	
	OLED_Clear();
		OLED_ShowString(1,1,"Check Connection");
			OLED_ShowString(2,1,"SX1278");
	
	}
	else
	{
	temp=SX1278_ReadReg(0x1D);
	OLED_ShowBinNum(4,1,temp,8);
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
			strcpy(cr,"4/5");
			break;
		case 2:
			strcpy(cr,"4/6");
			break;
		case 3:
			strcpy(cr,"4/7");
			break;
		case 4:
			strcpy(cr,"4/8");
			break;
	}
OLED_ShowString(1,9,"CR:");
OLED_ShowString(1,12,cr);
	
	if(temp&1==1)
	strcpy(Head,"OFF");
	else
		strcpy(Head,"ON");
	OLED_ShowString(2,1,"Head:");
	OLED_ShowString(2,6,Head);
	switch(power&0x0F)
		{
			case 0:strcpy(Power,"2dBm");break;
			case 1:strcpy(Power,"3dBm");break;
			case 2:strcpy(Power,"4dBm");break;
			case 3:strcpy(Power,"5dBm");break;
			case 4:strcpy(Power,"6dBm");break;
			case 5:strcpy(Power,"7dBm");break;
			case 6:strcpy(Power,"8dBm");break;
			case 7:strcpy(Power,"9dBm");break;
			case 8:strcpy(Power,"10dBm");break;
			case 9:strcpy(Power,"11dBm");break;
			case 10:strcpy(Power,"12dBm");break;
			case 11:strcpy(Power,"13dBm");break;
			case 12:strcpy(Power,"14dBm");break;
			case 13:strcpy(Power,"15dBm");break;
			case 14:strcpy(Power,"16dBm");break;
			case 15:strcpy(Power,"17dBm");break;
	}
		OLED_ShowString(3,1,"Power:");
	OLED_ShowString(3,7,Power);
	
}
	
	while(Key_GetNum()==0);
}
	