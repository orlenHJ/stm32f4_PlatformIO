
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

enum PID_MODE		//PID���е�ģʽ������ʽ����λ��ʽPID
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

    fp32 max_out;  		//PID��������޷�����ֹ����������󣬴���һ�����������Ʒ�ΧΪ[-max_out,+max_out]
    fp32 max_iout; 		/*PID���������������������޷�����Ϊϵͳ������ʱ��Ŀ�����ϴ��ۼ������������ܴ�Ӱ��ϵ
											ͳ�ȶ��ԣ����Զ��ۼ��������޷�������һ�����������Ʒ�ΧΪ[-max_iout,+max_iout]*/
    fp32 set;//PIDĿ��ֵ
    fp32 fdb;//PID��ǰֵ

    fp32 out;
    fp32 Pout;
    fp32 Iout;
    fp32 Dout;
	//΢�����������ֵ 0���� 1��һ�� 2���ϴ�
    fp32 Dbuf[3];  
	//������������ֵ 0���� 1��һ�� 2���ϴ�
    fp32 error[3]; 

}PidTypeDef;


extern PidTypeDef chassis_speed_pid;
extern PidTypeDef chassis_current_pid;










fp32 PID_Calc(PidTypeDef *pid,fp32 ref,fp32 set);
void PID_init(PidTypeDef *pid,uint8_t mode,const fp32 PID[3],fp32 max_out,fp32 max_iout);
void PID_clear(PidTypeDef *pid);
#endif

