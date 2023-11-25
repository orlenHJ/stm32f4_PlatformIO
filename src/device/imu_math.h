
#ifndef IMU_MATH_H
#define IMU_MATH_H

#include <stdint.h>





typedef struct _GimbalData_t
{
    int16_t gyro[3];
    float angle[3];
    float speed[3];
		int16_t accel[3];
}GIMBAL_DATA_T;



/*做连续化数据*/
typedef struct _Mcircle_t
{
    int32_t circle;
    int16_t angle;
}M_CIRCLE_T;





extern GIMBAL_DATA_T GBMsg;







/*function*/
void Msg_HolderDataProcess(GIMBAL_DATA_T *HolderMsg);








#endif
