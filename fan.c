#include "stm32f10x.h"
#include "portInit.h"
#include "fan.h"
#include "GPIO.h"

void fan_init(void){
	setPort_CRH(GPIOB,GPIO_CRH_CM8,GPIO_CRH_CM8_GP);

}
	
void fan_on(void){
	setBSRR(GPIOB,8);
}

void fan_off(void){
	
	clearBSRR(GPIOB,8);
}
