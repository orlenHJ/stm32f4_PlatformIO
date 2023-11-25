/**@file	DJI_motor.c
* @brief      �󽮵������ �ļ�
* @details  	��Ҫ�����󽮵���ĵײ����� �������ݽṹ��
* @author      orlen
* @date        2023-7-19
* @version     V1.0
* @copyright    Copyright (c) 2050
**********************************************************************************
* @attention
* @par �޸���־:
* <table>
* <tr><th>Date        <th>Version 	 <th>Author    	<th>Description
* <tr><td>2023-7-19  	<td>1.0     	 <td>orlen  		<td>������ʼ�汾
* </table>
*
**********************************************************************************
*/
#ifndef DJI_MOTOR_H
#define	DJI_MOTOR_H
#include "stm32f4xx_hal.h"
#include "stdint.h"


/* ����������� */
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
