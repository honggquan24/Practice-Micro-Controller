#include "main.h"
#include <stdint.h>




void Data8_put(uint8_t d8){
	// Transfer data
	for (int i = 0; i < 8; i++) {
		// 0x80 is 1000 0000
		// MSB First (Left bit) -> (Right bit)
		HAL_GPIO_WritePin(MOSI_GPIO_Port, MOSI_Pin, (GPIO_PinState) ( d8 & (0x80>>i) ) );
		HAL_GPIO_WritePin(SCK_GPIO_Port, SCK_Pin, 0);
		HAL_GPIO_WritePin(SCK_GPIO_Port, SCK_Pin, 1);
	}
	// Latch data
	HAL_GPIO_WritePin(RCK_GPIO_Port, RCK_Pin, 0);
	HAL_GPIO_WritePin(RCK_GPIO_Port, RCK_Pin, 1);
} 

void Data16_put(uint16_t d8){
	// Transfer data
	for (int i = 0; i < 16; i++) {
		// 0x80 is 1000 0000
		// MSB First (Left bit) -> (Right bit)
		HAL_GPIO_WritePin(MOSI_GPIO_Port, MOSI_Pin, (GPIO_PinState) ( d8 & (0x8000>>i) ) );
		HAL_GPIO_WritePin(SCK_GPIO_Port, SCK_Pin, 0);
		HAL_GPIO_WritePin(SCK_GPIO_Port, SCK_Pin, 1);
	}
	// Latch data
	HAL_GPIO_WritePin(RCK_GPIO_Port, RCK_Pin, 0);
	HAL_GPIO_WritePin(RCK_GPIO_Port, RCK_Pin, 1);
} 

void LED_data(uint8_t d8){
	uint8_t LED_num[10] = { 0xB7, 0xA0, 0x6E, 0xEA, 0xE1, 0xCB, 0xD7, 0xA2, 0xEF, 0xEB }; 
	
    if (d8 < 10) {
        Data8_put(LED_num[d8]); 
    } else {
        Data8_put(d8); 
    }
} 

void LED_put(uint8_t n, uint8_t p){ 
	// 0x08
		switch (p) {
			case 0: 
				// p = 0: T?t h?t các LED
				break; 
			case 1: 
				// p = 1: Hi?n th? LED v? trí k1   (00000001)
				break; 
			case 2: 
				// p = 2: Hi?n th? LED v? trí k2   (00000010)
				break; 
			case 4: 
				// p = 4: Hi?n th? LED v? trí k3   (00000100)
				break; 
			case 8: 
				// p = 8: Hi?n th? LED v? trí k4   (00001000)
				break; 
			case 16: 
				// p = 16: Hi?n th? LED v? trí k5 (00010000)
				break; 
			case 3: 
				// p = 3: Hi?n th? LED v? trí k1 và k2.  (00000011)
				break; 
			case 7: 
				// p = 7: Hi?n th? LED v? trí k1 và k2 và k3. (00000110)
				break; 
		}

}


