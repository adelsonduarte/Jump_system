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
//        resetTimer3Variable();
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

unsigned char transmissionCOMM()
{
	//	unsigned char numTeste = 1;
	unsigned char numTeste = getResultTestNumber();
	unsigned char count = 0;
	unsigned char aux = 0;
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
		vooTimeUnion.all = teste->Measurement[i].uiVooTime;
		for(unsigned j=2;j>0;j--)
		{
			uartMsg[5+count+aux] = vooTimeUnion.pt[j-1];
			count++;
		}
		count = 0;

		soloTimeUnion.all = teste->Measurement[i].uiSoloTime;
		for(unsigned j=2;j>0;j--)
		{
			uartMsg[7+count+aux] = soloTimeUnion.pt[j-1];
			count++;
		}
		count = 0;
		aux += 5;
	}
	//Tamanho do pacote = 4+5xresultTestAcquiredSamples
	unsigned long int* uartInstance = getUARTInstance();
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



