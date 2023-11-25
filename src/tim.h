/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    tim.h
  * @brief   This file contains all the function prototypes for
  *          the tim.c file
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
#ifndef __TIM_H__
#define __TIM_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern TIM_HandleTypeDef htim14;

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void MX_TIM14_Init(void);

/* USER CODE BEGIN Prototypes */





typedef struct _rate_t
{
    uint8_t  dr16_rate; /*< 遥控器接收机数据频率 */
		float    HI216_Value; /*陀螺仪数据频率*/
}RATE_T;

typedef struct _obser_t
{
    RATE_T Tx;
    RATE_T Rx;
}OBSER_T;

OBSER_T* getObser(void);




/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __TIM_H__ */

