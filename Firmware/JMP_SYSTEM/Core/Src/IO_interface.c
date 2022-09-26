//#include "Data.h"
#include "stdio.h"
#include "stdlib.h"
#include "LCDHW.h"
#include "SDMEMORYHW.h"
#include "TimerHW.h"
#include "UARTHW.h"
#include "IO_interface.h"
#include "string.h"
#include "UARTHW.h"
//TESTE
#include "main.h"

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

unsigned char startTM2(void)
{
        SET_HW_TIMER2();
}

unsigned char stopTM2(void)
{
    RESET_HW_TIMER2();
}

unsigned char startTM3(void)
{
        SET_HW_TIMER3();
}

unsigned char stopTM3(void)
{
    RESET_HW_TIMER3();
}

unsigned char rstHardware(void)
{
//    RESET_HARDWARE();
}

unsigned char printDataDisplay(unsigned char col, unsigned char linha,unsigned char* userData)
{
    HW_PRINT_DATA(col, linha,userData);
}

unsigned char insertDataDisplay(unsigned char col, unsigned char linha,unsigned char* userData)
{
	HW_INSERT_DATA(col, linha,userData);
}


unsigned char eraseDataDisplay()
{
    HW_ERASE_DATA();
}

unsigned char updateDataDisplay(unsigned char col, unsigned char linha)
{
	HW_UPDATE_DATA(col,linha);
}

unsigned char homeDataDisplay(unsigned char* appName,unsigned char* companyName,unsigned char* appVersion)
{
//    printf("%s\n",appName);
//    printf("%s\n",companyName);
//    printf("%s\n",appVersion);
    HW_HOME_DISP(appName,companyName,appVersion);

}

unsigned char mount_SD()
{
	unsigned char* fs =  HW_EXT_MEMORY_MAIN();
	HW_EXT_MEMORY_INIT(fs);
}

unsigned char check_SD_card()
{
//    HW_EXT_MEMORY_CHECK();
}

unsigned char* load_SD_card(unsigned char numTeste)
{
     unsigned char (*ptr_loadStringResult)[MAX_LINES][MAX_LEN];
     unsigned char loadStringResult;
     unsigned char line = 0;
     unsigned char column = 0;
     unsigned char count = 0;
     unsigned char* ptr_loadName = getArqName(numTeste);
     count = lineCounter(numTeste);
     setFileLineCounter(&count);



//     ptr_loadStringResult = HW_EXT_MEMORY_READ(ptr_loadName,count,ptr_loadStringResult);
     //COMENTADO DEVIDO AO PROBLEMA DE MEMORIA
//    FILE* ptr_file;
//    ptr_file = fopen(ptr_loadName,"r");
//    if (ptr_file == NULL )
//    {
//        printf( "error ao abrir\n");
//    }
//    else{
//        printf( "Abriu load_SD_card\n");
//
//        count = lineCounter(numTeste);
//        setFileLineCounter(&count);
//
//        for(line=0;line<count;line++)
//        {
//            for(column=0;column<4;column++)
//            {
//                fscanf(ptr_file,"%d",&ptr_loadStringResult[line][column]);
//                if(feof(ptr_file)) break;
//            }
//        }
//    }
//
////
//    fclose(ptr_file);
    return ptr_loadStringResult;
}

unsigned char save_SD_card(unsigned char* dataToSave, unsigned char numTeste)
{
    unsigned char* ptr_saveName = getArqName(numTeste);
    struct results* saveStruct = dataToSave;
    unsigned char sampleToSave = 0;
//    HW_EXT_MEMORY_WRITE(dataToSave,ptr_saveName);
    //COMENTADO DEVIDO AO PROBLEMA DE MEMORIA

//    FILE* ptr_file;
//    ptr_file = fopen(ptr_saveName,"w");
//    if ( ptr_file == NULL )
//    {
//        printf( "error ao abrir\n");
//    }
//    else{
//        printf( "abriu save_SD_card\n");
//        for(sampleToSave = 0;sampleToSave<(saveStruct->resultTestAcquiredSamples);sampleToSave++)
//        {
//           fprintf(ptr_file,"%d     %ld     %d     %d",
//                   saveStruct->Measurement[sampleToSave].sampleNum,
//                   saveStruct->Measurement[sampleToSave].ulReadingTime,
//				   saveStruct->Measurement[sampleToSave].uiVooTime,
//                   saveStruct->Measurement[sampleToSave].ucAltDistance);
//           fputs("\n", ptr_file) ;
//        }
//    }
//    fclose(ptr_file);



}

unsigned char startCOMM()
{
//    printf("SET_HW_UART2()\n");
	unsigned char* uartInstance = getUARTInstance();
	SET_HW_UART(uartInstance);
}

unsigned char stopCOMM()
{
//    printf("RESET_HW_UART2()\n");
	unsigned char* uartInstance = getUARTInstance();
	RESET_HW_UART(uartInstance);
}

unsigned char transmissionCOMM(unsigned char* msg)
{
//        printf("TRANSMISSION_HW_UART2()\n");
	unsigned char uartMsg[10] = "ADELSON10";
//	unsigned char uartMsg[10];
//	sprintf(uartMsg,"%d",msg);
	unsigned char* uartInstance = getUARTInstance();
	TRANSMISSION_HW_UART(uartInstance,uartMsg);
}

unsigned char receiveCOMM()
{
//    printf("RECEIVE_HW_UART2()\n");
//    RECEIVE_HW_UART2();
}

unsigned char statusCOMM()
{
//        printf("STATUS_HW_UART2()\n");
//    STATUS_HW_UART2();
}



