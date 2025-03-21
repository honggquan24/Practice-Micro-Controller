#ifndef MYGPIO_H
#define MYGPIO_H

#include "main.h"
#include <stdint.h>  

// �?nh nghia tr?ng th�i LED
#define D_ON  GPIO_PIN_RESET  // ��n b?t (0)
#define D_OFF GPIO_PIN_SET    // ��n t?t (1)

// �?nh nghia tr?ng th�i n�t nh?n
#define P_ACTIVE   GPIO_PIN_RESET // N�t nh?n du?c nh?n
#define P_INACTIVE GPIO_PIN_SET   // N�t nh?n kh�ng du?c nh?n

// �?nh nghia LED
#define D1 1
#define D2 2

// �?nh nghia tr?ng th�i c�ng t?c g?t
#define SW_ON       GPIO_PIN_RESET
#define SW_INACTIVE GPIO_PIN_SET  

#define SW1_ACTIVE  1
#define SW2_ACTIVE  2
#define SW3_ACTIVE  3

// �?nh nghia n�t nh?n
#define P1 1
#define P2 2
#define P3 3
#define P4 4

// Bi?n tr?ng th�i to�n c?c (extern d? tr�nh l?i multiple definition)
extern uint8_t stateSW;
extern uint8_t stateP1;
extern uint8_t stateP2;
extern uint16_t DelayCnt;

extern GPIO_PinState P1_STATUS;
extern GPIO_PinState P2_STATUS;
extern GPIO_PinState P3_STATUS;
extern GPIO_PinState P4_STATUS;

// Nguy�n m?u h�m di?u khi?n GPIO
void Light_cmd(uint8_t d, uint8_t status);
uint8_t PushButton_read(uint8_t p); 
uint8_t Switch_read(void);
void Baitap3_3(uint8_t P1_STATUS, uint8_t P2_STATUS);
void Baitap3_4(uint16_t SW_STATUS, uint8_t P1_Status);
void Baitap3_5(uint8_t P1_Status, uint8_t P2_Status);

#endif // MYGPIO_H
