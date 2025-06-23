#include "stm32f10x.h"                  // Device header
#include "My_spi.h"  
#include "SX1278_Reg_Define_Table.h"
#include "delay.h"
#include <string.h>
#include "OLED.h"
#include "Key.h"
#include "SX1278.h"
char FIFO_Buffer[256];

char Buffer[128]={
0x12, 0x34, 0x56, 0x12, 0x35,0x56,0x78,0x12,0x34,0x56,0x78,0xff,0xff, 0xff,0xff,0xff,  
0xff, 0xff, 0xff, 0xff, 0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff, 0xff,0xff,0xff,  
0xff, 0xff, 0xff, 0xff, 0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff, 0xff,0xff,0xff,  
0xff, 0xff, 0xff, 0xff, 0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff, 0xff,0xff,0xff,
0xff, 0xff, 0xff, 0xff, 0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff, 0xff,0xff,0xff,  
0xff, 0xff, 0xff, 0xff, 0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff, 0xff,0xff,0xff,  
0xff, 0xff, 0xff, 0xff, 0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff, 0xff,0xff,0xff,  
0xff, 0xff, 0xff, 0xff, 0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff, 0xff,0xff,0xff
};       


void SX1278_Init(void)
{
		//MySPI_Init();
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
	MySPI_LORA_Start();
	MySPI_SwapByte(sendbyte);
	temp=MySPI_SwapByte(0x00);
	MySPI_LORA_Stop();
return temp;
}


uint8_t SX1278_ReadReg(uint8_t addr)
{


uint8_t temp;
	MySPI_LORA_Start();
	MySPI_SwapByte(addr&0x7f);
	temp=MySPI_SwapByte(0x00);
	MySPI_LORA_Stop();
return temp;
	


}


void SX1278_WriteReg(uint8_t addr,uint8_t data)
	
{
	MySPI_LORA_Start();
	MySPI_SwapByte(addr|0x80);
	MySPI_SwapByte(data);
	MySPI_LORA_Stop();
	MySPI_SwapByte(0xFF); 
	//MySPI_SwapByte(0xFF); 
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



int Send_Data(int len)
{

SX1278_WriteReg(Mode,StandByMode);
SX1278_WriteReg(FIFO_Pointer,Send_Buffer_Start);
SX1278_WriteReg(Mode,SendMode);
 while ((SX1278_ReadReg(0x12) & 0x08) == 0); 
	SX1278_WriteReg(0x12, 0x08);
return 1;
	
	
}




int Recieve_Data(int receive_mode)
{
	//int times;
	//loop:
	
	SX1278_WriteReg(0x12, 0xFF);
  SX1278_WriteReg(Mode,StandByMode);
	SX1278_WriteReg(Recieve_BasePointer,Recieve_Buffer_Start);
	SX1278_WriteReg(FIFO_Pointer,Recieve_Buffer_Start);
	
	SX1278_WriteReg(Mode,Continue_Recieve);
	
	 int timeout = 8000;  // 自定义循环次数（根据系统主频估算时间，100000约等于数百毫秒~1秒）timeout/1000 s
    if (receive_mode)  // 有超时限制
{
    while ((SX1278_ReadReg(0x12) & 0x40) == 0)
    {
        if (--timeout == 0)
        {
            SX1278_WriteReg(Mode, StandByMode);
					MySPI_LORA_Stop();
					
            return 0;  // 超时退出
        }
        Delay_ms(1);
    }
}
else  // 永久监听
{
    while ((SX1278_ReadReg(0x12) & 0x40) == 0)
    {
        Delay_ms(1);
    }
}
	
	
	SX1278_WriteReg(0x12, 0xFF);
   SX1278_WriteReg(FIFO_Pointer,Recieve_Buffer_Start);
	if(SX1278_ReadReg(0x00)!=0x12|SX1278_ReadReg(0x00)!=0x34|SX1278_ReadReg(0x00)!=0x56)
	{
		SX1278_WriteReg(FIFO_Pointer,Recieve_Buffer_Start);
		return 0;
		
	}
	
	SX1278_WriteReg(FIFO_Pointer,Recieve_Buffer_Start);
MySPI_LORA_Stop();
return 1;

}
/*
void SX1278_Basic_Setting(uint8_t len)
{
	SX1278_WriteReg(Mode,SleepMode);
	SX1278_WriteReg(Sync_Word_Reg,Syne_Word);
	SX1278_WriteReg(Send_BasePointer,Send_Buffer_Start);//FIFO中发送区的指针基地址，从该指针向后进行写入
	SX1278_WriteReg(Recieve_BasePointer,Recieve_Buffer_Start);//FIFO中接收区基地址指向0x00
	SX1278_WriteReg(FIFO_Pointer,Send_Buffer_Start);//数据缓冲区FIFO中的指针地址
	SX1278_WriteReg(0x1D,0x66);//带宽，纠错编码率，报头选择
	SX1278_WriteReg(0x1E, 0xB4);
	SX1278_WriteReg(0x22,len);//有效负载长度
	SX1278_WriteReg(0x09,0xF8);//Transmit Power
	MySPI_LORA_Stop();
    MySPI_SwapByte(0xFF); 
	MySPI_SwapByte(0xFF); 
	MySPI_SwapByte(0xFF); 
	MySPI_SwapByte(0xFF); 
}

*/


/*void SX1278_Basic_Setting(uint8_t len)
{
    const uint8_t cfg[][2] = {
        {Mode,                SleepMode},
        {Sync_Word_Reg,       Syne_Word},
        {Send_BasePointer,    Send_Buffer_Start},
        {Recieve_BasePointer, Recieve_Buffer_Start},
        {FIFO_Pointer,        Send_Buffer_Start},
        {0x1D,                0x66},
        {0x1E,                0xB4},
        {0x22,                len},
        {0x09,                0xF8},
    };

    MySPI_LORA_Start();                         // NSS_LORA = 0

    for (uint8_t i = 0; i < sizeof(cfg)/2; i++) {
        MySPI_SwapByte(cfg[i][0] | 0x80);       // 写指令
        MySPI_SwapByte(cfg[i][1]);
    }
		Delay_ms(500);

    MySPI_LORA_Stop();                          // NSS_LORA = 1
    MySPI_SwapByte(0xFF);                       // ★仅 1 字节尾钟足矣
		SPI_FlushBus(16);
}
*/

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
		OLED_ShowHexNum(4,10,SX1278_ReadReg(0x39),4);
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



	void Receive_Test()
{
long recieved_times=0;
if(SX1278_ReadReg(0x42)!=0x12)
		OLED_ShowString(1,1,"Error");
		Get_Basic_Setting();
OLED_Clear();
while(1)
{
	
if(	Recieve_Data(0) )
	{
  SX1278_WriteReg(FIFO_Pointer,Recieve_Buffer_Start);
	for (int i=1;i<5;i++)
	{
		for(int j=0;j<5;j++)
			{
			OLED_ShowHexNum(i,1+j*3,SX1278_ReadReg(0x00),2);
		
			}
	}
	
OLED_ShowNum(1,1,recieved_times,3);
	recieved_times++;
}
	else 
	{
			OLED_Clear();	
			OLED_ShowString(1,1,"pack error");
			OLED_ShowString(2,1,"please check");
	Delay_s(2);

	}
		/*if(Key_GetNum()!=0)
	break;*/
}
	
	OLED_Clear();
	
		
	SX1278_WriteReg(FIFO_Pointer,0x00);
	
	for(int i=0;i<256;i++)
	{
	FIFO_Buffer[i]=SX1278_ReadReg(0x00);
	}
Menu();
}

void Sending_test()
{

unsigned int j;

SX1278_WriteReg(FIFO_Pointer,Send_Buffer_Start);
		while(1){
			SX1278_WriteReg(FIFO_Pointer,Send_Buffer_Start);
			for (int i=0;i<128;i++)
		{
		SX1278_WriteReg(0x00,Buffer[i]);
		}
		
		OLED_ShowString(1,1,"                ");
	OLED_ShowString(1,1,"Sending Data");
			
	OLED_ShowNum(3,13,j,3);
		j++;	
	SX1278_WriteReg(FIFO_Pointer,Send_Buffer_Start);
	OLED_ShowHexNum(3,1,SX1278_ReadReg(0x00),2);
	OLED_ShowHexNum(3,4,SX1278_ReadReg(0x00),2);
	OLED_ShowHexNum(3,7,SX1278_ReadReg(0x00),2);
	OLED_ShowHexNum(3,10,SX1278_ReadReg(0x00),2);
				if(Send_Data(128)==1)
		OLED_ShowString(4,1,"Send Success");
			
	Buffer[3]++;
}

}




void Edge_Device_Send_Data()
{


SX1278_WriteReg(FIFO_Pointer,Send_Buffer_Start);
	for (int i=0;i<128;i++)
		{
		SX1278_WriteReg(0x00,Buffer[i]);
		}
		
			SX1278_WriteReg(FIFO_Pointer,Send_Buffer_Start);
		
		OLED_ShowString(1,1,"                ");
	OLED_ShowString(1,1,"Sending Data");	
	SX1278_WriteReg(FIFO_Pointer,Send_Buffer_Start);
	
				Send_Data(128);
		OLED_ShowString(3,1,"Send Success");

}




void Central_Device_Send_Data()
{


SX1278_WriteReg(FIFO_Pointer,Send_Buffer_Start);
	for (int i=0;i<30;i++)
		{
		SX1278_WriteReg(0x00,Buffer[i]);
		}
		
			//SX1278_WriteReg(FIFO_Pointer,Send_Buffer_Start);
		
		OLED_ShowString(1,1,"                ");
	OLED_ShowString(1,1,"Sending Data");	
	SX1278_WriteReg(FIFO_Pointer,Send_Buffer_Start);
	
				Send_Data(128);
		OLED_ShowString(3,1,"Send Success");

}



void Send_Sensor_Data()
	{


	
	
	
	

	}



