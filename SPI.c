#include "SPI.h"
#include "GPIO.h"
#include "util.h"

void SPI_init(void){
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN | RCC_APB2ENR_AFIOEN;
	RCC->APB1ENR |= RCC_APB1ENR_SPI2EN;
	setPort_CRH(GPIOB,GPIO_CRH_CM12,GPIO_CRH_CM12_GP);
	setPort_CRH(GPIOB,GPIO_CRH_CM13,GPIO_CRH_CM13_AP);
	setPort_CRH(GPIOB,GPIO_CRH_CM14,GPIO_CRH_CM14_DF);
	setPort_CRH(GPIOB,GPIO_CRH_CM15,GPIO_CRH_CM15_AP);
	
	clearBSRR(GPIOB,12);
	
	SPI2->CR1 = 0x0;
	
	SPI2->CR1 |=  SPI_CR1_MSTR | SPI_CR1_BR_0 | SPI_CR1_BR_2;
	SPI2->CR1 |=  SPI_CR1_SSI | SPI_CR1_SSM | SPI_CR1_DFF;
	SPI2->CR1 |= SPI_CR1_SPE;
	
}


void SPI_go(void){
	uint16_t data;
	
	while(!(SPI2->SR & SPI_SR_TXE)){}
	clearBSRR(GPIOB,12);
	SPI2->DR = 0x0C01;
	while(!(SPI2->SR & SPI_SR_RXNE)){}
	data = SPI2->DR;
	setBSRR(GPIOB,12);
		
		
		
		
	while(!(SPI2->SR & SPI_SR_TXE)){}
	clearBSRR(GPIOB,12);
	SPI2->DR = 0x0B07;
	while(!(SPI2->SR & SPI_SR_RXNE)){}
	data = SPI2->DR;
	setBSRR(GPIOB,12);
		
		
	while(!(SPI2->SR & SPI_SR_TXE)){}
	clearBSRR(GPIOB,12);
	SPI2->DR = 0x012F;
	while(!(SPI2->SR & SPI_SR_RXNE)){}
	data = SPI2->DR;
	setBSRR(GPIOB,12);
		
		
	while(!(SPI2->SR & SPI_SR_TXE)){}
	clearBSRR(GPIOB,12);
	SPI2->DR = 0x02FF;
	while(!(SPI2->SR & SPI_SR_RXNE)){}
	data = SPI2->DR;
	setBSRR(GPIOB,12);
		
		
	while(!(SPI2->SR & SPI_SR_TXE)){}
	clearBSRR(GPIOB,12);
	SPI2->DR = 0x0a06;
	while(!(SPI2->SR & SPI_SR_RXNE)){}
	data = SPI2->DR;
	setBSRR(GPIOB,12);
		
	
	
	
}
