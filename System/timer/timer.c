#include "timer.h"

#include "misc.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"

uint32_t seconds;

// f = SystemCoreClock / TIM_TimeBaseStructure.TIM_ClockDivision / (psc + 1)
// 向上计数，计数次数times = arr + 1
static void TIM2_Int_Init(uint16_t arr,uint16_t psc,uint8_t pre,uint8_t sub)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //时钟使能
	
	//定时器TIM2初始化
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE ); //使能指定的TIM2中断,允许更新中断

	//中断优先级NVIC设置
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = pre;  //抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = sub;  //从优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器


	TIM_Cmd(TIM2, ENABLE);  //使能TIMx					 
}

// f = SystemCoreClock / TIM_TimeBaseStructure.TIM_ClockDivision / (psc + 1)
// 向上计数，计数次数times = arr + 1
static void TIM4_Int_Init(uint16_t arr,uint16_t psc,uint8_t pre,uint8_t sub)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //时钟使能
	
	//定时器TIM4初始化
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE ); //使能指定的TIM4中断,允许更新中断

	//中断优先级NVIC设置
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  //TIM4中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = pre;  //抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = sub;  //从优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器


	TIM_Cmd(TIM4, ENABLE);  //使能TIMx					 
}

void TIM_Init(void)
{
//	TIM2_Int_Init(9999, 7199, 5, 0);  // 10KHz, 1s
	TIM4_Int_Init(9999, 7199, 4, 0);  // 10KHz, 1s  用于计数
}

//定时器2中断服务程序
void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)  // 检查TIM2是否发生更新中断
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update  );  // 清除TIM2更新中断标志
	}
}

//定时器4中断服务程序
void TIM4_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)  // 检查TIM4是否发生更新中断
	{
		seconds++;
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update  );  // 清除TIM4更新中断标志
	}
}
