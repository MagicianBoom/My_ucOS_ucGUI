/*
*********************************************************************************************************
*                                              EXAMPLE CODE
*
*                             (c) Copyright 2013; Micrium, Inc.; Weston, FL
*
*                   All rights reserved.  Protected by international copyright laws.
*                   Knowledge of the source code may not be used to write a similar
*                   product.  This file may only be used in accordance with a license
*                   and should not be redistributed in any way.
*********************************************************************************************************
*/
#ifndef  INCLUDES_PRESENT
#define  INCLUDES_PRESENT


/*
*********************************************************************************************************
*                                         STANDARD LIBRARIES
*********************************************************************************************************
*/

#include  <stdarg.h>
#include  <stdio.h>
#include  <stdlib.h>
#include  <math.h>


/*
*********************************************************************************************************
*                                              LIBRARIES
*********************************************************************************************************
*/

#include  <cpu.h>
#include  <lib_def.h>
#include  <lib_ascii.h>
#include  <lib_math.h>
#include  <lib_mem.h>
#include  <lib_str.h>
#include  "stm32f4xx_conf.h"
#include  "GUI.h"


/*
*********************************************************************************************************
*                                                 OS
*********************************************************************************************************
*/

#include  <os.h>

/*
*********************************************************************************************************
*                                              APP / BSP
*********************************************************************************************************
*/

#include "bsp.h"
#include "app_cfg.h"
#include "stm32f4xx.h"
#include "misc.h"
#include "task.h"
#include "bsp_led.h"
#include "bsp_lcd.h"
#include "bsp_time.h"



/*
*********************************************************************************************************
*                                               SERIAL
*********************************************************************************************************
*/

#if (APP_CFG_SERIAL_EN == DEF_ENABLED)
#include  <app_serial.h>
#endif

//================ϵͳ===================

#define USE_US100           //ʹ��us100�ͺų����� 

#define MAXMOTORS 		(4)		//�������
#define GET_TIME_NUM 	(5)		//���û�ȡʱ�����������
#define CH_NUM 				(8) 	//���ջ�ͨ������

#define USE_TOE_IN_UNLOCK 0 // 0��Ĭ�Ͻ�����ʽ��1����˽�����ʽ
#define ANO_DT_USE_USART2 	//��������2��������
#define ANO_DT_USE_USB_HID	//�����ɿ�USBHID������λ������
//=======================================
/***************�ж����ȼ�******************/
#define NVIC_GROUP NVIC_PriorityGroup_3		//�жϷ���ѡ��
#define NVIC_PWMIN_P			1		//���ջ��ɼ�
#define NVIC_PWMIN_S			1
#define NVIC_TIME_P       2		//��δʹ��
#define NVIC_TIME_S       0
#define NVIC_UART_P				5		//��δʹ��
#define NVIC_UART_S				1
#define NVIC_UART2_P			3		//����2�ж�
#define NVIC_UART2_S			1
/***********************************************/

//================������===================
#define ACC_ADJ_EN 									//�Ƿ�����У׼���ٶȼ�,(����������)

#define OFFSET_AV_NUM 	50					//У׼ƫ����ʱ��ƽ��������
#define FILTER_NUM 			10					//����ƽ���˲���ֵ����

#define TO_ANGLE 				0.06103f 		//0.061036 //   4000/65536  +-2000   ???

#define FIX_GYRO_Y 			1.02f				//������Y����в���
#define FIX_GYRO_X 			1.02f				//������X����в���

#define TO_M_S2 				0.23926f   	//   980cm/s2    +-8g   980/4096
#define ANGLE_TO_RADIAN 0.01745329f //*0.01745 = /57.3	�Ƕ�ת����

#define MAX_ACC  4096.0f						//+-8G		���ٶȼ�����
#define TO_DEG_S 500.0f      				//T = 2ms  Ĭ��Ϊ2ms ����ֵ����1/T

enum
{
 A_X = 0,
 A_Y ,
 A_Z ,
 G_Y ,
 G_X ,
 G_Z ,
 TEM ,
 ITEMS ,
};

// CH_filter[],0�����1������2���ţ�3����		
enum
{
 ROL= 0,
 PIT ,
 THR ,
 YAW ,
 AUX1 ,
 AUX2 ,
 AUX3 ,
 AUX4 ,
};
//=========================================

//================����=====================
#define MAX_VERTICAL_SPEED_UP  5000										//��������ٶ�mm/s
#define MAX_VERTICAL_SPEED_DW  3000										//����½��ٶ�mm/s

#define MAX_CTRL_ANGLE			30.0f										//ң���ܴﵽ�����Ƕ�
#define ANGLE_TO_MAX_AS 		30.0f										//�Ƕ����Nʱ���������ٶȴﵽ��󣨿���ͨ������CTRL_2��Pֵ������
#define CTRL_2_INT_LIMIT 		0.5f *MAX_CTRL_ANGLE		//�⻷���ַ���

#define MAX_CTRL_ASPEED 	 	300.0f									//ROL,PIT����������ƽ��ٶ�
#define MAX_CTRL_YAW_SPEED 	150.0f									//YAW����������ƽ��ٶ�
#define CTRL_1_INT_LIMIT 		0.5f *MAX_CTRL_ASPEED		//�ڻ����ַ���


#define MAX_PWM				100			///%	���PWM���Ϊ100%����
#define MAX_THR       80 			///%	����ͨ�����ռ��80%����20%��������
#define READY_SPEED   20			///%	��������ת��20%����
//=========================================

/*
*********************************************************************************************************
*                                            INCLUDES END
*********************************************************************************************************
*/


#endif

