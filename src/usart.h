/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    usart.h
  * @brief   This file contains all the function prototypes for
  *          the usart.c file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#ifndef __USART_H__
#define __USART_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern UART_HandleTypeDef huart4;

extern UART_HandleTypeDef huart1;

extern UART_HandleTypeDef huart2;

extern UART_HandleTypeDef huart3;

extern UART_HandleTypeDef huart6;

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void MX_UART4_Init(void);
void MX_USART1_UART_Init(void);
void MX_USART2_UART_Init(void);
void MX_USART3_UART_Init(void);
void MX_USART6_UART_Init(void);

/* USER CODE BEGIN Prototypes */
#define CMD_WARE 3 


extern uint8_t uart_tmp;
extern uint8_t uart3_dma_flag;
extern uint8_t uart3_idle_flag;
extern uint8_t uart3_m0_buf[1024];
extern uint8_t uart3_m1_buf[1024];
extern uint8_t uart3_tx_buf[120];
extern DMA_HandleTypeDef hdma_usart3_rx;

void UART3_JudgeStart(void);
uint8_t __HAL_DMA_GET_CURRMEMTAR(DMA_HandleTypeDef *hdma);
uint16_t __HAL_DMA_GET_CURRDATCOUT(DMA_HandleTypeDef *hdma);
void UART6_VisionStart(void);
void UART2_SendWave(uint8_t num, uint8_t bytes, ...);
void UART4_IMUStart(void);
void sendwave(uint8_t *wareaddr, uint32_t waresize);
void sendchars(uint8_t *buff, uint32_t len);













/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __USART_H__ */

