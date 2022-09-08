#include <String.h>
#include "SD_module.h"
#include "Data.h"
#include "main.h"
#include "C:\MinGW\include\stdlib.h"

static struct config myUserConfigSave;
struct config* userDataSave = &myUserConfigSave;

//static unsigned char myResult;
static unsigned char* myResultString;
static unsigned char* myHeaderString;

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
    struct samples sampleMeasurement[MEASUREMENT_SIZE];
};

struct config{
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

static unsigned char msg1 = "TESTE";
static unsigned char msg2 = "AMOSTRAS";
static unsigned char msg3 = "AMOSTRA";
static unsigned char msg4 = "T_LEITURA";
static unsigned char msg5 = "T_VOO";
static unsigned char msg6 = "ALTURA";

unsigned char* getArquivoMsg()
{
    unsigned char* msgStrings[MSG_QTD][MSG_LEN];
    msgStrings[0] = msg1;
    msgStrings[1] = msg2;
    msgStrings[2] = msg3;
    msgStrings[3] = msg4;
    msgStrings[4] = msg5;
    msgStrings[5] = msg6;

    return msgStrings;
}

unsigned char* savedHeaderToString(struct results* dataToSave)
{
    unsigned char* headerString = getStringHeaderToSave();
    sprintf(headerString,"Teste %d, Amostras = %d\n",dataToSave->resultTestNum,
            dataToSave->resultTestAcquiredSamples);

    return headerString;
}


unsigned char* savedDataToString(struct results* dataToSave, unsigned char sample)
{
    unsigned char* stringToSave = getStringToSave();
    sprintf(stringToSave, "Amostra %d,Tempo de leitura = %d,Tempo de voo = %ld, Altura = %d\n",
            dataToSave->sampleMeasurement[sample].sampleNum,
            dataToSave->sampleMeasurement[sample].ulReadingTime,
            dataToSave->sampleMeasurement[sample].uiVooTime,
            dataToSave->sampleMeasurement[sample].ucAltDistance);
    return stringToSave;
}

unsigned char save_data(unsigned char numTest)
{
    static struct results* ptr_resultDataSave;
    unsigned char sampleToSave = 0;
    numTest++;
    ptr_resultDataSave = getUserResultData(numTest);
    myHeaderString = savedHeaderToString(ptr_resultDataSave);
    printf("myHeaderString = %s\n",myHeaderString);
    save_SD_card(myHeaderString,ptr_resultDataSave->resultTestNum);

    for(sampleToSave = 0;sampleToSave<(ptr_resultDataSave->resultTestAcquiredSamples);sampleToSave++)
    {
       myResultString = savedDataToString(ptr_resultDataSave,sampleToSave);
       printf("myResultString = %s\n",myResultString);
       save_SD_card(myResultString,ptr_resultDataSave->resultTestNum);
    }
}

unsigned char* load_data(unsigned char numTest)
{
    unsigned char* ptr_dataLoad;
    ptr_dataLoad = load_SD_card(numTest);
    return ptr_dataLoad;

}

unsigned char* getArqName(unsigned char numTeste)
{
    static unsigned char arqName[10];
    sprintf(arqName,"Teste %d.txt",numTeste);
    return arqName;
}










//userDataSave->userTest = getUserTest();
//    userDataSave->userTime = getUserTime();
//    userDataSave->userMass = getUserMass();
//    userDataSave->userOverMass = getUserOverMass();
//    userDataSave->userConsultTest = getUserConsultTest();
//    userDataSave->userAlturaMin = getUserAlturaMin();
//    userDataSave->userAlturaMax = getUserAlturaMax();
//    userDataSave->userIntervalSaltos = getUserIntervalSaltos();
//    userDataSave->userNumSaltos = getUserNumSaltos();
//    userDataSave->userCMJ = getUserCMJ();
//    userDataSave->userAlturaDJ = getUserAlturaDJ();
//    userDataSave->userNumSeries = getUserNumSeries();
//    userDataSave->userIntervalSeries = getUserIntervalSeries();
//    userDataSave->userCommConfig = getUserCommConfig();
//    userDataSave->userSelectTapete = getUserSelectTapete();
//    userDataSave->userSelectSensorChannel = getUserSelectSensorChannel();



