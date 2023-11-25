
#ifndef __PID_H__
#define __PID_H__

#include "stdint.h"


#define LimitMax(input, max)   	\
{                        				\
	if (input > max)       				\
  {                      				\
		input = max;       	 				\
  }                      				\
  else if (input < -max) 				\
  {                      				\
		input = -max;        				\
  }                      				\
}





typedef float fp32;

enum PID_MODE		//PID运行的模式，增量式还是位置式PID
{
    PID_POSITION = 0,
    PID_DELTA
};

typedef struct//pid
{
    uint8_t mode;
    
    fp32 Kp;
    fp32 Ki;
    fp32 Kd;

    fp32 max_out;  		//PID总输出的限幅，防止整体输出过大，传入一个正数，限制范围为[-max_out,+max_out]
    fp32 max_iout; 		/*PID最大积分输出积分项输出的限幅，因为系统刚启动时与目标误差较大，累计误差计算输出会很大，影响系
											统稳定性，所以对累计误差进行限幅，传入一个正数，限制范围为[-max_iout,+max_iout]*/
    fp32 set;//PID目标值
    fp32 fdb;//PID当前值

    fp32 out;
    fp32 Pout;
    fp32 Iout;
    fp32 Dout;
	//微分项最近三个值 0最新 1上一次 2上上次
    fp32 Dbuf[3];  
	//误差项最近三个值 0最新 1上一次 2上上次
    fp32 error[3]; 

}PidTypeDef;


extern PidTypeDef chassis_speed_pid;
extern PidTypeDef chassis_current_pid;










fp32 PID_Calc(PidTypeDef *pid,fp32 ref,fp32 set);
void PID_init(PidTypeDef *pid,uint8_t mode,const fp32 PID[3],fp32 max_out,fp32 max_iout);
void PID_clear(PidTypeDef *pid);
#endif

