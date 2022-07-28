#include "Data.h"

static unsigned char encoderStatus;
static unsigned char timerStatus;

unsigned char* start_encoder(void)
{
        printf("Liga Encoder \n");
        encoderStatus = 0;
//        encoderStatus = HAL_TIM_Encoder_Start_IT(&htim2, TIM_CHANNEL_ALL);
//      delay
        return !encoderStatus;
}

unsigned char* stop_encoder(void)
{
    printf("Desliga Encoder \n");
    encoderStatus = 1;
//        encoderStatus = HAL_TIM_Encoder_Stop_IT(&htim2, TIM_CHANNEL_ALL);
//      delay
        return encoderStatus;
}

unsigned char* start_timer(void)
{
    printf("Liga Timer \n");
    timerStatus = 0;
    // timerStatus =HAL_TIM_Base_Start_IT(&htim3);
    // delay
    return !timerStatus;
}

unsigned char* stop_timer(void)
{
    printf("Desliga Timer \n");
    timerStatus = 1;
    // timerStatus =HAL_TIM_Base_Stop_IT(&htim3);
    // delay
    return timerStatus;
}

unsigned char reset_hardware(void)
{
//    for(unsigned char i=0;i<SAMPLES;i++)
//	{
//	  counterPulso[i] = 0;
//	  currentTime[i] = 0;
//	  fimPulso[contador] = 0;
//	}
}

