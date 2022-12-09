#include "sys.h"
#include "delay.h"
#include "led.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"

static void LED_GPIO_Config(uint32_t LED_GPIO_CLK, GPIO_TypeDef* LED_GPIO_PORT, uint16_t LED_GPIO_PIN)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(LED_GPIO_CLK, ENABLE);
	
	GPIO_InitStruct.GPIO_Pin = LED_GPIO_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(LED_GPIO_PORT, &GPIO_InitStruct);
	
	if(LED_ON == 0) GPIO_SetBits(LED_GPIO_PORT,LED_GPIO_PIN);
	else if(LED_ON == 1) GPIO_ResetBits(LED_GPIO_PORT,LED_GPIO_PIN);
}

void LED_Init(void)
{
	LED_GPIO_Config(LED0_CLOCK, LED0_PORT, LED0_PIN);
//	LED_GPIO_Config(LED1_CLOCK, LED1_PORT, LED1_PIN);
}

// 翻转LED显示
void LED_Flip(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	switch(GPIO_ReadOutputDataBit(GPIOx, GPIO_Pin))
	{
		case LED_ON:
			GPIO_SetBits(GPIOx, GPIO_Pin);
			break;
		case LED_OFF:
			GPIO_ResetBits(GPIOx, GPIO_Pin);
			break;
	}
}

// LED0翻转显示
void LED0_Flip(void)
{
	LED_Flip(LED0_PORT, LED0_PIN);
}

// LED1翻转显示
void LED1_Flip(void)
{
	LED_Flip(LED1_PORT, LED1_PIN);
}
