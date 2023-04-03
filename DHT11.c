#include "DHT11.h"
#include "util.h"
#include "GPIO.h"
#include "portInit.h"







int DHT_start(void){
	
	
	setPort_CRH(GPIOA,GPIO_CRH_CM10,GPIO_CRH_CM10_GP);
	clearBSRR(GPIOA,10);
	delay_us(18000);
	setBSRR(GPIOA,10);
	delay_us(20);
	setPort_CRH(GPIOA,GPIO_CRH_CM10,GPIO_CRH_CM10_DF);
	
	
	int response = 0;
	if(!(getInput(GPIOA,10)))
	{
		delay_us(80);
		if((getInput(GPIOA,10))){
			response = 1;
		}
	}
	
	while(getInput(GPIOA,10)){}

	return response;
	
	
	
}
uint8_t DHT_receive(void){
	uint8_t i,j;
	for (j=0;j<8;j++){
		while (!(getInput(GPIOA,10))){}  
		delay_us (40);   
		if (!(getInput(GPIOA,10))){   
			i&= ~(1<<(7-j));  
		}
		else{ 
			i|= (1<<(7-j)); 
		}
		while(getInput(GPIOA,10)){}  
	}
	return i;	
	
	
}


void DHT_getReadings(DHT_data* dht){
	NVIC_DisableIRQ(EXTI15_10_IRQn);
	uint8_t humidity_byte1 = 0;
	uint8_t humidity_byte2 = 0;
	uint8_t temperature_byte1 = 0;
	uint8_t temperature_byte2 = 0;
	uint8_t check_sum = 0;
	int response = DHT_start();
	humidity_byte1 = DHT_receive();
	humidity_byte2 = DHT_receive();
	temperature_byte1 = DHT_receive();
	temperature_byte2 = DHT_receive();
	check_sum = DHT_receive();
	NVIC_EnableIRQ(EXTI15_10_IRQn);
	
	dht->Temperature = (float)temperature_byte1;
	dht->Humidity = (float)humidity_byte1;

}
