#include "1602.h"
#include "portInit.h"
#include "GPIO.h"
#include "util.h"



void lcd_init(void){
	setPort_CRL(GPIOC,GPIO_CRL_CM1,GPIO_CRL_CM1_GP);
	setPort_CRL(GPIOC,GPIO_CRL_CM2,GPIO_CRL_CM2_GP);
	setPort_CRL(GPIOC,GPIO_CRL_CM4,GPIO_CRL_CM4_GP);
	
	setPort_CRL(GPIOC,GPIO_CRL_CM7,GPIO_CRL_CM7_GP);
	setPort_CRH(GPIOC,GPIO_CRH_CM8,GPIO_CRH_CM8_GP);
	setPort_CRH(GPIOC,GPIO_CRH_CM9,GPIO_CRH_CM9_GP);
	setPort_CRH(GPIOC,GPIO_CRH_CM10,GPIO_CRH_CM10_GP);
	delay_us(40);
	clearBSRR(GPIOC,1);
	clearBSRR(GPIOC,2);
	clearBSRR(GPIOC,4);

	delay_us(50000);
	lcd_send_cmd(0x30);
	
	delay_us(6000);
	lcd_send_cmd(0x30);
	
	delay_us(100);
	lcd_send_cmd(0x30);
	delay_us(1000);
	lcd_send_cmd(0x20);
	delay_us(10000);
	lcd_send_cmd(0x28);
	delay_us(1000);
	lcd_send_cmd(0x08);
	delay_us(1000);
	lcd_send_cmd(0x01);
	delay_us(1000);
	lcd_send_cmd (0x06);
	delay_us(1000);
	lcd_send_cmd (0x0C);
	
}

void lcd_send(char data, int rs){
	
	if (rs) {
		setBSRR(GPIOC,4);
	} else {
		clearBSRR(GPIOC,4);
	}
	
	
	if ((data>>3)&0x1) {
		setBSRR(GPIOC,7);
	} else {
		clearBSRR(GPIOC,7);
	}
	
	if ((data>>2)&0x1) {
		setBSRR(GPIOC,8);
	} else {
		clearBSRR(GPIOC,8);
	}
	
	if ((data>>1)&0x1) {
		setBSRR(GPIOC,9);
	} else {
		clearBSRR(GPIOC,9);
	}
	
	if ((data >>0 )&0x1) {
		setBSRR(GPIOC,10);
	} else {
		clearBSRR(GPIOC,10);
	}
	
	setBSRR(GPIOC,1);
	delay_us(20);
	clearBSRR(GPIOC,1);
	delay_us(70);
}


void lcd_send_cmd(char data){
	char message;
	
	message = ((data >> 4) & 0xF);
	lcd_send(message,0);
	message = (data & 0xF);
	lcd_send(message,0);
}

void lcd_send_values(char data){
	char message;
	message = ((data >> 4) & 0xF);
	lcd_send(message,1);
	message = (data & 0xF);
	lcd_send(message,1);
}


void lcd_set_cursor(int row, int column){
	
	
	if(row == 1) {
		column |= 0xC0;
	} else {
		column |= 0x80;
	}
	
	lcd_send_cmd((char)column);
	
	
	
	
}

void lcd_clear(void){
	lcd_send_cmd(0x01);
	delay_us(2000);
}

void lcd_send_string (char *str)
{
	while (*str) lcd_send_values (*str++);
}

