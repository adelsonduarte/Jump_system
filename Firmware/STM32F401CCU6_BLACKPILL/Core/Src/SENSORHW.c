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

static struct results measuredData;

unsigned char readingSensor()
{
	struct dataInsert* configStruct = getUserConfigStruct();

	unsigned char userState = REPOUSO;
	unsigned char sensorFlag;
	unsigned int referenceTime,currentTime,totalTime,spentTimeVoo,spentTimeSolo = 0;
	unsigned int contatoTime[5] = {0,0,0,0,0};
	unsigned int vooTime[5]= {0,0,0,0,0};
	unsigned char key = 0;
	unsigned char samples = 0;
	unsigned long int intervalSaltos = 0;
	unsigned long int intervalSeries = 0;
	unsigned char numSaltos = 0;
	unsigned char numSeries = 0;


	unsigned char indexTest = getResultTestNumber();
//	unsigned long int userTime = getUserTime();
//	unsigned long int userIntervalSeries = getUserIntervalSeries();
//	unsigned char userNumSeries = getUserNumSeries();
//	unsigned char userTapete = getUserSelectTapete();
//	unsigned long int userIntervalSaltos = getUserIntervalSaltos();
//	unsigned char userNumSaltos = getUserNumSaltos();
	unsigned int timeMin = getTimeAltMin();
	unsigned int timeMax = getTimeAltMax();
	/*The definition below are used just for debugging proposes
	 *
	 */
//	unsigned long int userIntervalSeries = 2000;
//	unsigned char userNumSeries = 1;
//	unsigned char userTapete = TRUE;
//	unsigned long int userIntervalSaltos = 10000;
//	unsigned char userNumSaltos = 2;
//	unsigned int timeMin = 500;
//	unsigned int timeMax = 5000;

	//
	key = getKeyPressed();

//	while(key != PARAR && totalTime != configStruct->userTime && numSaltos != configStruct->userNumSaltos) //WHILE COMPLETO
//	while(key != PARAR && numSaltos != configStruct->userNumSaltos) //USADO PARA DEBUGGER DESCONSIDERANDO O TIMEOUT
	while(key != PARAR && numSeries != configStruct->userNumSeries) //USADO PARA DEBUGGER DESCONSIDERANDO O TIMEOUT e NUM SALTOS

	{
		totalTime = getTimer3Variable();
		key = getKeyPressed();
		switch(userState)
		{
			case REPOUSO:
				sensorFlag = getTimer2Variable();
				if(sensorFlag == 0 && configStruct->userSelectTapete == FALSE) //INICIO FORA DO TAPETE
				{
					userState = CONTATO;
					referenceTime = getTimer3Variable();
				}
				else if(sensorFlag == 0 && configStruct->userSelectTapete == TRUE) // INICIO DENTRO DO TAPETE
				{
					userState = CONTATO;
					referenceTime = 0;
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
					referenceTime = currentTime;
				}
				else
				{
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
						referenceTime = currentTime;

					}
					else if(spentTimeVoo>timeMax)
					{

						referenceTime = currentTime;
						//leitura invalida
					}
					else if((spentTimeVoo+spentTimeSolo)>configStruct->userIntervalSaltos)
					{
						/*leitura invalida --- confirmar com alex. Aqui estou consi
						 * derando que o tempo do ciclo (voo+contato) é um salto
						 * completo e portanto, userIntervalSaltos que é um param
						 * de configuração que limita o valor máximo que o ciclo
						 * deve ter.
						 */
						intervalSaltos = spentTimeVoo+spentTimeSolo;
						referenceTime = currentTime;


					}
					else
					{	//CONDIÇÃO NA QUAL O SALTO É VALIDO
						vooTime[samples] = spentTimeVoo;
						contatoTime[samples] = spentTimeSolo;
						referenceTime = currentTime;
						numSaltos++;
						samples++;
						if(numSaltos == configStruct->userNumSaltos)
						{
							numSeries++;
							userState = INTERVALO;
							HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, RESET);
						}
						else userState = CONTATO;
					}
				}
				else
				{
					userState = VOO;
				}
			break;

			case INTERVALO:
				currentTime = getTimer3Variable();
				intervalSeries = currentTime - referenceTime;
				if(intervalSeries == configStruct->userIntervalSeries)
				{
					HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, SET);
					userState = CONTATO;
					numSaltos = 0;
				}
				else userState = INTERVALO;
				break;
		}
	}

	if(totalTime == configStruct->userTime)
	{
		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
		measuredData.timeout = TRUE;
		return TIMEOUT;
	}

	else if(numSaltos == configStruct->userNumSaltos)
	{
		measuredData.timeout = FALSE;
		measuredData.resultTestAcquiredSamples = samples;
		for(unsigned i=0;i<samples;i++)
		{
			measuredData.Measurement[i].sampleNum = i+1;
			measuredData.Measurement[i].uiVooTime = vooTime[i];
			measuredData.Measurement[i].uiSoloTime = contatoTime[i];
			setUserResultData(&measuredData,indexTest);
		}
		return MAX_SALTOS;
	}

	else
	{
		measuredData.timeout = FALSE;
		measuredData.resultTestAcquiredSamples = samples;
		for(unsigned i=0;i<samples;i++)
		{
			measuredData.Measurement[i].sampleNum = i+1;
			measuredData.Measurement[i].uiVooTime = vooTime[i];
			measuredData.Measurement[i].uiSoloTime = contatoTime[i];
			setUserResultData(&measuredData,indexTest);
		}
		return PARAR;
	}
}


void calcAltura()
{
	//PAREI AQUI
}

void calcPotencia()
{
	//PAREI AQUI
}
