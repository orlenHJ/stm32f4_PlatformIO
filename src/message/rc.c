/**@file	rc.c
* @brief      DR16遥控控制器 文件
* @details  	主要包含遥控器的底层运行接受数据解析
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
#include "rc.h"

uint8_t rc_rx_buffer[RC_FRAME_LENGTH];
RC_ctl_t RC_CtrlData;












void RemoteProcess(uint8_t* pData)
{
	if(pData==NULL)
	{
		return;
	}
	RC_CtrlData.rc.ch0 = ((int16_t)pData[0] | ((int16_t)pData[1] << 8)) & 0x07FF; 
	RC_CtrlData.rc.ch1 = ((((int16_t)pData[1] >> 3) | ((int16_t)pData[2] << 5)) & 0x07FF);
	RC_CtrlData.rc.ch2 = ((((int16_t)pData[2] >> 6) | ((int16_t)pData[3] << 2) |((int16_t)pData[4] << 10)) & 0x07FF);
	RC_CtrlData.rc.ch3 = ((((int16_t)pData[4] >> 1) | ((int16_t)pData[5]<<7)) & 0x07FF);
	
	/*限幅在50内*/
	if(RC_CtrlData.rc.ch0<=1074&&RC_CtrlData.rc.ch0>=974)
		RC_CtrlData.rc.ch0=1024;
	if(RC_CtrlData.rc.ch1<=1074&&RC_CtrlData.rc.ch1>=974)
		RC_CtrlData.rc.ch1=1024;
	if(RC_CtrlData.rc.ch2<=1074&&RC_CtrlData.rc.ch2>=974)
		RC_CtrlData.rc.ch2=1024;
	if(RC_CtrlData.rc.ch3<=1074&&RC_CtrlData.rc.ch3>=974)
		RC_CtrlData.rc.ch3=1024;	
 
	RC_CtrlData.rc.s1 = ((pData[5] >> 4) & 0x000C) >> 2;
	RC_CtrlData.rc.s2 = ((pData[5] >> 4) & 0x0003);
	RC_CtrlData.mouse.x = ((int16_t)pData[6]) | ((int16_t)pData[7] << 8);
	RC_CtrlData.mouse.y = ((int16_t)pData[8]) | ((int16_t)pData[9] << 8);
	RC_CtrlData.mouse.z = ((int16_t)pData[10]) | ((int16_t)pData[11] << 8); 
	RC_CtrlData.mouse.press_l = pData[12];
	RC_CtrlData.mouse.press_r = pData[13];
	
	RC_CtrlData.key = ((int16_t)pData[14]) | ((int16_t)pData[15] << 8);
	
	
	RC_CtrlData.keyboard.W     = RC_CtrlData.key & KEY_PRESSED_OFFSET_W;
	RC_CtrlData.keyboard.S     = (RC_CtrlData.key & KEY_PRESSED_OFFSET_S)>>1;
	RC_CtrlData.keyboard.A     = (RC_CtrlData.key & KEY_PRESSED_OFFSET_A)>>2;
	RC_CtrlData.keyboard.D     = (RC_CtrlData.key & KEY_PRESSED_OFFSET_D)>>3;
	RC_CtrlData.keyboard.SHIFT = (RC_CtrlData.key & KEY_PRESSED_OFFSET_SHIFT)>>4;
	RC_CtrlData.keyboard.CTRL  = (RC_CtrlData.key & KEY_PRESSED_OFFSET_CTRL)>>5;
	RC_CtrlData.keyboard.Q     = (RC_CtrlData.key & KEY_PRESSED_OFFSET_Q)>>6;
	RC_CtrlData.keyboard.E     = (RC_CtrlData.key & KEY_PRESSED_OFFSET_E)>>7;
	RC_CtrlData.keyboard.R     = (RC_CtrlData.key & KEY_PRESSED_OFFSET_R)>>8;
	RC_CtrlData.keyboard.F     = (RC_CtrlData.key & KEY_PRESSED_OFFSET_F)>>9;
	RC_CtrlData.keyboard.G     = (RC_CtrlData.key & KEY_PRESSED_OFFSET_G)>>10;
	RC_CtrlData.keyboard.Z     = (RC_CtrlData.key & KEY_PRESSED_OFFSET_Z)>>11;
	RC_CtrlData.keyboard.X     = (RC_CtrlData.key & KEY_PRESSED_OFFSET_X)>>12;
	RC_CtrlData.keyboard.C     = (RC_CtrlData.key & KEY_PRESSED_OFFSET_C)>>13;
	RC_CtrlData.keyboard.V     = (RC_CtrlData.key & KEY_PRESSED_OFFSET_V)>>14;
	RC_CtrlData.keyboard.B     = (RC_CtrlData.key & KEY_PRESSED_OFFSET_B)>>15;
	

	
}












