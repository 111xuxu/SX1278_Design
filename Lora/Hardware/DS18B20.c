#include "DS18B20.h"
#include "delay.h"	
 

void DS18B20_Rst(void)	   
{                 
		DS18B20_Mode(OUT); 
    DS18B20_Low; 				
    Delay_us(750);    	
    DS18B20_High; 			
		Delay_us(15);     	
}


uint8_t DS18B20_Check(void) 	   
{   
	uint8_t retry=0;
	DS18B20_Mode(IN);	 
    while (GPIO_ReadInputDataBit(DS18B20_GPIO_PORT,DS18B20_GPIO_PIN)&&retry<200)
	{
		retry++;
		Delay_us(1);
	};	 
	if(retry>=200)return 1;
	else retry=0;
    while (!GPIO_ReadInputDataBit(DS18B20_GPIO_PORT,DS18B20_GPIO_PIN)&&retry<240)
	{
		retry++;
		Delay_us(1);
	};
	if(retry>=240)return 1;	    
	return 0;
}


uint8_t DS18B20_Read_Bit(void) 	 
{
    uint8_t data;
	DS18B20_Mode(OUT);	
    DS18B20_Low; 
	Delay_us(2);
    DS18B20_High; 
	DS18B20_Mode(IN);	
	Delay_us(12);
	if(GPIO_ReadInputDataBit(DS18B20_GPIO_PORT,DS18B20_GPIO_PIN))data=1;
    else data=0;	 
    Delay_us(50);           
    return data;
}


uint8_t DS18B20_Read_Byte(void)     
{        
    uint8_t i,j,dat;
    dat=0;
	for (i=1;i<=8;i++) 
	{
        j=DS18B20_Read_Bit();
        dat=(j<<7)|(dat>>1);
    }						    
    return dat;
}


void DS18B20_Write_Byte(uint8_t dat)     
 {             
    uint8_t j;
    uint8_t testb;
	DS18B20_Mode(OUT);	
    for (j=1;j<=8;j++) 
	{
        testb=dat&0x01;
        dat=dat>>1;
        if (testb) 
        {
            DS18B20_Low;	
            Delay_us(2);                            
            DS18B20_High;
            Delay_us(60);             
        }
        else 
        {
            DS18B20_Low;	
            Delay_us(60);             
            DS18B20_High;
            Delay_us(2);                          
        }
    }
}
 
void DS18B20_Start(void) 
{   						               
    DS18B20_Rst();	   
		DS18B20_Check();	 
    DS18B20_Write_Byte(0xcc);
    DS18B20_Write_Byte(0x44);	
} 
 	 
uint8_t DS18B20_Init(void)
{
 	GPIO_InitTypeDef  GPIO_InitStructure;
 	
 	RCC_APB2PeriphClockCmd(DS18B20_GPIO_CLK, ENABLE);	 
	
 	GPIO_InitStructure.GPIO_Pin = DS18B20_GPIO_PIN;				
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		  
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(DS18B20_GPIO_PORT, &GPIO_InitStructure);
 
 	GPIO_SetBits(DS18B20_GPIO_PORT,DS18B20_GPIO_PIN);   
 
	DS18B20_Rst();
 
	return DS18B20_Check();
}  

short DS18B20_Get_Temp(void)
{
    uint8_t temp;
    uint8_t TL,TH;
	short tem;
    DS18B20_Start ();  			
    DS18B20_Rst();
    DS18B20_Check();	 
    DS18B20_Write_Byte(0xcc);	
    DS18B20_Write_Byte(0xbe);	 
    TL=DS18B20_Read_Byte(); 	
    TH=DS18B20_Read_Byte(); 	
	    	  
    if(TH>7)
    {
        TH=~TH;
        TL=~TL; 
        temp=0;					
    }else temp=1;			 	  
    tem=TH; 				
    tem<<=8;    
    tem+=TL;					
    tem=(float)tem*0.625;	
if(tem>=800)
tem=250;	
	if(temp)return tem; 		
	else return -tem;    
}
 
void DS18B20_Mode(uint8_t mode)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(DS18B20_GPIO_CLK, ENABLE);	
	
	if(mode)
	{
		GPIO_InitStructure.GPIO_Pin = DS18B20_GPIO_PIN;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	}
	else
	{
		GPIO_InitStructure.GPIO_Pin =  DS18B20_GPIO_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	}
	GPIO_Init(DS18B20_GPIO_PORT, &GPIO_InitStructure);
}

void Show_DS18B20_Tempreature(int x,int y)
{
	short temp;
	temp=DS18B20_Get_Temp();
	
OLED_ShowNum(x,y,temp/10,2);
OLED_ShowChar(x,y+2,'.');
	OLED_ShowNum(x,y+3,(temp-(temp/10)*10),1);





}
