#include <String.h>
#include "stdio.h"
#include "SD_module.h"
#include "Data.h"
#include "main.h"
#include "C:\MinGW\include\stdlib.h"

static struct config myUserConfigSave;
struct config* userDataSave = &myUserConfigSave;

<<<<<<< HEAD
=======
static unsigned char loadFileLineCounter = 0;

>>>>>>> 86ffc1670df986741b7c1944748c75133f6cec1f
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

<<<<<<< HEAD
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
=======

unsigned char* savedDataToString(struct results* dataToSave, unsigned char sample)
{
    unsigned char* stringToSave = getStringToSave();
    sprintf(stringToSave, "%d     %d     %ld     %d\n",
            dataToSave->sampleMeasurement[sample].sampleNum,
            dataToSave->sampleMeasurement[sample].ulReadingTime,
            dataToSave->sampleMeasurement[sample].uiVooTime,
            dataToSave->sampleMeasurement[sample].ucAltDistance);
    return stringToSave;
}

unsigned char setFileLineCounter(unsigned char* count)
{
    loadFileLineCounter = *count;
}

unsigned char getFileLineCounter()
{
    return loadFileLineCounter;
>>>>>>> 86ffc1670df986741b7c1944748c75133f6cec1f
}

unsigned char save_data(unsigned char numTest)
{
<<<<<<< HEAD
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
=======
    numTest++;
    struct results* ptr_resultDataSave;
    ptr_resultDataSave = getUserResultData(numTest);
    save_SD_card(ptr_resultDataSave,numTest);
>>>>>>> 86ffc1670df986741b7c1944748c75133f6cec1f
}

unsigned char* load_data(unsigned char numTest)
{
    unsigned char* ptr_dataLoad;
<<<<<<< HEAD
    ptr_dataLoad = load_SD_card(numTest);
    return ptr_dataLoad;

}

unsigned char* getArqName(unsigned char numTeste)
{
    static unsigned char arqName[10];
=======
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
        ptr_loadedResults->sampleMeasurement[samples].ulReadingTime = (*loadData)[samples][1];
        ptr_loadedResults->sampleMeasurement[samples].uiVooTime = (*loadData)[samples][2];
        ptr_loadedResults->sampleMeasurement[samples].ucAltDistance = (*loadData)[samples][3];
    }

    return ptr_loadedResults;

}

unsigned char* getArqName(unsigned char numTeste)
{
    static unsigned char arqName[15]; //VERIFICAR SE VOU FAZER UM GET NISSO
>>>>>>> 86ffc1670df986741b7c1944748c75133f6cec1f
    sprintf(arqName,"Teste %d.txt",numTeste);
    return arqName;
}

<<<<<<< HEAD
=======
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

>>>>>>> 86ffc1670df986741b7c1944748c75133f6cec1f









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



