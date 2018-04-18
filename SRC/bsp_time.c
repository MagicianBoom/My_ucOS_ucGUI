#include "bsp_time.h"
#include "includes.h"

#define SYS_TIMx					TIM2
#define SYS_RCC_TIMx			RCC_APB1Periph_TIM2

void TIM_CONF()   //APB1  84M
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		
		/* ʹ��ʱ�� */
    RCC_APB1PeriphClockCmd(SYS_RCC_TIMx,ENABLE);

		TIM_DeInit(SYS_TIMx);
	
	/* �Զ���װ�ؼĴ������ڵ�ֵ(����ֵ) */
    TIM_TimeBaseStructure.TIM_Period=1000;
	
    /* �ۼ� TIM_Period��Ƶ�ʺ����һ�����»����ж� */
	  /* ʱ��Ԥ��Ƶ��Ϊ72 */
    TIM_TimeBaseStructure.TIM_Prescaler= 84 - 1;
	
		/* ���ⲿʱ�ӽ��в�����ʱ�ӷ�Ƶ,����û���õ� */
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;   //���ϼ���
	
	TIM_TimeBaseInit(SYS_TIMx,&TIM_TimeBaseStructure);

	TIM_ClearFlag(SYS_TIMx,TIM_FLAG_Update);

	TIM_ITConfig(SYS_TIMx,TIM_IT_Update,ENABLE);
		
		
    TIM_Cmd(SYS_TIMx, ENABLE);																		
    
    RCC_APB1PeriphClockCmd(SYS_RCC_TIMx , DISABLE);		/*�ȹرյȴ�ʹ��*/  
}
void TIM_NVIC()
{
    NVIC_InitTypeDef NVIC_InitStructure; 
    
//    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);  													
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;	  
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = NVIC_TIME_P;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = NVIC_TIME_S;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

void TIM_INIT()
{
    TIM_CONF();
    TIM_NVIC();

	/* TIM2 ���¿�ʱ�ӣ���ʼ��ʱ */
	RCC_APB1PeriphClockCmd(SYS_RCC_TIMx , ENABLE);
}


volatile uint32_t sysTickUptime = 0;

#define TICK_PER_SECOND 1000 
#define TICK_US	(1000000/TICK_PER_SECOND)


uint32_t GetSysTime_us(void) 
{
	register uint32_t ms;
	u32 value;
	ms = sysTickUptime;
	value = ms * TICK_US + (SysTick->LOAD - SysTick->VAL) * TICK_US / SysTick->LOAD;//TICK_US 1000��(SysTick->LOAD - SysTick->VAL) * TICK_US / SysTick->LOAD����΢����
	return value;//value ��λΪ΢��
}

void Delay_us(uint32_t us)
{
    uint32_t now = GetSysTime_us();
    while (GetSysTime_us() - now < us);
}

void Delay_ms(uint32_t ms)
{
    while (ms--)
        Delay_us(1000);
}