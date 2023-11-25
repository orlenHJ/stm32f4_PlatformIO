/**@file	DM_J4310_motor.h
* @brief      达妙电机 头文件
* @details  	根据官方例程 主要包含达妙电机的底层运行 返回数据结构体
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
#ifndef DM_J4310_MOTOR_H
#define	DM_J4310_MOTOR_H

#include <stdint.h>
#include "can.h"

#define LIMIT_MIN_MAX(x,min,max) (x) = (((x)<=(min))?(min):(((x)>=(max))?(max):(x)))
#define CAN_ID 0x1
//float KP=0.0f;
//float KD=0.0f;//0.1

//float pos_cmd=0.0f,vel_cmd=0.0f,torque_cmd=0.0f;
#define CMD_MOTOR_MODE      0x01
#define CMD_RESET_MODE      0x02
#define CMD_ZERO_POSITION   0x03


#define P_MIN -95.5f    // Radians
#define P_MAX 95.5f        
#define V_MIN -45.0f    // Rad/s
#define V_MAX 45.0f
#define KP_MIN 0.0f     // N-m/rad
#define KP_MAX 500.0f
#define KD_MIN 0.0f     // N-m/rad/s
#define KD_MAX 5.0f
#define T_MIN -18.0f
#define T_MAX 18.0f




typedef struct{
	int16_t	 	speed_rpm;
    float  	real_current;
    int16_t  	given_current;
    uint8_t  	hall;
	uint16_t 	angle;				//abs angle range:[0,8191]
	uint16_t 	last_angle;	//abs angle range:[0,8191]
	uint16_t	offset_angle;
	int32_t		round_cnt;
	int32_t		total_angle;
//	u8			buf_idx;
//	u16			angle_buf[FILTER_BUF_LEN];
//	u16			fited_angle;
//	u32			msg_cnt;
}moto_measure_t;






void start_motor_DM_MIT(CAN_HandleTypeDef* hcan,uint16_t id);
void ctrl_motor_DM_MIT(CAN_HandleTypeDef* hcan,uint16_t id, float _pos, float _vel, float _KP, float _KD, float _torq);
int float_to_uint(float x, float x_min, float x_max, int bits);  
float uint_to_float(int x_int, float x_min, float x_max, int bits);
void ctrl_motor_DM_Pos(CAN_HandleTypeDef* hcan,uint16_t id, float _pos, float _vel);
void MotorControl_Start(void);
void CanComm_ControlCmd(uint8_t cmd);
static void ZeroPosition(void);
static void CanTransmit(uint8_t *buf, uint8_t len);
void CanComm_SendControlPara(float f_p, float f_v, float f_kp, float f_kd, float f_t);

#endif
























