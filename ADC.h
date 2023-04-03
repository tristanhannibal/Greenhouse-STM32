#include "stm32f10x.h"
#include "portInit.h"

//@Purpose: Enable the clocks for IO, ADC and AFIO
//					Also get the PA4 to Analog input
//					Then finally turns on the ADC system
//@Returns void
void adcInit(void);

//@ Purpose Reads from analog port PA4
//@Returns uint32_t a 12 bit value from ADC1->DR corresponding to the analog signal
uint32_t readADC_PA4(void);
uint32_t readADC_PA1(void);
