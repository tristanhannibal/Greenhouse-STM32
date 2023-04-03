
#include "util.h"
#include "portInit.h"
#include "GPIO.h"
#include "ADC.h"
#include "interrupt.h"
#include "pwm.h"
#include "UART.h"
#include "SPI.h"
#include "MAX7219_Matrix.h"
#include "DHT11.h"
#include "1602.h"
#include <stdio.h>
#include "fan.h"
#include "pump.h"
#include <time.h>
#define WET 0.39
#define AIR 0.85
#define EMPTY 0.1
#define FULL 0.65
#define SOIL_RANGE (AIR-WET)
#define FAN_ON 25
#define PUMP_ON 
#define CLOCK_SPEED 64000000.0

void SysTick_Handler(void);
void delay_us(uint32_t us);
void system_init(void);
void output_lcd(void);
void EXTI15_10_IRQHandler(void);


//VARIABLES USED IN OUTPUTS
static double soilPercentage = 0;
static double waterPercentage = 0;
static	float temp = 0;
static	float humid = 0;
static unsigned int  mode = 0;
static double measured = 0;
static double timeInSeconds = -1; // -1 to indicate timing hasn't started
static int timeInMinutes = 0;
static uint16_t pumpAvailable = 1;


int main(void){
	system_init();
	//pump_on();
	pump_off();
	uint32_t soilHumid = 0;
	uint32_t waterLevel = 0;
	DHT_data* dht;
	dht->Humidity = 0;
	dht->Temperature = 0;
	uint16_t strobeMatrix = 0;
	uint16_t strobeRising = 1;
	uint16_t pumpOn = 0;

	uint32_t pumpCounter = 0;
	int loopCounter = 0;
	uint16_t intensity = 0x07;
	unsigned long totalTime = 0;
	unsigned long startTime = DWT->CYCCNT;

	
	measured = 0;
	soilPercentage = 0;
	while(1){
		loopCounter += 1;
		loopCounter %= 10000;
		startTime = DWT->CYCCNT;
		
		//FLASH MATRIX IF LOW WATER
		if(strobeMatrix && !(loopCounter % 3) && pumpOn == 0){
			if (strobeRising){
				intensity++;
			} else{
				intensity--;
			}
			if(intensity == 0xF || intensity == 0){
				strobeRising ^= 1;
			}
		}
		if(!strobeMatrix && pumpOn == 0)
			intensity = 0x7;
		
		
		//GET DHT READINGS AND TURN ON FAN IF TOO HOT
		setBSRR(GPIOA,10);
		DHT_getReadings(dht);
		setBSRR(GPIOA,10);
		temp = dht->Temperature;
		humid = dht->Humidity;
		soilHumid += readADC_PA1();
		waterLevel += readADC_PA4();
		
		if(temp > 30){
			fan_on();
		}else{
			fan_off();
		}
		
		
		//GET AVERAGE OF SAMPLES and CONVERT TO PERCENTAGES
		if(!(loopCounter % 100)){
			soilHumid /= 100;
			waterLevel /= 100;
			measured = (soilHumid / 4096.0);
			soilPercentage = (measured - AIR)/(WET-AIR) * 100.0;
			measured = (waterLevel / 4096.0);
			waterPercentage = (measured - EMPTY) / (FULL - EMPTY) * 100.0; 
			if(waterPercentage > -10000.0 && soilPercentage <= 25.0 && pumpAvailable == 1){
				uint16_t arr[8] = {0,0,0,0,0,0,0,0};
				matrix_send_array(arr);
				delay_us(400);
				fan_off();
				pump_on();
				pumpOn = 1;
				pumpCounter = 0;
				pumpAvailable = 0;
			}
			
			//OUTPUT WATER LEVEL PERCENTAGE TO MATRIX
			if(waterPercentage > (6.0/7.0)*100.0 && pumpOn == 0){
				matrix_send_drop_full();
				strobeMatrix = 0;
			}if(waterPercentage > (5.0/7.0)*100.0 && pumpOn == 0){
				matrix_send_drop_5();
				strobeMatrix = 0;
			}
			else if(waterPercentage > (4.0/7.0)*100.0 && pumpOn == 0){
				matrix_send_drop_4();
				strobeMatrix = 0;
			}
			else if(waterPercentage > (3.0/7.0)*100.0 && pumpOn == 0){
				matrix_send_drop_half();
				strobeMatrix = 0;
			}
			else if(waterPercentage > (2.0/7.0)*100.0 && pumpOn == 0){
				matrix_send_drop_2();
				strobeMatrix = 1;
			}
			else if(waterPercentage > (1.0/7.0)*100.0 && pumpOn == 0){
				matrix_send_drop_1();
				strobeMatrix = 1;
			}
			else if ( pumpOn == 0){
				matrix_send_drop_0();
				strobeMatrix = 1;
			}
			
			
		
		}
		
		
		//UPDATE LCD WITH DATA
		if(!(loopCounter % 16) && !(pumpOn)){
				output_lcd();
		}
	
		if(pumpOn == 0){
		matrix_intensity(intensity);
		}
		delay_us(10);
		
		pumpCounter+=1;
		if(pumpOn == 1 && pumpCounter >= 125){ //250 ~about 5 seconds every cycle about 0.02 seconds
			pumpOn = 0;
			pump_off();
			timeInMinutes = 0;
			timeInSeconds = 0;
		}
		if(pumpOn == 0 && pumpCounter >= 1409){ // 180000 Only allow a pump every ~60 minutes, 30 seconds for demo
			pumpOn = 0;
			pump_off();
			pumpAvailable = 1;
		}
		unsigned long endTime = DWT->CYCCNT;
		
		if (pumpAvailable == 0){
			totalTime =(endTime-startTime);
			timeInSeconds += totalTime/CLOCK_SPEED;
			if(timeInSeconds > 60.0){
					timeInMinutes +=1;
					timeInSeconds -= 60.0;
				}
		}
		

}
}

void system_init(void){
	setPort_CRH(GPIOC,GPIO_CRH_CM13,GPIO_CRH_CM13_DF);
	clockInit();
	matrix_init();
	initSYSTICK();
	initEXTI();
	lcd_init();
	fan_init();
	pump_init();
	lcd_set_cursor(0, 0);
	adcInit();
	
	
	
	//SET TIMER
	CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
	DWT->CYCCNT = 0;
	DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
	
}


void output_lcd(void){
	char lcd_string[16];
	if(mode == 0){
			lcd_clear();
			sprintf(lcd_string,"%.2f",temp);
			lcd_send_string(lcd_string);
			lcd_send_values(223);
			lcd_send_string("C");
			if(temp > 30)
				lcd_send_string("Too hot");
			if(temp < 15)
				lcd_send_string("Too cold");
			lcd_set_cursor(1,0);
			sprintf(lcd_string,"%.2f",humid);
			lcd_send_string(lcd_string);
			lcd_send_string("%");
			if(humid > 70)
				lcd_send_string(" Too hot");
			if(humid < 30)
				lcd_send_string(" Too dry");
	} else if (mode == 1){
			lcd_clear();
			lcd_send_string("Soil Humid: ");
			sprintf(lcd_string,"%.f",soilPercentage);
			lcd_send_string(lcd_string);
			lcd_send_string("%");
		
			lcd_set_cursor(1,0);
			lcd_send_string("Water ");
			
			
			if(pumpAvailable == 0){
				sprintf(lcd_string,"%X",timeInMinutes);
				lcd_send_string(lcd_string);
				lcd_send_string("m");
				sprintf(lcd_string,"%.0f",timeInSeconds);
				lcd_send_string(lcd_string);
				lcd_send_string("s");
			} else{
				lcd_send_string("Ready!");
			}
	}
	
}

void EXTI15_10_IRQHandler(void){
	
	EXTI->PR |= EXTI_PR_PR13; 
	mode = !mode;
}

