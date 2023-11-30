#include "cmsis_os.h"
#include "remote_control.h"
#include "tim.h"
#include "bsp_tim.h"
void PWM_Task(void const * argument)
{
   for(;;)
	{
		if(remote_ctrl.rc.s[0]==3)
		{
	 __HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_1,3800);
	HAL_Delay(10);
	__HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_1,6000);
		HAL_Delay(10);
//	__HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_1,185);
//	HAL_Delay(10);
//	__HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_1,180);
//		HAL_Delay(10);
//	__HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_1,175);
//		HAL_Delay(10);
	  }else if(remote_ctrl.rc.s[0]==2)
		__HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_1,1600);
	HAL_Delay(10);
	
	
	}






}
