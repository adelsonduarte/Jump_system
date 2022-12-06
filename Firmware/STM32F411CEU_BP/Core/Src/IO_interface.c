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
#include "stdint.h"
#include "FLASH_SECTOR_F4.h"

#define FLASH_ADDRESS 0x08060000

//

union vooTime
{
	unsigned int all;
	unsigned char pt[2];

};
union vooTime vooTimeUnion = {.all=0};

union soloTime
{
	unsigned int all;
	unsigned char pt[2];

};
union soloTime soloTimeUnion = {.all=0};

union totalTime
{
	unsigned int all;
	unsigned char pt[2];

};
union totalTime totalTimeUnion = {.all=0};

union alturaSalto
{
	unsigned int all;
	unsigned char pt[2];

};
union alturaSalto alturaSaltoUnion = {.all=0};


struct dataInsert{
    unsigned char userTest;
    unsigned long int userTime;
    unsigned char userMass;
    unsigned char userOverMass;
    unsigned char userConsultTest;
    unsigned int userAlturaMin;
    unsigned int userAlturaMax;
    unsigned char userNumSaltos;
    unsigned long int  userIntervalSaltos;
    unsigned char userCMJ;
    unsigned char userAlturaDJ;
    unsigned char userNumSeries;
    unsigned long int userIntervalSeries;
    unsigned char userCommConfig;
    unsigned char userSelectTapete;
    unsigned char userSelectSensorChannel;
};

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

void startTM2(void)
{
        SET_HW_TIMER2();
}

void stopTM2(void)
{
    RESET_HW_TIMER2();
}

void startTM3(void)
{
        SET_HW_TIMER3();
//        resetTimer3Variable();
}

void stopTM3(void)
{
    RESET_HW_TIMER3();
}


void eraseDataDisplay()
{
    HW_ERASE_DATA();
}

void homeDataDisplay(unsigned char* appName,unsigned char* companyName,unsigned char* appVersion)
{
//    printf("%s\n",appName);
//    printf("%s\n",companyName);
//    printf("%s\n",appVersion);
    HW_HOME_DISP(appName,companyName,appVersion);

}

void mount_SD()
{
	unsigned char* fs =  HW_EXT_MEMORY_MAIN();
	HW_EXT_MEMORY_INIT(fs);
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



     ptr_loadStringResult = HW_EXT_MEMORY_READ(ptr_loadName,count,ptr_loadStringResult);
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

void save_SD_card(unsigned char* dataToSave, unsigned char numTeste)
{
	numTeste++;
    unsigned char* ptr_saveName = getArqName(numTeste);
//    struct results* saveStruct = dataToSave;
//    unsigned char sampleToSave = 0;
    HW_EXT_MEMORY_WRITE(dataToSave,ptr_saveName);
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

void startCOMM()
{
//    printf("SET_HW_UART2()\n");
	unsigned char* uartInstance = getUARTInstance();
	SET_HW_UART(uartInstance);
}

void stopCOMM()
{
//    printf("RESET_HW_UART2()\n");
	unsigned char* uartInstance = getUARTInstance();
	RESET_HW_UART(uartInstance);
}

void transmissionCOMM()
{
	//	unsigned char numTeste = 1;
	unsigned int numTeste = getResultTestNumber();
	unsigned int count = 0;
	unsigned int aux = 0;
	struct results* teste = getUserResultData(numTeste);
	unsigned char uartMsg[50];
	/*PayloadSize (resultTestAcquiredSamples) = 4 + 5 x resultTestAcquiredSamples
	 * Defined: resultTestAcquiredSamples = 100
	 * Result: PayloadSize = 504 bytes
	 * Justify: It is an engineering in order to transmission up to 100 samples for each test
	 * I am extrapolating here...
	 *
	 * For debug : resultTestAcquiredSamples = 5
	 *
	 *
	 */


// For debug
//	teste->resultTestNum = 1;
//	teste->resultTestAcquiredSamples = 5;
//	teste->thereAreData = 0;
//	teste->timeout = 0;
//	teste->Measurement[0].sampleNum = 1;
//	teste->Measurement[0].uiVooTime = 1140;
//	teste->Measurement[0].uiSoloTime = 4040;
//	teste->Measurement[1].sampleNum = 2;
//	teste->Measurement[1].uiVooTime = 2260;
//	teste->Measurement[1].uiSoloTime = 2010;
//	teste->Measurement[2].sampleNum = 3;
//	teste->Measurement[2].uiVooTime = 3260;
//	teste->Measurement[2].uiSoloTime = 3010;
//	teste->Measurement[3].sampleNum = 4;
//	teste->Measurement[3].uiVooTime = 4260;
//	teste->Measurement[3].uiSoloTime = 4010;
//	teste->Measurement[4].sampleNum = 5;
//	teste->Measurement[4].uiVooTime = 5260;
//	teste->Measurement[4].uiSoloTime = 5010;
//

	uartMsg[0] = teste->resultTestNum;
	uartMsg[1] = teste->resultTestAcquiredSamples;
	uartMsg[2] = teste->thereAreData;
	uartMsg[3] = teste->timeout;

	for(unsigned char i=0;i<teste->resultTestAcquiredSamples;i++)
	{
		uartMsg[4+aux] = teste->Measurement[i].sampleNum;
//		vooTimeUnion.all = teste->Measurement[i].uiVooTime;
		totalTimeUnion.all = teste->Measurement[i].measureTime;
		for(unsigned j=2;j>0;j--)
		{
//			uartMsg[5+count+aux] = vooTimeUnion.pt[j-1];
			uartMsg[5+count+aux] = totalTimeUnion.pt[j-1];
			count++;
		}
		count = 0;

//		soloTimeUnion.all = teste->Measurement[i].uiSoloTime;
		alturaSaltoUnion.all = teste->Measurement[i].alturaSalto;
		for(unsigned j=2;j>0;j--)
		{
//			uartMsg[7+count+aux] = soloTimeUnion.pt[j-1];
			uartMsg[7+count+aux] = alturaSaltoUnion.pt[j-1];

			count++;
		}
		count = 0;
		aux += 5;
	}
	//Tamanho do pacote = 4+5xresultTestAcquiredSamples
	unsigned long int* uartInstance = getUARTInstance();
	TRANSMISSION_HW_UART(uartInstance,uartMsg);
}

void receiveCOMM()
{
//    printf("RECEIVE_HW_UART2()\n");
//    RECEIVE_HW_UART2();
}

unsigned int wflashConfigData(struct dataInsert* data)
{
	uint32_t flash[16];
	flash[0] = data->userTime;
	flash[1] = data->userTest;
	flash[2] = data->userMass;
	flash[3] = data->userOverMass;
	flash[4] = data->userConsultTest;
	flash[5] = data->userAlturaMin;
	flash[6] = data->userAlturaMax;
	flash[7] = data->userNumSaltos;
	flash[8] = data->userIntervalSaltos;
	flash[9] = data->userCMJ;
	flash[10] = data->userAlturaDJ;
	flash[11] = data->userNumSeries;
	flash[12] = data->userIntervalSeries;
	flash[13] = data->userCommConfig;
	flash[14] = data->userSelectTapete;
	flash[15] = data->userSelectSensorChannel;



//	Flash_Write_Data(FLASH_ADDRESS, (uint32_t *)flash, 16);
	Flash_Write_Data(FLASH_ADDRESS, flash, 16);
	return 1;
}

void rflashConfigData(void)
{
    struct dataInsert* dataFlashConfig = getUserConfigStruct();
	uint32_t flashData[30];
	Flash_Read_Data(FLASH_ADDRESS, flashData, 16);
	dataFlashConfig->userTime = flashData[0];
	dataFlashConfig->userTest = flashData[1];
	dataFlashConfig->userMass = flashData[2];
	dataFlashConfig->userOverMass = flashData[3];
	dataFlashConfig->userConsultTest = flashData[4];
	dataFlashConfig->userAlturaMin = flashData[5];
	dataFlashConfig->userAlturaMax = flashData[6];
	dataFlashConfig->userNumSaltos = flashData[7];
	dataFlashConfig->userIntervalSaltos = flashData[8];
	dataFlashConfig->userCMJ = flashData[9];
	dataFlashConfig->userAlturaDJ = flashData[10];
	dataFlashConfig->userNumSeries = flashData[11];
	dataFlashConfig->userIntervalSeries = flashData[12];
	dataFlashConfig->userCommConfig = flashData[13];
	dataFlashConfig->userSelectTapete = flashData[14];
	dataFlashConfig->userSelectSensorChannel = flashData[15];
}


