#ifndef __LED_H
#define __LED_H

#include "sys.h"

/* LED IO¶Ë¿Úºê -----------------------------*/
#define LED0			PCout(13)
#define LED0_CLOCK		RCC_APB2Periph_GPIOC
#define LED0_PORT		GPIOC
#define LED0_PIN		GPIO_Pin_13

#define LED1			PEout(5)
#define LED1_CLOCK		RCC_APB2Periph_GPIOE
#define LED1_PORT		GPIOE
#define LED1_PIN		GPIO_Pin_5

typedef enum{
	LED_ON = 0,
	LED_OFF = 1
}LED_State_Typedef;

void LED_Init(void);

void LED_Flip(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void LED0_Flip(void);
void LED1_Flip(void);

#endif
