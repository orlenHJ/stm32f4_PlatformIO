/**@file	DJI_motor.c
* @brief      大疆电机控制 文件
* @details  	主要包含大疆电机的底层运行 返回数据结构体
* @author      orlen
* @date        2023-7-19
* @version     V1.0
* @copyright    Copyright (c) 2050
**********************************************************************************
* @attention
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version 	 <th>Author    	<th>Description
* <tr><td>2023-7-19  	<td>1.0     	 <td>orlen  		<td>创建初始版本
* </table>
*
**********************************************************************************
*/
#ifndef DJI_MOTOR_H
#define	DJI_MOTOR_H
#include "stm32f4xx_hal.h"
#include "stdint.h"


/* 电机接收数据 */
typedef struct
{
		float target_position; 
    int16_t target_speed;
    int16_t target_current;
		int16_t output;
	
		uint8_t  temprature;
		uint16_t init_angle;
		uint16_t last_angle;
		int32_t total_angle;
		int16_t round;
		int16_t  speed;
		int16_t  current;
	
}DJI_motor_data;



















#endif
