

#include "stm32f10x.h"                 
#include "delay.h"

#define DHT11_GPIO_PORT  GPIOA
#define DHT11_GPIO_PIN   GPIO_Pin_6
#define DHT11_GPIO_CLK   RCC_APB2Periph_GPIOA
#define OUT 1
#define IN  0
#define DHT11_Low  GPIO_ResetBits(DHT11_GPIO_PORT,DHT11_GPIO_PIN)
#define DHT11_High GPIO_SetBits(DHT11_GPIO_PORT,DHT11_GPIO_PIN)
u8 DHT11_Init(void);
u8 DHT11_Read_Data(u8 *temp,u8 *humi);
u8 DHT11_Read_Byte(void);
u8 DHT11_Read_Bit(void);
void DHT11_Mode(u8 mode);
u8 DHT11_Check(void);
void DHT11_Rst(void); 

