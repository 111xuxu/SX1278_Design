#include "stm32f10x.h"                
#include "Menu.h"
#include "SX1278_Reg_Define_Table.h"
#include <MyRTC.h>
#include <time.h>
#include "SD_Card.h"
#include "ff.h"
#include "diskio.h"
#include "String.h"
#include "WIFI.h"
#include "math.h"
extern uint16_t MyRTC_Time[];
extern char Buffer[128];
uint8_t Cursor_position=1;
uint8_t Cursor_choice=1;
static int dry_value=2000;

//test
static int wet_value=700;
extern uint16_t CO2[6];
int Time_Status=0;
extern int16_t temperature;
extern int16_t humi;
void Setting_Menu(void);
void Menu(void)	;
int Server_Status=0;
void Parameter_Menu(void);
void Menu();

static uint8_t Device_ID;

void Sensor_Test(void)
{
while(1)
	{
	OLED_ShowNum(1,5,1111,4);
	OLED_ShowNum(2,5,AD_GetValue(ADC_Channel_0),4);
	OLED_ShowNum(1,1,Get_Light(),2);

	Show_DS18B20_Tempreature(3,8);
	Get_Tem_Hum();
	OLED_ShowNum(3,1,temperature,2);
	OLED_ShowNum(4,1,humi,2);
	OLED_ShowNum(4,5,Get_CO2(),4);
	}

}


void Show_Wifi_Status()
{
	OLED_SetCursor(0, 120); 
	if(Server_Status){
    for (uint8_t i = 0; i < 8; i++) { 
        OLED_WriteData(0xFF);        
    }
	}
	else{
	
	for (uint8_t i = 0; i < 8; i++) { 
        OLED_WriteData(0x00);         
    }
	}

}


void Show_Time()
{
	if(Time_Status)
	{
		MyRTC_ReadTime();
		OLED_ShowNum(1, 11, MyRTC_Time[3], 2);
		OLED_ShowChar(1, 13, ':');
		OLED_ShowNum(1, 14, MyRTC_Time[4], 2);

	}

}


uint8_t Show_Menu(char *Menu[],uint8_t rows)
{
	
uint8_t j=0;
	OLED_Clear();
	Cursor_position=1;
	Cursor_choice=1;
	while(1)
	{
		Show_Wifi_Status();
		Show_Time();
		//OLED_ShowNum(4,14,Cursor_choice,2);
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
		//OLED_ShowNum(1,1,Cursor_choice,3);
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
	}
	
	void BW_Menu()

{
	const static char BW_Parameter[]={0x00,0x10,0x20,0x30,0x40,0x50,0x60,0x70,0x80,0x90};
	
	SX1278_WriteReg(0x1D,((SX1278_SwapByte(0x1D)&0x0F)|BW_Parameter[Show_Menu(BW,sizeof(BW) / sizeof(BW[0]))-1]));

		Parameter_Menu();


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
	}

	
	
void	Power_Menu()
	
{
	const static char Power_Parameter[]={0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F};
	
	SX1278_WriteReg(0x09,((SX1278_SwapByte(0x09)&0xF0)|Power_Parameter[Show_Menu(POWER,sizeof(POWER) / sizeof(POWER[0]))-1]));
	
	Parameter_Menu();
}



void	INFORMATION_Menu()
{
OLED_ShowString(1,1,"Version:2.0");
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

	
	void Act_As_Edge_Device(){
		static uint16_t Rec_times=0;
		static uint16_t Send_times=0;
		int Response_Check=0;
		static int light;
		static uint16_t CO2;
		static uint16_t soil_Humidity;
		static uint16_t soil_Temperature;
		char Edge_Received_Response[128];
		char File_Name[20];
		char Content[512];
		
	Device_ID=Show_Menu(Choose_Device_ID,sizeof(Choose_Device_ID) / sizeof(Choose_Device_ID[0]));
		while(1)
		{
			
		Send_times++;
			OLED_ShowNum(2,1,Send_times,3);
			
			
			soil_Humidity = (dry_value - AD_GetValue(ADC_Channel_0)) * 100 / (dry_value - wet_value);
			if (soil_Humidity < 0) soil_Humidity = 0;
			if (soil_Humidity > 100) soil_Humidity = 100;
				soil_Temperature=DS18B20_Get_Temp();
			CO2=Get_CO2();
			MyRTC_ReadTime();
			light=Get_Light();
			Get_Tem_Hum();          
			
			Buffer[3]=1;						    //function id
			Buffer[4]=Device_ID;		    //device id
			Buffer[5]=25;               //year         
			Buffer[6]=MyRTC_Time[1];    //month
			Buffer[7]=MyRTC_Time[2];    //day
			Buffer[8]=MyRTC_Time[3];    //hour
			Buffer[9]=MyRTC_Time[4];    //minute
			Buffer[10]=MyRTC_Time[5];   //second
			Buffer[11]=(CO2>>8)&0xff;   //co2 value 1
			Buffer[12]=(CO2&0xff);      //co2 value 2
			Buffer[13]=light;
			Buffer[14]=soil_Temperature;
			
			Buffer[15]=soil_Humidity;
			Buffer[16]=temperature;
			Buffer[17]=humi;
			
			
			uint32_t check_temp=Buffer[11]+Buffer[12]+Buffer[13]+Buffer[14]+Buffer[15]+Buffer[16]+Buffer[17];
			
			Buffer[18]=(check_temp >> 16) & 0xFF;
			Buffer[19]=(check_temp >>  8) & 0xFF;
			Buffer[20]=(check_temp      ) & 0xFF;
			USART_SendArray(Buffer,128);
			Edge_Device_Send_Data();

			if(Recieve_Data(1))
			{
				Rec_times++;
				OLED_ShowNum(4,1,Rec_times,3);
				
				SX1278_WriteReg(FIFO_Pointer,Recieve_Buffer_Start);
			 for(int i=0;i<128;i++)
				{
						Edge_Received_Response[i]=SX1278_ReadReg(0x00);
				}
			 if(Edge_Received_Response[4]==Device_ID)
				{
					if(check_temp==((uint32_t)Edge_Received_Response[11] << 16)|((uint32_t)Edge_Received_Response[12] << 8)|(Edge_Received_Response[13] ))
					{
						Response_Check=1;
						 if(Edge_Received_Response[3]==1)//normol send data
						 {
						 
						 }
					 
						 else if(Edge_Received_Response[3]==2){   //requireing update time
						 
							 struct tm my_time;
							my_time.tm_year = Edge_Received_Response[5]+100;
							my_time.tm_mon  = Edge_Received_Response[6] - 1;
							my_time.tm_mday = Edge_Received_Response[7];
							my_time.tm_hour = Edge_Received_Response[8];
							my_time.tm_min  = Edge_Received_Response[9];
							my_time.tm_sec  = Edge_Received_Response[10];
							MyRTC_UpdateTime(&my_time);
		          }
		
						}
					else
					{
					
					Response_Check=0;
					}
		
														
				}
				
				
				
			}
			
			
			
			sprintf(File_Name, "Edge.TXT");
			sprintf(Content, "Record_Time:%04d-%02d-%02d %02d:%02d:%02d--ID:%02d: ,CO2:%04d, Air_Humidity:%02d,Air_Temperature:%02d,Soil_Humidity:%02d,Soil_Tempreature:%02d,Light:%d,Send_successful:%d\r\n",
													MyRTC_Time[0], MyRTC_Time[1], MyRTC_Time[2],MyRTC_Time[3], MyRTC_Time[4], MyRTC_Time[5],Device_ID,CO2,humi,temperature,soil_Humidity,soil_Temperature,light,Response_Check);
								WriteFileToSD(File_Name,Content,Append_In_File);       // 写入文件	
			
			
				
				
			}
		
		}
	
		
		
		void Act_As_Central_Device(){
			
			
		static uint16_t Rec_times;
			static char File_Name[30]="Central.TXT";
			static char Record_Time[30];
			static char Central_Recieved_Packet[30];
			 char Record_State[128];
			
			
			while(1){
			
		while(Recieve_Data(0)!=1);
			
			for(int i=0;i<30;i++)
				{
						Central_Recieved_Packet[i]=SX1278_ReadReg(0x00);
				}
		
		if(((uint32_t)Central_Recieved_Packet[18] << 16)|((uint32_t)Central_Recieved_Packet[19] << 8)|Central_Recieved_Packet[20] ==Central_Recieved_Packet[11]+Central_Recieved_Packet[12]+Central_Recieved_Packet[13]+Central_Recieved_Packet[14]+Central_Recieved_Packet[15]+Buffer[16]+Buffer[17]|1)
		
		{//验证check value
			Rec_times++;
			//OLED_ShowNum(4,1,Rec_times,3);
			MyRTC_ReadTime();
			if(abs(MyRTC_Time[4]-Central_Recieved_Packet[9])>1)
				Buffer[3]=2;
			else
				Buffer[3]=1;
			
			Buffer[4]=Central_Recieved_Packet[4];
			
	
	MyRTC_ReadTime();
			Buffer[5]=25;
			Buffer[6]=MyRTC_Time[1];
			Buffer[7]=MyRTC_Time[2];
			Buffer[8]=MyRTC_Time[3];
			Buffer[9]=MyRTC_Time[4];
			Buffer[10]=MyRTC_Time[5];
			Buffer[11]=Central_Recieved_Packet[18];
			Buffer[12]=Central_Recieved_Packet[19];
			Buffer[13]=Central_Recieved_Packet[20];
			
			Central_Device_Send_Data();
			//sprintf(Record_Time,"20%02d-%02d-%02d--%02d:%02d:%02d",Central_Recieved_Packet[5],Central_Recieved_Packet[6],Central_Recieved_Packet[7],Central_Recieved_Packet[8],Central_Recieved_Packet[9],Central_Recieved_Packet[10]);
			//sprintf(File_Name, "Central.TXT");
			memset(Record_State, 0, sizeof(Record_State));
			sprintf(Record_State,"Record_Time:20%02d-%02d-%02d--%02d:%02d:%02d--ID:%02d--recieved:%d\r\n",Central_Recieved_Packet[5],Central_Recieved_Packet[6],Central_Recieved_Packet[7],Central_Recieved_Packet[8],Central_Recieved_Packet[9],Central_Recieved_Packet[10],Central_Recieved_Packet[4],1);
				WriteFileToSD(File_Name,Record_State,Append_In_File);       // 写入文件	*/
				
		uint16_t CO2_Temp=(int)Central_Recieved_Packet[11] << 8 | (int)Central_Recieved_Packet[12];
		Data *data = (Data*)calloc(1, sizeof(Data)); // 初始化为0
		data->ID = (int)Central_Recieved_Packet[4];
		data->CO2_concentration = (int)CO2_Temp;
		data->Light_time = (int)Central_Recieved_Packet[13];
		data->Soil_temperature = (int)Central_Recieved_Packet[14];
		data->Soil_humidity = (int)Central_Recieved_Packet[15];
		data->Air_temperature = (int)Central_Recieved_Packet[16];
		data->Air_humidity = (int)Central_Recieved_Packet[17];

memset(data->Record_Time, 0, sizeof(data->Record_Time));  
snprintf(data->Record_Time, sizeof(data->Record_Time),
         "20%02d-%02d-%02d %02d:%02d:%02d",
         (int)Central_Recieved_Packet[5],
         (int)Central_Recieved_Packet[6],
         (int)Central_Recieved_Packet[7],
         (int)Central_Recieved_Packet[8],
         (int)Central_Recieved_Packet[9],
         (int)Central_Recieved_Packet[10]);

				/* OLED_Clear();
				 OLED_ShowHexNum(1,1,Central_Recieved_Packet[5],2);
				 OLED_ShowHexNum(1,4,Central_Recieved_Packet[6],2);
				 OLED_ShowHexNum(1,7,Central_Recieved_Packet[7],2);
				 OLED_ShowHexNum(2,1,Central_Recieved_Packet[8],2);
				 OLED_ShowHexNum(2,4,Central_Recieved_Packet[9],2);
				 OLED_ShowHexNum(2,7,Central_Recieved_Packet[10],2);
			 	 OLED_ShowNum(4,1,CO2_Temp,4);
				 OLED_ShowString(3,1,data->Record_Time);
				 OLED_ShowNum(4,1,sizeof(data->Record_Time),5);*/
					//while(1);
	Send_Http(data);
			free(data);
				
									
		}
	}
		
	}
		
	
	void Start()
{
switch (Show_Menu(Start_Choose_Role,sizeof(Start_Choose_Role) / sizeof(Start_Choose_Role[0])))
{
		case 1:
			Act_As_Edge_Device();
	  case 2:
			Act_As_Central_Device();
		case 3:
			Menu();



}
	
	
	



}
	

void Adjust_Soil_Humidity(void)
{
OLED_ShowString(1,1,"Clean Sensor ");
	OLED_ShowString(2,1,"And Put In Air");
	OLED_ShowString(3,1,"Press to Adjust");
	while(Key_GetNum()==0);
	
dry_value=AD_GetValue(ADC_Channel_0);
	OLED_Clear();
	OLED_ShowString(1,1,"Succeed");
	Delay_ms(500);
	OLED_ShowString(1,1,"Clean Sensor ");
	OLED_ShowString(2,1,"And Put In Water");
	OLED_ShowString(3,1,"Press to Adjust");
		while(Key_GetNum()==0);
	OLED_Clear();
wet_value=AD_GetValue(ADC_Channel_0);
OLED_ShowString(1,1,"Succeed");
	Delay_ms(500);


}


void Menu()	
{
	switch (Show_Menu(menu,sizeof(menu) / sizeof(menu[0])))
		{
		case 1:
			Start();
			break;
		case 2:
			Setting_Menu();
			break;
		case 3:
			Receive_Test();
		break;
		case 5:
			INFORMATION_Menu();
		Menu();
			break;
		case 6:
			Get_Basic_Setting();
	Menu();
		case 7:
					Sending_test();
		case 8:
			
			if(check_AP_Connection())
				Server_Status=1;
			else 
				Server_Status=0;
		Menu();
		
		break;
		case 9:
			Sensor_Test();
		case 10:
			Send_Sensor_Data();
		case 11:
			
			if(SD_Check())
				{
				 OLED_ShowString(1,1,"SD Ready        ");
			Delay_s(1);
			}
				else
				{
				
				//OLED_ShowString(1,1,"SD Not Ready        ");
			Delay_s(1);
				}
		Menu();
		case 12:
			int temp=Get_Time_Stamp();
		OLED_ShowNum(1,1,temp,1);
		 if(temp){
			 Time_Status=1;
		 MyRTC_SetTime();}
		 else
			 Time_Status=0;
		Menu();
		case 13:
			Adjust_Soil_Humidity();
		Menu();
}


}



