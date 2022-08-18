//#include "Data.h"
#include "stdio.h"
#include "stdlib.h"


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
//    printf("Liga Timer \n");
    timerStatus = 0;
    // timerStatus =HAL_TIM_Base_Start_IT(&htim3);
    // delay
    return !timerStatus;
}

unsigned char* stop_timer(void)
{
//    printf("Desliga Timer \n");
    timerStatus = 1;
    // timerStatus =HAL_TIM_Base_Stop_IT(&htim3);
    // delay
    return timerStatus;
}


unsigned char reset_hardware(void)
{

}

unsigned char printDataDisplay(unsigned char col, unsigned char linha,unsigned char* userData)
{
    printf(userData);
    printf("\n");
//	unsigned char buffer[2];
//	setCursor(&lcdDisplay, col, linha);
//	cursor(&lcdDisplay);
//	HAL_Delay(250);
//	noCursor(&lcdDisplay);
//	HAL_Delay(250);
//	sprintf(buffer,"%d",*userData);
//	print(&lcdDisplay,buffer);
}

unsigned char eraseDataDisplay()
{
    system("clear");
//	clear(&lcdDisplay);
}

unsigned char updateDataDisplay(unsigned char col, unsigned char linha, unsigned char *userMessage, unsigned char* status)
{

}

unsigned char homeDataDisplay(unsigned char* appName,unsigned char* companyName,unsigned char* appVersion)
{
    printf("%s\n",appName);
    printf("%s\n",companyName);
    printf("%s\n",appVersion);
//	begin(&lcdDisplay,16,4,LCD_5x10DOTS);
//	setCursor(&lcdDisplay, 0, 0);
//	print(&lcdDisplay,appName);
//	setCursor(&lcdDisplay, 0, 1);
//	print(&lcdDisplay,companyName);
//	setCursor(&lcdDisplay, 0, 3);
//	print(&lcdDisplay,appVersion);
//	return &(lcdDisplay);
}





