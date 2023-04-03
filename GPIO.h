// Filename: GPIO.c
// Description: Contains functions which can set a ports ODR and get the input IDR from a pin
// Author: Tristan Brown-Hannibal 200400651
#include <stdint.h>
#include "stm32f10x.h"


//@Purpose: to set the output of a specific bit of a ports ODR
//@Params: 	GPIO_TypeDef* port The port in which we want to affect
//					uint16_t pin The pin we are setting
// 					uint16_t state The state we are setting the pin to (1/0) (high or low)
//@Returns void
void setODR(GPIO_TypeDef* port, uint32_t pin, uint32_t state);

//@Purpose: to get the input of a specific bit of a ports IDR
//@Params: 	GPIO_TypeDef* port The port in which we want to read
//					uint16_t pin The pin we are reading
//@Returns uint16_t The state of the pin in which we read
unsigned int getInput(GPIO_TypeDef* port, unsigned int pin);




void setBSRR(GPIO_TypeDef* port, uint32_t pin);
void clearBSRR(GPIO_TypeDef* port, uint32_t pin);
