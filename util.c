
 #include "stm32f10x.h"
 #include "util.h"

//**************************** Utility ************************************************************
// i= 6000 is approximately 1 ms @ SYSCLK = 24 MHz

void delay(uint32_t delay)
{
  uint32_t i=0;
	for(i=0; i< delay; ++i)
	{
	}
	return;
}

static volatile uint32_t delayCounter;
void SysTick_Handler() {
	delayCounter++;
}


void delay_us(uint32_t us){
	SysTick->CTRL |= SysTick_CTRL_ENABLE;
	delayCounter = 0;
	while(delayCounter < us);
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE;
	
}

//**************************** Clock Configuration ************************************************************
void clockInit(void)
{
  
//* enable HSI and wait for it to be ready
    RCC->CR |= 0x00000001;
    while (((RCC->CR) & 0x00000003) == 0);
			
//* enable HSE with Bypass and wait for it to be ready
    RCC->CR |= 0x00050000;
    while (((RCC->CR) & 0x0007000) == 0);
				
//* enable flash prefetch buffer */
//FLASH->ACR = 0x00000012;
    
////SET HSI as SYSCLK and wait for it to be recognized
//    RCC->CFGR = 0x04000000;
//    while (((RCC->CFGR) & 0x0000000C) != 0);
			
//SET HSE as SYSCLK and wait for it to be recognized
    RCC->CFGR = 0x04000001;
    while (((RCC->CFGR) & 0x00000005) == 0);
			
// Disable PLL. 
		
		RCC->CR &= ~RCC_CR_PLLON;
			
//Change PLL source and set the PLL multiplier
			
//These are the SYSCLK values when using the PLL with HSI/2 as the input. The max value is 64 MHz
		//RCC->CFGR = 0x00000000;// 8MHz
		//RCC->CFGR = 0x00040000;// 12 MHz
		//RCC->CFGR = 0x00080000;// 16 MHz
		//RCC->CFGR = 0x000c0000;// 20 MHz			
		//RCC->CFGR = 0x00100000;// 24 MHz **** MAX SPEED for VLDISCOVERY *****
		//RCC->CFGR = 0x00140000;//	28 MHz
		//RCC->CFGR = 0x00180000;// 32 MHz
		//RCC->CFGR = 0x001C0000;// 36 MHz			
		//RCC->CFGR = 0x00200000;// 40 MHz
		//RCC->CFGR = 0x00240000;//	44 MHz
		//RCC->CFGR = 0x00280000;// 48 MHz
		//RCC->CFGR = 0x002C0000;// 52 MHz
		RCC->CFGR = 0x003C0000;// 64 MHz			

//These are the SYSCLK values when using the PLL with HSE/Bypass as the input. The max value is 72 MHz
		//RCC->CFGR = 0x00010000;// 16 MHz
		//RCC->CFGR = 0x00050000;// 24 MHz **** MAX SPEED for VLDISCOVERY *****
		//RCC->CFGR = 0x00090000;// 32 MHz
		//RCC->CFGR = 0x000d0000;// 40 MHz			
		//RCC->CFGR = 0x00110000;// 48 MHz
		//RCC->CFGR = 0x00150000;//	56 MHz
		//RCC->CFGR = 0x00190000;// 64 MHz
		//RCC->CFGR = 0x001d0000;// 72 MHz			

//ENABLE PLL and wait for it to be ready

    RCC->CR |= RCC_CR_PLLON;
    while (((RCC->CR) & 0x03000000) == 0);
   
// Set PLL as SYSCLK and wait for it to be ready
			
    RCC->CFGR |= 0x00000002;
    while (((RCC->CFGR) & 0x00000008) == 0);
			
// Enable clock visibity on PA8, select PLL/2 as output source
			
		RCC->CFGR |= RCC_CFGR_MCO_PLL;

	
//Enable peripheral clocks for various ports and subsystems
			
    RCC->APB2ENR |=  RCC_APB2ENR_IOPAEN | RCC_APB2ENR_AFIOEN;
		RCC->APB2ENR |=  RCC_APB2ENR_IOPBEN;
		RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
		RCC->APB2ENR |=  RCC_APB2ENR_IOPCEN;
	
		
		

}

//**************************** I/O ************************************************************

void led_IO_init (void)
{
    //Enable peripheral clocks for various ports and subsystems
    //Bit 4: Port C Bit3: Port A
    
	
	// Uncomment the appropriate board specific port configuration

	//****************VLDiscovery*******************************************************************
    //Set the config and mode bits for Port C bit 9 so it will be a push-pull output (up to 50 MHz)
//    GPIOC->CRH |= GPIO_CRH_MODE9;
//    GPIOC->CRH &= ~GPIO_CRH_CNF9;
	//****************VLDiscovery*******************************************************************
	
	//****************NUCLEO-64*******************************************************************
//    //Set the config and mode bits for Port A bit 5 so it will be a push-pull output (up to 50 MHz)
    GPIOA->CRL |= GPIO_CRL_MODE5;
    GPIOA->CRL &= ~GPIO_CRL_CNF5;
	//****************NUCLEO-64*******************************************************************
	
}	
	
void sw2led(void)
{
	
  	// Read the USER button and control the GREEN LED pattern according to its state
  
	//Uncomment for VLDiscovery	
	
//	if ((GPIOA->IDR & GPIO_IDR_IDR0) == 1)
//		
//    {
//        GPIOC->BSRR = VL_GREEN_ON;
//     }
//    else
//    {
//        GPIOC->BSRR = VL_GREEN_OFF;
//     }
	
	
			
	//Uncomment for Nucleo 64

	if ((GPIOC->IDR & GPIO_IDR_IDR13) == 0)
		
  {
     GPIOA->BSRR = NUC_GREEN_ON;
  }
  else
  {
     GPIOA->BSRR = NUC_GREEN_OFF;
  }
}
	
	


