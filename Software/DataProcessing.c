#include "main.h"
#include "time.h"
#include "Display_module.h"
#include "Data.h"
#include "C:\MinGW\include\stdlib.h"

static unsigned char massString[10];
static unsigned char overMassString[10];
static unsigned char altMinString[10];
static unsigned char altMaxString[10];
static unsigned char numSaltosString[10];
static unsigned char interSaltosString[10];
static unsigned char tipoSaltoString[10];
static unsigned char altDJString[10];
static unsigned char numSeriesString[10];
static unsigned char interSeriesString[10];
static unsigned char numTestString[10];
static unsigned char eraseTestString[10];

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

unsigned char indexChange(unsigned char* index, unsigned char size)
{
    *index = *index +1;
    if(*index==size)
    {
        *index = 0;
    }
}

unsigned char* getAltMinString()
{
    unsigned char* altMinArray = getAltMinArray();
    sprintf(altMinString,"%d%d%d",altMinArray[0],altMinArray[1],altMinArray[2]);
    return altMinString;
}

unsigned char* getAltMaxString()
{
    unsigned char* altMaxArray = getAltMaxArray();
    sprintf(altMaxString,"%d%d%d",altMaxArray[0],altMaxArray[1],altMaxArray[2]);
    return altMaxString;
}

unsigned char* getNumSaltosString()
{
    unsigned char* numSaltosArray = getNumSaltosArray();
    sprintf(numSaltosString,"%d%d%d",numSaltosArray[0],numSaltosArray[1],numSaltosArray[2]);
    return numSaltosString;
}

unsigned char* getIntervalSaltosString()
{
    unsigned char* IntervalSaltosArray = getIntervalSaltosArray();
    sprintf(interSaltosString,"%d%d%d",IntervalSaltosArray[0],IntervalSaltosArray[1],IntervalSaltosArray[2]);
    return interSaltosString;
}

unsigned char* getTypeJumpString()
{
    unsigned char* typeJumpArray = getTypeJumpArray();
    sprintf(tipoSaltoString,"%d",typeJumpArray[0]);
    return tipoSaltoString;
}

unsigned char* getAltDJString()
{
    unsigned char* altDJArray = getAltDJArray();
    sprintf(altDJString,"%d%d%",altDJArray[0],altDJArray[1]);
    return altDJString;
}

unsigned char* getNumSeriesString()
{
    unsigned char* numSeriesArray = getNumSeriesArray();
    sprintf(numSeriesString,"%d%d%d",numSeriesArray[0],numSeriesArray[1],numSeriesArray[2]);
    return numSeriesString;
}

unsigned char* getIntervalSeriesString()
{
    unsigned char* intervalSeriesArray = getIntervalSeriesArray();
    sprintf(interSeriesString,"%d%d%d",intervalSeriesArray[0],intervalSeriesArray[1],intervalSeriesArray[2]);
    return interSeriesString;
}

unsigned char* getMassString()
{
    unsigned char* massArray = getMassArray();
    sprintf(massString,"%d%d%d.%d",massArray[0],massArray[1],massArray[2],massArray[3]);
    return massString;
}

unsigned char* getOverMassString()
{
    unsigned char* overMassArray = getOverMassArray();
    sprintf(overMassString,"%d%d%d.%d",overMassArray[0],overMassArray[1],overMassArray[2],overMassArray[3]);
    return overMassString;
}

unsigned char* getNumTestString()
{
    unsigned char* numTestArray = getNumTestArray();
    sprintf(numTestString,"%d%d%d",numTestArray[0],numTestArray[1],numTestArray[2]);
    return numTestString;
}

unsigned char* getEraseTestString()
{
    unsigned char* eraseTestArray = getEraseTestArray();
    sprintf(eraseTestString,"%d",eraseTestArray[0]);
    return eraseTestString;
}

unsigned char* getStringHeaderToSave() //fiz aqui pra ficar mais simples
{
        static unsigned char saveHeaderString[50];
        return saveHeaderString;
}

unsigned char* getStringToSave() //fiz aqui pra ficar mais simples
{
        static unsigned char saveResultString[50];
        return saveResultString;
}

unsigned int* param_1_toString(unsigned char* string)
{
    static unsigned char result[TEST_SIZE];
    sprintf(result,"%d",*string);
    return result;
}

unsigned int* param_2_toString(unsigned char* string)
{
    static unsigned char result[TEST_SIZE];
    sprintf(result,"%d",*string);
    return result;
}

unsigned int* param_3_toString(unsigned char* string)
{
    static unsigned char result[TEST_SIZE];
    sprintf(result,"%d",*string);
    return result;
}

unsigned char setUserAltMin(unsigned char* idx)
{
    unsigned char* altMinArray = getAltMinArray();
    unsigned char index = *idx;
    altMinArray[index] = altMinArray[index]+1;
    if(altMinArray[index]>9) altMinArray[index]= 0;
}

unsigned char setUserErase(unsigned char* idx)
{
    unsigned char* eraseArray = getEraseTestArray();
    unsigned char index = *idx;
    eraseArray[index] = eraseArray[index]+1;
    if(eraseArray[index]>9) eraseArray[index]= 0;
}

unsigned char setUserAltMax(unsigned char* idx)
{
    unsigned char* altMaxArray = getAltMaxArray();
    unsigned char index = *idx;
    altMaxArray[index] = altMaxArray[index]+1;
    if(altMaxArray[index]>9) altMaxArray[index]= 0;
}

unsigned char setUserNumSaltos(unsigned char* idx)
{
    unsigned char* numSaltosArray = getNumSaltosArray();
    unsigned char index = *idx;
    numSaltosArray[index] = numSaltosArray[index]+1;
    if(numSaltosArray[index]>9) numSaltosArray[index]= 0;
}

unsigned char setUserIntervalSaltos(unsigned char* idx)
{
    unsigned char* intervalSaltosArray = getIntervalSaltosArray();
    unsigned char index = *idx;
    intervalSaltosArray[index] = intervalSaltosArray[index]+1;
    if(intervalSaltosArray[index]>9) intervalSaltosArray[index]= 0;
}

unsigned char setUserTypeJump(unsigned char* idx)
{
    unsigned char* typeJumpArray = getTypeJumpArray();
    unsigned char index = *idx;
    typeJumpArray[index] = typeJumpArray[index]+1;
    if(typeJumpArray[index]>3) typeJumpArray[index]= 0;
}

unsigned char setUserAltDJ(unsigned char* idx)
{
    unsigned char* AltDJArray = getAltDJArray();
    unsigned char index = *idx;
    AltDJArray[index] = AltDJArray[index]+1;
    if(AltDJArray[index]>9) AltDJArray[index]= 0;
}

unsigned char setUserNumSeries(unsigned char* idx)
{
    unsigned char* numSeriesArray = getNumSeriesArray();
    unsigned char index = *idx;
    numSeriesArray[index] = numSeriesArray[index]+1;
    if(numSeriesArray[index]>9) numSeriesArray[index]= 0;
}

unsigned char setUserIntervalSeries(unsigned char* idx)
{
    unsigned char* IntervalSeriesArray = getIntervalSeriesArray();
    unsigned char index = *idx;
    IntervalSeriesArray[index] = IntervalSeriesArray[index]+1;
    if(IntervalSeriesArray[index]>9) IntervalSeriesArray[index]= 0;
}

unsigned char setUserMass(unsigned char* idx)
{
    unsigned char* massArray = getMassArray();
    unsigned char index = *idx;
    massArray[index] = massArray[index]+1;
    if(massArray[index]>9) massArray[index]= 0;
}

unsigned char setUserOverMass(unsigned char* idx)
{
    unsigned char* overMassArray = getOverMassArray();
    unsigned char index = *idx;
    overMassArray[index] = overMassArray[index]+1;
    if(overMassArray[index]>9) overMassArray[index]= 0;
}

unsigned char setUserNumTest(unsigned char* idx)
{
    unsigned char* numTestArray = getNumTestArray();
    unsigned char index = *idx;
    numTestArray[index] = numTestArray[index]+1;
    if(numTestArray[index]>9) numTestArray[index]= 0;
}
//unsigned char* setIntervaloSaltosTime(unsigned char* inputUserTimer)
//{
//
//}
unsigned char* setUserTime(unsigned char* inputUserTimer)
{
    unsigned char index = *inputUserTimer;
    struct tm* insertTime = getTimeStruct();
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
