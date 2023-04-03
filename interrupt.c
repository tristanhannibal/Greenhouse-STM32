#include "interrupt.h"

void initSYSTICK(void){
	
	SysTick->CTRL &= 0x0;
	SysTick->VAL &= 0x0;
	uint32_t test = (uint32_t)((0x3D09000 / 1000000) - 1);
	SysTick->LOAD = test;
	SysTick->CTRL |= 0x6;
	
}


void initEXTI(void){
	AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI13_PC;
	EXTI->IMR = EXTI_IMR_MR13;
	EXTI->FTSR = EXTI_FTSR_TR13;
	NVIC->ISER[0] = NVIC_ISER_SETENA_10;
	NVIC_EnableIRQ(EXTI15_10_IRQn);

}


