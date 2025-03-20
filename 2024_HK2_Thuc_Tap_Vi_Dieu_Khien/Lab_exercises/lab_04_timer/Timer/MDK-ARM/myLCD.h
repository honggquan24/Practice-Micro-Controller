#ifndef MYLCD_H
#define MYLCD_H
#include <stdint.h>

// LCD Commands
#define LCD_CLEAR 0x01           // Xóa màn hình
#define LCD_HOME 0x02            // Ðua con tr? v? v? trí ban d?u
#define LCD_ENTRY_MODE 0x06      // Ch? d? nh?p d? li?u
#define LCD_DISPLAY_ON 0x0C      // B?t hi?n th?, t?t con tr?
#define LCD_DISPLAY_OFF 0x08     // T?t màn hình
#define LCD_CURSOR_ON 0x0E       // Hi?n th? con tr?
#define LCD_CURSOR_BLINK 0x0F    // Con tr? nh?p nháy
#define LCD_SHIFT_LEFT 0x18      // D?ch màn hình sang trái
#define LCD_SHIFT_RIGHT 0x1C     // D?ch màn hình sang ph?i
#define LCD_FUNCTION_SET 0x28    // Giao ti?p 4-bit, 2 dòng, font 5x8

// Prototype các hàm
void LCD_Init(void);
void LCD_Command(uint8_t cmd);
void LCD_PutChar(uint8_t ch);
void LCD_PutString(uint8_t *s);
void LCD_GotoXY(uint8_t x, uint8_t y);

#endif // MYLCD_H
