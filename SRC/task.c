#include "app_cfg.h"
#include "includes.h"

/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/
void  AppTaskCreate         (void);
void  AppTask_LedTest         (void     *p_arg);


/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/
static  OS_TCB   AppTask_LedTest_TCB;
static  CPU_STK  AppTask_LedTest_Stk[APP_TASK_LED_TEST_STK_SIZE];




/*
*********************************************************************************************************
*	函 数 名: AppTask_LedTest
*	功能说明: 
*	形    参：p_arg 是在创建该任务时传递的形参
*	返 回 值: 无
*	优 先 级：
*********************************************************************************************************
*/
void AppTask_LedTest(void *p_arg)
{
	OS_ERR      err;
	(void)p_arg;
	
	u8 x=0;
	u8 lcd_id[12];				//存放LCD ID字符串
	
	POINT_COLOR=RED;      //画笔颜色：红色
	sprintf((char*)lcd_id,"LCD ID:%04X",lcddev.id);//将LCD ID打印到lcd_id数组。  
	while(1)
	{		
		switch(x)
		{
			case 0:LCD_Clear(WHITE);break;
			case 1:LCD_Clear(BLACK);break;
			case 2:LCD_Clear(BLUE);break;
			case 3:LCD_Clear(RED);break;
			case 4:LCD_Clear(MAGENTA);break;
			case 5:LCD_Clear(GREEN);break;
			case 6:LCD_Clear(CYAN);break; 
			case 7:LCD_Clear(YELLOW);break;
			case 8:LCD_Clear(BRRED);break;
			case 9:LCD_Clear(GRAY);break;
			case 10:LCD_Clear(LGRAY);break;
			case 11:LCD_Clear(BROWN);break;
		}
		POINT_COLOR=RED;	  
		LCD_ShowString(30,40,210,24,24,"Explorer STM32F4");	
		LCD_ShowString(30,70,200,16,16,"TFTLCD TEST");
		LCD_ShowString(30,90,200,16,16,"ATOM@ALIENTEK");
 		LCD_ShowString(30,110,200,16,16,lcd_id);		//显示LCD ID	      					 
		LCD_ShowString(30,130,200,12,12,"2014/5/4");	      					 
		x++;
		if(x==12)
			x=0;
		LED0=!LED0;	 
		OSTimeDly(1000, OS_OPT_TIME_DLY, &err);
	}   
}


extern void MainTask(void);


/*
*********************************************************************************************************
*	函 数 名: AppTaskCreate
*	功能说明: 创建应用任务
*	形    参：p_arg 是在创建该任务时传递的形参
*	返 回 值: 无
*********************************************************************************************************
*/
void  AppTaskCreate (void)
{
	OS_ERR      err;
	
	/***********************************/
	OSTaskCreate((OS_TCB       *)&AppTask_LedTest_TCB,             
                 (CPU_CHAR     *)"LedTest",
//                 (OS_TASK_PTR   )AppTask_LedTest, 
                 (OS_TASK_PTR   )MainTask, 
                 (void         *)0,
                 (OS_PRIO       )AppTask_LedTest_PRIO,
                 (CPU_STK      *)&AppTask_LedTest_Stk[0],
                 (CPU_STK_SIZE  )APP_TASK_LED_TEST_STK_SIZE / 10,
                 (CPU_STK_SIZE  )APP_TASK_LED_TEST_STK_SIZE,
                 (OS_MSG_QTY    )1,
                 (OS_TICK       )0,
                 (void         *)0,
                 (OS_OPT        )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR       *)&err);
		 
}

