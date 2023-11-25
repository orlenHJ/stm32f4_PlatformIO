#ifndef CHASSIS_H
#define CHASSIS_H


#include "stdint.h"
#include "stddef.h"
#include "DJI_motor.h"
#include "pid.h"



		/* ���ӵ��̵��ͼ
				 ^					
			0|||||2
			|||||||
			|||||||
			1|||||3

		*/




typedef struct _MoveData_t
{
    int16_t y;
    int16_t x;
    int16_t yaw;
}MoveData_t;

typedef struct _Chassis_t
{
    DJI_motor_data M3508[4];
		DJI_motor_data M3508_LPf[4];
    MoveData_t MoveData;
}Chassis_t;


void Chassis_Speed_Control(void);
void Chassis_Speed_Reset(void);
void Chassis_Set_Current(void);
void Chassis_PidRun(void);
void Chassis_Process(void);
void Chassis_Rc_CMD(void);
void Chassis_Init(void);










#endif 

