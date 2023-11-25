/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    can.c
  * @brief   This file provides code for the configuration
  *          of the CAN instances.
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
/* Includes ------------------------------------------------------------------*/
#include "can.h"

/* USER CODE BEGIN 0 */

DJI_motor_data Motor_Data[2][8]; //电机数据结构体数组
uint8_t motor_init_flag=0;//初始化标识符
uint8_t turn[2][8]={0}; //偏移量初始化标识符，用于偏移量只记录一次，防止多余计算
int angle_offset[2][8] = {0};//电机编码偏移量






void CAN_Filter_Init(CAN_HandleTypeDef *hcan)
{
	CAN_FilterTypeDef FilterConfig;
	FilterConfig.FilterBank=14;
	FilterConfig.FilterMode=CAN_FILTERMODE_IDMASK;
	FilterConfig.FilterScale=CAN_FILTERSCALE_32BIT;
	FilterConfig.FilterIdHigh=0x0000;
	FilterConfig.FilterIdLow=0x0000;
	FilterConfig.FilterMaskIdHigh=0x0000;
	FilterConfig.FilterMaskIdLow=0x0000;
	FilterConfig.FilterFIFOAssignment=CAN_FilterFIFO0;
	FilterConfig.FilterActivation=CAN_FILTER_ENABLE;
	FilterConfig.SlaveStartFilterBank=0;
	HAL_CAN_ConfigFilter(hcan,&FilterConfig);
	HAL_CAN_Start(hcan);
}

void set_current_0x200(CAN_HandleTypeDef *hcan,int16_t current1,int16_t current2,int16_t current3,int16_t current4)
{
	uint8_t data[8];
	CAN_TxHeaderTypeDef CAN_TX;
	CAN_TX.DLC=8;
	CAN_TX.IDE=CAN_ID_STD;
	CAN_TX.RTR=CAN_RTR_DATA;
	CAN_TX.StdId=0x200;

	data[0]=current1>>8;
	data[1]=current1;
	data[2]=current2>>8;
	data[3]=current2;
	data[4]=current3>>8;
	data[5]=current3;
	data[6]=current4>>8;
	data[7]=current4;
	HAL_CAN_AddTxMessage(hcan,&CAN_TX,data,(uint32_t* )CAN_TX_MAILBOX0);
}

void set_current_0x1FF(CAN_HandleTypeDef *hcan,int16_t current1,int16_t current2,int16_t current3,int16_t current4)
{
	uint8_t data[8];
	CAN_TxHeaderTypeDef CAN_TX;
	CAN_TX.DLC=8;
	CAN_TX.IDE=CAN_ID_STD;
	CAN_TX.RTR=CAN_RTR_DATA;
	CAN_TX.StdId=0x1FF;

	data[0]=current1>>8;
	data[1]=current1;
	data[2]=current2>>8;
	data[3]=current2;
	data[4]=current3>>8;
	data[5]=current3;
	data[6]=current4>>8;
	data[7]=current4;
	HAL_CAN_AddTxMessage(hcan,&CAN_TX,data,(uint32_t* )CAN_TX_MAILBOX0);
}


void motor_data_init(void)
{
	int i,j;
	for(j=0;j<2;j++)
	{
	for(i=0;i<8;i++)
		{
			Motor_Data[j][i].round=0;
			Motor_Data[j][i].total_angle=0;
		}
	}
	motor_init_flag=1;
}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	if(motor_init_flag==1)
	{
	UNUSED(hcan);
	uint8_t rx_data[8];
	CAN_RxHeaderTypeDef RxMsg;
	HAL_CAN_GetRxMessage(hcan,CAN_RX_FIFO0,&RxMsg,rx_data);
	if(hcan==&hcan1)
	{	
		switch(RxMsg.StdId)
		{
			case 0x201:
			case 0x202:
			case 0x203:
			case 0x204:
		  case 0x205:
		  case 0x206:
		  case 0x207:
		  case 0x208: 
			{

				static uint8_t ID =0; //get motor id
				ID = RxMsg.StdId - 0x201;
				if(turn[_CAN1][ID]==0)
				{
				angle_offset[_CAN1][ID] = ((rx_data[0] << 8) | rx_data[1]);
				Motor_Data[_CAN1][ID].init_angle = angle_offset[_CAN1][ID];
				turn[_CAN1][ID]++;
				}
				Motor_Data[_CAN1][ID].last_angle = Motor_Data[_CAN1][ID].init_angle;				
				Motor_Data[_CAN1][ID].init_angle = ((rx_data[0] << 8) | rx_data[1]);
				if (Motor_Data[_CAN1][ID].init_angle - Motor_Data[_CAN1][ID].last_angle < -4096)
					{
						Motor_Data[_CAN1][ID].round++;
					}
				else if (Motor_Data[_CAN1][ID].init_angle - Motor_Data[_CAN1][ID].last_angle > 4096)
					{
						Motor_Data[_CAN1][ID].round--;
					}
				Motor_Data[_CAN1][ID].total_angle = Motor_Data[_CAN1][ID].round * 8192 + Motor_Data[_CAN1][ID].init_angle - angle_offset[_CAN1][ID];
				if((Motor_Data[_CAN1][ID].total_angle>=-100)&&(Motor_Data[_CAN1][ID].total_angle<=100))	Motor_Data[_CAN1][ID].total_angle=0;	
				Motor_Data[_CAN1][ID].speed = ((rx_data[2] << 8) | rx_data[3]);
				Motor_Data[_CAN1][ID].current = ((rx_data[4] << 8) | rx_data[5]);
				if(Motor_Data[_CAN1][ID].current<=200&&Motor_Data[_CAN1][ID].current>=-200)
					Motor_Data[_CAN1][ID].current=0;
				Motor_Data[_CAN1][ID].temprature = rx_data[6]; 
				break;
			}
			default:
				break;
		}
	}
	if(hcan==&hcan2)
	{
		switch(RxMsg.StdId)
		{
			case 0x201:
			case 0x202:
			case 0x203:
			case 0x204:
		  case 0x205:
		  case 0x206:
		  case 0x207:
		  case 0x208:	
			{
				static uint8_t ID =0; //get motor id
				ID = RxMsg.StdId - 0x201;
				if(turn[_CAN2][ID]==0)
				{
					angle_offset[_CAN2][ID] = ((rx_data[0] << 8) | rx_data[1]);
					Motor_Data[_CAN2][ID].init_angle = angle_offset[_CAN2][ID];
					turn[_CAN2][ID]++;
				}
				Motor_Data[_CAN2][ID].last_angle = Motor_Data[_CAN2][ID].init_angle;
				Motor_Data[_CAN2][ID].init_angle = ((rx_data[0] << 8) | rx_data[1]);
				if (Motor_Data[_CAN2][ID].init_angle - Motor_Data[_CAN2][ID].last_angle < -4096)
					{
						Motor_Data[_CAN2][ID].round++;
					}
				else if (Motor_Data[_CAN2][ID].init_angle - Motor_Data[_CAN2][ID].last_angle > 4096)
					{
						Motor_Data[_CAN2][ID].round--;
					}
				Motor_Data[_CAN2][ID].total_angle= Motor_Data[_CAN2][ID].round * 8192 + Motor_Data[_CAN2][ID].init_angle - angle_offset[_CAN2][ID];
				if((Motor_Data[_CAN2][ID].total_angle>=-100)&&(Motor_Data[_CAN2][ID].total_angle<=100))	Motor_Data[_CAN2][ID].total_angle=0;	
				Motor_Data[_CAN2][ID].speed = ((rx_data[2] << 8) | rx_data[3]);
				Motor_Data[_CAN2][ID].current = ((rx_data[4] << 8) | rx_data[5]);
				if(Motor_Data[_CAN2][ID].current<=200&&Motor_Data[1][ID].current>=-200)
					Motor_Data[_CAN2][ID].current=0;
				Motor_Data[_CAN2][ID].temprature = rx_data[6]; 
				break;
			}
			default:
				break;
		}			
	}
	}
}














/* USER CODE END 0 */

CAN_HandleTypeDef hcan1;
CAN_HandleTypeDef hcan2;

/* CAN1 init function */
void MX_CAN1_Init(void)
{

  /* USER CODE BEGIN CAN1_Init 0 */

  /* USER CODE END CAN1_Init 0 */

  /* USER CODE BEGIN CAN1_Init 1 */

  /* USER CODE END CAN1_Init 1 */
  hcan1.Instance = CAN1;
  hcan1.Init.Prescaler = 3;
  hcan1.Init.Mode = CAN_MODE_NORMAL;
  hcan1.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan1.Init.TimeSeg1 = CAN_BS1_7TQ;
  hcan1.Init.TimeSeg2 = CAN_BS2_6TQ;
  hcan1.Init.TimeTriggeredMode = DISABLE;
  hcan1.Init.AutoBusOff = DISABLE;
  hcan1.Init.AutoWakeUp = DISABLE;
  hcan1.Init.AutoRetransmission = DISABLE;
  hcan1.Init.ReceiveFifoLocked = DISABLE;
  hcan1.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN1_Init 2 */

  /* USER CODE END CAN1_Init 2 */

}
/* CAN2 init function */
void MX_CAN2_Init(void)
{

  /* USER CODE BEGIN CAN2_Init 0 */

  /* USER CODE END CAN2_Init 0 */

  /* USER CODE BEGIN CAN2_Init 1 */

  /* USER CODE END CAN2_Init 1 */
  hcan2.Instance = CAN2;
  hcan2.Init.Prescaler = 3;
  hcan2.Init.Mode = CAN_MODE_NORMAL;
  hcan2.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan2.Init.TimeSeg1 = CAN_BS1_7TQ;
  hcan2.Init.TimeSeg2 = CAN_BS2_6TQ;
  hcan2.Init.TimeTriggeredMode = DISABLE;
  hcan2.Init.AutoBusOff = DISABLE;
  hcan2.Init.AutoWakeUp = DISABLE;
  hcan2.Init.AutoRetransmission = DISABLE;
  hcan2.Init.ReceiveFifoLocked = DISABLE;
  hcan2.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN2_Init 2 */

  /* USER CODE END CAN2_Init 2 */

}

static uint32_t HAL_RCC_CAN1_CLK_ENABLED=0;

void HAL_CAN_MspInit(CAN_HandleTypeDef* canHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(canHandle->Instance==CAN1)
  {
  /* USER CODE BEGIN CAN1_MspInit 0 */

  /* USER CODE END CAN1_MspInit 0 */
    /* CAN1 clock enable */
    HAL_RCC_CAN1_CLK_ENABLED++;
    if(HAL_RCC_CAN1_CLK_ENABLED==1){
      __HAL_RCC_CAN1_CLK_ENABLE();
    }

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**CAN1 GPIO Configuration
    PA11     ------> CAN1_RX
    PA12     ------> CAN1_TX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_11|GPIO_PIN_12;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_CAN1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* CAN1 interrupt Init */
    HAL_NVIC_SetPriority(CAN1_RX0_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(CAN1_RX0_IRQn);
  /* USER CODE BEGIN CAN1_MspInit 1 */

  /* USER CODE END CAN1_MspInit 1 */
  }
  else if(canHandle->Instance==CAN2)
  {
  /* USER CODE BEGIN CAN2_MspInit 0 */

  /* USER CODE END CAN2_MspInit 0 */
    /* CAN2 clock enable */
    __HAL_RCC_CAN2_CLK_ENABLE();
    HAL_RCC_CAN1_CLK_ENABLED++;
    if(HAL_RCC_CAN1_CLK_ENABLED==1){
      __HAL_RCC_CAN1_CLK_ENABLE();
    }

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**CAN2 GPIO Configuration
    PB12     ------> CAN2_RX
    PB13     ------> CAN2_TX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_CAN2;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* CAN2 interrupt Init */
    HAL_NVIC_SetPriority(CAN2_RX0_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(CAN2_RX0_IRQn);
  /* USER CODE BEGIN CAN2_MspInit 1 */

  /* USER CODE END CAN2_MspInit 1 */
  }
}

void HAL_CAN_MspDeInit(CAN_HandleTypeDef* canHandle)
{

  if(canHandle->Instance==CAN1)
  {
  /* USER CODE BEGIN CAN1_MspDeInit 0 */

  /* USER CODE END CAN1_MspDeInit 0 */
    /* Peripheral clock disable */
    HAL_RCC_CAN1_CLK_ENABLED--;
    if(HAL_RCC_CAN1_CLK_ENABLED==0){
      __HAL_RCC_CAN1_CLK_DISABLE();
    }

    /**CAN1 GPIO Configuration
    PA11     ------> CAN1_RX
    PA12     ------> CAN1_TX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_11|GPIO_PIN_12);

    /* CAN1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(CAN1_RX0_IRQn);
  /* USER CODE BEGIN CAN1_MspDeInit 1 */

  /* USER CODE END CAN1_MspDeInit 1 */
  }
  else if(canHandle->Instance==CAN2)
  {
  /* USER CODE BEGIN CAN2_MspDeInit 0 */

  /* USER CODE END CAN2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_CAN2_CLK_DISABLE();
    HAL_RCC_CAN1_CLK_ENABLED--;
    if(HAL_RCC_CAN1_CLK_ENABLED==0){
      __HAL_RCC_CAN1_CLK_DISABLE();
    }

    /**CAN2 GPIO Configuration
    PB12     ------> CAN2_RX
    PB13     ------> CAN2_TX
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_12|GPIO_PIN_13);

    /* CAN2 interrupt Deinit */
    HAL_NVIC_DisableIRQ(CAN2_RX0_IRQn);
  /* USER CODE BEGIN CAN2_MspDeInit 1 */

  /* USER CODE END CAN2_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
