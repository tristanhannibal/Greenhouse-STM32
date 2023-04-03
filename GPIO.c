// Filename: GPIO.c
// Description: Contains functions which can set a ports ODR and get the input IDR from a pin
// Author: Tristan Brown-Hannibal 200400651
#include "GPIO.h"


//@Purpose: to set the output of a specific bit of a ports ODR
//@Params: 	GPIO_TypeDef* port The port in which we want to affect
//					uint16_t pin The pin we are setting
// 					uint16_t state The state we are setting the pin to (1/0) (high or low)
//@Returns void
void setODR(GPIO_TypeDef* port, uint32_t pin, uint32_t state){
	port->ODR &= ~(1UL << pin);
	port->ODR |= (state << pin);
	return;
			
}

void setBSRR(GPIO_TypeDef* port, uint32_t pin){

	port->BSRR &= ~(1UL << pin);
	port->BSRR |= (1UL << pin);
	return;
			
}

void clearBSRR(GPIO_TypeDef* port, uint32_t pin){
	port->BSRR &= ~(1UL << (pin + 16));
	port->BSRR |= (1UL << (pin + 16));
	port->BSRR &= ~(1UL << (pin + 16));
	return;
}



//@Purpose: to get the input of a specific bit of a ports IDR
//@Params: 	GPIO_TypeDef* port The port in which we want to read
//					uint16_t pin The pin we are reading
//@Returns uint16_t The state of the pin in which we read
unsigned int getInput(GPIO_TypeDef* port, unsigned int pin){
	unsigned int state = 0;
	unsigned int mask = (1UL << pin);
	state = port->IDR & mask;
	return state >> pin;
}


