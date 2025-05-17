#ifndef __WIFI_h
#define __WIFI_h

typedef struct {
	int ID;
	float Soil_temperature;
	float Soil_humidity;
	float Light_time;
	float CO2_concentration;
	float Air_temperature;
	float Air_humidity;


}Data;


static char Recieve_String[500];
static char Check_CIPMODE[]={"AT+CIPMODE?\r\n"};
static char Check_AT[]={"AT\r\n"};
static char Change_CIPMODE[]={"AT+CIPMODE=1\r\n"};
static char Connect_To_Server[]={"AT+CIPSTART=\42TCP\42,\428.208.52.104\42,5000\r\n"};
static char CIP_Send[]={"AT+CIPSEND\r\n"};
static char Disconnect_To_Server[]={"AT+CIPCLOSE\r\n"};
static char Connection_Status[]={"AT+CIPSTATUS\r\n"};
static char Join_Ap[]={"AT+CWJAP=\42 111\42£¬\42 287132018\42\r\n"};

static char HTTP_Header[]=
"POST /postdata HTTP/1.1\r\n"
"Host: 8.208.52.104\r\n"
"Content-Type: application/json\r\n"
"Content-Length: 146\r\n"
"Connection: close\r\n"
"\r\n";
static char Data_Container[] =

"{\"CO2_concentration\": 450,\"ID\": 4,\"Light_time\": 1,"
"\"Sequence\": 1,\"Soil_humidity\": 51,\"Soil_temperature\": 25,"
"\"Air_humidity\":30,\"Air_temperature\":24}";

int Connect_Server();
void  Wifi_USART_Init();

void WIFI_SendByte(uint8_t Byte);
void WIFI_SendArray(uint8_t *Array,uint16_t Length);
void WIFI_SendString(char *string);
uint32_t WIFI_Serial_Pow(uint32_t X,uint32_t Y);
void WIFI_SendNumber(uint32_t Number,uint8_t Length);
uint8_t WIFI_GetRxData(void);
uint8_t WIFI_GetRxFlag(void);
void USART2_IRQHandler(void);
int Join_AP();
	int check_AP_Connection();
#endif