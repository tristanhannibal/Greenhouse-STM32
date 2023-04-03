#include "SPI.h"
#include "MAX7219_Matrix.h"
#include "GPIO.h"


void matrix_init(void){
	
	SPI_init();
	matrix_send(0x0C,0x01);
	matrix_send(0x0B,0x07);
	matrix_send(0x0A,0x0F);
	
	for (uint16_t i = 1; i < 9; i++){
		matrix_send(i,0x00);
	}
}



void matrix_intensity(uint16_t intensity){
	matrix_send(0x0A,intensity);
}

void matrix_send(uint16_t address,uint16_t data){
	uint16_t message = address;
	message <<= 8;
	message |= data;
	
	while(!(SPI2->SR & SPI_SR_TXE)){}
	clearBSRR(GPIOB,12);
	SPI2->DR = message;
	while(!(SPI2->SR & SPI_SR_RXNE)){}
	data = SPI2->DR;
	setBSRR(GPIOB,12);	
	
}

void matrix_send_array(uint16_t matrix[8]){
	
	for (uint16_t i = 0; i < 8; i++){
		matrix_send(i+1,matrix[i]);
	}
	
}


void matrix_send_drop_full(void){
	uint16_t arr[8] = {0x38,0x7C,0xFE,0xFF,0xFE,0x7C,0x38,0x0};
	matrix_send_array(arr);
	
}


void matrix_send_drop_5(void){
	uint16_t arr[8] = {0x38,0x7C,0xFE,0xFD,0xFE,0x7C,0x38,0x0};
	matrix_send_array(arr);
	
}

void matrix_send_drop_4(void){
	uint16_t arr[8] = {0x38,0x7C,0xFA,0xF9,0xFA,0x7C,0x38,0x0};
	matrix_send_array(arr);
	
}

void matrix_send_drop_half(void){
	uint16_t arr[8] = {0x38,0x74,0xF2,0xF1,0xF2,0x74,0x38,0x0};
	matrix_send_array(arr);
	
}

void matrix_send_drop_2(void){
	uint16_t arr[8] = {0x38,0x64,0xE2,0xE1,0xE2,0x64,0x38,0x0};
	matrix_send_array(arr);
	
}

void matrix_send_drop_1(void){
	uint16_t arr[8] = {0x38,0x44,0xC2,0xC1,0xC2,0x44,0x38,0x0};
	matrix_send_array(arr);
	
}

void matrix_send_drop_0(void){
	uint16_t arr[8] = {0x38,0x44,0x82,0x81,0x82,0x44,0x38,0x0};
	matrix_send_array(arr);
	
}
