//#include "Data.h"
#include "stdio.h"
#include "stdlib.h"
#include "LCDHW.h"
#include "SDMEMORYHW.h"
#include "TimerHW.h"
#include "UARTHW.h"
#include "IO_interface.h"
#include "string.h"
//TESTE
#include "main.h"
<<<<<<< HEAD
#define MAX_LINES 100
#define MAX_LEN 100
//

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

=======

//

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

>>>>>>> 86ffc1670df986741b7c1944748c75133f6cec1f
unsigned char startTM1(void)
{
        printf("startTM1 \n");
//        SET_HW_TIMER1();
}

unsigned char stopTM1(void)
{
    printf("Desliga Encoder \n");
//    RESET_HW_TIMER1();
}

unsigned char startTM2(void)
{
        printf("startTM2 \n");
//        SET_HW_TIMER2();
}

unsigned char stopTM2(void)
{
    printf("stopTM2 \n");
//    RESET_HW_TIMER2();
}

unsigned char rstHardware(void)
{
    printf("ResetHardware");
//    RESET_HARDWARE();
}

unsigned char printDataDisplay(unsigned char col, unsigned char linha,unsigned char* userData)
{
    printf(userData);
    printf("\n");
//    HW_PRINT_DATA();
}

unsigned char eraseDataDisplay()
{
    system("clear");
//    HW_ERASE_DATA();
}

unsigned char updateDataDisplay(unsigned char col, unsigned char linha, unsigned char *userMessage, unsigned char* status)
{

}

unsigned char homeDataDisplay(unsigned char* appName,unsigned char* companyName,unsigned char* appVersion)
{
    printf("%s\n",appName);
    printf("%s\n",companyName);
    printf("%s\n",appVersion);
//    HW_HOME_DISP();

}

unsigned char check_SD_card()
{
    printf("HW_EXT_MEMORY_CHECK()\n");
//    HW_EXT_MEMORY_CHECK();
}

<<<<<<< HEAD
unsigned char load_SD_card(unsigned char numTeste)
{
     struct results* ptr_structConsultResult;
     static unsigned char ptr_loadStringResult[MAX_LINES][MAX_LEN];
     unsigned char line = 0;
     unsigned char i = 0;
     unsigned char* ptr_loadName = getArqName(numTeste);
//    unsigned char* ptr_loadStringResult = getUserResultData(numTeste);

    printf("HW_EXT_MEMORY_READ()\n");
=======
unsigned char* load_SD_card(unsigned char numTeste)
{
    //    printf("HW_EXT_MEMORY_READ()\n");

     static unsigned char ptr_loadStringResult[MAX_LINES][MAX_LEN];
     unsigned char line = 0;
     unsigned char column = 0;
     unsigned char count = 0;
     unsigned char* ptr_loadName = getArqName(numTeste);



        //    ptr_loadStringResult = HW_EXT_MEMORY_READ(ptr_loadName,);
>>>>>>> 86ffc1670df986741b7c1944748c75133f6cec1f
    FILE* ptr_file;
    ptr_file = fopen(ptr_loadName,"r");
    if (ptr_file == NULL )
    {
        printf( "error ao abrir\n");
    }
    else{
        printf( "Abriu load_SD_card\n");

<<<<<<< HEAD
        while(fgets(ptr_loadStringResult[line],MAX_LEN,ptr_file))
        {

            printf("ptr_loadStringResult[%d] = %s",line,ptr_loadStringResult[line]);
            line++;
        }
    }
    ptr_structConsultResult = &ptr_loadResult[0];
    printf("resultTestNum = %d\n",ptr_structConsultResult->resultTestNum);
    printf("resultTestAcquiredSamples = %d\n",ptr_structConsultResult->resultTestAcquiredSamples);


//    ptr_loadResult = HW_EXT_MEMORY_READ();
    return ptr_loadResult;
=======
        count = lineCounter(numTeste);
        setFileLineCounter(&count);

        for(line=0;line<count;line++)
        {
            for(column=0;column<4;column++)
            {
                fscanf(ptr_file,"%d",&ptr_loadStringResult[line][column]);
                if(feof(ptr_file)) break;
            }
        }
    }

//
    fclose(ptr_file);
    return ptr_loadStringResult;
>>>>>>> 86ffc1670df986741b7c1944748c75133f6cec1f
}

unsigned char save_SD_card(unsigned char* dataToSave, unsigned char numTeste)
{
    unsigned char* ptr_saveName = getArqName(numTeste);
<<<<<<< HEAD

    printf("HW_EXT_MEMORY_WRITE()\n");
    FILE* ptr_file;
    ptr_file = fopen(ptr_saveName,"a");
=======
    struct results* saveStruct = dataToSave;
    unsigned char sampleToSave = 0;

//    printf("HW_EXT_MEMORY_WRITE()\n");
    FILE* ptr_file;
    ptr_file = fopen(ptr_saveName,"w");
>>>>>>> 86ffc1670df986741b7c1944748c75133f6cec1f
    if ( ptr_file == NULL )
    {
        printf( "error ao abrir\n");
    }
    else{
        printf( "abriu save_SD_card\n");
<<<<<<< HEAD
        fputs(dataToSave,ptr_file);
=======
        for(sampleToSave = 0;sampleToSave<(saveStruct->resultTestAcquiredSamples);sampleToSave++)
        {
           fprintf(ptr_file,"%d     %ld     %d     %d",
                   saveStruct->Measurement[sampleToSave].sampleNum,
                   saveStruct->Measurement[sampleToSave].ulReadingTime,saveStruct->Measurement[sampleToSave].uiVooTime,
                   saveStruct->Measurement[sampleToSave].ucAltDistance);
           fputs("\n", ptr_file) ;
        }
>>>>>>> 86ffc1670df986741b7c1944748c75133f6cec1f
    }
    fclose(ptr_file);


//    HW_EXT_MEMORY_WRITE(dataToSave,numTeste);
}

unsigned char startCOMM()
{
    printf("SET_HW_UART2()\n");
//    SET_HW_UART2();
}

unsigned char stopCOMM()
{
    printf("RESET_HW_UART2()\n");
//    RESET_HW_UART2();
}

unsigned char transmissionCOMM()
{
        printf("TRANSMISSION_HW_UART2()\n");
//    TRANSMISSION_HW_UART2();
}

unsigned char receiveCOMM()
{
    printf("RECEIVE_HW_UART2()\n");
//    RECEIVE_HW_UART2();
}

unsigned char statusCOMM()
{
        printf("STATUS_HW_UART2()\n");
//    STATUS_HW_UART2();
}



