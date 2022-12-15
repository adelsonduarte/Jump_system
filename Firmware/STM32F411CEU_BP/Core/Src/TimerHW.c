#include "main.h"
#include "TimerHW.h"
#include "IO_interface.h"

static unsigned char encoderStatus;
static unsigned char timerStatus;

unsigned char SET_HW_TIMER2(void)
{
	encoderStatus = 0;
//	TIM_HandleTypeDef* htim2 =  getTimer2Instance();
	TIM_HandleTypeDef* htim2 =  getTimer2Instance();
	encoderStatus = HAL_TIM_Encoder_Start_IT(htim2, TIM_CHANNEL_ALL);
	return !encoderStatus;
}

unsigned char RESET_HW_TIMER2(void)
{
    encoderStatus = 1;
//    TIM_HandleTypeDef* htim2 =  getTimer2Instance();
    TIM_HandleTypeDef* htim2 =  getTimer2Instance();
	encoderStatus = HAL_TIM_Encoder_Stop_IT(htim2, TIM_CHANNEL_ALL);
	HAL_Delay(100);
	return encoderStatus;
}

unsigned char SET_HW_TIMER3(void)
{
    timerStatus = 0;
    TIM_HandleTypeDef* htim3 =  getTimer3Instance();
    __HAL_TIM_SET_COUNTER(htim3,0);
    timerStatus =HAL_TIM_Base_Start_IT(htim3);
    return !timerStatus;
}

unsigned char RESET_HW_TIMER3(void)
{
    timerStatus = 1;
    TIM_HandleTypeDef* htim3 =  getTimer3Instance();
    timerStatus = HAL_TIM_Base_Stop(htim3);
    __HAL_TIM_SET_COUNTER(htim3,0);
//     timerStatus =HAL_TIM_Base_Stop_IT(htim3);
    return timerStatus;
}
