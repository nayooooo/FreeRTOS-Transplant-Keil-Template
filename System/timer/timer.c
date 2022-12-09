#include "timer.h"

#include "misc.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"

uint32_t seconds;

// f = SystemCoreClock / TIM_TimeBaseStructure.TIM_ClockDivision / (psc + 1)
// ���ϼ�������������times = arr + 1
static void TIM2_Int_Init(uint16_t arr,uint16_t psc,uint8_t pre,uint8_t sub)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //ʱ��ʹ��
	
	//��ʱ��TIM2��ʼ��
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM2�ж�,��������ж�

	//�ж����ȼ�NVIC����
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = pre;  //��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = sub;  //�����ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���


	TIM_Cmd(TIM2, ENABLE);  //ʹ��TIMx					 
}

// f = SystemCoreClock / TIM_TimeBaseStructure.TIM_ClockDivision / (psc + 1)
// ���ϼ�������������times = arr + 1
static void TIM4_Int_Init(uint16_t arr,uint16_t psc,uint8_t pre,uint8_t sub)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //ʱ��ʹ��
	
	//��ʱ��TIM4��ʼ��
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM4�ж�,��������ж�

	//�ж����ȼ�NVIC����
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  //TIM4�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = pre;  //��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = sub;  //�����ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���


	TIM_Cmd(TIM4, ENABLE);  //ʹ��TIMx					 
}

void TIM_Init(void)
{
//	TIM2_Int_Init(9999, 7199, 5, 0);  // 10KHz, 1s
	TIM4_Int_Init(9999, 7199, 4, 0);  // 10KHz, 1s  ���ڼ���
}

//��ʱ��2�жϷ������
void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)  // ���TIM2�Ƿ��������ж�
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update  );  // ���TIM2�����жϱ�־
	}
}

//��ʱ��4�жϷ������
void TIM4_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)  // ���TIM4�Ƿ��������ж�
	{
		seconds++;
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update  );  // ���TIM4�����жϱ�־
	}
}
