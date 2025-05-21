#ifndef __DH11_h
#define __DH11_h



#define DHT11_GPIO_PORT  GPIOA
#define DHT11_GPIO_PIN   GPIO_Pin_6
#define DHT11_GPIO_CLK   RCC_APB2Periph_GPIOA
#define OUT 1
#define IN  0
#define DHT11_Low  GPIO_ResetBits(DHT11_GPIO_PORT,DHT11_GPIO_PIN)
#define DHT11_High GPIO_SetBits(DHT11_GPIO_PORT,DHT11_GPIO_PIN)
uint8_t DHT11_Init(void);
uint8_t DHT11_Read_Data(u8 *temp,u8 *humi);
uint8_t DHT11_Read_Byte(void);
uint8_t DHT11_Read_Bit(void);
void DHT11_Mode(u8 mode);
uint8_t DHT11_Check(void);
void DHT11_Rst(void); 



#endif
