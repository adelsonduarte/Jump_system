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
    unsigned char timeout;
    struct samples Measurement[MEASUREMENT_SIZE];
};

static struct results measuredData;

unsigned char startReadingOutsideSensor()
{
	unsigned char userState = REPOUSO;
	unsigned char sensorFlag;
	unsigned int referenceTime,currentTime,totalTime = 0;
	unsigned int contatoTime[5] = {0,0,0,0,0};
	unsigned int vooTime[5]= {0,0,0,0,0};
	unsigned char key = 0;
	unsigned char samples = 0;


	unsigned char indexTest = getResultTestNumber();
	unsigned long int userTime = getUserTime();
	userTime = userTime/100;
	key = getKeyPressed();
//	unsigned int altMin = stringToInt(getAltMinString());
//	unsigned int altMax = stringToInt(getAltMaxString());

	while(key != PARAR && totalTime != userTime) //&& totalTime != COLOCAR O VALOR DE TEMPO DE ENTRADA
	{ //parei aqui, pensar em alguma flag para avisar que o totaltime == usertime e forçar a parada da leitura
		totalTime = getTimer3Variable();
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
					contatoTime[samples] = currentTime-referenceTime;
					referenceTime = currentTime;
				}
				else
				{
//					HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, RESET);
					userState = CONTATO;
				}

			break;

			case VOO:
				sensorFlag = getTimer2Variable();

				if(sensorFlag == 0)
				{
					userState = CONTATO;
					currentTime = getTimer3Variable();
					vooTime[samples] = currentTime - referenceTime;
					referenceTime = currentTime;
					samples++;
				}
				else
				{
//					HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, SET);
					userState = VOO;
				}
			break;

		}
	}
	if(totalTime == userTime)
	{
		measuredData.timeout = TRUE;
		return TIMEOUT;
	}

	else
	{
		measuredData.timeout = FALSE;
		measuredData.resultTestAcquiredSamples = samples;
		for(unsigned i=0;i<samples;i++)
		{
			measuredData.Measurement[i].sampleNum = i+1;
			measuredData.Measurement[i].uiVooTime = vooTime[i]*100;
			measuredData.Measurement[i].uiSoloTime = contatoTime[i]*100;
			setUserResultData(&measuredData,indexTest);
			return PARAR;
		}
	}
}

unsigned char startReadingInsideSensor()
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

void calcAltura()
{

}

void calcPotencia()
{

}
