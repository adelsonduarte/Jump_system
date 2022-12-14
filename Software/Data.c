#include <stdio.h>
#include <stdlib.h>
#include "Data.h"
#include "main.h"
#include "time.h"

struct samples{
    unsigned char sampleNum;
    unsigned long int ulReadingTime;
    unsigned int uiVooTime;
    unsigned char ucAltDistance;
};

struct results{
    unsigned char resultTestNum;
    unsigned char resultTestAcquiredSamples;
    unsigned char thereAreData;
    struct samples Measurement[MEASUREMENT_SIZE];
};

struct dataInsert{
    unsigned char userTest;
    unsigned long int userTime;
    unsigned char userMass;
    unsigned char userOverMass;
    unsigned char userConsultTest;
    unsigned char userAlturaMin;
    unsigned char userAlturaMax;
    unsigned char userNumSaltos;
    unsigned char userIntervalSaltos;
    unsigned char userCMJ;
    unsigned char userAlturaDJ;
    unsigned char userNumSeries;
    unsigned char userIntervalSeries;
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

static unsigned char massArray[] = {0,0,0,0};
static unsigned char overMassArray[] = {0,0,0,0};
static unsigned char altMinArray[] = {0,0,0};
static unsigned char altMaxArray[] = {0,0,0};
static unsigned char numSaltosArray[] = {0,0,0};
static unsigned char intervalSaltosArray[] = {0,0,0};
static unsigned char altDJArray[] = {0,0};
static unsigned char JumpTypeArray[] = {0};
static unsigned char numSeriesArray[] = {0,0,0};
static unsigned char intervalSeriesArray[] = {0,0,0};
static unsigned char numTestArray[] = {0,0,1};
static unsigned char selectEraseArray[] = {0};

static unsigned char numberTest = 0;


unsigned long int getUserTest()
{
   return myData.userTest;
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

unsigned char* getIntervalSaltosArray()
{
    return intervalSaltosArray;
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

unsigned char* getIntervalSeriesArray()
{
    return intervalSeriesArray;
}

unsigned char* getNumTestArray()
{
    return numTestArray;
}

unsigned char* getEraseTestArray()
{
    return selectEraseArray;
}

unsigned char* getUserConfigStruct() //VERIFICAR SE VOU USAR
{
    static struct dataInsert configStruct;
    configStruct = myData;
    return &configStruct;
}

unsigned char setUserInputConfigData(struct dataInsert* dataToInsert)
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


    printf("myData.userTest = %d\n",myData.userTest);
    printf("myData.userTime = %ld\n",myData.userTime);
    printf("myData.userMass = %d\n",myData.userMass);
    printf("myData.userOverMass = %d\n",myData.userOverMass);
    printf("myData.userConsultTest = %d\n",myData.userConsultTest);
    printf("myData.userAlturaMin = %d\n",myData.userAlturaMin);
    printf("myData.userAlturaMax = %d\n",myData.userAlturaMax);
    printf("myData.userNumSaltos = %d\n",myData.userNumSaltos);
    printf("myData.userIntervalSaltos = %d\n",myData.userIntervalSaltos);
    printf("myData.userCMJ = %d\n",myData.userCMJ);
    printf("myData.userAlturaDJ = %ld\n",myData.userAlturaDJ);
    printf("myData.userNumSeries = %d\n",myData.userNumSeries);
    printf("myData.userIntervalSeries = %d\n",myData.userIntervalSeries);
    printf("myData.userCommConfig = %d\n",myData.userCommConfig);
    printf("myData.userSelectTapete = %d\n",myData.userSelectTapete);
    printf("myData.userSelectSensorChannel = %d\n",myData.userSelectSensorChannel);
}

unsigned char* getUserResultData(unsigned char numTest)
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

unsigned char setUserResultData(struct results* structDataResult, unsigned char numTest, unsigned char numSample)
{
    myResults[numTest].resultTestNum = numTest+1;
    myResults[numTest].resultTestAcquiredSamples = numSample;
    myResults[numTest].thereAreData = TRUE;
    for(unsigned char i = 0;i<numSample;i++)
    {
        myResults[numTest].Measurement[i].sampleNum = structDataResult->Measurement[i].sampleNum;
        myResults[numTest].Measurement[i].ulReadingTime = structDataResult->Measurement[i].ulReadingTime;
        myResults[numTest].Measurement[i].uiVooTime = structDataResult->Measurement[i].uiVooTime;
        myResults[numTest].Measurement[i].ucAltDistance = structDataResult->Measurement[i].ucAltDistance;
    }

    for(unsigned char i = 0;i<numSample;i++)
    {
      printf("myResults[%d].Measurement[%d].sampleNum = %d\n",numTest,i,myResults[numTest].Measurement[i].sampleNum);
    printf("myResults[%d].Measurement[%d].ulReadingTime  = %d\n",numTest,i,myResults[numTest].Measurement[i].ulReadingTime);
    printf("myResults[%d].Measurement[%d].uiVooTime = %d\n",numTest,i,myResults[numTest].Measurement[i].uiVooTime);
    printf("myResults[%d].Measurement[%d].ucAltDistance = %d\n",numTest,i,myResults[numTest].Measurement[i].ucAltDistance);
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
        structToReset->Measurement[i].ulReadingTime = 0;
        structToReset->Measurement[i].uiVooTime = 0;
        structToReset->Measurement[i].ucAltDistance = 0;
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
            myResults[test].Measurement[sample].ulReadingTime = 0;
            myResults[test].Measurement[sample].uiVooTime = 0;
            myResults[test].Measurement[sample].ucAltDistance = 0;
        }

    }
}

