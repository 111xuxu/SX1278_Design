#include "stm32f10x.h"                  // Device header
#include "delay.h"
#include "serial.h"
#include "OLED.h"
#include "SX1278.h"
#include "My_spi.h"
#include "SX1278_Reg_Define_Table.h"
//test123
char Buffer[128]={
0x12, 0x34, 0x56, 0x00, 0x5f, 0x11, 0xed, 0x4b, 0xd2, 0xee, 0x95, 0xe2, 0x24, 0x35, 0x74, 0x79,  
0xe4, 0x82, 0xc1, 0x48, 0x9c, 0x6c, 0x08, 0x2f, 0x3c, 0xa5, 0xfb, 0x73, 0xdf, 0x2e, 0x31, 0xf8,  
0x08, 0xd6, 0x07, 0x9f, 0x5a, 0xd4, 0x5e, 0x4e, 0x72, 0x01, 0x7a, 0x69, 0xd3, 0x12, 0x09, 0xe5,  
0x62, 0x36, 0x39, 0xdb, 0xc2, 0x68, 0x82, 0x27, 0x48, 0x4a, 0x18, 0x6b, 0xb8, 0x31, 0x06, 0xaf,
0x12, 0x34, 0x56, 0x4f, 0x5f, 0x11, 0xed, 0x4b, 0xd2, 0xee, 0x95, 0xe2, 0x24, 0x35, 0x74, 0x79,  
0xe4, 0x82, 0xc1, 0x48, 0x9c, 0x6c, 0x08, 0x2f, 0x3c, 0xa5, 0xfb, 0x73, 0xdf, 0x2e, 0x31, 0xf8,  
0x08, 0xd6, 0x07, 0x9f, 0x5a, 0xd4, 0x5e, 0x4e, 0x72, 0x01, 0x7a, 0x69, 0xd3, 0x12, 0x09, 0xe5,  
0x62, 0x36, 0x39, 0xdb, 0xc2, 0x68, 0x82, 0x27, 0x48, 0x4a, 0x18, 0x6b, 0xb8, 0x31, 0x06, 0xaf  
};

char Recieve_String[500];
 char Check_CIPMODE[]={"AT+CIPMODE?\r\n"};
 char Check_AT[]={"AT\r\n"};
 char Change_CIPMODE[]={"AT+CIPMODE=1\r\n"};
 char Connect_To_Server[]={"AT+CIPSTART=\42TCP\42,\428.208.52.104\42,5000\r\n"};
char CIP_Send[]={"AT+CIPSEND\r\n"};
char Data_Container[] =
"POST /postdata HTTP/1.1\r\n"
"Host: 8.208.52.104\r\n"
"Content-Type: application/json\r\n"
"Content-Length: 146\r\n"
"Connection: close\r\n"
"\r\n"
"{\"CO2_concentration\": 450,\"ID\": 4,\"Light_time\": 1,"
"\"Sequence\": 1,\"Soil_humidity\": 51,\"Soil_temperature\": 25,"
"\"Air_humidity\":30,\"Air_temperature\":24}";


uint32_t pRxstate=0;
uint16_t p;
int state;

void Temp()

{
	for(int i=0;i<15;i++)
	{
OLED_ShowChar(1, i+1, Recieve_String[i]);
	}
	for(int i=0;i<15;i++)
	{
OLED_ShowChar(2, i+1, Recieve_String[i+15]);
	}
	for(int i=0;i<15;i++)
	{
OLED_ShowChar(3, i+1, Recieve_String[i+30]);
	}
	for(int i=0;i<15;i++)
	{
OLED_ShowChar(4, i+1, Recieve_String[i+45]);
	}


}

/*在FIFO中一共有三个指针，分别是发送缓冲区的基地址（0x0E），接受缓冲区的基地址（0x0F），
以及访问0x0D也就是FIFO时开始的地址*/
/*                            发送端                               */
/*                            发送端                               */
/*                            发送端                               */
/*                            发送端                               */
/*                            发送端                               */
/*                            发送端                               */
/*                            发送端                               */
/*                            发送端                               */
/*                            发送端                               */
/*                            发送端                               */
int main(void)

{
	unsigned int j=0;
	OLED_Init();
	MYUSART_Init();
	MYDMA_Init();
/*	SX1278_Init();*/
/*	SX1278_Basic_Setting();*/
	/*Get_Basic_Setting();*/

	
	USART_SendString(Check_AT);
Delay_s(1);
	Temp();
	
	USART_SendString(Check_CIPMODE);
Delay_s(1);
	Temp();
	USART_SendString(Change_CIPMODE);
Delay_s(1);
	Temp();
	USART_SendString(Connect_To_Server);
Delay_s(1);
	Temp();
	USART_SendString(CIP_Send);
Delay_s(1);
	Temp();
	USART_SendString(Data_Container);
Delay_s(1);
	Temp();
	
	
	SX1278_WriteReg(FIFO_Pointer,Send_Buffer_Start);
		while(1){
			SX1278_WriteReg(FIFO_Pointer,Send_Buffer_Start);
			for (int i=0;i<128;i++)
		{
		SX1278_WriteReg(0x00,Buffer[i]);
		}
		
		OLED_ShowString(4,1,"                ");
	OLED_ShowString(4,1,"Sending Data");
			
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

