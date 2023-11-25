/**@file	DM_J4310_motor.c
* @brief      达妙电机J4310 文件
* @details  	主要包含达妙电机各种模式的底层运行，来自官方例程
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
#include "DM_J4310_motor.h"
#include "rc.h"


int float_to_uint(float x, float x_min, float x_max, int bits){
    /// Converts a float to an unsigned int, given range and number of bits ///
    float span = x_max - x_min;
    float offset = x_min;
    return (int) ((x-offset)*((float)((1<<bits)-1))/span);
    }
    
    
float uint_to_float(int x_int, float x_min, float x_max, int bits){
    /// converts unsigned int to float, given range and number of bits ///
    float span = x_max - x_min;
    float offset = x_min;
    return ((float)x_int)*span/((float)((1<<bits)-1)) + offset;
    }



/*  
void start_motor(CAN_HandleTypeDef* hcan,uint16_t id)
{
	hcan->pTxMsg->StdId = id;
	hcan->pTxMsg->IDE = CAN_ID_STD;
	hcan->pTxMsg->RTR = CAN_RTR_DATA;
	hcan->pTxMsg->DLC = 0x08;
	hcan->pTxMsg->Data[0] = 0xFF;
	hcan->pTxMsg->Data[1] = 0xFF;
	hcan->pTxMsg->Data[2] = 0xFF;
	hcan->pTxMsg->Data[3] = 0xFF;
	hcan->pTxMsg->Data[4] = 0xFF;
	hcan->pTxMsg->Data[5] = 0xFF;
	hcan->pTxMsg->Data[6] = 0xFF;
	hcan->pTxMsg->Data[7] = 0xFC;
	
	HAL_CAN_Transmit(hcan, 100);
	
}	
*/

/* 修改-> MIT电机模式 */
void start_motor_DM_MIT(CAN_HandleTypeDef* hcan,uint16_t id)
{
	uint8_t data[8];
	CAN_TxHeaderTypeDef CAN_TX;
	CAN_TX.DLC=8;
	CAN_TX.IDE=CAN_ID_STD;
	CAN_TX.RTR=CAN_RTR_DATA;
	CAN_TX.StdId=id;

	data[0]=0xFF;
	data[1]=0xFF;
	data[2]=0xFF;
	data[3]=0xFF;
	data[4]=0xFF;
	data[5]=0xFF;
	data[6]=0xFF;
	data[7]=0xFC;
	HAL_CAN_AddTxMessage(hcan,&CAN_TX,data,(uint32_t* )CAN_TX_MAILBOX0);
}



void ctrl_motor_DM_MIT(CAN_HandleTypeDef* hcan,uint16_t id, float _pos, float _vel, float _KP, float _KD, float _torq)
{
  uint16_t pos_tmp,vel_tmp,kp_tmp,kd_tmp,tor_tmp;
	pos_tmp = float_to_uint(_pos, P_MIN, P_MAX, 16);
  vel_tmp = float_to_uint(_vel, V_MIN, V_MAX, 12);
	kp_tmp  = float_to_uint(_KP, KP_MIN, KP_MAX, 12);
	kd_tmp  = float_to_uint(_KD, KD_MIN, KD_MAX, 12);
  tor_tmp = float_to_uint(_torq, T_MIN, T_MAX, 12);

//	hcan->pTxMsg->Data[0] = (pos_tmp >> 8);
//	hcan->pTxMsg->Data[1] = pos_tmp;
//	hcan->pTxMsg->Data[2] = (vel_tmp >> 4);
//	hcan->pTxMsg->Data[3] = ((vel_tmp&0xF)<<4)|(kp_tmp>>8);
//	hcan->pTxMsg->Data[4] = kp_tmp;
//	hcan->pTxMsg->Data[5] = (kd_tmp >> 4);
//	hcan->pTxMsg->Data[6] = ((kd_tmp&0xF)<<4)|(tor_tmp>>8);
//	hcan->pTxMsg->Data[7] = tor_tmp;
//	
//	HAL_CAN_Transmit(hcan, 100);
	
	uint8_t data[8];
	CAN_TxHeaderTypeDef CAN_TX;
	CAN_TX.DLC=8;
	CAN_TX.IDE=CAN_ID_STD;
	CAN_TX.RTR=CAN_RTR_DATA;
	CAN_TX.StdId=id;

	data[0]=(pos_tmp >> 8);
	data[1]=pos_tmp;
	data[2]=(vel_tmp >> 4);
	data[3]=((vel_tmp&0xF)<<4)|(kp_tmp>>8);
	data[4]=kp_tmp;
	data[5]=(kd_tmp >> 4);
	data[6]=((kd_tmp&0xF)<<4)|(tor_tmp>>8);
	data[7]=tor_tmp;
	
	HAL_CAN_AddTxMessage(hcan,&CAN_TX,data,(uint32_t* )CAN_TX_MAILBOX0);
	
}	



void ctrl_motor_DM_Pos(CAN_HandleTypeDef* hcan,uint16_t id, float _pos, float _vel)
{
	uint8_t *pbuf,*vbuf;
	pbuf=(uint8_t*)&_pos;
	vbuf=(uint8_t*)&_vel;
	
	uint8_t data[8];
	CAN_TxHeaderTypeDef CAN_TX;
	CAN_TX.DLC=8;
	CAN_TX.IDE=CAN_ID_STD;
	CAN_TX.RTR=CAN_RTR_DATA;
	CAN_TX.StdId=id;
	
//	hcan->pTxMsg->StdId = id;
//	hcan->pTxMsg->IDE = CAN_ID_STD;
//	hcan->pTxMsg->RTR = CAN_RTR_DATA;
//	hcan->pTxMsg->DLC = 0x08;
//	hcan->pTxMsg->Data[0] = *pbuf;
//	hcan->pTxMsg->Data[1] = *(pbuf+1);
//	hcan->pTxMsg->Data[2] = *(pbuf+2);
//	hcan->pTxMsg->Data[3] = *(pbuf+3);
//	hcan->pTxMsg->Data[4] = *vbuf;
//	hcan->pTxMsg->Data[5] = *(vbuf+1);
//	hcan->pTxMsg->Data[6] = *(vbuf+2);
//	hcan->pTxMsg->Data[7] = *(vbuf+3);
//	
//	HAL_CAN_Transmit(hcan, 100);
	
	data[0]=*pbuf;
	data[1]=*(pbuf+1);
	data[2]=*(pbuf+2);
	data[3]=*(pbuf+3);
	data[4]=*vbuf;
	data[5]=*(vbuf+1);
	data[6]=*(vbuf+2);
	data[7]=*(vbuf+3);
	
	HAL_CAN_AddTxMessage(hcan,&CAN_TX,data,(uint32_t* )CAN_TX_MAILBOX0);
	
}	



/* 用于达妙电机 ID = 0x1 */
static void CanTransmit(uint8_t *buf, uint8_t len)
{
    CAN_TxHeaderTypeDef TxHead;             /**!< can通信发送协议头 */
    uint32_t canTxMailbox;
    
    if((buf != NULL) && (len != 0))
    {
//        TxHead.StdId    = CAN_SLAVE_ID;     /* 指定标准标识符，该值在0x00-0x7FF */
				TxHead.StdId    = 0x1;
        TxHead.IDE      = CAN_ID_STD;       /* 指定将要传输消息的标识符类型 */
        TxHead.RTR      = CAN_RTR_DATA;     /* 指定消息传输帧类型 */
        TxHead.DLC      = len;              /* 指定将要传输的帧长度 */
        
        if(HAL_CAN_AddTxMessage(&hcan1, &TxHead, buf, (uint32_t *)&canTxMailbox) == HAL_OK )
        {
            
        }
    }
}


/**
  * @brief  DM-J4310 Can总线发送控制参数
  * @param
  * @retval 
  */
void CanComm_SendControlPara(float f_p, float f_v, float f_kp, float f_kd, float f_t)
{
    uint16_t p, v, kp, kd, t;
    uint8_t buf[8];
    
    /* 限制输入的参数在定义的范围内 */
    LIMIT_MIN_MAX(f_p,  P_MIN,  P_MAX);
    LIMIT_MIN_MAX(f_v,  V_MIN,  V_MAX);
    LIMIT_MIN_MAX(f_kp, KP_MIN, KP_MAX);
    LIMIT_MIN_MAX(f_kd, KD_MIN, KD_MAX);
    LIMIT_MIN_MAX(f_t,  T_MIN,  T_MAX);
    
    /* 根据协议，对float参数进行转换 */
    p = float_to_uint(f_p,      P_MIN,  P_MAX,  16);            
    v = float_to_uint(f_v,      V_MIN,  V_MAX,  12);
    kp = float_to_uint(f_kp,    KP_MIN, KP_MAX, 12);
    kd = float_to_uint(f_kd,    KD_MIN, KD_MAX, 12);
    t = float_to_uint(f_t,      T_MIN,  T_MAX,  12);
    
    /* 根据传输协议，把数据转换为CAN命令数据字段 */
    buf[0] = p>>8;
    buf[1] = p&0xFF;
    buf[2] = v>>4;
    buf[3] = ((v&0xF)<<4)|(kp>>8);
    buf[4] = kp&0xFF;
    buf[5] = kd>>4;
    buf[6] = ((kd&0xF)<<4)|(t>>8);
    buf[7] = t&0xff;
    
    /* 通过CAN接口把buf中的内容发送出去 */
    CanTransmit(buf, sizeof(buf));
}


volatile uint32_t pre_PCtick = 0;       /**!< 位置控制前一个tick */
volatile uint32_t pre_VCtick = 0;       /**!< 速度控制前一个tick */
volatile uint32_t loop_counter = 0;
volatile float f_p = 0;

/* 启动电机控制 */
void MotorControl_Start(void)
{
    ZeroPosition();
    CanComm_ControlCmd(CMD_ZERO_POSITION);
    loop_counter = 0;
    pre_PCtick = HAL_GetTick();
    pre_VCtick = HAL_GetTick();
}


/* 在发送电机位置零前，需要把电机的所有控制参数设置为0 */
static void ZeroPosition(void)
{
    CanComm_ControlCmd(CMD_MOTOR_MODE);
    HAL_Delay(100);
    CanComm_SendControlPara(0,0,0,0,0);
    HAL_Delay(100);
}


void CanComm_ControlCmd(uint8_t cmd)
{
    uint8_t buf[8] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00};
    switch(cmd)
    {
        case CMD_MOTOR_MODE:
            buf[7] = 0xFC;
            break;
        
        case CMD_RESET_MODE:
            buf[7] = 0xFD;
        break;
        
        case CMD_ZERO_POSITION:
            buf[7] = 0xFE;
        break;
        
        default:
        return; /* 直接退出函数 */
    }
    CanTransmit(buf, sizeof(buf));
}



































