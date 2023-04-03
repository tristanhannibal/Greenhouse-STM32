#include "pwm.h"

void tim3GpioSetup(void){
	TIM3->CR1 |= TIM_CR1_CEN; // Enable Timer3
	TIM3->EGR |= TIM_EGR_UG; // Reinitialize the counter
	TIM3->CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1; // PWM mode 1
	TIM3->CCMR1 |= TIM_CCMR1_OC1PE | TIM_CCMR1_OC1FE; // Preload Enable, Fast Enable
	TIM3->CCER |= TIM_CCER_CC1E; // Enable CH1
	TIM3->PSC = 0x095F; // Divide 24 MHz by 2400 (PSC+1), PSC_CLK= 10000 Hz, 1 count = 0.1 ms
	TIM3->ARR = 100; // 100 counts = 10 ms or 100 Hz
	TIM3->CCR1 = 50; // 50 counts = 5 ms = 50% duty cycle
	TIM3->CR1 |= TIM_CR1_ARPE | TIM_CR1_CEN; // Enable Timer3
}
void changeTim3Duty(uint16_t percentage){
	TIM3->CCR1 = percentage;
}
