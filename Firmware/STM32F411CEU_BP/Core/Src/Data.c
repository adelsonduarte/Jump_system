#include <stdio.h>
#include <stdlib.h>
#include "Data.h"
#include "main.h"
#include "time.h"

struct samples{
    unsigned char sampleNum;
    unsigned int uiVooTime;
    unsigned int uiSoloTime;
    unsigned int measureTime;
    unsigned int alturaSalto;
    unsigned int potenciaSalto;
};

struct results{
    unsigned char resultTestNum;
    unsigned char resultTestAcquiredSamples;
    unsigned char thereAreData;
    unsigned char timeout;
    struct samples Measurement[MEASUREMENT_SIZE];
};

struct dataInsert{
    unsigned char userTest;
    unsigned long int userTime;
    unsigned char userMass;
    unsigned char userOverMass;
    unsigned char userConsultTest;
    unsigned int userAlturaMin;
    unsigned int userAlturaMax;
    unsigned char userNumSaltos;
    unsigned long int userIntervalSaltos;
    unsigned char userCMJ;
    unsigned char userAlturaDJ;
    unsigned char userNumSeries;
    unsigned long int userIntervalSeries;
    unsigned char userCommConfig;
    unsigned char userSelectTapete;
    unsigned char userSelectSensorChannel;
};
struct Menu{
        unsigned char menuNext;
        unsigned char menuSelect;
        unsigned char menuDisplay;
        unsigned char menuState;
        struct dataInsert menuInsert;
    };

static struct dataInsert myData;
static struct results myResults[TEST_SIZE];
static struct tm myTime;
struct tm* insertTime = &myTime;
static struct tm intervalSaltosTime;
struct tm* intervalSaltos = &intervalSaltosTime;

static struct tm intervalSeriesTime;
struct tm* intervalSeries = &intervalSeriesTime;

static unsigned char massArray[] = {0,0,0,0,0};
static unsigned char overMassArray[] = {0,0,0,0,0};
static unsigned char altMinArray[] = {0,0,0}; //cm
static unsigned char altMaxArray[] = {0,0,0}; //cm
static unsigned char numSaltosArray[] = {0,0,1};

static unsigned char altDJArray[] = {0,0};
static unsigned char JumpTypeArray[] = {0};
static unsigned char numSeriesArray[] = {0,0,1};
//static unsigned char intervalSeriesArray[] = {0,0,0};
static unsigned char numTestArray[] = {0,0,0};
static unsigned char selectEraseArray[] = {0};


static unsigned char numberTest = 0;

unsigned char setNumSeriesTest() //Funcao somenet para teste
{
	return myData.userNumSeries;
}

unsigned long int getUserTime()
{
    return myData.userTime;
}

unsigned char getUserMass()
{
    return myData.userMass;
}

unsigned char getUserOverMass()
{
    return myData.userOverMass;
}

unsigned char getUserConsultTest()
{
    return myData.userConsultTest;
}

unsigned char getUserAlturaMin()
{
    return myData.userAlturaMin;
}

unsigned char getUserAlturaMax()
{
    return myData.userAlturaMax;
}

unsigned char getUserNumSaltos()
{
    return myData.userNumSaltos;
}

unsigned char getUserIntervalSaltos()
{
    return myData.userIntervalSaltos;
}

unsigned char getUserCMJ()
{
    return myData.userCMJ;
}

unsigned char getUserAlturaDJ()
{
    return myData.userAlturaDJ;
}

unsigned char getUserNumSeries()
{
    return myData.userNumSeries;
}

unsigned char getUserIntervalSeries()
{
    return myData.userIntervalSeries;
}

unsigned char getUserCommConfig()
{
    return myData.userCommConfig;
}

unsigned char getUserSelectSensorChannel()
{
    return myData.userSelectSensorChannel;
}

unsigned char getUserSelectTapete()
{
    return myData.userSelectTapete;
}

unsigned char* getTimeStruct()
{
    return insertTime;
}

unsigned char* getIntervalSaltosTimeStruct()
{
    return intervalSaltos;
}

unsigned char* getintervalSeriesTimeStruct()
{
    return intervalSeries;
}

unsigned char* getMassArray()
{
    return massArray;
}

unsigned char* getOverMassArray()
{
    return overMassArray;
}

unsigned char* getAltMinArray()
{
    return altMinArray;
}

unsigned char* getAltMaxArray()
{
    return altMaxArray;
}

unsigned char* getNumSaltosArray()
{
    return numSaltosArray;
}


unsigned char* getTypeJumpArray()
{
    return JumpTypeArray;
}

unsigned char* getAltDJArray()
{
    return altDJArray;
}

unsigned char* getNumSeriesArray()
{
    return numSeriesArray;
}

unsigned char* getNumTestArray()
{
    return numTestArray;
}

unsigned char* getEraseTestArray()
{
    return selectEraseArray;
}

unsigned char* getUserConfigStruct() //VERIFICAR SE VOU USAR -- por enquanto sim 26/10
{
	return &myData;
}

unsigned int getTimeAltMin()
{
	return myData.userAlturaMin;
}

unsigned int getTimeAltMax()
{
	return myData.userAlturaMax;
}


unsigned char setUserInputConfigData(struct dataInsert* dataToInsert) //alterar
{
    myData.userTest = dataToInsert->userTest;
    myData.userTime = dataToInsert->userTime;
    myData.userMass = dataToInsert->userMass;
    myData.userOverMass = dataToInsert->userOverMass;
    myData.userConsultTest = dataToInsert->userConsultTest;
    myData.userAlturaMin = dataToInsert->userAlturaMin;
    myData.userAlturaMax = dataToInsert->userAlturaMax;
    myData.userNumSaltos = dataToInsert->userNumSaltos;
    myData.userIntervalSaltos = dataToInsert->userIntervalSaltos;
    myData.userCMJ = dataToInsert->userCMJ;
    myData.userAlturaDJ = dataToInsert->userAlturaDJ;
    myData.userNumSeries = dataToInsert->userNumSeries;
    myData.userIntervalSeries = dataToInsert->userIntervalSeries;
    myData.userCommConfig = dataToInsert->userCommConfig;
    myData.userSelectTapete = dataToInsert->userSelectTapete;
    myData.userSelectSensorChannel = dataToInsert->userSelectSensorChannel;
}

unsigned int* getUserResultData(unsigned char numTest)
{
    return &myResults[numTest-1];
}

unsigned char getResultTestNumber()
{
    return numberTest;
}

unsigned char getThereAreData(unsigned char numTest)
{
    return myResults[numTest].thereAreData;
}

unsigned char getTimeout(unsigned char numTest)
{
    return myResults[numTest].timeout;
}

unsigned char getResultOccupiedFlag(unsigned char numTest)
{
    return  myResults[numTest].thereAreData;
}

unsigned char setResultOccupiedFlag(unsigned char numTest)
{
     myResults[numTest].thereAreData = TRUE;
}

unsigned char setResultTestNumber()
{
     numberTest++;
}

unsigned char setUserResultData(struct results* structDataResult, unsigned char numTest)
{
	unsigned char numSample = structDataResult->resultTestAcquiredSamples;
    myResults[numTest].resultTestNum = numTest+1;
    myResults[numTest].resultTestAcquiredSamples = numSample;
    myResults[numTest].thereAreData = TRUE;
    for(unsigned char i = 0;i<numSample;i++)
    {
        myResults[numTest].Measurement[i].sampleNum = structDataResult->Measurement[i].sampleNum;
        myResults[numTest].Measurement[i].alturaSalto = structDataResult->Measurement[i].alturaSalto;
        myResults[numTest].Measurement[i].potenciaSalto = structDataResult->Measurement[i].potenciaSalto;
        myResults[numTest].Measurement[i].uiSoloTime = structDataResult->Measurement[i].uiSoloTime;
        myResults[numTest].Measurement[i].uiVooTime = structDataResult->Measurement[i].uiVooTime;
    }
}

unsigned char resetResultStruct(struct results* structToReset) //verificar se vai precisar
{
    structToReset->resultTestNum = 0;
    structToReset->resultTestAcquiredSamples = 0;
    structToReset->thereAreData = FALSE;
    for(unsigned char i = 0;i<MEASUREMENT_SIZE;i++)
    {
        structToReset->Measurement[i].sampleNum = 0;
        structToReset->Measurement[i].alturaSalto = 0;
        structToReset->Measurement[i].uiSoloTime = 0;
    }

}

unsigned char resetConfigStruct(struct dataInsert* structToReset)
{
    structToReset->userTest = 0;
    structToReset->userAlturaDJ = 0;
    structToReset->userAlturaMax = 0;
    structToReset->userAlturaMin = 0;
    structToReset->userCMJ = 0;
    structToReset->userCommConfig = 0;
    structToReset->userConsultTest = 0;
    structToReset->userIntervalSaltos = 0;
    structToReset->userIntervalSeries = 0;
    structToReset->userMass = 0;
    structToReset->userNumSaltos = 0;
    structToReset->userNumSeries = 0;
    structToReset->userOverMass = 0;
    structToReset->userSelectSensorChannel = 0;
    structToReset->userSelectTapete = 0;
    structToReset->userTime = 0;

}

void resetMyResults()
{
    numberTest = 0;
    for(unsigned char test=0;test<TEST_SIZE;test++)
    {
        myResults[test].resultTestNum = 0;
        myResults[test].resultTestAcquiredSamples = 0;
        myResults[test].thereAreData = FALSE;
        for(unsigned sample=0;sample<MEASUREMENT_SIZE;sample++)
        {
            myResults[test].Measurement[sample].sampleNum = 0;
            myResults[test].Measurement[sample].alturaSalto = 0;
            myResults[test].Measurement[sample].uiSoloTime = 0;
        }

    }
}

