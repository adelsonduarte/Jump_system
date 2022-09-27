#include "main.h"
#include "SENSORHW.h"
#include "Data.h"
#include "stdlib.h"

struct samples{
    unsigned char sampleNum;
    unsigned int uiVooTime;
    unsigned int uiSoloTime;
};

struct results{
    unsigned char resultTestNum;
    unsigned char resultTestAcquiredSamples;
    unsigned char thereAreData;
    struct samples Measurement[MEASUREMENT_SIZE];
};

static struct results measuredData;

void startReadingOutsideSensor()
{
	unsigned char userState = REPOUSO;
	unsigned char sensorFlag;
	unsigned int referenceTime,currentTime,contatoTime,vooTime,totalTime = 0;
	unsigned char key = 0;
	unsigned char samples = 0;

	key = getKeyPressed();
	unsigned char indexTest = getResultTestNumber();

	while(key != PARAR) //&& totalTime != COLOCAR O VALOR DE TEMPO DE ENTRADA
	{
		totalTime = getTimer2Variable();
		key = getKeyPressed();
		switch(userState)
		{
			case REPOUSO:
				sensorFlag = getTimer2Variable();
				if(sensorFlag == 0)
				{
					userState = CONTATO;
					referenceTime = getTimer3Variable();
				}

				else userState = REPOUSO;


			break;

			case CONTATO:
				sensorFlag = getTimer2Variable();
				if(sensorFlag == 1)
				{
					userState = VOO;
					currentTime = getTimer3Variable();
					measuredData.Measurement[samples].uiSoloTime = currentTime-referenceTime;
					measuredData.Measurement[samples].sampleNum = samples+1;
//					contatoTime[samples] = currentTime-referenceTime;
					referenceTime = currentTime;
				}
				else
				{
					HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, RESET);
					userState = CONTATO;
				}

			break;

			case VOO:
				sensorFlag = getTimer2Variable();
				if(sensorFlag == 0)
				{
					userState = CONTATO;
					currentTime = getTimer3Variable();
					measuredData.Measurement[samples].uiVooTime = currentTime - referenceTime;
//					vooTime[samples] = currentTime - referenceTime;
					referenceTime = currentTime;
					samples++;
				}
				else
				{
					HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, SET);
					userState = VOO;
				}
			break;

		}
	}

    setUserResultData(&measuredData,indexTest,samples);



}
void startReadingInsideSensor()
{
//	unsigned char userState = CONTATO;
//	switch(userState)
//	{
//		case CONTATO:
//
//			start_dentro_state = VOO;
//		break;
//
//		case VOO:
//
//			start_dentro_state = CONTATO;
//		break;
//	}

}
