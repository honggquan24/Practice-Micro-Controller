#include "myLED.h"
#include "main.h"

void Data8_put(uint8_t d8) {
    for (int i = 0; i < 8; i++) {
        // Iterate from MSB to LSB: check the bit (0x80 >> i)
        HAL_GPIO_WritePin(MOSI_GPIO_Port, MOSI_Pin,
            ((d8 & (0x80 >> i)) ? GPIO_PIN_SET : GPIO_PIN_RESET));
        // Clock pulse: set SCK low then high.
        HAL_GPIO_WritePin(SCK_GPIO_Port, SCK_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(SCK_GPIO_Port, SCK_Pin, GPIO_PIN_SET);
    }
    // Latch the data by toggling RCK.
    HAL_GPIO_WritePin(RCK_GPIO_Port, RCK_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(RCK_GPIO_Port, RCK_Pin, GPIO_PIN_SET);
}

void Data16_put(uint16_t d16) {
    for (int i = 0; i < 16; i++) {
        HAL_GPIO_WritePin(MOSI_GPIO_Port, MOSI_Pin,
            ((d16 & (0x8000 >> i)) ? GPIO_PIN_SET : GPIO_PIN_RESET));
        HAL_GPIO_WritePin(SCK_GPIO_Port, SCK_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(SCK_GPIO_Port, SCK_Pin, GPIO_PIN_SET);
    }
    HAL_GPIO_WritePin(RCK_GPIO_Port, RCK_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(RCK_GPIO_Port, RCK_Pin, GPIO_PIN_SET);
}

void LED_data(uint8_t n) {
    uint8_t LED_num[10] = { 0xFD, 0x09, 0x6E, 0xEA, 0xE1, 0xCB, 0xD7, 0xA2, 0xEF, 0xEB };
    if (n < 10)
        Data8_put(LED_num[n]);
    else
        Data8_put(n);
}

void LED_put(uint8_t n, uint8_t p) {
    if (p == 0) {
        Data16_put(0x0000);
        return;
    }
    uint8_t LED_num[10] = { 0xFD, 0x09, 0x6E, 0xEA, 0xE1, 0xCB, 0xD7, 0xA2, 0xEF, 0xEB };
    
    uint8_t digit;
    if (n < 10)
        digit = LED_num[n];
    else
        digit = n;  
    uint16_t pos_mask = (uint16_t)p << 8;
    uint16_t d16 = pos_mask | digit;
    Data16_put(d16);
}

static uint8_t LED_decode_char(uint8_t ch) {
    if (ch >= '0' && ch <= '9') {
        uint8_t LED_num[10] = { 0xFD, 0x09, 0x6E, 0xEA, 0xE1, 0xCB, 0xD7, 0xA2, 0xEF, 0xEB };
        return LED_num[ch - '0'];
    }
    switch(ch) {
        case 'A': return A;
        case 'b': return b;
        case 'C': return C;
        case 'd': return d;
        case 'E': return E;
        case 'F': return F;
        case 'H': return H;
        case 'I': return I;
        case 'J': return J;
        case 'L': return L;
        case 'N': return N;
        case 'O': return O;
        case 'P': return P;
        case 'S': return S;
        case 'U': return U;
        default:  return LED_OFF;
    }
}

void LED_putstring(uint8_t *s) {
    // Position masks for up to 5 digits: k5, k4, k3, k2, k1
    // (Each value will be shifted into the high byte)
    uint8_t pos[5] = { 16, 8, 4, 2, 1 };

    for (int i = 0; i < 5; i++) {
        uint8_t code;
        // If we've reached the end of the string, turn off this digit
        if (s[i] == '\0') {
            code = LED_OFF;
        } else {
            // Decode the character into a 7-segment code
            code = LED_decode_char(s[i]);
        }
        // pos[i] -> shifted into the high byte, 'code' stays in the low byte
        uint16_t d16 = ((uint16_t)pos[i] << 8) | code;
        
        // Send the 16-bit value to the shift registers
        Data16_put(d16);

        // Small delay to stabilize multiplexed display
        HAL_Delay(1000);
    }
}

