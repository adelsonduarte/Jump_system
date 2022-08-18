//User interface module: Aqui ser� possivel setar os parametros de entrada do usuario
#include "main.h"
#include "stdio.h"
#include "Display_module.h"
//#include "LiquidCrystal.h"
#include "time.h"
#include "C:\MinGW\include\stdlib.h"

//static LiquidCrystal lcdDisplay;

struct tm myTime;
struct tm* insertTime = &myTime;

unsigned char massArray[] = {0,0,0,0};
unsigned char massString[10];

unsigned char overMassArray[] = {0,0,0,0};
unsigned char overMassString[10];



unsigned char startUserInterface(unsigned char* appName,unsigned char* companyName,unsigned char* appVersion)
{
    homeDataDisplay(appName, companyName, appVersion);
}

unsigned char updateUserMsg(unsigned char col, unsigned char linha, unsigned char *userMessage, unsigned char* status)
{
	if(*status == IDDLE)
	{
	    printDataDisplay(col,linha,userMessage);
		*status = PRINTED;
	}
}

unsigned char eraseUserInterface()
{
    eraseDataDisplay();
}

unsigned char readyUserInterface(unsigned char* displayStatus,unsigned char* cursorPosition)
{
	statusUserInterface(displayStatus);
//	resetKeyPressed();
	resetCursorInterface(cursorPosition);
}

unsigned char statusUserInterface(unsigned char* displayStatus)
{
	*displayStatus = IDDLE;
}

unsigned char insertUserInterface(unsigned char col, unsigned char linha,unsigned char* userData)
{
    printDataDisplay(col,linha,userData);
}

unsigned char cursorChangeInterface(unsigned char col, unsigned char linha)
{
	unsigned char actualposition = col;
	actualposition++;
	if(actualposition == 15) actualposition=0;
//	setCursor(&lcdDisplay, actualposition, linha);
	return actualposition;
}

unsigned char resetCursorInterface(unsigned char* cursorPosition)
{
	cursorPosition[0] = 0;
	cursorPosition[1] = 0;
}

unsigned char* setUserTime(unsigned char* inputUserTimer)
{
    unsigned char index = *inputUserTimer;
    static unsigned char timeString[9];

    switch(index)
    {
        case DEZENA_H:
            insertTime->tm_hour = insertTime->tm_hour+10;
            if(insertTime->tm_hour>23) insertTime->tm_hour = 0;
            strftime(timeString, sizeof(timeString), "%H:%M:%S", insertTime);
        break;

        case UNIDADE_H:
            insertTime->tm_hour = insertTime->tm_hour+1;
            if(insertTime->tm_hour>23) insertTime->tm_hour = 0;
            strftime(timeString, sizeof(timeString), "%H:%M:%S", insertTime);
        break;

        case DEZENA_M:
            insertTime->tm_min = insertTime->tm_min+10;
            if(insertTime->tm_min>60) insertTime->tm_min = 0;
            strftime(timeString, sizeof(timeString), "%H:%M:%S", insertTime);
        break;

        case UNIDADE_M:
            insertTime->tm_min = insertTime->tm_min+1;
            if(insertTime->tm_min>60) insertTime->tm_min = 0;
            strftime(timeString, sizeof(timeString), "%H:%M:%S", insertTime);
        break;

        case DEZENA_S:
            printf("idx = %d\n",index);
            insertTime->tm_sec =insertTime->tm_sec+10 ;
            if(insertTime->tm_sec>60) insertTime->tm_sec = 0;
            strftime(timeString, sizeof(timeString), "%H:%M:%S", insertTime);
        break;

        case UNIDADE_S:
            printf("idx = %d\n",index);
            insertTime->tm_sec =insertTime->tm_sec+1 ;
            if(insertTime->tm_sec>60) insertTime->tm_sec = 0;
            strftime(timeString, sizeof(timeString), "%H:%M:%S", insertTime);
        break;
    }
    return timeString;
}

unsigned char indexTime(unsigned char* index)
{
    *index = *index +1;
    if(*index == 2) *index = *index +1;
    else if(*index == 5)*index = *index +1;
    if(*index==8)
    {
        *index = 0;
    }
}

unsigned char* getTimeStruct()
{
    return insertTime;
}

unsigned long stringToLong(unsigned char* string)
{
    char *ptr;
    unsigned long int intTime = strtol(string,&ptr,10);
    //fazer a conversão de hhmmss para ms
    return intTime;
}

unsigned int stringToInt(unsigned char* string)
{
    char *ptr;
    unsigned int x = strtol(string,&ptr,10);
    return x;
}

unsigned char stringToFloat(unsigned char* string)
{
    float x = strtof(string,NULL);
    return x;
}

unsigned char indexMass(unsigned char* index)
{
    *index = *index +1;
    if(*index==4)
    {
        *index = 0;
    }
}

unsigned char* getMassArray()
{
    return massArray;
}

unsigned char* getMassString()
{
    sprintf(massString,"%d%d%d.%d",massArray[0],massArray[1],massArray[2],massArray[3]);
    return massString;
}

unsigned char* getOverMassArray()
{
    return overMassArray;
}

unsigned char* getOverMassString()
{
    sprintf(overMassString,"%d%d%d.%d",overMassArray[0],overMassArray[1],overMassArray[2],overMassArray[3]);
    return overMassString;
}

unsigned int* param_1_toString(unsigned char* string)
{
    static unsigned char result[5];
    sprintf(result,"%d",*string);
    return result;
}
unsigned int* param_2_toString(unsigned char* string)
{
    static unsigned char result[5];
    sprintf(result,"%d",*string);
    return result;
}

unsigned int* param_3_toString(unsigned char* string)
{
    static unsigned char result[5];
    sprintf(result,"%d",*string);
    return result;
}

unsigned char* setUserMass(unsigned char* idx)
{
    unsigned char index = *idx;
    massArray[index] = massArray[index]+1;
    if(massArray[index]>9) massArray[index]= 0;
    sprintf(massString,"%d%d%d.%d",massArray[0],massArray[1],massArray[2],massArray[3]);
    return massString;
}

unsigned char* setUserOverMass(unsigned char* idx)
{
    unsigned char index = *idx;
    overMassArray[index] = overMassArray[index]+1;
    if(overMassArray[index]>9) overMassArray[index]= 0;
    sprintf(overMassString,"%d%d%d.%d",overMassArray[0],overMassArray[1],overMassArray[2],overMassArray[3]);
    return overMassString;
}







