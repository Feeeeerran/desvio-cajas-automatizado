/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "stm32f1xx_hal.h"

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
#define stepper_in_1_Pin GPIO_PIN_3
#define stepper_in_1_GPIO_Port GPIOA
#define stepper_in_2_Pin GPIO_PIN_4
#define stepper_in_2_GPIO_Port GPIOA
#define stepper_in_3_Pin GPIO_PIN_5
#define stepper_in_3_GPIO_Port GPIOA
#define stepper_in_4_Pin GPIO_PIN_6
#define stepper_in_4_GPIO_Port GPIOA
#define sensor_1_Pin GPIO_PIN_7
#define sensor_1_GPIO_Port GPIOA
#define sensor_1_EXTI_IRQn EXTI9_5_IRQn
#define sensor_2_Pin GPIO_PIN_0
#define sensor_2_GPIO_Port GPIOB
#define sensor_2_EXTI_IRQn EXTI0_IRQn
#define motor_2_Pin GPIO_PIN_1
#define motor_2_GPIO_Port GPIOB
#define led_proceso_Pin GPIO_PIN_8
#define led_proceso_GPIO_Port GPIOA
#define led_alerta_Pin GPIO_PIN_11
#define led_alerta_GPIO_Port GPIOA
#define pulsador_parada_Pin GPIO_PIN_12
#define pulsador_parada_GPIO_Port GPIOA
#define pulsador_parada_EXTI_IRQn EXTI15_10_IRQn
#define LCD_D4_Pin GPIO_PIN_4
#define LCD_D4_GPIO_Port GPIOB
#define LCD_D5_Pin GPIO_PIN_5
#define LCD_D5_GPIO_Port GPIOB
#define LCD_D6_Pin GPIO_PIN_6
#define LCD_D6_GPIO_Port GPIOB
#define LCD_D7_Pin GPIO_PIN_7
#define LCD_D7_GPIO_Port GPIOB
#define LCD_EN_Pin GPIO_PIN_8
#define LCD_EN_GPIO_Port GPIOB
#define LCD_RS_Pin GPIO_PIN_9
#define LCD_RS_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
