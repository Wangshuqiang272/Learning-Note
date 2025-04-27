#include "server.h"

/*
 *	舵机驱动文件
 */

void TIM8_PWM_Init(void) {
    GPIO_InitTypeDef        GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_OCInitTypeDef       TIM_OCInitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);  // 开启定时器时钟,即内部时钟CK_INT=72M

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  // 设置输出速度
    GPIO_Init(GPIOC, &GPIO_InitStructure);             // 初始化GPIOC_Pin_9


		TIM_TimeBaseStructure.TIM_Period = (SystemCoreClock / 500000) - 1;  // 1000000.0/(CONTI_FREQ_35*THOUSAND)*72/ 2 ;
    TIM_TimeBaseStructure.TIM_Prescaler         = 0;                      // 2??,???
    TIM_TimeBaseStructure.TIM_ClockDivision     = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode       = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 10;  // ??
    TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);

    TIM_OCInitStructure.TIM_OCMode       = TIM_OCMode_PWM1;         // TIMx_CCMR2--????
    TIM_OCInitStructure.TIM_OutputState  = TIM_OutputState_Enable;  // TIMx_CCER,????
    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
    TIM_OCInitStructure.TIM_Pulse =
        (SystemCoreClock / 500000) / 2;  // 1000000.0/(CONTI_FREQ_35*THOUSAND)*72/4 + 15 ;TIMx_CCR3
    TIM_OCInitStructure.TIM_OCPolarity   = TIM_OCPolarity_Low;  // TIMx_CCER,????
    TIM_OCInitStructure.TIM_OCNPolarity  = TIM_OCNPolarity_Low;
    TIM_OCInitStructure.TIM_OCIdleState  = TIM_OCIdleState_Set;  // ??????TIMx_CR2
    TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Set;
    TIM_OC1Init(TIM8, &TIM_OCInitStructure);
   
	  TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable);  // ?????,TIMx_CCMR2

    TIM_SelectOnePulseMode(TIM8, TIM_OPMode_Single);  // ??TIM8??????
		

    TIM_ARRPreloadConfig(TIM8, ENABLE);  // ???????
    TIM_SetCounter(TIM8, 0);
		

		TIM_CtrlPWMOutputs(TIM8, ENABLE);  // 主输出使能，当使用的是通用定时器时，这句不需要
		TIM_Cmd(TIM8, DISABLE);
}
