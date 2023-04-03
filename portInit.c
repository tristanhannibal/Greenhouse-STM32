// Filename: portInit.c
// Description: Contains functions which can set a port to our specified configuration
// Author: Tristan Brown-Hannibal 200400651
#include "portInit.h"



//@Purpose: to set the port pin to the configuration which we desire, for all ports in CRL
//@Params: 	GPIO_TypeDef* port The port in which we want to affect
//					uint32_t portMask The mask of the pin we are affecting
//					uint32_t portConfig The configuration setting of the pin, as desfined in IOdef.h
//@Returns void
void setPort_CRL(GPIO_TypeDef* port,uint32_t portMask, uint32_t portConfig){
	
	port->CRL &= ~portMask;
	port->CRL |= portConfig;

	
	
}


//@Purpose: to set the port pin to the configuration which we desire, for all ports in CRH
//@Params: 	GPIO_TypeDef* port The port in which we want to affect
//					uint32_t portMask The mask of the pin we are affecting
//					uint32_t portConfig The configuration setting of the pin, as desfined in IOdef.h
//@Returns void
void setPort_CRH(GPIO_TypeDef* port,uint32_t portMask, uint32_t portConfig){
	
	port->CRH &= ~portMask;
	port->CRH |= portConfig;

	
	
}
