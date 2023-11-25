

/* includes ------------------------------------------------------------------*/
#include "ramp.h"

/* typedef -------------------------------------------------------------------*/

/* define --------------------------------------------------------------------*/

/* variables -----------------------------------------------------------------*/

/* function ------------------------------------------------------------------*/

/**
  * @brief  斜坡函数,使目标输出值缓慢等于期望值
  * @param  期望最终输出,当前输出,变化速度(每次增加的值)
  * @retval 当前输出
  * @attention  
  */
float rampFloat(float final, float now, float ramp)
{
    float buffer = 0;

    buffer = final - now;

    if (buffer > 0)
    {
        if (buffer > ramp)
        {  
            now += ramp;
        }   
        else
        {
            now += buffer;
        }
    }
    else
    {
        if (buffer < -ramp)
        {
            now += -ramp;
        }
        else
        {
            now += buffer;
        }
    }

    return now;
}

int rampInt(int final, int now, int ramp)
{
    int buffer = 0;

    buffer = final - now;

    if (buffer > 0)
    {
        if (buffer > ramp)
        {  
            now += ramp;
        }   
        else
        {
            now += buffer;
        }
    }
    else
    {
        if (buffer < -ramp)
        {
            now += -ramp;
        }
        else
        {
            now += buffer;
        }
    }

    return now;
}

int8_t rampInt8(int8_t final, int8_t now, int8_t ramp)
{
    int buffer = 0;

    buffer = final - now;

    if (buffer > 0)
    {
        if (buffer > ramp)
        {  
            now += ramp;
        }   
        else
        {
            now += buffer;
        }
    }
    else
    {
        if (buffer < -ramp)
        {
            now += -ramp;
        }
        else
        {
            now += buffer;
        }
    }

    return now;
}

int16_t rampInt16(int16_t final, int16_t now, int16_t ramp)
{
    int buffer = 0;

    buffer = final - now;

    if (buffer > 0)
    {
        if (buffer > ramp)
        {  
            now += ramp;
        }   
        else
        {
            now += buffer;
        }
    }
    else
    {
        if (buffer < -ramp)
        {
            now += -ramp;
        }
        else
        {
            now += buffer;
        }
    }

    return now;
}

int32_t rampInt32(int32_t final, int32_t now, int32_t ramp)
{
    int buffer = 0;

    buffer = final - now;

    if (buffer > 0)
    {
        if (buffer > ramp)
        {  
            now += ramp;
        }   
        else
        {
            now += buffer;
        }
    }
    else
    {
        if (buffer < -ramp)
        {
            now += -ramp;
        }
        else
        {
            now += buffer;
        }
    }

    return now;
}

uint8_t rampUint8(uint8_t final, uint8_t now, uint8_t ramp)
{
    uint8_t buffer = 0;

    buffer = final - now;

    if (buffer > 0)
    {
        if (buffer > ramp)
        {  
            now += ramp;
        }   
        else
        {
            now += buffer;
        }
    }
    else
    {
        if (buffer < -ramp)
        {
            now += -ramp;
        }
        else
        {
            now += buffer;
        }
    }

    return now;
}

uint16_t rampUint16(uint16_t final, uint16_t now, uint16_t ramp)
{
    uint16_t buffer = 0;

    buffer = final - now;

    if (buffer > 0)
    {
        if (buffer > ramp)
        {  
            now += ramp;
        }   
        else
        {
            now += buffer;
        }
    }
    else
    {
        if (buffer < -ramp)
        {
            now += -ramp;
        }
        else
        {
            now += buffer;
        }
    }

    return now;
}

uint32_t rampUint32(uint32_t final, uint32_t now, uint32_t ramp)
{
    uint32_t buffer = 0;

    buffer = final - now;

    if (buffer > 0)
    {
        if (buffer > ramp)
        {  
            now += ramp;
        }   
        else
        {
            now += buffer;
        }
    }
    else
    {
        if (buffer < -ramp)
        {
            now += -ramp;
        }
        else
        {
            now += buffer;
        }
    }

    return now;
}



/*数字信号处理函数*/

/**
  * @brief  递推（滑动）平均滤波
  * @param  
  * @retval void
  * @attention 
  */
#define  RM_BUF_LEN                         4 /*递推数组的长度*/
int16_t RM_Filter_Buf[RM_BUF_LEN];            /*保存数据的递推数组*/

int16_t Misc_s16Recursive_Mean_Filter(int16_t get_data)
{
    int16_t sum = 0;
    uint8_t i;
    
    for(i = 0; i < RM_BUF_LEN - 1; i++) 
    {
		RM_Filter_Buf[i] = RM_Filter_Buf[i+1];  /*数组中所有数据左移一位 第一个数据扔掉*/
		sum += RM_Filter_Buf[i];                /*计算递推数组中处最后一个前面所有数据的和*/
	}
    
    RM_Filter_Buf[RM_BUF_LEN - 1] = get_data;
    
    sum += RM_Filter_Buf[RM_BUF_LEN - 1];                     /*计算递推数组所有数据的和*/
    sum = sum / RM_BUF_LEN;
    return sum;
}

int32_t Misc_s32Recursive_Mean4_Filter(int32_t get_data, int32_t RM4_Filter_Buf[4])
{
    int32_t sum = 0;
    uint8_t i;
    
    for(i = 0; i < 3; i++) 
    {
		RM4_Filter_Buf[i] = RM4_Filter_Buf[i+1];  /*数组中所有数据左移一位 第一个数据扔掉*/
		sum += RM4_Filter_Buf[i];                 /*计算递推数组中处最后一个前面所有数据的和*/
	}
    
    RM4_Filter_Buf[3] = get_data;
    
    sum =  RM4_Filter_Buf[0]*0.1 + RM4_Filter_Buf[1]*0.2 +RM4_Filter_Buf[2]*0.3 + RM4_Filter_Buf[3]*0.4;
    return sum;
}

float Misc_fRecursive_Mean4_Filter(float get_data, float RM4_Filter_Buf[4])
{
    float sum = 0;
    uint8_t i;
    
    for(i = 0; i < 3; i++) 
    {
		RM4_Filter_Buf[i] = RM4_Filter_Buf[i+1];  /*数组中所有数据左移一位 第一个数据扔掉*/
		sum += RM4_Filter_Buf[i];                 /*计算递推数组中处最后一个前面所有数据的和*/
	}
    
    RM4_Filter_Buf[3] = get_data;
    
    sum =  RM4_Filter_Buf[0]*0.1f + RM4_Filter_Buf[1]*0.2f +RM4_Filter_Buf[2]*0.3f + RM4_Filter_Buf[3]*0.4f;
    return sum;
}


void LimitV(int16_t x,uint16_t range)
{
	if(x >= range)
	{
		x	= range;
	}
	if(x <= -range)
	{
		x = -range;
	}
}















