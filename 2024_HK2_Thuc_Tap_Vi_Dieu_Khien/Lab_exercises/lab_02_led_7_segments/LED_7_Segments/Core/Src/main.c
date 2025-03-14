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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "myLED.h"
#include <stdio.h>

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */


#define P_ACTIVE GPIO_PIN_RESET  // Assuming active-low buttons

int main(void)
{
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();

    uint32_t num_display = 12345;  // Start value
    uint8_t auto_increment = 0;    // Flag for auto-increment mode
    uint32_t last_increment_time = 0;  // Stores the last time auto-increment happened

    while (1)
    {
        // Convert num_display to a string
        char str_num[6];  // 5 digits + null terminator
        sprintf(str_num, "%05lu", num_display);  // Convert number to string with 5 digits

        // Display the number on the 7-segment display
        LED_putstring((uint8_t *)str_num);

        // Read button states
        uint8_t P1 = HAL_GPIO_ReadPin(P1_GPIO_Port, P1_Pin);
        uint8_t P2 = HAL_GPIO_ReadPin(P2_GPIO_Port, P2_Pin);
        uint8_t P3 = HAL_GPIO_ReadPin(P3_GPIO_Port, P3_Pin);
        uint8_t P4 = HAL_GPIO_ReadPin(P4_GPIO_Port, P4_Pin);

        // P1: Increment number
        if (P1 == P_ACTIVE) {
            num_display++;
            while (HAL_GPIO_ReadPin(P1_GPIO_Port, P1_Pin) == P_ACTIVE); // Wait for button release
        }

        // P2: Decrement number
        if (P2 == P_ACTIVE) {
            num_display--;
            while (HAL_GPIO_ReadPin(P2_GPIO_Port, P2_Pin) == P_ACTIVE); // Wait for button release
        }

        // P3: Reset to 12345
        if (P3 == P_ACTIVE) {
            num_display = 12345;
            while (HAL_GPIO_ReadPin(P3_GPIO_Port, P3_Pin) == P_ACTIVE); // Wait for button release
        }

        // P4: Start/stop auto-increment mode
        if (P4 == P_ACTIVE) {
            auto_increment = !auto_increment;  // Toggle auto-increment mode
            while (HAL_GPIO_ReadPin(P4_GPIO_Port, P4_Pin) == P_ACTIVE); // Wait for button release
        }

        // Auto-increment mode (non-blocking)
        if (auto_increment && num_display < 99999) {
            if (HAL_GetTick() - last_increment_time >= 1000) { // Check if 1 second has passed
                num_display++;
                last_increment_time = HAL_GetTick(); // Reset timer
            }
        }

        // Prevent overflow (max 99999)
        if (num_display > 99999) {
            num_display = 99999;
        }
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
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, RCL_Pin|RCK_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, SCK_Pin|MOSI_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : RCL_Pin RCK_Pin */
  GPIO_InitStruct.Pin = RCL_Pin|RCK_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : P4_Pin P3_Pin P2_Pin P1_Pin */
  GPIO_InitStruct.Pin = P4_Pin|P3_Pin|P2_Pin|P1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : SCK_Pin MOSI_Pin */
  GPIO_InitStruct.Pin = SCK_Pin|MOSI_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

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
