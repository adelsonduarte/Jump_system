#include "SDMEMORYHW.h"
#include "fatfs.h"
#include "fatfs_sd.h"
//teste
#include "main.h"
//
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

unsigned char* HW_EXT_MEMORY_MAIN()
{
	FATFS fs;
	return &fs;
}

unsigned char HW_EXT_MEMORY_INIT(unsigned char* fs)
{
	FRESULT result;
	result = f_mount(fs, "", 0);
}

unsigned char* HW_EXT_MEMORY_READ(unsigned char* loadName,unsigned char numSamples, unsigned char* loadPointer)
{
     unsigned char line = numSamples;
     unsigned char column = 0;
     FIL fil;
    unsigned char (*loadDataHW)[MAX_LINES][MAX_LEN] = loadPointer;
   f_open(&fil, loadName, FA_OPEN_ALWAYS | FA_WRITE | FA_READ);
    for(line=0;line<numSamples;line++)
    {
        for(column=0;column<4;column++)
        {
//        	f_gets(&loadDataHW[line][column],fil.fsize,&fil);
            if(f_eof(&fil)) break;
        }
    }
    f_close(&fil);
    return loadDataHW;
}

unsigned char HW_EXT_MEMORY_WRITE(unsigned char* saveString, unsigned char* nameString)
{
	unsigned char sampleToSave = 0;
	struct results* saveStruct = saveString;
	FRESULT result;
	FIL fil;
	FATFS fs;
	result = f_mount(&fs," ", 0);
//	unsigned char* a = HW_EXT_MEMORY_MAIN();
//	HW_EXT_MEMORY_INIT(a);
    HAL_Delay(500);
    result = f_open(&fil, nameString, FA_OPEN_ALWAYS | FA_WRITE | FA_READ);
//    f_lseek(&fil, teste.fsize);
	if (&fil == NULL)
	{

//		printf( "error ao abrir\n");
	}
	else{
		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
//		printf( "abriu save_SD_card\n");
		f_puts("Amostra \tAltura(cm) \tPotência(W) \tTvoo(ms) \tTsolo(ms)\n", &fil);
		HAL_Delay(10);
		for(sampleToSave = 0;sampleToSave<saveStruct->resultTestAcquiredSamples;sampleToSave++)
		{
//			result = f_printf(&fil,"%d",10);
			f_printf(&fil,"%d \t\t %d \t\t %d \t\t %d \t\t %d",
				   saveStruct->Measurement[sampleToSave].sampleNum,
				   saveStruct->Measurement[sampleToSave].alturaSalto,
				   saveStruct->Measurement[sampleToSave].potenciaSalto,
				   saveStruct->Measurement[sampleToSave].uiVooTime,
				   saveStruct->Measurement[sampleToSave].uiSoloTime);
			HAL_Delay(100);
			result = f_puts("\n", &fil);
		}
	}
	result = f_close(&fil);
    return 1;
}
