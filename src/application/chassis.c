
#include "chassis.h"
#include "DJI_motor.h"
#include "rc.h"
#include "ramp.h"
#include "tim.h"
#include "can.h"
#include "usart.h"

//#define CHASSIS_DEBUG

#define GAIN_X 5
#define CHASSIS_RAMP_SPEED 80
Chassis_t chassis = {0};

void Chassis_Rc_CMD(void)//ң��������
{
    switch (RC_CtrlData.rc.s1)
    {
        case S_UP:
            switch (RC_CtrlData.rc.s1)
            {
                case S_UP:
									/*S1S2 ˫�Ͽ��Ƶ���*/
                    chassis.MoveData.x = RC_CtrlData.rc.ch2;
										chassis.MoveData.y = RC_CtrlData.rc.ch3;
										chassis.MoveData.yaw = RC_CtrlData.rc.ch0;
                break;
                
                default:
                break;
            }
        break;
        
        case S_MID:
            
        break;
        
        case S_DOWN:
            
        break;
        
        default:
        break;
    }
}

void Chassis_Speed_Control(void)//�����ķ�ֽ���
{
//x y yaw
	
				chassis.M3508[0].target_speed=rampInt16(GAIN_X * ((chassis.MoveData.x)+(chassis.MoveData.y)+(chassis.MoveData.yaw)),   	\
															chassis.M3508[0].target_speed, CHASSIS_RAMP_SPEED);																							\
				chassis.M3508[1].target_speed=rampInt16(GAIN_X * (-(chassis.MoveData.x)+(chassis.MoveData.y)+(chassis.MoveData.yaw)),  	\
															chassis.M3508[1].target_speed, CHASSIS_RAMP_SPEED);																							\
				chassis.M3508[2].target_speed=rampInt16(GAIN_X * (-(chassis.MoveData.x)+(chassis.MoveData.y)-(chassis.MoveData.yaw)),		\
															chassis.M3508[2].target_speed, CHASSIS_RAMP_SPEED);																							\
				chassis.M3508[3].target_speed=rampInt16(GAIN_X * ((chassis.MoveData.x)+(chassis.MoveData.y)-(chassis.MoveData.yaw)),				\
															chassis.M3508[3].target_speed, CHASSIS_RAMP_SPEED);																							\
	

}



void Chassis_PidRun(void)//���̴���PID����
{
    uint8_t i;

    #ifdef CHASSIS_DEBUG
					static float debug_wave[8] = {0};
					for (i = 0; i < 4; i++)
						debug_wave[i] = chassis.M3508[i].target_speed;
					for (i = 3; i < 8; i++)
						debug_wave[i] = chassis.M3508_LPf[i].speed;
					
					sendwave((uint8_t *)debug_wave, sizeof(debug_wave));
		#endif


    for (i = 0; i < 4; i++)    
    {
        chassis.M3508_LPf[i].speed = 0.8 * chassis.M3508[i].speed + 0.2 * chassis.M3508_LPf[i].speed;
    }   
    for (i = 0; i < 4; i++)   
    {
        chassis.M3508[i].target_current = PID_Calc(&chassis_speed_pid, chassis.M3508_LPf[i].speed, chassis.M3508[i].target_speed);
    }
    for (i = 0; i < 4; i++)    
    {
        chassis.M3508_LPf[i].target_current = 0.8 * chassis.M3508[i].target_current + 0.2 * chassis.M3508_LPf[i].target_current;
    }
    
    for (i = 0; i < 4; i++)     
    {
        chassis.M3508_LPf[i].current = 0.8 * chassis.M3508[i].current + 0.2 * chassis.M3508_LPf[i].current;
    }
    
    for (i = 0; i < 4; i++)     
    {
        chassis.M3508[i].output = PID_Calc(&chassis_current_pid, chassis.M3508_LPf[i].current, chassis.M3508_LPf[i].target_current);
    }

}




void Chassis_Set_Current(void)
{
   // uint8_t i;
		OBSER_T Observer = *getObser(); 
    if(Observer.Tx.dr16_rate>15) 
    {
						set_current_0x200(&hcan2,chassis.M3508[0].output,chassis.M3508[1].output,chassis.M3508[2].output,chassis.M3508[3].output);
    }
    else
    {
        Chassis_Speed_Reset(); 
    }
}





void Chassis_Speed_Reset(void)
{
	uint8_t i = 0;
	for(i = 0;i<4;i++)
	{
		chassis.M3508[i].target_speed = 0;
		chassis.M3508[i].target_position = 0;
		chassis.M3508[i].target_current = 0;
		chassis.M3508[i].output = 0;
		chassis.M3508_LPf[i].target_speed = 0;
		chassis.M3508_LPf[i].target_position = 0;
		chassis.M3508_LPf[i].target_current = 0;
		chassis.M3508_LPf[i].output = 0;
		
	}	

	PID_clear(&chassis_speed_pid);
	PID_clear(&chassis_current_pid);
	
}

/*
	PID_Chasis_SpeedInit(16.0,2.14,4.0);
	PID_Chasis_CurrentInit(1,0.1,0.15);
*/
//Kp ,Ki , Kd
static float K_pid_chassis_speed[3] = {16.0, 2.14, 4.0};
static float K_pid_chassis_current[3] = {1, 0.1, 0.15};
void Chassis_Init(void)
{   
    PID_init(&chassis_speed_pid , PID_POSITION, K_pid_chassis_speed,12000, 3000);
    PID_init(&chassis_current_pid , PID_POSITION, K_pid_chassis_current,12000, 3000);

}





void Chassis_Process(void) //д������
{
	Chassis_Rc_CMD();
	Chassis_Speed_Control();
	Chassis_PidRun();
	Chassis_Set_Current();
	
}











