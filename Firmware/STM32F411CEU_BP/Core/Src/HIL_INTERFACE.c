#include "main.h"
#include "IO_interface.h"
#include "stdint.h"
#include "DisplayMessages.h"
#include "HIL_INTERFACE.h"
#include "SDMEMORYHW.h"
#include "fatfs.h"
#include "fatfs_sd.h"

#if _VI
#define EXIT 'E'
#define SOLICITA '1'
#define PARA '2'

volatile uint16_t vooTime;
volatile uint16_t contatoTime;

static unsigned char userState = REPOUSO;

unsigned char getUserState()
{
	return userState;
}

unsigned char setUserState(unsigned char state)
{
	userState = state;
	return userState;
}

//hardware completamente setado
unsigned int HIL()
{
    unsigned char INIT = FALSE;
    unsigned char* uartBufRx = getRxBuffer();
    unsigned char commandRx = 0;

    while(commandRx != EXIT)
    {
        commandRx = uartBufRx[0];
        if(commandRx == SOLICITA)
        {
        	for(unsigned char i=0;i<2;i++) uartBufRx[i] = 0;
            if(INIT == FALSE)
            {
                startTM2();
                startTM3();
                INIT = TRUE;
            }
            processApplication();
        }
        else if(commandRx == PARA)
        {
        	for(unsigned char i=0;i<2;i++) uartBufRx[i] = 0;
            stopTM2();
            stopTM3();
        }

    }

    if(commandRx == EXIT)
    {
            stopTM2();
            stopTM3();
    }

    return 0;


}

void processApplication() //parei aqui
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, RESET);
	unsigned long int* uartInstance = getUARTInstance();
//	unsigned char sensorFlag;
	unsigned int contatoTime[SAMPLES];
	unsigned int vooTime[SAMPLES];
	unsigned int totalTimeArray[SAMPLES];
	unsigned int* ptr_measurementTotalTime;
	unsigned int* ptr_measurementContatoTime;
	unsigned int* ptr_measurementVooTime;
	unsigned long int alturaSalto[SAMPLES];
	unsigned char* ptr_samples;
	unsigned char* ptr_sensorFlag;
	unsigned char count = 0;
	unsigned char userSelectTapete = FALSE;
	unsigned char uartMsg[40];
	unsigned char TRANSMISSION = FALSE;
	unsigned int* ptr_totalTime;

	float aux1;
	unsigned int aux2 = 981>>3;

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

	ptr_samples = getSamplesCount();
	ptr_sensorFlag = getSensorFlag();
	ptr_totalTime = getTimer3Variable();
	ptr_measurementContatoTime = getTimeSolo();
	ptr_measurementVooTime = getTimeVoo();
	unsigned int transitionStateTime = 0;

    while(TRANSMISSION == FALSE) //AQUI
    {
    	switch(userState)
		{
			case REPOUSO:
				if(*ptr_sensorFlag == 0 && userSelectTapete == FALSE) //INICIO FORA DO TAPETE
				{
					userState = CONTATO;
					transitionStateTime = *ptr_totalTime;
				}
				else
				{
					while(*ptr_samples < SAMPLES)
					{
						totalTimeArray[*ptr_samples] = *ptr_totalTime;
						contatoTime[*ptr_samples] = 0;
						vooTime[*ptr_samples] = 0;
						if(*ptr_samples == SAMPLES)
						{
							resetSamplesCount();
							for(unsigned i=0;i<SAMPLES;i++)
							{
								totalTimeUnion.all = totalTimeArray[i];
								for(unsigned j=2;j>0;j--)
								{
									uartMsg[count] = totalTimeUnion.pt[j-1];
									count++;
								}
								alturaSaltoUnion.all = vooTime[i];
								for(unsigned j=2;j>0;j--)
								{
									uartMsg[count] = alturaSaltoUnion.pt[j-1];
									count++;
								}
							}
							TRANSMISSION_HW_UART(uartInstance,uartMsg);
							TRANSMISSION = TRUE;
							resetSamplesCount();
							count=0;
						}
					}
				}
			break;

			case CONTATO:
				if(*ptr_sensorFlag == 1)
				{
					userState = VOO;
					transitionStateTime = *ptr_totalTime;
				}
				else
				{
					while(*ptr_samples < SAMPLES)
					{
						totalTimeArray[*ptr_samples] = *ptr_totalTime;
						contatoTime[*ptr_samples] = *ptr_totalTime - transitionStateTime;
						vooTime[*ptr_samples] = 0;
						if(*ptr_samples == SAMPLES)
						{
							resetSamplesCount();
							for(unsigned i=0;i<SAMPLES;i++)
							{
								totalTimeUnion.all = totalTimeArray[i];
								for(unsigned j=2;j>0;j--)
								{
									uartMsg[count] = totalTimeUnion.pt[j-1];
									count++;
								}
								alturaSaltoUnion.all = vooTime[i];
								for(unsigned j=2;j>0;j--)
								{
									uartMsg[count] = alturaSaltoUnion.pt[j-1];
									count++;
								}
							}
							TRANSMISSION_HW_UART(uartInstance,uartMsg);
							TRANSMISSION = TRUE;
							resetSamplesCount();
							count=0;
						}
					}
				}

			break;

			case VOO:
				if(*ptr_sensorFlag  == 0)
				{

					userState = CONTATO;
					transitionStateTime = *ptr_totalTime;
				}
				else
				{
					while(*ptr_samples < SAMPLES)
					{
						totalTimeArray[*ptr_samples] = *ptr_totalTime;
						contatoTime[*ptr_samples] = 0;
						vooTime[*ptr_samples] = *ptr_totalTime - transitionStateTime;
						if(*ptr_samples == SAMPLES)
						{
							resetSamplesCount();
							for(unsigned i=0;i<SAMPLES;i++)
							{
								totalTimeUnion.all = totalTimeArray[i];
								for(unsigned j=2;j>0;j--)
								{
									uartMsg[count] = totalTimeUnion.pt[j-1];
									count++;
								}
								alturaSaltoUnion.all = vooTime[i];
								for(unsigned j=2;j>0;j--)
								{
									uartMsg[count] = alturaSaltoUnion.pt[j-1];
									count++;
								}
							}
							TRANSMISSION_HW_UART(uartInstance,uartMsg);
							TRANSMISSION = TRUE;
							count=0;
						}
					}
				}
			break;
		}
    }
}
#endif

#if _MEASUREVALIDATION

#define AMOSTRAS 102
uint16_t contatoTimeSamples[AMOSTRAS] = {0,0,0,0,0};

uint16_t vooTimeSamples[AMOSTRAS] = {0,0,0,0,0};

void measureValidation(void)
{
	unsigned char key = 0;
	unsigned char logicZeroFile[30];
	unsigned char logicOneFile[30];
	unsigned char idx = 0;
	uint32_t accum1 = 0;
	uint32_t accum2 = 0;
	float TvooAVG,TcontatoAVG;
	while(1)
	{
		do
		{
//			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, SET);
			key = (unsigned char)getKeyPressed();
		}
		while(key != CONFIRMAR);
		validation();
		stopTM2();
		stopTM3();
		resetKeyPressed();
		idx++;
//		sprintf(logicZeroFile,"Tcontato_meas_%d.txt",idx);
//		sprintf(logicOneFile,"Tvoo_meas_%d.txt",idx);
//		SAVE_ARRAY(contatoTimeString, logicZeroFile);
//		SAVE_ARRAY(vooTimeString, logicOneFile);
//		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, RESET);
	}

}
void validation(void)
{
	uint32_t* ptr_totalTime;
	unsigned char* ptr_samples;
	unsigned char userState = REPOUSO;

	unsigned char key = 0;
	unsigned char* ptr_sensorFlag;
	uint32_t contatoTime,vooTime;
	ptr_totalTime = (uint16_t*)getTimer3Variable();
	ptr_sensorFlag = (unsigned char*)getSensorFlag();
	ptr_samples = (unsigned char*)getSamplesCount();
	uint32_t transitionStateTime=0;
	unsigned char transitionString[50];
	unsigned char contatoTimeString[30];
	unsigned char vooTimeString[30];
	uint16_t contato = 0;
	unsigned char voo = 0;
	startTM2();
	startTM3();

	while(key!=PARAR)
	{
//		key = (unsigned char)getKeyPressed();
//		if(contato == AMOSTRAS && voo == AMOSTRAS) key = PARAR;
		switch(userState)
		{
			case REPOUSO:
				if(*ptr_sensorFlag == 0) //INICIO FORA DO TAPETE
				{
					userState = CONTATO;
					transitionStateTime = *ptr_totalTime;
//					sprintf((char*)transitionString,"Trepouso = %d",(char*)transitionStateTime);
//					HW_PRINT_DATA(0,USERMSG2,transitionString);
				}
				else userState = REPOUSO;
			break;

			case CONTATO:
				if(*ptr_sensorFlag == 1)
				{
					userState = VOO;
					contatoTime = *ptr_totalTime - transitionStateTime;
//					contatoTimeSamples[contato] = contatoTime;
//					contato++;
//					transitionStateTime = *ptr_totalTime;
//					HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, SET);
					transitionStateTime = *ptr_totalTime;
				}
				else
				{
					userState = CONTATO;
				}

			break;

			case VOO:
				if(*ptr_sensorFlag  == 0)
				{
					userState = CONTATO;
					vooTime = *ptr_totalTime - transitionStateTime;
//					vooTimeSamples[voo] = vooTime;
//					voo++;
//					transitionStateTime = *ptr_totalTime;
//					HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, RESET);
					sprintf((char*)vooTimeString,"Tvoo = %d",(char*)vooTime);
					HW_PRINT_DATA(0,INSERTMSG,vooTimeString);
					sprintf((char*)contatoTimeString,"Tcontato = %d",(char*)contatoTime);
					HW_PRINT_DATA(0,USERMSG2,contatoTimeString);
					transitionStateTime = *ptr_totalTime;
				}
				else
				{
					userState = VOO;
				}
			break;
		}
	}
	contato = 0;
	voo = 0;
}
unsigned char SAVE_ARRAY(uint16_t* saveString, unsigned char* nameString)
{
	uint16_t sampleToSave = 0;
	unsigned char idx = 1;
	FRESULT result;
	FIL fil;
	FATFS fs;
	result = f_mount(&fs," ", 0);
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
		f_puts("Amostra \tTempo(us)\n", &fil);
		HAL_Delay(10);
		for(sampleToSave = 0;sampleToSave<AMOSTRAS;sampleToSave++)
		{
//			result = f_printf(&fil,"%d",10);
			f_printf(&fil,"%d \t\t %d",idx,saveString[sampleToSave]);
			idx++;
//			HAL_Delay(10);
			result = f_puts("\n", &fil);
		}
	}
    idx = 0;
	result = f_close(&fil);
    return 1;

}
#endif


