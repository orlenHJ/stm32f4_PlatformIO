
#include "imu_math.h"
#include "imu_data_decode.h"
#include "imu_packet.h"
#include "math.h"
#include "usart.h"


GIMBAL_DATA_T GBMsg;
static M_CIRCLE_T mc_imu_yaw = {0};
static M_CIRCLE_T mc_imu_pitch = {0};
float eular[3] = {0};
int16_t gyro[3] = {0};
int16_t accel[3] = {0};

/*debug*/
float warebuf[8] =  {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}; 

//#define IMU_WAVE


/**
  * @brief  电机反馈连续换
  * @param  连续换结构体、当前角度值
  * @retval void
  * @attention
  */
void circleContinue(M_CIRCLE_T *mc, uint16_t angle, uint16_t half_angle)
{
    if (angle - mc->angle > half_angle)
    {
        mc->circle--;
    }
    else if (angle - mc->angle < -half_angle)
    {
        mc->circle++;
    }
    mc->angle = angle;
}



void Msg_HolderDataProcess(GIMBAL_DATA_T *HolderMsg)
{
		
		
    get_eular(eular);
		circleContinue(&mc_imu_yaw, eular[2] + 180, 180);
    circleContinue(&mc_imu_pitch, eular[0] + 180, 180);
//    HolderMsg->angle[2] = eular[2];
//    HolderMsg->angle[0] = eular[0];
	  HolderMsg->angle[2] = mc_imu_yaw.angle + mc_imu_yaw.circle*360;
    HolderMsg->angle[0] = mc_imu_pitch.angle + mc_imu_pitch.circle*360;

    get_raw_gyo(gyro);
    HolderMsg->gyro[2] = gyro[2];
		HolderMsg->gyro[1] = gyro[1];
    HolderMsg->gyro[0] = gyro[0];
		
		get_raw_acc(accel);
    HolderMsg->accel[2] = accel[2];
		HolderMsg->accel[1] = accel[1];
    HolderMsg->accel[0] = accel[0];
		
	
		#ifdef IMU_WAVE

		warebuf[0] = (int16_t)accel[0];
		warebuf[1] = (int16_t)accel[1];
		warebuf[2] = (int16_t)accel[2];
		warebuf[3] = (int16_t)gyro[0];
		warebuf[4] = (int16_t)gyro[1];
		warebuf[5] = (int16_t)gyro[2];
		warebuf[6] = 1000;
		
	
	  UART2_SendWave(6, 2, &warebuf[0], &warebuf[1],
									&warebuf[2], &warebuf[3], &warebuf[4], &warebuf[5]);

    #endif
	
	
	
	
}




//static float IMUAngle_Continue(Mcircle_t *mc_imu,float imu_angle)
//{
//	float out_data = 0; 

//	Circle_Continue(mc_imu, (imu_angle + 180.0f) * 22.7555556f);
//	out_data = 819 * (float)(mc_imu->Circle + (float)(mc_imu->Angle) / 8192);

//	return out_data;    
//}

//void HolderDataMsg_Process(HolderData_t *HDMsg)
//{
//    get_eular(Eular);
//    
//    HDMsg->Angle[2] = IMUAngle_Continue(&mc_imu_yaw,Eular[2]);
//    HDMsg->Angle[0] = IMUAngle_Continue(&mc_imu_pitch,Eular[0]);
//    
//    get_raw_gyo(Gyro);
//    HDMsg->Gyro[2] = -(Gyro[2]/2.6f);
//    HDMsg->Gyro[0] = -Gyro[0];
//}








