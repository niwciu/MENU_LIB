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
#include "stm32g0xx_ll_rcc.h"
#include "stm32g0xx_ll_bus.h"
#include "stm32g0xx_ll_system.h"
#include "stm32g0xx_ll_exti.h"
#include "stm32g0xx_ll_cortex.h"
#include "stm32g0xx_ll_utils.h"
#include "stm32g0xx_ll_pwr.h"
#include "stm32g0xx_ll_dma.h"
#include "stm32g0xx_ll_gpio.h"

#if defined(USE_FULL_ASSERT)
#include "stm32_assert.h"
#endif /* USE_FULL_ASSERT */

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
void MX_GPIO_Init(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define ESC_Pin LL_GPIO_PIN_1
#define ESC_GPIO_Port GPIOB
#define DOWN_Pin LL_GPIO_PIN_2
#define DOWN_GPIO_Port GPIOB
#define UP_Pin LL_GPIO_PIN_10
#define UP_GPIO_Port GPIOB
#define ENTER_Pin LL_GPIO_PIN_11
#define ENTER_GPIO_Port GPIOB
#define FUNC_Pin LL_GPIO_PIN_12
#define FUNC_GPIO_Port GPIOB
#define LCD_RS_Pin LL_GPIO_PIN_13
#define LCD_RS_GPIO_Port GPIOB
#define LCD_RW_Pin LL_GPIO_PIN_14
#define LCD_RW_GPIO_Port GPIOB
#define LCD_E_Pin LL_GPIO_PIN_15
#define LCD_E_GPIO_Port GPIOB
#define BUZZER_Pin LL_GPIO_PIN_8
#define BUZZER_GPIO_Port GPIOA
#define LCD_BCKL_Pin LL_GPIO_PIN_7
#define LCD_BCKL_GPIO_Port GPIOC
#define LCD_DB4_Pin LL_GPIO_PIN_0
#define LCD_DB4_GPIO_Port GPIOD
#define LCD_DB5_Pin LL_GPIO_PIN_1
#define LCD_DB5_GPIO_Port GPIOD
#define LCD_DB6_Pin LL_GPIO_PIN_2
#define LCD_DB6_GPIO_Port GPIOD
#define LCD_DB7_Pin LL_GPIO_PIN_3
#define LCD_DB7_GPIO_Port GPIOD

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
