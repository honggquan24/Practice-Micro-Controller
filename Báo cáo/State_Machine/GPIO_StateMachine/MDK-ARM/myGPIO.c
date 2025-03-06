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

uint8_t Switch_read(void) {
	if (HAL_GPIO_ReadPin(SW1_1_GPIO_Port, SW1_1_Pin) == SW_ON) {
		return SW1_ACTIVE; 
	} else if (HAL_GPIO_ReadPin(SW1_2_GPIO_Port, SW1_2_Pin) == SW_ON) {
		return SW2_ACTIVE; 
	} else if (HAL_GPIO_ReadPin(SW1_3_GPIO_Port, SW1_3_Pin) == SW_ON) {
		return SW3_ACTIVE; 
	} else {
		return SW_INACTIVE; 
	}
}




void Baitap3_3(uint8_t P1_STATUS, uint8_t P2_STATUS) {
	// P1 state	
	if (stateP1 == 0) {
		Light_cmd(D1, D_OFF);
		stateP1 = 1; 
	} else if (stateP1 == 1) {
		Light_cmd(D1, D_OFF);
		if (P1_STATUS == P_ACTIVE) {
			stateP1 = 2; 
		}
	} else if (stateP1 == 2) {
		Light_cmd(D1, D_ON);
		if (P1_STATUS == P_INACTIVE) {
			stateP1 = 3; 
		}
	} else if (stateP1 == 3) {
		Light_cmd(D1, D_ON);
		if (P1_STATUS == P_ACTIVE) {
			stateP1 = 4; 
		}
	} else if (stateP1 == 4) {
		Light_cmd(D1, D_OFF);
		if (P1_STATUS == P_INACTIVE) {
			stateP1 = 0; 
		}
	}
	
	// P2 state	
	uint16_t valueCnt = 0; 
	if (stateP2 == 0) {
		Light_cmd(D2, D_OFF);
		if (P2_STATUS == P_ACTIVE) {
			stateP2 = 1; 
		}
	} else if (stateP2 == 1) {
		Light_cmd(D2, D_OFF);
		if (P2_STATUS == P_INACTIVE) {
			stateP2 = 2; 
		}
	// Blink 2s
	} else if (stateP2 == 2) {
		if (DelayCnt < 1000) {
			Light_cmd(D2, D_ON);
			HAL_Delay(20);
			DelayCnt+=20; 
		}
		else if (DelayCnt < 2000) {
			Light_cmd(D2, D_OFF);
			HAL_Delay(20);
			DelayCnt+=20; 
		}
		else {
			DelayCnt = 0; 
		}
		if (P2_STATUS == P_ACTIVE) {
			stateP2 = 3; 
		}
	} else if (stateP2 == 3) {
		if (DelayCnt < 1000) {
			Light_cmd(D2, D_ON);
			HAL_Delay(20);
			DelayCnt+=20; 
		}
		else if (DelayCnt < 2000) {
			Light_cmd(D2, D_OFF);
			HAL_Delay(20);
			DelayCnt+=20; 
		}
		else {
			DelayCnt = 0; 
		}
		if (P2_STATUS == P_INACTIVE) {
			stateP2 = 4; 
		}
	} else if (stateP2 == 4) {
		Light_cmd(D2, D_OFF);
		if (P2_STATUS == P_ACTIVE) {
			stateP2 = 0; 
		}
	}

}


void Baitap3_4(uint16_t SW_STATUS) {
// State-machine logic
switch (stateSW)
{
	case 0:
		Light_cmd(D1, D_OFF);
		Light_cmd(D2, D_OFF);
		if (SW_STATUS == SW1_ACTIVE) stateSW = SW1_ACTIVE;
		break;

	case SW1_ACTIVE:
		Light_cmd(D1, D_OFF);
		if (SW_STATUS == SW2_ACTIVE) {
				stateSW = SW2_ACTIVE;
				DelayCnt = 0;  // Reset delay counter when entering blinking state
		}
		break;

	case SW2_ACTIVE:
		if (DelayCnt < 1000) {
				Light_cmd(D1, D_ON);
				HAL_Delay(20);
				DelayCnt += 20;
		}
		else if (DelayCnt < 2000) {
				Light_cmd(D1, D_OFF);
				HAL_Delay(20);
				DelayCnt += 20;
		}
		else {
				DelayCnt = 0; // Reset the blink counter only after one full ON/OFF cycle
		}

		if (SW_STATUS == SW3_ACTIVE) {
				stateSW = SW3_ACTIVE;
		}
		break;

	case SW3_ACTIVE:
		Light_cmd(D1, D_ON);
		if (SW_STATUS == SW1_ACTIVE) {
				stateSW = SW1_ACTIVE;  // Reset to initial active state
		}
		break;

	default:
		stateSW = 0; // Fallback safety case
		break;
	}
}
