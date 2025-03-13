/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "myGPIO.h"
#include <stdbool.h> // Include for boolean type

void SystemClock_Config(void);
static void MX_GPIO_Init(void);

/* Global Variables */
uint8_t stateP1 = 0;	
uint8_t stateP2 = 0;
uint8_t stateP3 = 0;	
uint8_t stateP4 = 0;
uint16_t DelayCnt = 0;
uint8_t stateSW = 0;

/**
  * @brief  Handles button press behavior for P1 and P2
  */
void Baitap3_6(uint8_t P1_Status, uint8_t P2_Status, uint8_t P3_Status, uint8_t P4_Status) {
    // P1: 需n D1 s醤g/t?t chu k? 2s, D2 lu鬾 t?t
    bool buttonPressed = (P1_Status == P_ACTIVE);
    switch (stateP1) {
        case 0:
            Light_cmd(D1, D_OFF);
            Light_cmd(D2, D_OFF);
            if (buttonPressed) {
                stateP1 = 1;
                while (PushButton_read(P1) == P_ACTIVE) HAL_Delay(10); // Ch? nh? n鷗
            }
            break;

        case 1:
            if (DelayCnt < 1000) {
                Light_cmd(D1, D_ON);
                HAL_Delay(20);
                DelayCnt += 20;
            } else if (DelayCnt < 2000) {
                Light_cmd(D1, D_OFF);
                HAL_Delay(20);
                DelayCnt += 20;
            } else {
                DelayCnt = 0;
            }
            if (buttonPressed) {
                stateP1 = 0;
                while (PushButton_read(P1) == P_ACTIVE) HAL_Delay(10);
            }
            break;
    }

    // P2: 需n D2 s醤g/t?t chu k? 2s, D1 lu鬾 t?t
    buttonPressed = (P2_Status == P_ACTIVE);
    switch (stateP2) {
        case 0:
            Light_cmd(D1, D_OFF);
            Light_cmd(D2, D_OFF);
            if (buttonPressed) {
                stateP2 = 1;
                while (PushButton_read(P2) == P_ACTIVE) HAL_Delay(10);
            }
            break;

        case 1:
            if (DelayCnt < 1000) {
                Light_cmd(D2, D_ON);
                HAL_Delay(20);
                DelayCnt += 20;
            } else if (DelayCnt < 2000) {
                Light_cmd(D2, D_OFF);
                HAL_Delay(20);
                DelayCnt += 20;
            } else {
                DelayCnt = 0;
            }
            if (buttonPressed) {
                stateP2 = 0;
                while (PushButton_read(P2) == P_ACTIVE) HAL_Delay(10);
            }
            break;
    }

    // P3: 需n D1 & D2 s醤g t?t **so le** chu k? 2s
    buttonPressed = (P3_Status == P_ACTIVE);
    switch (stateP3) {
        case 0:
            Light_cmd(D1, D_OFF);
            Light_cmd(D2, D_OFF);
            if (buttonPressed) {
                stateP3 = 1;
                while (PushButton_read(P3) == P_ACTIVE) HAL_Delay(10);
            }
            break;

        case 1:
            if (DelayCnt < 1000) {
                Light_cmd(D1, D_ON);
                Light_cmd(D2, D_OFF);
                HAL_Delay(20);
                DelayCnt += 20;
            } else if (DelayCnt < 2000) {
                Light_cmd(D1, D_OFF);
                Light_cmd(D2, D_ON);
                HAL_Delay(20);
                DelayCnt += 20;
            } else {
                DelayCnt = 0;
            }
            if (buttonPressed) {
                stateP3 = 0;
                while (PushButton_read(P3) == P_ACTIVE) HAL_Delay(10);
            }
            break;
    }

    // P4: 需n D1 & D2 s醤g t?t **c鵱g l鷆** chu k? 2s
    buttonPressed = (P4_Status == P_ACTIVE);
    switch (stateP4) {
        case 0:
            Light_cmd(D1, D_OFF);
            Light_cmd(D2, D_OFF);
            if (buttonPressed) {
                stateP4 = 1;
                while (PushButton_read(P4) == P_ACTIVE) HAL_Delay(10);
            }
            break;

        case 1:
            if (DelayCnt < 1000) {
                Light_cmd(D1, D_ON);
                Light_cmd(D2, D_ON);
                HAL_Delay(20);
                DelayCnt += 20;
            } else if (DelayCnt < 2000) {
                Light_cmd(D1, D_OFF);
                Light_cmd(D2, D_OFF);
                HAL_Delay(20);
                DelayCnt += 20;
            } else {
                DelayCnt = 0;
            }
            if (buttonPressed) {
                stateP4 = 0;
                while (PushButton_read(P4) == P_ACTIVE) HAL_Delay(10);
            }
            break;
    }
}


/**
  * @brief  The main application loop.
  */
int main(void)
{
    // Initialize HAL and system configuration
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();

    stateSW = 0;
    DelayCnt = 0; 

    while (1)
    {
        // Read button and switch status
        P1_STATUS = PushButton_read(P1);
        P2_STATUS = PushButton_read(P2);
				P3_STATUS = PushButton_read(P3);
        P4_STATUS = PushButton_read(P4);
        uint8_t SW_STATUS = Switch_read();

        // Execute button control logic
        Baitap3_6(P1_STATUS, P2_STATUS, P3_STATUS, P4_STATUS); 
    }
}




/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(D2_GPIO_Port, D2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(D1_GPIO_Port, D1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : SW_3_Pin */
  GPIO_InitStruct.Pin = SW_3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(SW_3_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : SW_2_Pin */
  GPIO_InitStruct.Pin = SW_2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(SW_2_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : SW_1_Pin P4_Pin P3_Pin P2_Pin
                           P1_Pin */
  GPIO_InitStruct.Pin = SW_1_Pin|P4_Pin|P3_Pin|P2_Pin
                          |P1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : D2_Pin */
  GPIO_InitStruct.Pin = D2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(D2_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : D1_Pin */
  GPIO_InitStruct.Pin = D1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(D1_GPIO_Port, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
