#include "pid.h"
#include "main.h"



PidTypeDef chassis_speed_pid;
PidTypeDef chassis_current_pid;



void PID_init(PidTypeDef *pid,uint8_t mode,const fp32 PID[3],fp32 max_out,fp32 max_iout)
{
	if(pid==NULL||PID==NULL)
	{
		return;
	}
	pid->mode=mode;
	pid->Kp=PID[0];
	pid->Ki=PID[1];
	pid->Kd=PID[2];
	pid->max_out=max_out;
	pid->max_iout=max_iout;
	pid->Dbuf[0]=pid->Dbuf[1]=pid->Dbuf[2]=0.0f;
	pid->error[0]=pid->error[1]=pid->error[2]=pid->Pout=pid->Iout=pid->Dout=pid->out=0.0f;
	
}

fp32 PID_Calc(PidTypeDef *pid, fp32 ref, fp32 set)  //pid计算
{
    if (pid == NULL)
    {
        return 0.0f;
    }

    pid->error[2] = pid->error[1];
    pid->error[1] = pid->error[0];
    pid->set = set;
    pid->fdb = ref;
    pid->error[0] = set - ref;
    if (pid->mode == PID_POSITION) //位置式PID
    {
        pid->Pout = pid->Kp * pid->error[0];
        pid->Iout += pid->Ki * pid->error[0];
        pid->Dbuf[2] = pid->Dbuf[1];
        pid->Dbuf[1] = pid->Dbuf[0];
        pid->Dbuf[0] = (pid->error[0] - pid->error[1]);
        pid->Dout = pid->Kd * pid->Dbuf[0];
        LimitMax(pid->Iout, pid->max_iout);//对积分项进行限幅
        pid->out = pid->Pout + pid->Iout + pid->Dout;//叠加三个输出到总输出
        LimitMax(pid->out, pid->max_out);//对总输出进行限幅
    }
    else if (pid->mode == PID_DELTA)  //增量式PID
    {
        pid->Pout = pid->Kp * (pid->error[0] - pid->error[1]);
        pid->Iout = pid->Ki * pid->error[0];
        pid->Dbuf[2] = pid->Dbuf[1];
        pid->Dbuf[1] = pid->Dbuf[0];
        pid->Dbuf[0] = (pid->error[0] - 2.0f * pid->error[1] + pid->error[2]);
        pid->Dout = pid->Kd * pid->Dbuf[0];
        pid->out += pid->Pout + pid->Iout + pid->Dout;
        LimitMax(pid->out, pid->max_out); //对总输出做一个先限幅
    }
    return pid->out;
}


void PID_clear(PidTypeDef *pid)
{
    if (pid == NULL)
    {
        return;
    }
	//当前误差清零
    pid->error[0] = pid->error[1] = pid->error[2] = 0.0f;
    //微分项清零
    pid->Dbuf[0] = pid->Dbuf[1] = pid->Dbuf[2] = 0.0f;
    //输出清零
    pid->out = pid->Pout = pid->Iout = pid->Dout = 0.0f;
    //目标值和当前值清零
    pid->fdb = pid->set = 0.0f;
}





























