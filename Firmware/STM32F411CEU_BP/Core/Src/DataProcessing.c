#include "main.h"
#include "time.h"
#include "Display_module.h"
//#include "DataProcessing.h"
#include "Data.h"
#include "stdlib.h"

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

unsigned char indexColumn(short* currentColumn, unsigned char size)
{
    *currentColumn = *currentColumn -1;
    if(*currentColumn == 5) *currentColumn = *currentColumn -1;
    else if(*currentColumn == 2) *currentColumn = *currentColumn -1;
    if(*currentColumn <0)
    {
        *currentColumn = size;
    }
}

unsigned long milisecondsTime(unsigned char* ptr_inputTime)
{
	struct tm* time = ptr_inputTime;
	unsigned long int msTime = 0;

	msTime = time->tm_hour*3600;
	msTime += time->tm_min*60;
	msTime += time->tm_sec;
	msTime = msTime*1000;

	return msTime;
}

unsigned long stringToLong(unsigned char* string)
{
    char *ptr;
    unsigned long int intTime = strtol(string,&ptr,10); //REFAZER
    //fazer a convers�o de hhmmss para ms
    return intTime;
}

unsigned int stringToInt(unsigned char* string) //REFAZER
{
    char *ptr;
    unsigned int x = strtol(string,&ptr,10);
    return x;
}

unsigned char stringToFloat(unsigned char* string) //REFAZER
{
    float x = strtof(string,NULL);
    return x;
}

unsigned char stringLenght(unsigned char* str)
{
    unsigned char strLen = 0;
    for(unsigned i = 0; str[i] != '\0';i++)
        strLen++;
    return strLen;
}

unsigned char indexMass(short* index)
{
    *index = *index -1;
    if(*index == 3) *index = *index -1;
    if(*index<0)
    {
        *index = 4;
    }
}

unsigned char indexChange(short* index, unsigned char size)
{
    *index = *index - 1;
    if(*index<0)
    {
        *index = size;
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
    sprintf(massString,"%d%d%d.%d",massArray[0],massArray[1],massArray[2],massArray[4]);
    //massArray[3] ficou representando o "." no display
    return massString;
}

unsigned char* getOverMassString()
{
    unsigned char* overMassArray = getOverMassArray();
    sprintf(overMassString,"%d%d%d.%d",overMassArray[0],overMassArray[1],overMassArray[2],overMassArray[4]);
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
    sprintf(eraseTestString,"(%d)",eraseTestArray[0]);
    return eraseTestString;
}

unsigned char* getStringToSave() //fiz aqui pra ficar mais simples
{
	static unsigned char saveResultString[50];
	return saveResultString;
}

unsigned int* param_1_toString(unsigned int* string)
{
    static unsigned int result[TEST_SIZE];
    sprintf(result,"%d",*string);
    return result;
}

unsigned int* param_2_toString(unsigned int* string)
{
    static unsigned int result[TEST_SIZE];
    sprintf(result,"%dms",*string);
    return result;
}

unsigned int* param_3_toString(unsigned int* string)
{
    static unsigned int result[TEST_SIZE];
    sprintf(result,"%c",*string);
    return result;
}

unsigned char setUserAltMin(unsigned char* idx)
{
    unsigned char* altMinArray = getAltMinArray();
    unsigned char index = *idx;
    altMinArray[index] = altMinArray[index]+1;
    if(altMinArray[index]>9) altMinArray[index]= 0;
}

unsigned char setUserErase(unsigned int* idx)
{
    unsigned char* eraseArray = getEraseTestArray();
    unsigned int index = *idx;
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

unsigned char* setIntervalSaltosTime(unsigned char* configInputTimer)
{
	unsigned char index = *configInputTimer + 3;
	struct tm* insertTime = getIntervalTimeStruct();

	switch(index)
	{
		case DEZENA_M:
			insertTime->tm_min = insertTime->tm_min+10;
			if(insertTime->tm_min>60) insertTime->tm_min = 0;
		break;

		case UNIDADE_M:
			insertTime->tm_min = insertTime->tm_min+1;
			if(insertTime->tm_min>60) insertTime->tm_min = 0;
		break;

		case DEZENA_S:
			insertTime->tm_sec =insertTime->tm_sec+10 ;
			if(insertTime->tm_sec>60) insertTime->tm_sec = 0;

		break;

		case UNIDADE_S:
			insertTime->tm_sec =insertTime->tm_sec+1 ;
			if(insertTime->tm_sec>60) insertTime->tm_sec = 0;
		break;
	}

}

unsigned char* setUserTime(unsigned char* inputUserTimer)
{
    unsigned char index = *inputUserTimer;
    struct tm* insertTime = getTimeStruct();
//    static unsigned char timeString[9];

    switch(index)
    {
        case DEZENA_H:
            insertTime->tm_hour = insertTime->tm_hour+10;
            if(insertTime->tm_hour>23) insertTime->tm_hour = 0;
//            strftime(timeString, sizeof(timeString), "%H:%M:%S", insertTime);
        break;

        case UNIDADE_H:
            insertTime->tm_hour = insertTime->tm_hour+1;
            if(insertTime->tm_hour>23) insertTime->tm_hour = 0;
//            strftime(timeString, sizeof(timeString), "%H:%M:%S", insertTime);
        break;

        case DEZENA_M:
            insertTime->tm_min = insertTime->tm_min+10;
            if(insertTime->tm_min>60) insertTime->tm_min = 0;
//            strftime(timeString, sizeof(timeString), "%H:%M:%S", insertTime);
        break;

        case UNIDADE_M:
        	insertTime->tm_min = insertTime->tm_min+1;
            if(insertTime->tm_min>60) insertTime->tm_min = 0;
//            strftime(timeString, sizeof(timeString), "%H:%M:%S", insertTime);
        break;

        case DEZENA_S:
            insertTime->tm_sec =insertTime->tm_sec+10 ;
            if(insertTime->tm_sec>60) insertTime->tm_sec = 0;
//            strftime(timeString, sizeof(timeString), "%H:%M:%S", insertTime);
        break;

        case UNIDADE_S:
            insertTime->tm_sec =insertTime->tm_sec+1 ;
            if(insertTime->tm_sec>60) insertTime->tm_sec = 0;
//            strftime(timeString, sizeof(timeString), "%H:%M:%S", insertTime);
        break;
    }
}

unsigned int alturaToTempo(unsigned int altura)
{
	unsigned int tempo = 0;
	unsigned int nominator = 8 * altura;
	unsigned int  g = 981; // cm/s^2
	float relation =  nominator/g;
	tempo = sqrt(relation);
	tempo = tempo*1000;
	return tempo;
}
