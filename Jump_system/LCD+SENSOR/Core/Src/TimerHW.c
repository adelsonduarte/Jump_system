#include "main.h"
#include "TimerHW.h"

static unsigned char encoderStatus;
static unsigned char timerStatus;

unsigned char SET_HW_TIMER2(unsigned char* instance)
{
	encoderStatus = 0;
	TIM_HandleTypeDef* htim2 =  instance;
	encoderStatus = HAL_TIM_Encoder_Start_IT(htim2, TIM_CHANNEL_ALL);
	return !encoderStatus;
}

unsigned char RESET_HW_TIMER2(unsigned char* instance)
{
    encoderStatus = 1;
    TIM_HandleTypeDef* htim2 =  instance;
	encoderStatus = HAL_TIM_Encoder_Stop_IT(htim2, TIM_CHANNEL_ALL);
	HAL_Delay(100);
	return encoderStatus;
}

unsigned char SET_HW_TIMER3(unsigned char* instance)
{
    timerStatus = 0;
    TIM_HandleTypeDef* htim3 =  instance;
    timerStatus =HAL_TIM_Base_Start(htim3);
//    __HAL_TIM_SET_COUNTER(htim3,0);
    return !timerStatus;
}

unsigned char RESET_HW_TIMER3(unsigned char* instance)
{
    timerStatus = 1;
    TIM_HandleTypeDef* htim3 =  instance;
    timerStatus = HAL_TIM_Base_Stop(htim3);
//     timerStatus =HAL_TIM_Base_Stop_IT(htim3);
    return timerStatus;
}
