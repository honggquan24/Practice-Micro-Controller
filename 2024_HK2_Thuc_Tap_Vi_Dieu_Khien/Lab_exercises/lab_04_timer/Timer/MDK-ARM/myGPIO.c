#include "main.h"
#include "myGPIO.h"

// Define global variables (Only in myGPIO.c)
uint8_t stateSW = 0;
uint8_t stateP1 = 0;
uint8_t stateP2 = 0;
uint16_t DelayCnt = 0;

GPIO_PinState P1_STATUS;
GPIO_PinState P2_STATUS;
GPIO_PinState P3_STATUS;
GPIO_PinState P4_STATUS;

void Light_cmd(uint8_t d, uint8_t status){
	switch(d){
		case D1:
			HAL_GPIO_WritePin(D1_GPIO_Port, D1_Pin, status);
			break;
		case D2:
			HAL_GPIO_WritePin(D2_GPIO_Port, D2_Pin, status);
			break;
		default:
			return;
	}
}

uint8_t PushButton_read(uint8_t p) {
    switch (p) {
        case P1:
            return HAL_GPIO_ReadPin(P1_GPIO_Port, P1_Pin);
        case P2:
            return HAL_GPIO_ReadPin(P2_GPIO_Port, P2_Pin);
        case P3:
            return HAL_GPIO_ReadPin(P3_GPIO_Port, P3_Pin);
        case P4:
            return HAL_GPIO_ReadPin(P4_GPIO_Port, P4_Pin);
        default:
            return P_INACTIVE;
    }
}



