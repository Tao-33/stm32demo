#include "stm32f10x.h"                  // Device header
extern float Kp,Ki,Kd;
float err;
float err_sum=0;
float err_diff;
float err_last=0;

extern float VKp,VKi;
float filt_velocity;
float last_filt_velocity=0;
float velocity_sum=0;

void I_xianfu(int16_t value)
{
	if(velocity_sum>value)  velocity_sum=value;
	if(velocity_sum<-value) velocity_sum=-value;
}

int Vertical_Pid(float measure,float ideal)
{
	err = measure-ideal;
	err_diff = err-err_last;
	err_last = err;
	return (int)(Kp*err+Kd*err_diff);
}

int Speed_Pid(float measure,float ideal)
{
	float a=0.3;                                           //滤波系数（反映滤波程度）
	filt_velocity = a*measure + (1-a)*last_filt_velocity; //一阶速度滤波
	velocity_sum +=  filt_velocity;                        
	I_xianfu(800);                                 
	last_filt_velocity = filt_velocity;                    
	return VKp*filt_velocity + VKi*velocity_sum;
	
}


