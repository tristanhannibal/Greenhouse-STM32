#include "ADC.h"
//@Purpose: Enable the clocks for IO, ADC and AFIO
//					Also get the PA4 to Analog input
//					Then finally turns on the ADC system
//@Returns void
void adcInit(void){
	RCC->APB2ENR |=  RCC_APB2ENR_IOPAEN | RCC_APB2ENR_AFIOEN;
	RCC->APB2ENR |=  RCC_APB2ENR_ADC1EN | RCC_APB2ENR_ADC2EN ;
	setPort_CRL(GPIOA, GPIO_CRL_CM4, GPIO_CRL_CM4_AN);
	setPort_CRL(GPIOA, GPIO_CRL_CM1, GPIO_CRL_CM1_AN);
	ADC1->CR2 |= 0x00000001;
	ADC2->CR2 |= 0x00000001;
	
}


uint32_t readADC_PA1(void){
	ADC2->SQR3 |= 0x1;
	ADC2->CR2 |= 0x1;
	
	while(!(ADC2->SR & 0x2)) continue; 
	
	return ADC2->DR;
	
}

uint32_t readADC_PA4(void){
	ADC1->SQR3 |= 0x4;
	ADC1->CR2 |= 0x1;
	
	while(!(ADC1->SR & 0x2)) continue;
	
	return ADC1->DR;
}

