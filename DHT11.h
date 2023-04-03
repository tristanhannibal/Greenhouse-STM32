#include "IOdef.h"
#include "stm32f10x.h"

typedef struct
{
	float Temperature;
	float Humidity;
}DHT_data;
void DHT_getReadings(DHT_data* dht);
int DHT_start(void);
uint8_t DHT_receive(void);
