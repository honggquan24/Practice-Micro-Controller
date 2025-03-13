#ifndef MYLED_H
#define MYLED_H

#include "main.h"
#include <stdint.h>


void Data8_put(uint8_t d8);

void Data16_put(uint16_t d16);

void LED_data(uint8_t n);

/**
 * @brief  Decodes and displays the digit n on the 7-segment LED at position p.
 *         p = 0 : Turn off all LEDs.
 *         p = 1 : Display at position k1   (00000001).
 *         p = 2 : Display at position k2   (00000010).
 *         p = 4 : Display at position k3   (00000100).
 *         p = 8 : Display at position k4   (00001000).
 *         p = 16: Display at position k5   (00010000).
 *         p = 3 : Display at positions k1 and k2 (00000011).
 *         p = 7 : Display at positions k1, k2, and k3 (00000110).
 * @param  n: The digit (0-9) to display.
 * @param  p: The position mask.
 */
void LED_put(uint8_t n, uint8_t p);

void LED_putstring(uint8_t *s);

#define A   0xE7
#define b   0xCD
#define C   0x0F
#define d   0xEC
#define E   0x4F
#define F   0x47
#define H   0xE5
#define I   0x05
#define J   0xA8
#define L   0x0D
#define N   0xA7
#define O   0xB7
#define P   0x67
#define S   0xCB
#define U   0xAD
#define LED_OFF 0x00

#endif // MYLED_H
