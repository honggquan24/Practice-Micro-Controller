/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f2xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define RCL_Pin GPIO_PIN_2
#define RCL_GPIO_Port GPIOE
#define P4_Pin GPIO_PIN_8
#define P4_GPIO_Port GPIOE
#define P3_Pin GPIO_PIN_10
#define P3_GPIO_Port GPIOE
#define P2_Pin GPIO_PIN_12
#define P2_GPIO_Port GPIOE
#define P1_Pin GPIO_PIN_13
#define P1_GPIO_Port GPIOE
#define D2_Pin GPIO_PIN_9
#define D2_GPIO_Port GPIOC
#define D1_Pin GPIO_PIN_8
#define D1_GPIO_Port GPIOA
#define LCDD4_Pin GPIO_PIN_0
#define LCDD4_GPIO_Port GPIOD
#define LCDD5_Pin GPIO_PIN_1
#define LCDD5_GPIO_Port GPIOD
#define LCDD6_Pin GPIO_PIN_2
#define LCDD6_GPIO_Port GPIOD
#define LCDD7_Pin GPIO_PIN_3
#define LCDD7_GPIO_Port GPIOD
#define LCDLED_Pin GPIO_PIN_4
#define LCDLED_GPIO_Port GPIOD
#define LCDE_Pin GPIO_PIN_5
#define LCDE_GPIO_Port GPIOD
#define LCDRW_Pin GPIO_PIN_6
#define LCDRW_GPIO_Port GPIOD
#define LCDRS_Pin GPIO_PIN_7
#define LCDRS_GPIO_Port GPIOD
#define SCK_Pin GPIO_PIN_3
#define SCK_GPIO_Port GPIOB
#define MOSI_Pin GPIO_PIN_5
#define MOSI_GPIO_Port GPIOB
#define RCK_Pin GPIO_PIN_0
#define RCK_GPIO_Port GPIOE

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
