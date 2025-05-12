#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "MPU6050.h"
#include "inv_mpu.h"
#include "Timer.h"
#include "Pid.h"
#include "PWM.h"
#include "Motor.h"
#include "Encoder.h"
float Kp=-420,Ki=0,Kd=-1900;//Kp为负值，Kd为负值  -420 -1800
float VKp=180,VKi=0.9;
extern int cnt;
float Pitch,Roll,Yaw;								//俯仰角默认跟中值一样，翻滚角，偏航角
int16_t ax,ay,az,gx,gy,gz;							//加速度陀螺仪角速度

u8 MPU_Get_Gyroscope(short *gx,short *gy,short *gz);
u8 MPU_Get_Accelerometer(short *ax,short *ay,short *az);

int main(void)
{
	OLED_Init();
	MPU6050_Init();
	MPU6050_DMP_Init();
	Timer_Init();
	Motor_Pin_Init();
	Motor_Init();
	Left_Encoder_Init();
	Right_Encoder_Init();
	OLED_ShowString(1,1,"duty");
	OLED_ShowString(2,1,"speed");
	OLED_ShowString(3,1,"cnt");
	OLED_ShowString(4,1,"pitch");
	while (1)
	{
//		SetDuty(2880,2880);
//		if(Pitch>30|Pitch<-30){SetDuty(0,0);}
		OLED_ShowSignedNum(1,7,GetDuty(),5);
		OLED_ShowSignedNum(2,7,Get_L_Speed(),5);	
		OLED_ShowSignedNum(3, 7, cnt, 5);	
		OLED_ShowSignedNum(4, 7, Pitch, 5);
		SetDuty(2000,2000);

	}
}	
//		MPU6050_DMP_Get_Data(&Pitch,&Roll,&Yaw);				//读取姿态信息(其中偏航角有飘移是正常现象)
//		if(MPU_Get_Gyroscope(&gx,&gy,&gz)==0){OLED_ShowString(1,1,"ok");}
//		else{OLED_ShowString(1,1,"2");}
//		MPU_Get_Gyroscope(&gx,&gy,&gz);
//		MPU_Get_Accelerometer(&ax,&ay,&az);

//		OLED_ShowSignedNum(3, 1, Roll, 5);
//		OLED_ShowSignedNum(4, 1, Yaw, 5);
//		OLED_ShowSignedNum(2, 8, gx, 5);
//		OLED_ShowSignedNum(3, 8, gy, 5);
//		OLED_ShowSignedNum(4, 8, gz, 5);
