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
	unsigned int referenceTime,currentTime,totalTime,spentTimeVoo,spentTimeSolo = 0;
	unsigned int contatoTime[5] = {0,0,0,0,0};
	unsigned int vooTime[5]= {0,0,0,0,0};
	unsigned char key = 0;
	unsigned char samples = 0;


	unsigned char indexTest = getResultTestNumber();
	unsigned long int userTime = getUserTime();
//	unsigned int timeMin = getTimeAltMin();
//	unsigned int timeMax = getTimeAltMax();
	unsigned int timeMin = 2000;
	unsigned int timeMax = 5000;
//	userTime = userTime/100;
	key = getKeyPressed();

//	while(key != PARAR && totalTime != userTime)
	while(key != PARAR)
	{
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
					spentTimeSolo = currentTime-referenceTime;
//					contatoTime[samples] = currentTime-referenceTime;
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
					spentTimeVoo= currentTime - referenceTime;
					if(spentTimeVoo<timeMin)
					{
						//leitura invalida
//						HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, SET);
						contatoTime[samples] = 0;
						referenceTime = currentTime;

					}
					else if(spentTimeVoo>timeMax)
					{
						contatoTime[samples] = 0;
						referenceTime = currentTime;
//						HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, RESET);
						//leitura invalida
					}
					else
					{
						vooTime[samples] = spentTimeVoo;
						contatoTime[samples] = spentTimeSolo;
						referenceTime = currentTime;
						samples++;
					}
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
		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
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
