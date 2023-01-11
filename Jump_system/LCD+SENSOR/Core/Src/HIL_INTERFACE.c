#include "main.h"
#include "stdint.h"
#include "HIL_INTERFACE.h"
#include "string.h"

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

void SensorAcqRoutine()
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

#define AMOSTRAS 12
uint16_t contatoTimeSamples[AMOSTRAS] = {0,0,0,0,0};
uint16_t vooTimeSamples[AMOSTRAS] = {0,0,0,0,0};

void measureValidation(void)
{
	unsigned char key = 0;
	unsigned char logicZeroFile[30];
	unsigned char logicOneFile[30];
	unsigned char idx = 0;

	while(1)
	{
		do
		{
			key = (unsigned char)getKeyPressed();
		}
		while(key != CONFIRMAR);
		lcd_clear();
		lcd_put_cur(0, 0);
		lcd_send_string("START");
		HAL_Delay(1000);
		validation();
		idx++;

		/*R Rotina abaixo é usada para gravar no cartao SD
		 *
		 */
//		sprintf(logicZeroFile,"Tcontato_meas_%d.txt",idx);
//		sprintf(logicOneFile,"Tvoo_meas_%d.txt",idx);
//		SAVE_ARRAY(contatoTimeString, logicZeroFile);
//		SAVE_ARRAY(vooTimeString, logicOneFile);
//		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, RESET);
//		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
	}

}

void validation(void)
{

	/*
	 * 15/12/22
	 * Observações: É necessário que a informação seja apresentada
	 * após o salto completo, ou seja, após o salto o programa deve sair
	 * da maquina de estado REPOUSO-CONTATO-VOO. Outro trigger externo
	 * deve ser utilizado para reiniciar a maquina de estado.
	 * Nesse cenário, o timer principal, aqui apresentado como *ptr_totalTime
	 * não deve zerar pois cabe a ele monitorar o tempo total do inicio da
	 * medida. Contudo
	 * contu
	 */
//	uint32_t* ptr_totalTime;
	unsigned char* ptr_totalTime;
	unsigned char* ptr_samples;
	unsigned char* ptr_timer2Instance;
	TIM_HandleTypeDef* ptr_timer3Instance;
	unsigned char userState = REPOUSO;

	unsigned char key = 0;
	unsigned char* ptr_sensorFlag;
	unsigned char transitionString[20];
	unsigned char contatoTimeString[100];
	unsigned char vooTimeString[20];
	unsigned char printString[5] = {0,0,0,0,'\n'};
	unsigned char contato = 0;
	unsigned char voo = 0;
	uint32_t contatoTime = 0.000;
	uint32_t vooTime = 0.000;
	uint32_t transitionStateTime=0.000;
//	ptr_totalTime = getTimer3Variable();
	ptr_sensorFlag = getSensorFlag();
	ptr_samples = getSamplesCount();
	ptr_timer2Instance = getTimer2Instance();
	ptr_timer3Instance = getTimer3Instance();
	resetKeyPressed();


	SET_HW_TIMER2(ptr_timer2Instance);
	SET_HW_TIMER3(ptr_timer3Instance);
	while(key!=CONFIRMAR)
	{
		key = (unsigned char)getKeyPressed();
//		if(contato == AMOSTRAS && voo == AMOSTRAS) key = PARAR;
		switch(userState)
		{
			case REPOUSO:
				lcd_clear();
				lcd_put_cur(0, 0);
				lcd_send_string("ESTADO:REPOUSO");
				 __HAL_TIM_SET_COUNTER(ptr_timer3Instance,0);
				 HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
				while (*ptr_sensorFlag == 1);

				transitionStateTime = __HAL_TIM_GET_COUNTER(ptr_timer3Instance);
				HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
				userState = CONTATO;
			break;

			case CONTATO:
				lcd_clear();
				lcd_put_cur(0,0);
				lcd_send_string("ESTADO:CONTATO");
				lcd_put_cur(1, 0);
				lcd_send_string("Tvoo: ");
				lcd_put_cur(1, 6);
				lcd_send_string(printString);
				lcd_send_string("ms");
//				 HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
				while(*ptr_sensorFlag == 0);

				contatoTime = __HAL_TIM_GET_COUNTER(ptr_timer3Instance) - transitionStateTime;
				transitionStateTime = __HAL_TIM_GET_COUNTER(ptr_timer3Instance);
//				HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
				sprintf(contatoTimeString,"%d\n",contatoTime);
				memcpy(printString,contatoTimeString,sizeof(printString)-1);
				//lcd_printf("Volts: %d.%02d ",mvolts/1000, (mvolts%1000)/10);
				userState = VOO;
			break;

			case VOO:
				lcd_clear();
				lcd_put_cur(0,0);
				lcd_send_string("ATUAL:VOO");
				lcd_put_cur(1, 0);
				lcd_send_string("Tsolo: ");
				lcd_put_cur(1, 6);
				lcd_send_string(printString);
				lcd_send_string("ms");
//				 HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
				while(*ptr_sensorFlag == 1);

				vooTime = __HAL_TIM_GET_COUNTER(ptr_timer3Instance) - transitionStateTime;
				transitionStateTime = __HAL_TIM_GET_COUNTER(ptr_timer3Instance);
//				HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
				sprintf((char*)vooTimeString,"%d\n",vooTime);
				memcpy(printString,vooTimeString,sizeof(printString)-1);
				userState = CONTATO;
			break;
		}
	}
	RESET_HW_TIMER2(ptr_timer2Instance);
	RESET_HW_TIMER3(ptr_timer3Instance);
	lcd_clear();
	lcd_put_cur(0, 0);
	lcd_send_string("STOP");
	contato = 0;
	voo = 0;
}

#endif


