#include "IOdef.h"
#include "stm32f10x.h"


void lcd_init(void);

void lcd_send(char data, int rs);
void lcd_send_cmd(char data);
void lcd_send_values(char data);
void lcd_set_cursor(int row, int column);

void lcd_send_string (char *str);
void lcd_clear (void);