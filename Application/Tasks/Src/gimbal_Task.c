#include "Gimbal_Task.h"
#include "cmsis_os.h"
#include "motor.h"
#include "remote_control.h"
#include "arm_math.h"
#include "gpio.h"
#include "bsp_can.h"
#include "CANTx_Task.h"
#include "pid.h"
#include "bsp_uart.h"
#include "tim.h"
Gimbal_Info_Typedef Gimbal_Info={
	.v1=0,
	.v2=0,
  .SendValue=0,
};
float Gimbal_PID_v1_Param[6]={15,0,0,0.f,5000.f,15000,};
float Gimbal_PID_v2_Param[6]={15,0,0,0.f,5000.f,15000,};

PID_Info_TypeDef Gimbal_PID_v1;
PID_Info_TypeDef Gimbal_PID_v2;
static void Gimbal_Task_Init(void);

static void Gimbal(Gimbal_Info_Typedef *Gimbal_Info);
  
void gimbal_Task(void const * argument)
{
	
  Gimbal_Task_Init();  
  for(;;)
{
	Gimbal( &Gimbal_Info); 
	if(remote_ctrl.rc.s[1]==1)
	{
		//卸力
	  Gimbal_Info.SendValue[0]=0;
		Gimbal_Info.SendValue[1]=0;
	}
//限幅
  VAL_LIMIT(Gimbal_Info.Target.v1_velocity,-10,1000);
	VAL_LIMIT(Gimbal_Info.Target.v2_velocity,-10,1000);   
  osDelay(1);	
}

}

static void Gimbal_Task_Init(){
  PID_Init(&Gimbal_PID_v1,PID_POSITION,Gimbal_PID_v1_Param); 
  PID_Init(&Gimbal_PID_v2,PID_POSITION,Gimbal_PID_v2_Param);
}
static void Gimbal(Gimbal_Info_Typedef *Gimbal_Info){
	//云台速度关联遥控器
  Gimbal_Info->Target.v1_velocity=remote_ctrl.rc.ch[1]*6;
	Gimbal_Info->Target.v2_velocity=remote_ctrl.rc.ch[1]*6;
	
	//云台速度关联PID
	Gimbal_Info->SendValue[0]=f_PID_Calculate(&Gimbal_PID_v1,Gimbal_Info->Target.v1_velocity,Gimbal_motor[motor1].Data.velocity);
	Gimbal_Info->SendValue[1]=f_PID_Calculate(&Gimbal_PID_v2,Gimbal_Info->Target.v2_velocity,Gimbal_motor[motor2].Data.velocity);
	
	
}
