#include "UART.h"
#include "portInit.h"
void  transmit(uint16_t value){
	while (!(USART1->SR & USART_SR_TXE));
	USART1->DR = value;
	
}
uint16_t  receive(void){
	while ((USART1->SR & USART_SR_NE));
	return USART1->DR;
}
void UART_init(void){
	setPort_CRH(GPIOA,GPIO_CRH_CM9,GPIO_CRH_CM9_AP);
	setPort_CRH(GPIOA,GPIO_CRH_CM10,GPIO_CRH_CM10_DF);
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
	USART1->BRR |= 0x9C4;
	USART1->CR1 |= USART_CR1_TE | USART_CR1_RE | USART_CR1_UE;
}
