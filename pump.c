#include "stm32f10x.h"
#include "portInit.h"
#include "pump.h"
#include "GPIO.h"
#include "pwm.h"
#include "util.h"

void pump_init(void){
	setPort_CRH(GPIOB,GPIO_CRH_CM9,GPIO_CRH_CM9_GP);
	setPort_CRL(GPIOA,GPIO_CRL_CM6, GPIO_CRL_CM6_AP);
	tim3GpioSetup();
	
}
void pump_on(void)
{
	changeTim3Duty(99);
	delay_us(1000000);
	
}
void pump_off(void){
	changeTim3Duty(0);
}
