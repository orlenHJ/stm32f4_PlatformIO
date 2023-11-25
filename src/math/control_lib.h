#ifndef CONTROL_H
#define CONTROL_H


/* includes ------------------------------------------------------------------*/
#include "pid.h"
#include "stdint.h"

/* typedef -------------------------------------------------------------------*/
typedef float fp32;
/* define --------------------------------------------------------------------*/

/* variables -----------------------------------------------------------------*/

/* function ------------------------------------------------------------------*/
fp32 control_feedback_n1(PidTypeDef *pid , fp32 K_F);
fp32 control_feedback_n2(PidTypeDef *pid , fp32 K_F);

































#endif
