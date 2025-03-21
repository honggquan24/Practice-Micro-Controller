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

uint8_t LED_decode_char(uint8_t ch) {
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
    uint8_t pos[5] = {0x08, 0x10, 0x20, 0x40, 0x80};

    static uint32_t last_refresh_time = 0;  // Last time a digit was updated
    static uint8_t current_digit = 0;       // Current digit index (0-4)

    if (HAL_GetTick() - last_refresh_time >= 10) { // Refresh every 5ms (adjust as needed)
        last_refresh_time = HAL_GetTick();  // Update last refresh time

        uint8_t code;
        // If we've reached the end of the string, turn off this digit
        if (s[current_digit] == '\0') {
            code = LED_OFF;
        } else {
            // Decode the character into a 7-segment code
            code = LED_decode_char(s[current_digit]);
        }

        // Construct 16-bit data: High byte for position, Low byte for segment data
        uint16_t d16 = ((uint16_t)pos[current_digit] << 8) | code;

        // Send the 16-bit value to the shift registers
        Data16_put(d16);

        // Move to the next digit
        current_digit++;
        if (current_digit >= 5) {
            current_digit = 0;  // Reset to the first digit after cycling through all
        }
    }
}


