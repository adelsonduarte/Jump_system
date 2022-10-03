#include <String.h>
#include "stdio.h"
#include "SD_module.h"
#include "Data.h"
#include "main.h"
#include "stdlib.h"

//static struct config myUserConfigSave;
//struct config* userDataSave = &myUserConfigSave;

static unsigned char loadFileLineCounter = 0;

//static unsigned char myResult;
static unsigned char* myResultString;
static unsigned char* myHeaderString;

struct samples{
    unsigned char sampleNum;
    unsigned int uiVooTime;
    unsigned int uiSoloTime;
};
struct results{
    unsigned char resultTestNum;
    unsigned char resultTestAcquiredSamples;
    unsigned char thereAreData;
    unsigned char timeout;
    struct samples sampleMeasurement[MEASUREMENT_SIZE];
};

//struct config{
//    unsigned char userTest;
//    unsigned long int userTime;
//    unsigned char userMass;
//    unsigned char userOverMass;
//    unsigned char userConsultTest;
//    unsigned char userAlturaMin;
//    unsigned char userAlturaMax;
//    unsigned char userNumSaltos;
//    unsigned char userIntervalSaltos;
//    unsigned char userCMJ;
//    unsigned char userAlturaDJ;
//    unsigned char userNumSeries;
//    unsigned char userIntervalSeries;
//    unsigned char userCommConfig;
//    unsigned char userSelectTapete;
//    unsigned char userSelectSensorChannel;
//};


unsigned char* savedDataToString(struct results* dataToSave, unsigned char sample)
{
    unsigned char* stringToSave = getStringToSave();
    sprintf(stringToSave, "%d     %d     %d\n",
            dataToSave->sampleMeasurement[sample].sampleNum,
            dataToSave->sampleMeasurement[sample].uiVooTime,
            dataToSave->sampleMeasurement[sample].uiSoloTime);
    return stringToSave;
}

unsigned char setFileLineCounter(unsigned char* count)
{
    loadFileLineCounter = *count;
}

unsigned char getFileLineCounter()
{
    return loadFileLineCounter;
}

unsigned char save_data(unsigned char numTest)
{
    numTest++;
    struct results* ptr_resultDataSave;
    ptr_resultDataSave = getUserResultData(numTest);
    save_SD_card(ptr_resultDataSave,numTest);
}

unsigned char* load_data(unsigned char numTest)
{
    unsigned char* ptr_dataLoad;
    struct results* ptr_resultLoadStruct;
    ptr_dataLoad = load_SD_card(numTest);
    ptr_resultLoadStruct = loadDataArrayToStruct(ptr_dataLoad);
    return ptr_resultLoadStruct;

}

unsigned char* loadDataArrayToStruct(unsigned char* data)
{
    static struct results loadedResults; //
    struct results* ptr_loadedResults = &loadedResults;

    unsigned char (*loadData)[MAX_LINES][MAX_LEN] = data;
    unsigned char numTeste = getResultTestNumber();
    unsigned char samplesCounter = getFileLineCounter();

    ptr_loadedResults->resultTestNum = numTeste;
    ptr_loadedResults->resultTestAcquiredSamples = samplesCounter;

    for(unsigned char samples = 0; samples<samplesCounter;samples++)
    {
        ptr_loadedResults->sampleMeasurement[samples].sampleNum = (*loadData)[samples][0];
        ptr_loadedResults->sampleMeasurement[samples].uiVooTime = (*loadData)[samples][1];
        ptr_loadedResults->sampleMeasurement[samples].uiSoloTime = (*loadData)[samples][2];
    }

    return ptr_loadedResults;

}

unsigned char* getArqName(unsigned char numTeste)
{
    static unsigned char arqName[15]; //VERIFICAR SE VOU FAZER UM GET NISSO
    sprintf(arqName,"Teste %d.txt",numTeste);
    return arqName;
}

unsigned char lineCounter(unsigned char numTeste)
{
    unsigned char* arqName = getArqName(numTeste);
    char c = 0;
    unsigned char count = 0;
    FILE* ptr_file;
    ptr_file = fopen(arqName,"r");
    if (ptr_file == NULL )
    {
        printf( "error ao abrir\n");
    }
    for(c = fgetc(ptr_file); c != EOF; c = fgetc(ptr_file))
    {
        if (c == '\n') // Increment count if this character is newline
        {
          count = count + 1;
        }
    }
    fclose(ptr_file);
    return count;
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



