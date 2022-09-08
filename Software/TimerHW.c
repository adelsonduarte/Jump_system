#include "main.h"
#include "TimerHW.h"
#include "IO_interface.h"

static unsigned char encoderStatus;
static unsigned char timerStatus;

unsigned char SET_HW_TIMER1(void)
{
        encoderStatus = 0;
//        encoderStatus = HAL_TIM_Encoder_Start_IT(&htim2, TIM_CHANNEL_ALL);
//      delay
        return !encoderStatus;
}

unsigned char RESET_HW_TIMER1(void)
{
    encoderStatus = 1;
//        encoderStatus = HAL_TIM_Encoder_Stop_IT(&htim2, TIM_CHANNEL_ALL);
//      delay
        return encoderStatus;
}

unsigned char SET_HW_TIMER2(void)
{
    timerStatus = 0;
    // timerStatus =HAL_TIM_Base_Start_IT(&htim3);
    // delay
    return !timerStatus;
}

unsigned char RESET_HW_TIMER2(void)
{
    timerStatus = 1;
    // timerStatus =HAL_TIM_Base_Stop_IT(&htim3);
    // delay
    return timerStatus;
}
