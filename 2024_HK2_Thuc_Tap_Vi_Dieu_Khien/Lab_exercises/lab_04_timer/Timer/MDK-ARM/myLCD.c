#include "myLCD.h"
#include "main.h"
// Hàm kích xung Enable (E) d? xác nh?n d? li?u
void LCD_Enable(void) {
    HAL_GPIO_WritePin(LCDE_GPIO_Port, LCDE_Pin, GPIO_PIN_SET);
    HAL_Delay(1);
    HAL_GPIO_WritePin(LCDE_GPIO_Port, LCDE_Pin, GPIO_PIN_RESET);
    HAL_Delay(1);
}

// Hàm g?i 4-bit d? li?u d?n LCD
void LCD_Send4Bit(uint8_t data) {
    HAL_GPIO_WritePin(LCDD4_GPIO_Port, LCDD4_Pin, (data >> 0) & 0x01);
    HAL_GPIO_WritePin(LCDD5_GPIO_Port, LCDD5_Pin, (data >> 1) & 0x01);
    HAL_GPIO_WritePin(LCDD6_GPIO_Port, LCDD6_Pin, (data >> 2) & 0x01);
    HAL_GPIO_WritePin(LCDD7_GPIO_Port, LCDD7_Pin, (data >> 3) & 0x01);
    LCD_Enable();
}

// Hàm g?i l?nh d?n LCD
void LCD_Command(uint8_t cmd) {
    HAL_GPIO_WritePin(LCDRS_GPIO_Port, LCDRS_Pin, GPIO_PIN_RESET); // RS = 0 (G?i l?nh)
    LCD_Send4Bit(cmd >> 4);  // G?i 4-bit cao
    LCD_Send4Bit(cmd & 0x0F);  // G?i 4-bit th?p
}

// Hàm g?i ký t? lên LCD
void LCD_PutChar(uint8_t ch) {
    HAL_GPIO_WritePin(LCDRS_GPIO_Port, LCDRS_Pin, GPIO_PIN_SET); // RS = 1 (G?i d? li?u)
    LCD_Send4Bit(ch >> 4);  // G?i 4-bit cao
    LCD_Send4Bit(ch & 0x0F);  // G?i 4-bit th?p
}

// Hàm g?i chu?i lên LCD
void LCD_PutString(uint8_t *s) {
    while (*s) {
        LCD_PutChar(*s++);
    }
}

// Hàm d?t v? trí con tr? LCD
void LCD_GotoXY(uint8_t x, uint8_t y) {
    uint8_t address = (y == 0) ? (0x80 + x) : (0xC0 + x);
    LCD_Command(address);
}

// Hàm kh?i t?o LCD
void LCD_Init(void) {
    HAL_Delay(40); // Ch? ngu?n ?n d?nh

    // Chuy?n sang ch? d? 4-bit
    LCD_Send4Bit(0x03);
    HAL_Delay(5);
    LCD_Send4Bit(0x03);
    HAL_Delay(1);
    LCD_Send4Bit(0x03);
    HAL_Delay(1);
    LCD_Send4Bit(0x02);  // Ch? d? 4-bit
    HAL_Delay(1);

    // Thi?t l?p LCD
    LCD_Command(LCD_FUNCTION_SET);
    LCD_Command(LCD_DISPLAY_ON);
    LCD_Command(LCD_ENTRY_MODE);
    LCD_Command(LCD_CLEAR);
    HAL_Delay(2);
}
