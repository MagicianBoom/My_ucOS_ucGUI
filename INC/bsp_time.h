#ifndef _BSP_TIME_H_
#define _BSP_TIME_H_

#include "stm32f4xx.h"

void TIM_INIT(void);
void sys_time(void);

u16 Get_Time(u8,u16,u16);


void Delay_us(uint32_t);
void Delay_ms(uint32_t);
uint32_t GetSysTime_us(void);
#endif
