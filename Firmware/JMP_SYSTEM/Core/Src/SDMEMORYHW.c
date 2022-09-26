#include "SDMEMORYHW.h"
#include "fatfs.h"
#include "fatfs_sd.h"
//teste
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

unsigned char* HW_EXT_MEMORY_MAIN()
{
	FATFS fs;
	return &fs;
}

unsigned char HW_EXT_MEMORY_INIT(unsigned char* fs)
{
	f_mount(fs, "", 0);
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
        	f_gets(&loadDataHW[line][column],fil.fsize,&fil);
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
	FIL fil;
    HAL_Delay(500);
    f_open(&fil, nameString, FA_OPEN_ALWAYS | FA_WRITE | FA_READ);
    f_lseek(&fil, fil.fsize);
	if (&fil == NULL)
	{

//		printf( "error ao abrir\n");
	}
	else{
		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
//		printf( "abriu save_SD_card\n");
		for(sampleToSave = 0;sampleToSave<1;sampleToSave++)
		{
			f_printf(&fil,"%d     %ld     %d     %d",
				   saveStruct->Measurement[sampleToSave].sampleNum,
				   saveStruct->Measurement[sampleToSave].ulReadingTime,
				   saveStruct->Measurement[sampleToSave].uiVooTime,
				   saveStruct->Measurement[sampleToSave].ucAltDistance);
			f_puts("\n", &fil);

		}
	}
    f_close(&fil);
    return 1;
}
