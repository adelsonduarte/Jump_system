#include "main.h"
#include "IO_interface.h"
#if _VI
#define EXIT 'E'
#define SOLICITA '1'
#define PARA '2'

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
	ptr_measurementTotalTime = getTotalTime();
	ptr_measurementContatoTime = getTimeSolo();
	ptr_measurementVooTime = getTimeVoo();

    while(TRANSMISSION == FALSE) //AQUI
    {
        switch(userState)
        {
            case REPOUSO:
//                sensorFlag = getTimer2Variable();
                if(*ptr_sensorFlag == 0 && userSelectTapete == FALSE) //INICIO FORA DO TAPETE
                {
					count = 0;
                    userState = CONTATO;
                }
                else
				{
					if(*ptr_samples == SAMPLES)
					{
						for(unsigned char i=0;i<SAMPLES;i++)
						{
							totalTimeArray[i] = ptr_measurementTotalTime[i];
							contatoTime[i] = ptr_measurementContatoTime[i];
							vooTime[i] = ptr_measurementVooTime[i];
						}

						for(unsigned char i=0;i<SAMPLES;i++)
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
						HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, SET);
						TRANSMISSION = TRUE;
						resetSamplesCount();
					}
					else if(*ptr_samples> SAMPLES) resetSamplesCount();
                	userState = REPOUSO;
				}

            break;

            case CONTATO:
//                sensorFlag = getTimer2Variable();
                if(*ptr_sensorFlag == 1)
                {
                    userState = VOO;
                    count = 0;
                }
                else
                {
					if(*ptr_samples == SAMPLES)
					{
						for(unsigned char i=0;i<SAMPLES;i++)
						{
							totalTimeArray[i] = ptr_measurementTotalTime[i];
							contatoTime[i] = ptr_measurementContatoTime[i];
							vooTime[i] = ptr_measurementVooTime[i];
						}

						for(unsigned char i=0;i<SAMPLES;i++)
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
						HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
						TRANSMISSION = TRUE;
						resetSamplesCount();
					}
					userState = CONTATO;
                }

            break;

            case VOO:
                if(*ptr_sensorFlag == 0)
                {
                    userState = CONTATO;
                    count = 0;
                }
                else
                {
					if(*ptr_samples == SAMPLES)
					{
						/*
						 * Tempo total dessa rotina = 3,8ms
						 */
						for(unsigned char i=0;i<SAMPLES;i++)
						{
							totalTimeArray[i] = ptr_measurementTotalTime[i];
							contatoTime[i] = ptr_measurementContatoTime[i];
							vooTime[i] = ptr_measurementVooTime[i];
						}
						/*
						 * Altura do Salto em Centímetros = ((Tempo Voo^2) *  (981/8))
						 */
						HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, RESET);
						for(unsigned char i=0;i<SAMPLES;i++)
						{
							aux1 = vooTime[i]*vooTime[i];
							aux1 = aux1/1000000;
							alturaSalto[i] = aux1*aux2;
						}
						HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, SET);


						for(unsigned char i=0;i<SAMPLES;i++)
						{
							totalTimeUnion.all = totalTimeArray[i];
							for(unsigned j=2;j>0;j--)
							{
								uartMsg[count] = totalTimeUnion.pt[j-1];
								count++;
							}

							alturaSaltoUnion.all = alturaSalto[i];
							for(unsigned j=2;j>0;j--)
							{
								uartMsg[count] = alturaSaltoUnion.pt[j-1];
								count++;
							}
						}
						TRANSMISSION_HW_UART(uartInstance,uartMsg);
						HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
						TRANSMISSION = TRUE;
						resetSamplesCount();
					}
                }
            break;
        }
    }
}
#endif


