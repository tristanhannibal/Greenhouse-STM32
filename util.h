#include <stdint.h>

void delay(uint32_t delay);
void SysTick_Handler(void);
void delay_us(uint32_t us);
void clockInit(void);
void led_IO_init (void);
void sw2led(void);

//Bit masks for leds on STM32VLDiscovery board PC8 and PC9 using GPIOC_BSRR
// Green LED is on bit 9 of port C, Blue LED is on bit 8.
// #define VL_GREEN_ON	0X00000200
// #define VL_GREEN_OFF	0x02000000
// #define VL_BLUE_ON	0x00000100
// #define VL_BLUE_OFF	0x01000000



//Bit masks for led on NUCLEO-6 board PA5 GPIOA_BSRR
// Green LED is on bit 5 of port A
 #define NUC_GREEN_ON	0X00000020
 #define NUC_GREEN_OFF	0x00200000 

