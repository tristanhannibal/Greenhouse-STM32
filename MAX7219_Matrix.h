#include "IOdef.h"
#include "stm32f10x.h"
void matrix_send_drop_full(void);
void matrix_send_drop_5(void);
void matrix_send_drop_4(void);
void matrix_send_drop_half(void);
void matrix_send_drop_2(void);
void matrix_send_drop_1(void);
void matrix_send_drop_0(void);
void matrix_init(void);
void matrix_send(uint16_t address,uint16_t data);
void matrix_send_array(uint16_t matrix[8]);
void matrix_intensity(uint16_t intensity);

