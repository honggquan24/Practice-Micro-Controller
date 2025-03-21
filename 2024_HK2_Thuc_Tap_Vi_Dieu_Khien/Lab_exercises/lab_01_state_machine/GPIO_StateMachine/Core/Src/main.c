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
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
TIM_HandleTypeDef htim1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */

uint32_t LastTick = 0;
uint8_t stateSW = 0;
uint16_t DelayCnt = 0;
uint32_t DelayCnt_SW = 0;
uint32_t DelayCnt_P1 = 0;

	
void Baitap3_3(uint8_t P1_STATUS, uint8_t P2_STATUS) {
    // ===== X? lý nút P1 (di?u khi?n dèn D1) =====
    switch (stateP1) {
        case 0:
            // Ban d?u: D1 t?t
            Light_cmd(D1, D_OFF);
            // Chuy?n ngay sang tr?ng thái 1
            stateP1 = 1;
            break;
        case 1:
            // Trong tr?ng thái 1: D1 v?n t?t
            Light_cmd(D1, D_OFF);
            // N?u nút P1 du?c nh?n (active low), chuy?n sang tr?ng thái 2
            if (P1_STATUS == P_ACTIVE) {
                stateP1 = 2;
            }
            break;
        case 2:
            // Trong tr?ng thái 2: D1 sáng
            Light_cmd(D1, D_ON);
            // Khi nút P1 du?c th? (active high), chuy?n sang tr?ng thái 3
            if (P1_STATUS == P_INACTIVE) {
                stateP1 = 3;
            }
            break;
        case 3:
            // Trong tr?ng thái 3: D1 v?n sáng
            Light_cmd(D1, D_ON);
            // N?u nh?n P1 l?n n?a, chuy?n sang tr?ng thái 4
            if (P1_STATUS == P_ACTIVE) {
                stateP1 = 4;
            }
            break;
        case 4:
            // Trong tr?ng thái 4: D1 t?t
            Light_cmd(D1, D_OFF);
            // Khi nút P1 du?c th?, reset state v? 0
            if (P1_STATUS == P_INACTIVE) {
                stateP1 = 0;
            }
            break;
        default:
            stateP1 = 0;
            break;
    }

    // ===== X? lý nút P2 (di?u khi?n dèn D2 v?i hi?u ?ng ch?p t?t) =====
    switch (stateP2) {
        case 0:
            // Ban d?u: D2 t?t
            Light_cmd(D2, D_OFF);
            if (P2_STATUS == P_ACTIVE) {
                stateP2 = 1;
            }
            break;
        case 1:
            // Ch? nh? nút P2
            Light_cmd(D2, D_OFF);
            if (P2_STATUS == P_INACTIVE) {
                stateP2 = 2;
                // Reset DelayCnt khi vào ch? d? ch?p
                DelayCnt = 0;
            }
            break;
        case 2:
            // Ch? d? ch?p: Ðèn D2 nh?p nháy v?i chu k? 2 giây
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
            // N?u nh?n P2, chuy?n sang tr?ng thái 3 (t?t ch? d? ch?p)
            if (P2_STATUS == P_ACTIVE) {
                stateP2 = 3;
            }
            break;
        case 3:
            // Trong tr?ng thái t?t ch? d? ch?p, D2 t?t
            Light_cmd(D2, D_OFF);
            // Khi nút P2 du?c th?, chuy?n v? tr?ng thái 0 (tr?ng thái ban d?u)
            if (P2_STATUS == P_INACTIVE) {
                stateP2 = 0;
            }
            break;
        default:
            stateP2 = 0;
            break;
    }
}


void Baitap3_4(uint16_t SW_STATUS, uint8_t P1_Status) {
    uint32_t currentTick = HAL_GetTick();
    
    /* --- X? lý công t?c SW (di?u khi?n dèn D1) --- */
    switch (stateSW) {
        case 0:
            // Ban d?u: D1 và D2 t?t
            Light_cmd(D1, D_OFF);
            Light_cmd(D2, D_OFF);
            if (SW_STATUS == SW1_ACTIVE)
                stateSW = SW1_ACTIVE;
            else if (SW_STATUS == SW2_ACTIVE)
                stateSW = SW2_ACTIVE;
            else if (SW_STATUS == SW3_ACTIVE)
                stateSW = SW3_ACTIVE;
            break;
            
        case SW1_ACTIVE:
            // Tr?ng thái SW1: D1 t?t
            Light_cmd(D1, D_OFF);
            if (SW_STATUS == SW2_ACTIVE) {
                stateSW = SW2_ACTIVE;
                DelayCnt_SW = currentTick;  // Reset b? d?m th?i gian cho ch? d? ch?p c?a D1
            }
            break;
            
        case SW2_ACTIVE:
            // Ch? d? ch?p D1: chu k? 2 giây (1s ON, 1s OFF)
            if (currentTick - DelayCnt_SW < 1000)
                Light_cmd(D1, D_ON);
            else if (currentTick - DelayCnt_SW < 2000)
                Light_cmd(D1, D_OFF);
            else {
                DelayCnt_SW = currentTick; // Reset l?i chu k?
            }
            if (SW_STATUS == SW3_ACTIVE)
                stateSW = SW3_ACTIVE;
            else if (SW_STATUS == SW1_ACTIVE)
                stateSW = SW1_ACTIVE;
            break;
            
        case SW3_ACTIVE:
            // SW3: D1 luôn sáng
            Light_cmd(D1, D_ON);
            if (SW_STATUS == SW2_ACTIVE)
                stateSW = SW2_ACTIVE;
            break;
            
        default:
            stateSW = 0;
            break;
    }
    
    /* --- X? lý nút P1 (di?u khi?n dèn D2) --- */
    switch (stateP1) {
        case 0:
            // Ban d?u: D2 t?t
            Light_cmd(D2, D_OFF);
            if (P1_Status == P_ACTIVE) {
                stateP1 = 1;
                while (PushButton_read(P1) == P_ACTIVE); // Ch? nút du?c th? (debounce)
            }
            break;
            
        case 1:
            // Tr?ng thái 1: D2 v?n t?t
            Light_cmd(D2, D_OFF);
            if (P1_Status == P_ACTIVE) {
                stateP1 = 2;
                DelayCnt_P1 = currentTick; // Reset b? d?m cho ch? d? ch?p c?a D2
                while (PushButton_read(P1) == P_ACTIVE);
            }
            break;
            
        case 2:
            // Ch? d? ch?p D2: chu k? 2 giây (1s ON, 1s OFF)
            if (currentTick - DelayCnt_P1 < 1000)
                Light_cmd(D2, D_ON);
            else if (currentTick - DelayCnt_P1 < 2000)
                Light_cmd(D2, D_OFF);
            else {
                DelayCnt_P1 = currentTick; // Reset l?i chu k?
            }
            if (P1_Status == P_ACTIVE) {
                stateP1 = 3;
                while (PushButton_read(P1) == P_ACTIVE);
            }
            break;
            
        case 3:
            // Tr?ng thái 3: D2 sáng liên t?c
            Light_cmd(D2, D_ON);
            if (P1_Status == P_ACTIVE) {
                stateP1 = 0;  // Reset v? tr?ng thái ban d?u
                while (PushButton_read(P1) == P_ACTIVE);
            }
            break;
            
        default:
            stateP1 = 0;
            break;
    }
}

	
void Baitap3_5(uint8_t P1_Status, uint8_t P2_Status) {	
    // Check if either button P1 or P2 is pressed (using bool for readability)
    bool buttonPressed = (PushButton_read(P1) == P_ACTIVE + PushButton_read(P2) == P_ACTIVE);

    switch (stateP1) {
        case 0:
            Light_cmd(D1, D_OFF);
            Light_cmd(D2, D_OFF);
            if (buttonPressed) {
                stateP1 = 1;
                // Wait for button release (Debounce)
                while ((uint8_t) (PushButton_read(P1) == P_ACTIVE + PushButton_read(P2) == P_ACTIVE)) {
                    HAL_Delay(10);
                }
            }
            break;

        case 1:
            Light_cmd(D1, D_OFF);
            if (buttonPressed) {
                stateP1 = 2;
                DelayCnt = 0;  // Reset delay counter for blinking mode
                // Wait for button release (Debounce)
                while ((uint8_t) (PushButton_read(P1) == P_ACTIVE + PushButton_read(P2) == P_ACTIVE)) {
                    HAL_Delay(10);
                }
            }
            break;

        case 2:
            if (DelayCnt < 1000) {
                Light_cmd(D1, D_ON);
                HAL_Delay(20);
                DelayCnt += 20;
            }
            else if (DelayCnt < 2000) {
                Light_cmd(D1, D_OFF);
                HAL_Delay(20);
                DelayCnt += 20;
            }
            else {
                DelayCnt = 0; // Reset the blink counter after a full cycle
            }

            if (buttonPressed) {
                stateP1 = 3;
                // Wait for button release (Debounce)
                while ((uint8_t) (PushButton_read(P1) == P_ACTIVE + PushButton_read(P2) == P_ACTIVE)) {
                    HAL_Delay(10);
                }
            }
            break;

        case 3:
            Light_cmd(D1, D_ON);
            if (buttonPressed) {
                stateP1 = 0;  // Reset to the beginning of the cycle
                // Wait for button release (Debounce)
                while ((uint8_t) (PushButton_read(P1) == P_ACTIVE + PushButton_read(P2) == P_ACTIVE)) {
                    HAL_Delay(10);
                }
            }
            break;

        default:
            stateP1 = 0; // Fallback safety case
            break;
    }
}




/* Global Variables */
uint8_t stateP1 = 0, stateP2 = 0, stateP3 = 0, stateP4 = 0;
uint32_t lastTick_P1 = 0, lastTick_P2 = 0, lastTick_P3 = 0, lastTick_P4 = 0;

/**
  * @brief  Handles button press behavior for P1, P2, P3, and P4
  */

void Baitap3_6(uint8_t P1_Status, uint8_t P2_Status, uint8_t P3_Status, uint8_t P4_Status) {
    // ========================= X? LÝ NÚT P1 =========================
    // Ði?u khi?n LED D1 ch?p t?t 2s, D2 luôn t?t
    bool buttonPressed = (P1_Status == P_ACTIVE);
    switch (stateP1) {
        case 0:  // Tr?ng thái ban d?u
            Light_cmd(D1, D_OFF);
            Light_cmd(D2, D_OFF);
            if (buttonPressed) {
                stateP1 = 1;
                while (PushButton_read(P1) == P_ACTIVE) HAL_Delay(10);  // Ch? nh? nút
            }
            break;

        case 1:  // Ch?p LED D1 chu k? 2s (1s ON, 1s OFF)
            if (DelayCnt < 1000) {
                Light_cmd(D1, D_ON);
            } else if (DelayCnt < 2000) {
                Light_cmd(D1, D_OFF);
            } else {
                DelayCnt = 0;
            }
            DelayCnt += 20;
            HAL_Delay(20);

            if (buttonPressed) {
                stateP1 = 0;
                while (PushButton_read(P1) == P_ACTIVE) HAL_Delay(10);
            }
            break;
    }

    // ========================= X? LÝ NÚT P2 =========================
    // Ði?u khi?n LED D2 ch?p t?t 2s, D1 luôn t?t
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
            } else if (DelayCnt < 2000) {
                Light_cmd(D2, D_OFF);
            } else {
                DelayCnt = 0;
            }
            DelayCnt += 20;
            HAL_Delay(20);

            if (buttonPressed) {
                stateP2 = 0;
                while (PushButton_read(P2) == P_ACTIVE) HAL_Delay(10);
            }
            break;
    }

    // ========================= X? LÝ NÚT P3 =========================
    // Ði?u khi?n D1/D2 ch?p t?t SO LE, m?i LED sáng 1s luân phiên
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
            } else if (DelayCnt < 2000) {
                Light_cmd(D1, D_OFF);
                Light_cmd(D2, D_ON);
            } else {
                DelayCnt = 0;
            }
            DelayCnt += 20;
            HAL_Delay(20);

            if (buttonPressed) {
                stateP3 = 0;
                while (PushButton_read(P3) == P_ACTIVE) HAL_Delay(10);
            }
            break;
    }

    // ========================= X? LÝ NÚT P4 =========================
    // Ði?u khi?n D1 và D2 cùng ch?p t?t, sáng cùng lúc
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
            } else if (DelayCnt < 2000) {
                Light_cmd(D1, D_OFF);
                Light_cmd(D2, D_OFF);
            } else {
                DelayCnt = 0;
            }
            DelayCnt += 20;
            HAL_Delay(20);

            if (buttonPressed) {
                stateP4 = 0;
                while (PushButton_read(P4) == P_ACTIVE) HAL_Delay(10);
            }
            break;
    }
}



int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();

	
	DelayCnt = HAL_GetTick(); // S? d?ng HAL_GetTick d? tránh s? d?ng delay blocking
	
  while (1)
  {
        P1_STATUS = PushButton_read(P1);
        P2_STATUS = PushButton_read(P2);
        P3_STATUS = PushButton_read(P3);
        P4_STATUS = PushButton_read(P4);

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
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 999;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 15999;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */

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
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, RCL_Pin|RCK_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(D2_GPIO_Port, D2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(D1_GPIO_Port, D1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, LCDD4_Pin|LCDD5_Pin|LCDD6_Pin|LCDD7_Pin
                          |LCDLED_Pin|LCDE_Pin|LCDRW_Pin|LCDRS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, SCK_Pin|MOSI_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : RCL_Pin RCK_Pin */
  GPIO_InitStruct.Pin = RCL_Pin|RCK_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : SW1_3_Pin */
  GPIO_InitStruct.Pin = SW1_3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(SW1_3_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : SW1_2_Pin */
  GPIO_InitStruct.Pin = SW1_2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(SW1_2_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : SW1_1_Pin P4_Pin P3_Pin P2_Pin
                           P1_Pin */
  GPIO_InitStruct.Pin = SW1_1_Pin|P4_Pin|P3_Pin|P2_Pin
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

  /*Configure GPIO pins : LCDD4_Pin LCDD5_Pin LCDD6_Pin LCDD7_Pin
                           LCDLED_Pin LCDE_Pin LCDRW_Pin LCDRS_Pin */
  GPIO_InitStruct.Pin = LCDD4_Pin|LCDD5_Pin|LCDD6_Pin|LCDD7_Pin
                          |LCDLED_Pin|LCDE_Pin|LCDRW_Pin|LCDRS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

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
