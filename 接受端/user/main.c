#include "stm32f10x.h"                
#include "delay.h"
#include "serial.h"
#include "OLED.h"
#include "SX1278.h"
#include "My_spi.h"
#include "SX1278_Reg_Define_Table.h"
#include <string.h>
#include "Key.h"
#include "stdio.h"
void Menu();
void Parameter_Menu();
void Setting_Menu();
char FIFO_Buffer[256];
uint8_t temp;
	uint8_t humi;
uint8_t Cursor_position=1;
uint8_t Cursor_choice=1;
/*在FIFO中一共有三个指针，分别是发送缓冲区的基地址（0x0E），接受缓冲区的基地址（0x0F），
以及访问0x0D也就是FIFO时开始的地址*/
/*                            接收端                               */
/*                            接收端                               */
/*                            接收端                               */
/*                            接收端                               */
/*                            接收端                               */
/*                            接收端                               */
/*                            接收端                               */
/*                            接收端                               */
/*                            接收端                               */
char *menu[]={
									"Start",
									"Setting",
									"Test",
									"Mode",
									"Information",
									"Basic setting",
									"Test2",
									"Test3"
};

char *Setting[]={
									"Parameter",
									"back",
	

};
									
char *parameter[]={
									"BandWidth",
									"Header",
									"Power",
									"CR",
									"Back"

};

char *BW[]={
									"7.8KHZ",
									"10.4KHZ",
									"15.6KHZ",
									"20.8KHZ",
									"31.25KHZ",
									"41.7KHZ",
									"62.5KHZ",
									"125KHZ",
									"250KHZ",
									"500KHZ",
									"Back"

};
char *CR[]={
									"4/5",
									"4/6",
									"4/7",
									"4/8",
									"Back"
									

};
char *HEADER[]={
									"ON",
									"OFF",
									"Back"
									
									

};
char *POWER[]={
									"2dBm",
									"3dBm",
									"4dBm",
									"5dBm",
									"6dBm",
									"7dBm",
									"8dBm",
									"9dBm",
									"10dBm",
									"11dBm",
									"12dBm",
									"13dBm",
									"14dBm",
									"15dBm",
									"16dBm",
									"17dBm",
									"Back"
									
									

};



void Set_Cursor(uint8_t	i)
{
	OLED_ShowString(1,1," ");
	OLED_ShowString(2,1," ");
	OLED_ShowString(3,1," ");
	OLED_ShowString(4,1," ");
	OLED_ShowString(i,1,">");


}

void Welcome_menu()
{
	OLED_ShowString(1,1,"  Welcome to    ");
	OLED_ShowString(2,1,"     LoRa       ");
	OLED_ShowString(3,1,"    Press to    ");
	OLED_ShowString(4,1,"    continue    ");
}




uint8_t Show_Menu(char *Menu[],uint8_t rows)
{

uint8_t j=0;
	OLED_Clear();
	Cursor_position=1;
	Cursor_choice=1;
	while(1)
	{
		OLED_ShowNum(4,14,Cursor_choice,2);
		for(int i=0;i<4&& (i + j) < rows;i++)
	{
	OLED_ShowString(i+1,2,Menu[i+j]);
	}
	
	Set_Cursor(Cursor_position);
	if(Key_GetNum()==2)
		{
			
		Cursor_choice++;
		Cursor_position++;
			
			
			if(Cursor_position==rows+1)
			{
			Cursor_position=1;
			Cursor_choice=1;
			}	
			
		if(Cursor_position==5)
		{
			Cursor_position=4;
		j++;	
			if(j==(rows-3))
			{
			j=0;
			Cursor_position=1;
				Cursor_choice=1;
			}
			
			OLED_Clear();
		}
		
		
		
	}
		
	else 
	{
	
	OLED_Clear();
		OLED_ShowNum(1,1,Cursor_choice,3);
		return Cursor_choice;

	}


}
	


	}

	void HEADER_Menu()
	{
	switch (Show_Menu(HEADER,sizeof(HEADER) / sizeof(HEADER[0])))
	{
		case 1:
			SX1278_WriteReg(0x1D,((SX1278_SwapByte(0x1D)&0xFE)|0x00));
		break;
		case 2:
			SX1278_WriteReg(0x1D,((SX1278_SwapByte(0x1D)&0xFE)|0x01));
		break;
		
			
	}	
	Parameter_Menu();
	//Get_Basic_Setting();
	}
	
	void BW_Menu()

{
switch (Show_Menu(BW,sizeof(BW) / sizeof(BW[0])))
		{
			case 1:	
			SX1278_WriteReg(0x1D,((SX1278_SwapByte(0x1D)&0x0F)|0x00));
			break;
			case 2:	
			SX1278_WriteReg(0x1D,((SX1278_SwapByte(0x1D)&0x0F)|0x10));
			break;
			case 3:	
			SX1278_WriteReg(0x1D,((SX1278_SwapByte(0x1D)&0x0F)|0x20));
			break;                                          
			case 4:	                                        
			SX1278_WriteReg(0x1D,((SX1278_SwapByte(0x1D)&0x0F)|0x30));
			break;                                          
			case 5:	                                        
			SX1278_WriteReg(0x1D,((SX1278_SwapByte(0x1D)&0x0F)|0x40));
			break;                                          
			case 6:	                                        
			SX1278_WriteReg(0x1D,((SX1278_SwapByte(0x1D)&0x0F)|0x50));
			break;                                          
			case 7:	                                        
			SX1278_WriteReg(0x1D,((SX1278_SwapByte(0x1D)&0x0F)|0x60));
			break;                                          
			case 8:	                                        
			SX1278_WriteReg(0x1D,((SX1278_SwapByte(0x1D)&0x0F)|0x70));
			break;                                          
			case 9:	                                        
			SX1278_WriteReg(0x1D,((SX1278_SwapByte(0x1D)&0x0F)|0x80));
			break;                                         
			case 10:	                                      
			SX1278_WriteReg(0x1D,((SX1278_SwapByte(0x1D)&0x0F)|0x90));
			break;
			                                   
			
		
}	
		Parameter_Menu();

//Get_Basic_Setting();
	}

		void CR_Menu()

{
switch (Show_Menu(CR,sizeof(CR) / sizeof(CR[0])))
		{case 1:
			SX1278_WriteReg(0x1D,((SX1278_SwapByte(0x1D)&0xF1)|(0x01<<1)));
			break;
			case 2:
			SX1278_WriteReg(0x1D,((SX1278_SwapByte(0x1D)&0xF1)|(0x02<<1)));
			break;
			case 3:
			SX1278_WriteReg(0x1D,((SX1278_SwapByte(0x1D)&0xF1)|(0x03<<1)));
			break;
			case 4:
			SX1278_WriteReg(0x1D,((SX1278_SwapByte(0x1D)&0xF1)|(0x04<<1)));
			break;
			                                 
			
		

}
		Parameter_Menu();
		//Get_Basic_Setting();
	}

	
void	Power_Menu()
	
{
switch (Show_Menu(POWER,sizeof(POWER) / sizeof(POWER[0])))

{
			case 1:
	SX1278_WriteReg(0x09,((SX1278_SwapByte(0x09)&0xF0)|0x00));
			break;
			case 2:
	SX1278_WriteReg(0x09,((SX1278_SwapByte(0x09)&0xF0)|0x01));
			break;
			case 3:
	SX1278_WriteReg(0x09,((SX1278_SwapByte(0x09)&0xF0)|0x02));
			break;
			case 4:
	SX1278_WriteReg(0x09,((SX1278_SwapByte(0x09)&0xF0)|0x03));
			break;
			case 5:
	SX1278_WriteReg(0x09,((SX1278_SwapByte(0x09)&0xF0)|0x04));
			break;
			case 6:
	SX1278_WriteReg(0x09,((SX1278_SwapByte(0x09)&0xF0)|0x05));
			break;
			case 7:
	SX1278_WriteReg(0x09,((SX1278_SwapByte(0x09)&0xF0)|0x06));
			break;
			case 8:
	SX1278_WriteReg(0x09,((SX1278_SwapByte(0x09)&0xF0)|0x07));
			break;
			case 9:
	SX1278_WriteReg(0x09,((SX1278_SwapByte(0x09)&0xF0)|0x08));
			break;
			case 10:
	SX1278_WriteReg(0x09,((SX1278_SwapByte(0x09)&0xF0)|0x09));
			break;
			case 11:
	SX1278_WriteReg(0x09,((SX1278_SwapByte(0x09)&0xF0)|0x0A));
			break;
			case 12:
	SX1278_WriteReg(0x09,((SX1278_SwapByte(0x09)&0xF0)|0x0B));
			break;
			case 13:
	SX1278_WriteReg(0x09,((SX1278_SwapByte(0x09)&0xF0)|0x0C));
			break;
			case 14:
	SX1278_WriteReg(0x09,((SX1278_SwapByte(0x09)&0xF0)|0x0D));
			break;
			case 15:
	SX1278_WriteReg(0x09,((SX1278_SwapByte(0x09)&0xF0)|0x0E));
			break;
			case 16:
	SX1278_WriteReg(0x09,((SX1278_SwapByte(0x09)&0xF0)|0x0F));
			break;


}
	Parameter_Menu();
}
	
void	INFORMATION_Menu()
{
OLED_ShowString(1,1,"Version:1.0");
	while(Key_GetNum()==0);


}
	
void Parameter_Menu()
{

switch (Show_Menu(parameter,sizeof(parameter) / sizeof(parameter[0])))
		{
		case 1:
			BW_Menu();
			break;
		case 2:
			HEADER_Menu();
			break;
		case 3:
			Power_Menu();
			break;
		case 4:
			CR_Menu();
			break;
		
		
		
			
}
			Setting_Menu();

}
void Setting_Menu()
{
switch (Show_Menu(Setting,sizeof(Setting) / sizeof(Setting[0])))
		{
		case 1:
			Parameter_Menu();
			break;	
}
Menu();
	}



void Test()
{

if(SX1278_ReadReg(0x42)!=0x12)
		OLED_ShowString(1,1,"Error");
		Get_Basic_Setting();
OLED_Clear();
while(1)
{
	
	Recieve_Data();
  SX1278_WriteReg(FIFO_Pointer,Recieve_Buffer_Start);
	for (int i=1;i<5;i++)
	{
		for(int j=0;j<5;j++)
			{
			OLED_ShowHexNum(i,1+j*3,SX1278_ReadReg(0x00),2);
		
			}
	}

		//if(Key_GetNum()!=0)
	//break;
}
	
	OLED_Clear();
	
		
	SX1278_WriteReg(FIFO_Pointer,0x00);
	
	for(int i=0;i<256;i++)
	{
	FIFO_Buffer[i]=SX1278_ReadReg(0x00);
	}
Menu();
}


void Menu()	
{
	switch (Show_Menu(menu,sizeof(menu) / sizeof(menu[0])))
		{case 1:
			//Start();
			break;
		case 2:Setting_Menu();
			break;
		case 3:
			Test();
		break;
		case 5:
			INFORMATION_Menu();
		Menu();
			break;
		case 6:
			Get_Basic_Setting();
	Menu();
		break;
}

}

uint8_t Get_Tem_Hum()
{
DHT11_Read_Data(&temp,&humi);
Delay_ms(2000);
DHT11_Read_Data(&temp,&humi);
return 1;
}

int main(void)

{
	
	OLED_Init();
	Key_Init();
	DHT11_Init();
	MYUSART_Init();
	SX1278_Init();
	SX1278_Basic_Setting(128);
	
	
	Welcome_menu();
	while(Key_GetNum()==0);
	OLED_Clear();
	Menu();
	
  
	
	

	

	
}

