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

#define P_ACTIVE GPIO_PIN_RESET  // Active-low buttons

// Clock variables
uint8_t minutes = 12;   // Initial minute value
uint8_t seconds = 00;    // Initial second value
uint8_t auto_increment = 0;  // Flag for auto-increment mode (P1)
uint8_t auto_decrement = 0;  // Flag for auto-decrement mode (P2)
uint8_t adjust_mode = 0;     // 0 = Normal, 1 = Adjust Seconds, 2 = Adjust Minutes

uint32_t last_update_time = 0;   // Timer for updating time
uint32_t blink_time = 0;         // Timer for blinking effect
uint8_t blink_state = 1;         // State for LED blinking

void update_display(void) {
    char str[6]; // Format: "MM-SS"
    sprintf(str, "%02d-%02d", minutes, seconds); // Format the time string

    if (adjust_mode == 1) {  // Blinking mode for seconds
        if (HAL_GetTick() - blink_time >= 5) { // 0.5s toggle
            blink_time = HAL_GetTick();
            blink_state = !blink_state;
        }
        if (!blink_state) {
            str[3] = str[4] = ' ';  // Hide seconds
        }
    } else if (adjust_mode == 2) {  // Blinking mode for minutes
        if (HAL_GetTick() - blink_time >= 5) { // 0.5s toggle
            blink_time = HAL_GetTick();
            blink_state = !blink_state;
        }
        if (!blink_state) {
            str[0] = str[1] = ' ';  // Hide minutes
        }
    }

    LED_putstring((uint8_t *)str);
}

int main(void)
{
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();

    while (1)
    {
        // **Time Update Logic** (Every 1 second)
        if (HAL_GetTick() - last_update_time >= 1000) {  
            last_update_time = HAL_GetTick();

            if (auto_increment) {  // Auto count up mode
                seconds++;
                if (seconds > 59) {
                    seconds = 0;
                    minutes = (minutes + 1) % 60; // Rolls over at 59
                }
            }

            if (auto_decrement) {  // Auto count down mode
                if (seconds == 0) {
                    seconds = 59;
                    minutes = (minutes == 0) ? 59 : (minutes - 1);
                } else {
                    seconds--;
                }
            }

            update_display(); // Refresh display
        }

        // **Read Button Inputs**
        uint8_t P1 = HAL_GPIO_ReadPin(P1_GPIO_Port, P1_Pin);
        uint8_t P2 = HAL_GPIO_ReadPin(P2_GPIO_Port, P2_Pin);
        uint8_t P3 = HAL_GPIO_ReadPin(P3_GPIO_Port, P3_Pin);
        uint8_t P4 = HAL_GPIO_ReadPin(P4_GPIO_Port, P4_Pin);

        // **P1: Toggle Auto Increment Mode**
        if (P1 == P_ACTIVE) {
            auto_increment = !auto_increment;
            auto_decrement = 0;  // Stop decrement mode if active
            while (HAL_GPIO_ReadPin(P1_GPIO_Port, P1_Pin) == P_ACTIVE);
        }

        // **P2: Toggle Auto Decrement Mode**
        if (P2 == P_ACTIVE) {
            auto_decrement = !auto_decrement;
            auto_increment = 0;  // Stop increment mode if active
            while (HAL_GPIO_ReadPin(P2_GPIO_Port, P2_Pin) == P_ACTIVE);
        }

        // **P3: Toggle Adjust Mode (Cycle through 3 modes)**
        if (P3 == P_ACTIVE) {
            adjust_mode = (adjust_mode + 1) % 3;
            blink_time = HAL_GetTick(); // Reset blink timer
            blink_state = 1;            // Reset blink state
            while (HAL_GPIO_ReadPin(P3_GPIO_Port, P3_Pin) == P_ACTIVE);
        }

        // **P4: Adjust Seconds or Minutes**
        if (P4 == P_ACTIVE) {
            if (adjust_mode == 1) {  // Adjust seconds
                seconds = (seconds + 1) % 60;
            } else if (adjust_mode == 2) {  // Adjust minutes
                minutes = (minutes + 1) % 60;
            }
            update_display(); // Refresh after adjustment
            while (HAL_GPIO_ReadPin(P4_GPIO_Port, P4_Pin) == P_ACTIVE);
        }

        update_display(); // Continuous refresh
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
  GPIO_InitStruct.Pull = GPIO_PULLUP;
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
