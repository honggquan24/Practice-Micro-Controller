#include "main.h"
#include "myGPIO.h"

// Bi?n tr?ng th�i
GPIO_PinState P1_STATUS; 
GPIO_PinState P2_STATUS;
GPIO_PinState P3_STATUS;
GPIO_PinState P4_STATUS;

//======== Light_cmd (B?t/t?t d�n) ========//
void Light_cmd(uint8_t d, uint8_t status) {
    switch (d) {
        case D1:
            HAL_GPIO_WritePin(D1_GPIO_Port, D1_Pin, status);
            break;
        case D2:
            HAL_GPIO_WritePin(D2_GPIO_Port, D2_Pin, status);
            break;
        default:    
            return; // N?u gi� tr? kh�ng h?p l?, kh�ng l�m g� c?
    }
}

//======== PushButton_read (�?c tr?ng th�i n�t nh?n) ========//
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
            return P_INACTIVE; // Tr? v? tr?ng th�i kh�ng nh?n n?u kh�ng h?p l?
    }
}

//======== Switch_read (�?c tr?ng th�i c�ng t?c g?t) ========//
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
