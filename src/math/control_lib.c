/**@file	control_lib.c
* @brief      
* @details  	
* @author      orlen
* @date        2023-7-25
* @version     V1.0
* @copyright    Copyright (c) 2050
**********************************************************************************
* @attention
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version 	 <th>Author    	<th>Description
* <tr><td>2023-7-25  	<td>1.0     	 <td>orlen  		<td>创建初始版本
* </table>
*
**********************************************************************************
*/

/* includes ------------------------------------------------------------------*/
#include "control_lib.h"
#include "main.h"

/* typedef -------------------------------------------------------------------*/

/* define --------------------------------------------------------------------*/

/* variables -----------------------------------------------------------------*/

/* function ------------------------------------------------------------------*/


/**
  * @brief  基于目标的前馈控制 延迟补偿
  * @param  PID结构体指针
  * @retval 当前输出前馈量
  * @attention  
  */
fp32 control_feedback_n1(PidTypeDef *pid , fp32 K_F)
{
		static fp32 set_last ,f_out;
		f_out = (pid->set - set_last)* K_F ;	
		set_last = pid->set;
		return f_out;
}


fp32 control_feedback_n2(PidTypeDef *pid , fp32 K_F)
{
		static fp32 set_last ,f_out;
		f_out = (pid->set - set_last)* K_F + pid->set;	
		set_last = pid->set;
		return f_out;
}























