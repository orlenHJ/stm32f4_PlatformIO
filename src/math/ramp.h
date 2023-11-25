#ifndef RAMP_H
#define RAMP_H


/* includes ------------------------------------------------------------------*/
#include <stdint.h>


/* define --------------------------------------------------------------------*/
#define RAD2DEG (57.296f) /* 1»¡¶È = 57.296¶È */
#define PI (3.1415926f)
/* variables -----------------------------------------------------------------*/




/* function ------------------------------------------------------------------*/



/* Ð±ÆÂ */
float rampFloat(float Final, float now, float ramp);
int rampInt(int Final, int now, int ramp);
int8_t rampInt8(int8_t Final, int8_t now, int8_t ramp);
int16_t rampInt16(int16_t Final, int16_t now, int16_t ramp);
int32_t rampInt32(int32_t Final, int32_t now, int32_t ramp);
uint8_t rampUint8(uint8_t Final, uint8_t now, uint8_t ramp);
uint16_t rampUint16(uint16_t Final, uint16_t now, uint16_t ramp);
uint32_t rampUint32(uint32_t Final, uint32_t now, uint32_t ramp);

/* ÂË²¨ */
int16_t Misc_s16Recursive_Mean_Filter(int16_t get_data);
int32_t Misc_s32Recursive_Mean4_Filter(int32_t get_data, int32_t RM4_Filter_Buf[4]);
float Misc_fRecursive_Mean4_Filter(float get_data, float RM4_Filter_Buf[4]);



void LimitV(int16_t x,uint16_t range);



#endif
