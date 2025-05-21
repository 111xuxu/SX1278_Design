#ifndef __DS18B20_H
#define __DS18B20_H 
#include "stm32f10x.h"             
 				
 
#define DS18B20_GPIO_PORT		GPIOA
#define DS18B20_GPIO_PIN		GPIO_Pin_5
#define DS18B20_GPIO_CLK   	RCC_APB2Periph_GPIOA
 
#define OUT 1
#define IN  0
 

#define DS18B20_Low  GPIO_ResetBits(DS18B20_GPIO_PORT,DS18B20_GPIO_PIN)
#define DS18B20_High GPIO_SetBits(DS18B20_GPIO_PORT,DS18B20_GPIO_PIN)		
		
uint8_t DS18B20_Init(void);
short DS18B20_Get_Temp(void);
void DS18B20_Start(void);
void DS18B20_Write_Byte(u8 dat);
uint8_t DS18B20_Read_Byte(void);
uint8_t DS18B20_Read_Bit(void);
void DS18B20_Mode(u8 mode);
uint8_t DS18B20_Check(void);
void DS18B20_Rst(void);
 void Show_DS18B20_Tempreature(int x,int y);
#endif