/**@file	rc.c
* @brief      DR16遥控控制器 头文件
* @details  	主要包含遥控器的底层运行接受数据解析相关变量
* @author      orlen
* @date        2023-7-19
* @version     V1.0
* @copyright    Copyright (c) 2050
**********************************************************************************
* @attention
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version 	 <th>Author    	<th>Description
* <tr><td>2023-7-19  	<td>1.0     	 <td>orlen  		<td>创建初始版本
* </table>
*
**********************************************************************************
*/
#ifndef RC_H
#define RC_H




#include "stdint.h"
#include "stddef.h"

/* define --------------------------------------------------------------------*/
#define KEY_PRESSED_OFFSET_W	    (1U << 0)
#define KEY_PRESSED_OFFSET_S	    (1U << 1)
#define KEY_PRESSED_OFFSET_A	    (1U << 2)
#define KEY_PRESSED_OFFSET_D	    (1U << 3)
#define KEY_PRESSED_OFFSET_SHIFT	(1U << 4)
#define KEY_PRESSED_OFFSET_CTRL	(1U << 5)
#define KEY_PRESSED_OFFSET_Q	    (1U << 6)
#define KEY_PRESSED_OFFSET_E	    (1U << 7)
#define KEY_PRESSED_OFFSET_R	    (1U << 8)
#define KEY_PRESSED_OFFSET_F	    (1U << 9)
#define KEY_PRESSED_OFFSET_G	    (1U << 10)
#define KEY_PRESSED_OFFSET_Z	    (1U << 11)
#define KEY_PRESSED_OFFSET_X	    (1U << 12)
#define KEY_PRESSED_OFFSET_C	    (1U << 13)
#define KEY_PRESSED_OFFSET_V	    (1U << 14)
#define KEY_PRESSED_OFFSET_B	    (1U << 15)


#define RC_FRAME_LENGTH 18u
#define S_UP 1
#define S_MID 3
#define S_DOWN 2



/**struct***************************************/
typedef struct 
{
	uint16_t W;
	uint16_t S;
	uint16_t A;
	uint16_t D;	
  uint16_t SHIFT;
	uint16_t CTRL;
	uint16_t Q;
	uint16_t E;
	uint16_t R;
	uint16_t F;
	uint16_t G;
	uint16_t Z;
	uint16_t X;
	uint16_t C;
	uint16_t V;
	uint16_t B;
}Keyboard16_t;


typedef struct
{
	struct
	{
		uint16_t ch0;
		uint16_t ch1;
		uint16_t ch2;
		uint16_t ch3;
		uint8_t s1;
		uint8_t s2;
	}rc;

	struct
	{
		int16_t x;
		int16_t y;
		int16_t z;
		uint8_t press_l;
		uint8_t press_r;
	}mouse;

	uint16_t key;
	
	Keyboard16_t keyboard;
	
	
}RC_ctl_t;


/*value*******************************************************/
extern uint8_t rc_rx_buffer[RC_FRAME_LENGTH];
extern RC_ctl_t RC_CtrlData;



/*function*******************************************************/
void RemoteProcess(uint8_t* pData);






/* 附录 --------------------------------------------------------------------*/

/** 《遥控器信息图》
 * ┌──────────────────────────────────────────┐
 * │ ┌───┐1  660                  660  ┌───┐1 │
 * │ │S 1│3   Λ                    Λ   │S 2│3 │
 * │ └───┘2   │                    │   └───┘2 │
 * │          │                    │          │
 * │ CH2<─────┼─────>660  CH0<─────┼─────>660 │
 * │          │                    │          │
 * │          │                    │          │
 * │          V                    V          │
 * │         CH3                  CH1         │
 * └──────────────────────────────────────────┘
 */




#endif

