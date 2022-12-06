#include "main.h"
#include "SENSORHW.h"
#include "Data.h"
#include "stdlib.h"

//struct samples{
//    unsigned char sampleNum;
//    unsigned int uiVooTime;
//    unsigned int uiSoloTime;
//};
#if _APPLICATION
#define ERROSALTO 1
#define OK 0

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

unsigned char readingSensor()
{
	struct dataInsert* configStruct = getUserConfigStruct();

	unsigned int contatoTime[SAMPLES];
	unsigned int totalTimeArray[SAMPLES];
	unsigned int vooTime[SAMPLES];
	unsigned int contatoTimeLocal[20]; 	//Para salvar no cartão SD
	unsigned int vooTimeLocal[20]; 	//Para salvar no cartão SD
	unsigned int alturaSaltoLocal[20];
	unsigned int potenciaSaltoLocal[20];
	unsigned int* ptr_measurementTotalTime;
	unsigned int* ptr_measurementContatoTime;
	unsigned int* ptr_measurementVooTime;
	unsigned int* ptr_totalTime;
	unsigned char* ptr_samples;
	unsigned char* ptr_sensorFlag;
	unsigned char count = 0;
	unsigned char userSelectTapete = FALSE;
	unsigned int transitionStateTime = 0;


	unsigned char key = 0;
	unsigned long int intervalSaltos = 0;
	unsigned long int intervalSeries = 0;
	unsigned char numSaltos = 0;
	unsigned char numSeries = 0;
	unsigned char readStatus = OK;



	ptr_samples = getSamplesCount();
	ptr_sensorFlag = getSensorFlag();
	ptr_measurementTotalTime = getTotalTime();
	ptr_measurementContatoTime = getTimeSolo();
	ptr_measurementVooTime = getTimeVoo();
	ptr_totalTime = getTimer3Variable();
	unsigned char indexTest = getResultTestNumber();
	unsigned long int userTime = getUserTime();
	unsigned long int userIntervalSeries = getUserIntervalSeries();
	unsigned char userNumSeries = getUserNumSeries();
	unsigned char userTapete = getUserSelectTapete();
	unsigned long int userIntervalSaltos = getUserIntervalSaltos();
	unsigned char userNumSaltos = getUserNumSaltos();
	unsigned int timeMin = getTimeAltMin();
	unsigned int timeMax = getTimeAltMax();



	/*The definition below are used just for debugging proposes
	 *
	 */
//	unsigned long int userIntervalSeries = 2000;
//	unsigned char userNumSeries = 1;
////	unsigned char userTapete = TRUE;
//	unsigned long int userIntervalSaltos = 10000;
//	unsigned char userNumSaltos = 2;
//	unsigned int timeMin = 50;
//	unsigned int timeMax = 5000;
//	unsigned int massaCorp = 10; //10kg
//	configStruct->userIntervalSeries = userIntervalSeries;
//	configStruct->userNumSeries = userNumSeries;
//	configStruct->userNumSaltos = userNumSaltos;
//	configStruct->userIntervalSaltos = userIntervalSaltos;
//	configStruct->userMass = massaCorp;


	//
	key = getKeyPressed();

//	while(key != PARAR && totalTime != configStruct->userTime && numSaltos != configStruct->userNumSaltos) //WHILE COMPLETO
//	while(key != PARAR && numSeries != configStruct->userNumSeries && *ptr_totalTime != configStruct->userTime)
	while(key != PARAR && numSeries != configStruct->userNumSeries)
	{
		key = getKeyPressed();
		switch(userState)
		{
			case REPOUSO:
				if(*ptr_sensorFlag == 0 && configStruct->userSelectTapete == FALSE) //INICIO FORA DO TAPETE
				{
					userState = CONTATO;
					transitionStateTime = *ptr_totalTime;
				}
				else if(*ptr_sensorFlag == 0 && configStruct->userSelectTapete == TRUE) // INICIO DENTRO DO TAPETE
				{
					userState = CONTATO;
					transitionStateTime=0;
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
					resetSamplesCount();
					while(*ptr_samples < SAMPLES)
					{
						totalTimeArray[*ptr_samples] = *ptr_totalTime;
						contatoTime[*ptr_samples] = *ptr_totalTime - transitionStateTime;
					}

					if(*ptr_samples == SAMPLES)
					{
						contatoTimeLocal[count] = contatoTime[SAMPLES-1];
						readStatus = OK;
					}
					userState = CONTATO;
				}

			break;

			case VOO:
				if(*ptr_sensorFlag  == 0)
				{
					if(readStatus == OK)
					{
						numSaltos++;
						count++;
						transitionStateTime = *ptr_totalTime;
						if(numSaltos == configStruct->userNumSaltos)
						{
							numSeries++;
							if(numSeries ==  configStruct->userNumSeries) userState = REPOUSO;
							else userState = INTERVALO;
						}
						else userState = CONTATO;
					}
					else userState = CONTATO;
				}

				else
				{
					resetSamplesCount();
					while(*ptr_samples < SAMPLES)
					{
						totalTimeArray[*ptr_samples] = *ptr_totalTime;
						vooTime[*ptr_samples] = *ptr_totalTime - transitionStateTime;
					}
					if(*ptr_samples == SAMPLES)
					{
						vooTimeLocal[count] = vooTime[SAMPLES-1];

						if(vooTimeLocal[count]>timeMin && vooTimeLocal[count]<timeMax)
						{
							readStatus = OK;
						}
						else readStatus = ERROSALTO;
					}
				}
			break;

			case INTERVALO:
				intervalSeries = *ptr_totalTime - transitionStateTime;
				if(intervalSeries == configStruct->userIntervalSeries)
				{
					userState = CONTATO;
					numSaltos = 0;
				}
				else userState = INTERVALO;
				break;
		}
	}

	measuredData.resultTestAcquiredSamples = count;
	for(unsigned i=0;i<count;i++)
	{
		alturaSaltoLocal[i] = calcAltura(vooTimeLocal[i]);
		potenciaSaltoLocal[i] = calcPotencia(alturaSaltoLocal[i],configStruct->userMass);
		measuredData.Measurement[i].sampleNum = i+1;
		measuredData.Measurement[i].alturaSalto = alturaSaltoLocal[i];
		measuredData.Measurement[i].potenciaSalto = potenciaSaltoLocal[i];
		measuredData.Measurement[i].uiSoloTime = contatoTimeLocal[i];
		measuredData.Measurement[i].uiVooTime = vooTimeLocal[i];
		setUserResultData(&measuredData,indexTest);
	}

	if(*ptr_totalTime == configStruct->userTime)
	{
		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
		measuredData.timeout = TRUE;
		return TIMEOUT;
	}

	else if(numSeries == configStruct->userNumSeries)
	{
		measuredData.timeout = FALSE;
		return MAX_SERIE;
	}

	else
	{
		measuredData.timeout = FALSE;
		return PARAR;
	}
}


unsigned int calcAltura(float vooTimeLocal)
{
	/*
	 * Altura do Salto em Centímetros = ((Tempo Voo^2) *  (981/8))
	 */
	float aux1;
	unsigned const int aux2 = 981>>3;
	unsigned int alturaSalto;
	vooTimeLocal = vooTimeLocal/1000;
	aux1 = vooTimeLocal*vooTimeLocal;
//	aux1 = aux1/10000;
	alturaSalto = aux1*aux2;

	return alturaSalto;
}

float calcPotencia(unsigned int alturaSalto,unsigned int massaCorpo)
{
	float aux1,aux2,potSalto;
	float const constant1 = 60.7;
	float const constant2 = 45.3;
	unsigned const int constant3 = 2055;
	aux1 = constant1*alturaSalto;
	aux2 = constant2*massaCorpo;
	potSalto = aux1+aux2-constant3;

	return potSalto;
//	Potência em Watts =  60,7 x (h [cm]) + 45,3 x (MC [Kg]) – 2055
}
#endif
