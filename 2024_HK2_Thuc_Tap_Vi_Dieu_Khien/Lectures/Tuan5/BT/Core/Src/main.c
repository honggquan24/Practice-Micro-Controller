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
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
		HAL_GPIO_WritePin(C_GPIO_Port, C_Pin, 1);

  while (1)
  {
				// LCD init
		HAL_Delay(100);\
		// RS RW D7 D6 D5 D4 = 0 0 0 0 1 1
		HAL_GPIO_WritePin(RS_GPIO_Port,RS_Pin,0);
		HAL_GPIO_WritePin(RW_GPIO_Port,RW_Pin,0);
		HAL_GPIO_WritePin(D7_GPIO_Port,D7_Pin,0);
		HAL_GPIO_WritePin(D6_GPIO_Port,D6_Pin,0);
		HAL_GPIO_WritePin(D5_GPIO_Port,D5_Pin,1);
		HAL_GPIO_WritePin(D4_GPIO_Port,D4_Pin,1);
		HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, 1);
		HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, 0);
		HAL_Delay(5);  // 4.1ms
		
		// RS RW D7 D6 D5 D4 = 0 0 0 0 1 1
		HAL_GPIO_WritePin(RS_GPIO_Port,RS_Pin,0);
		HAL_GPIO_WritePin(RW_GPIO_Port,RW_Pin,0);
		HAL_GPIO_WritePin(D7_GPIO_Port,D7_Pin,0);
		HAL_GPIO_WritePin(D6_GPIO_Port,D6_Pin,0);
		HAL_GPIO_WritePin(D5_GPIO_Port,D5_Pin,1);
		HAL_GPIO_WritePin(D4_GPIO_Port,D4_Pin,1);
		HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, 1);
		HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, 0);
		
		HAL_Delay(1);  // 100us
		
		// RS RW D7 D6 D5 D4 = 0 0 0 0 1 1
		HAL_GPIO_WritePin(RS_GPIO_Port,RS_Pin,0);
		HAL_GPIO_WritePin(RW_GPIO_Port,RW_Pin,0);
		HAL_GPIO_WritePin(D7_GPIO_Port,D7_Pin,0);
		HAL_GPIO_WritePin(D6_GPIO_Port,D6_Pin,0);
		HAL_GPIO_WritePin(D5_GPIO_Port,D5_Pin,1);
		HAL_GPIO_WritePin(D4_GPIO_Port,D4_Pin,1);
		HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, 1);
		HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, 0);
		
		// RS RW D7 D6 D5 D4 = 0 0 0 0 1 0
		HAL_GPIO_WritePin(RS_GPIO_Port,RS_Pin,0);
		HAL_GPIO_WritePin(RW_GPIO_Port,RW_Pin,0);
		HAL_GPIO_WritePin(D7_GPIO_Port,D7_Pin,0);
		HAL_GPIO_WritePin(D6_GPIO_Port,D6_Pin,0);
		HAL_GPIO_WritePin(D5_GPIO_Port,D5_Pin,1);
		HAL_GPIO_WritePin(D4_GPIO_Port,D4_Pin,0);
		HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, 1);
		HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, 0);
		HAL_Delay(1);
		
		// RS RW D7 D6 D5 D4 = 0 0 0 0 1 0
		HAL_GPIO_WritePin(RS_GPIO_Port,RS_Pin,0);
		HAL_GPIO_WritePin(RW_GPIO_Port,RW_Pin,0);
		HAL_GPIO_WritePin(D7_GPIO_Port,D7_Pin,0);
		HAL_GPIO_WritePin(D6_GPIO_Port,D6_Pin,0);
		HAL_GPIO_WritePin(D5_GPIO_Port,D5_Pin,1);
		HAL_GPIO_WritePin(D4_GPIO_Port,D4_Pin,0);
		HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, 1);
		HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, 0);
		
		// RS RW D7 D6 D5 D4 = 0 0 N F * *
		// N = 1 ( 2 lines LCD ; 5x8 )
		HAL_GPIO_WritePin(RS_GPIO_Port,RS_Pin,0);
		HAL_GPIO_WritePin(RW_GPIO_Port,RW_Pin,0);
		HAL_GPIO_WritePin(D7_GPIO_Port,D7_Pin,1);
		HAL_GPIO_WritePin(D6_GPIO_Port,D6_Pin,0);
		HAL_GPIO_WritePin(D5_GPIO_Port,D5_Pin,0);
		HAL_GPIO_WritePin(D4_GPIO_Port,D4_Pin,0);
		HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, 1);
		HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, 0);
		HAL_Delay(1);
		
		// RS RW D7 D6 D5 D4 = 0 0 0 0 0 0
		HAL_GPIO_WritePin(RS_GPIO_Port,RS_Pin,0);
		HAL_GPIO_WritePin(RW_GPIO_Port,RW_Pin,0);
		HAL_GPIO_WritePin(D7_GPIO_Port,D7_Pin,0); 
		HAL_GPIO_WritePin(D6_GPIO_Port,D6_Pin,0);
		HAL_GPIO_WritePin(D5_GPIO_Port,D5_Pin,0);
		HAL_GPIO_WritePin(D4_GPIO_Port,D4_Pin,0);
		HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, 1);
		HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, 0);
		
		// RS RW D7 D6 D5 D4 = 0 0 1 0 0 0
		HAL_GPIO_WritePin(RS_GPIO_Port,RS_Pin,0);
		HAL_GPIO_WritePin(RW_GPIO_Port,RW_Pin,0);
		HAL_GPIO_WritePin(D7_GPIO_Port,D7_Pin,1); 
		HAL_GPIO_WritePin(D6_GPIO_Port,D6_Pin,0);
		HAL_GPIO_WritePin(D5_GPIO_Port,D5_Pin,0);
		HAL_GPIO_WritePin(D4_GPIO_Port,D4_Pin,0);
		HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, 1);
		HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, 0);
		HAL_Delay(1);
		
		// RS RW D7 D6 D5 D4 = 0 0 0 0 0 0
		HAL_GPIO_WritePin(RS_GPIO_Port,RS_Pin,0);
		HAL_GPIO_WritePin(RW_GPIO_Port,RW_Pin,0);
		HAL_GPIO_WritePin(D7_GPIO_Port,D7_Pin,0); 
		HAL_GPIO_WritePin(D6_GPIO_Port,D6_Pin,0);
		HAL_GPIO_WritePin(D5_GPIO_Port,D5_Pin,0);
		HAL_GPIO_WritePin(D4_GPIO_Port,D4_Pin,0);
		HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, 1);
		HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, 0);
		HAL_Delay(1);
		
		// RS RW D7 D6 D5 D4 = 0 0 0 0 0 1
		HAL_GPIO_WritePin(RS_GPIO_Port,RS_Pin,0);
		HAL_GPIO_WritePin(RW_GPIO_Port,RW_Pin,0);
		HAL_GPIO_WritePin(D7_GPIO_Port,D7_Pin,0); 
		HAL_GPIO_WritePin(D6_GPIO_Port,D6_Pin,0);
		HAL_GPIO_WritePin(D5_GPIO_Port,D5_Pin,0);
		HAL_GPIO_WritePin(D4_GPIO_Port,D4_Pin,1);
		HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, 1);
		HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, 0);
		HAL_Delay(1);
		
		// RS RW D7 D6 D5 D4 = 0 0 0 0 0 0
		HAL_GPIO_WritePin(RS_GPIO_Port,RS_Pin,0);
		HAL_GPIO_WritePin(RW_GPIO_Port,RW_Pin,0);
		HAL_GPIO_WritePin(D7_GPIO_Port,D7_Pin,0); 
		HAL_GPIO_WritePin(D6_GPIO_Port,D6_Pin,0);
		HAL_GPIO_WritePin(D5_GPIO_Port,D5_Pin,0);
		HAL_GPIO_WritePin(D4_GPIO_Port,D4_Pin,0);
		HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, 1);
		HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, 0);
		
		// RS RW D7 D6 D5 D4 = 0 0 0 1 ID S
		// ID = 1: Increment by 1
		// S = 0 : No shift
		HAL_GPIO_WritePin(RS_GPIO_Port,RS_Pin,0);
		HAL_GPIO_WritePin(RW_GPIO_Port,RW_Pin,0);
		HAL_GPIO_WritePin(D7_GPIO_Port,D7_Pin,0); 
		HAL_GPIO_WritePin(D6_GPIO_Port,D6_Pin,1);
		HAL_GPIO_WritePin(D5_GPIO_Port,D5_Pin,1);
		HAL_GPIO_WritePin(D4_GPIO_Port,D4_Pin,0);
		HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, 1);
		HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, 0);
		HAL_Delay(1);
		// End of LCD init
		
		// RS RW D7 D6 D5 D4 D3 D2 D1 D0 
		// 0  0  0   0 0  0  1   D  C  B
		HAL_GPIO_WritePin(RS_GPIO_Port,RS_Pin,0);
		HAL_GPIO_WritePin(RW_GPIO_Port,RW_Pin,0);
		HAL_GPIO_WritePin(D7_GPIO_Port,D7_Pin,0); 
		HAL_GPIO_WritePin(D6_GPIO_Port,D6_Pin,0);
		HAL_GPIO_WritePin(D5_GPIO_Port,D5_Pin,0);
		HAL_GPIO_WritePin(D4_GPIO_Port,D4_Pin,0);
		HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, 1);
		HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, 0);
		
	  HAL_GPIO_WritePin(D7_GPIO_Port,D7_Pin,1); 
		HAL_GPIO_WritePin(D6_GPIO_Port,D6_Pin,1); //D
		HAL_GPIO_WritePin(D5_GPIO_Port,D5_Pin,1); //C
		HAL_GPIO_WritePin(D4_GPIO_Port,D4_Pin,1); //B
		HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, 1);
		HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, 0);
		HAL_Delay(1);
		
		// 'A' -> 0100 0001  (65) (RS = 1)
		// RS RW D7 D6 D5 D4 D3 D2 D1 D0 
		// 1  0  0   1  0  0  0  0  0  1
		HAL_GPIO_WritePin(RS_GPIO_Port,RS_Pin,1);
		HAL_GPIO_WritePin(RW_GPIO_Port,RW_Pin,0);
		HAL_GPIO_WritePin(D7_GPIO_Port,D7_Pin,1); 
		HAL_GPIO_WritePin(D6_GPIO_Port,D6_Pin,1);
		HAL_GPIO_WritePin(D5_GPIO_Port,D5_Pin,0);
		HAL_GPIO_WritePin(D4_GPIO_Port,D4_Pin,0);
		HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, 1);
		HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, 0);
		
	  HAL_GPIO_WritePin(D7_GPIO_Port,D7_Pin,0); 
		HAL_GPIO_WritePin(D6_GPIO_Port,D6_Pin,0); //D
		HAL_GPIO_WritePin(D5_GPIO_Port,D5_Pin,0); //C
		HAL_GPIO_WritePin(D4_GPIO_Port,D4_Pin,1); //B
		HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, 1);
		HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, 0);
		HAL_Delay(1);
		
		while(1);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
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
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, D4_Pin|D5_Pin|D6_Pin|D7_Pin
                          |C_Pin|E_Pin|RW_Pin|RS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : D4_Pin D5_Pin D6_Pin D7_Pin
                           C_Pin E_Pin RW_Pin RS_Pin */
  GPIO_InitStruct.Pin = D4_Pin|D5_Pin|D6_Pin|D7_Pin
                          |C_Pin|E_Pin|RW_Pin|RS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

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
