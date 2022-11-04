#define EXIT 'E'
#define SOLICITA '1'
#define PARA '0'
#define SAMPLES 10

#include "main.h"
#include "IO_interface.h"




//hardware completamente setado
unsigned int HIL()
{
    unsigned char INIT = FALSE;
    unsigned char* uartBufRx = getRxBuffer();
    unsigned char commandRx = uartBufRx[0];

    while(commandRx != EXIT)
    {
        uartBufRx = getRxBuffer();
        commandRx = uartBufRx[0];
        if(commandRx == SOLICITA)
        {
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
            stopTM2();
            stopTM3();
            uartBufRx = PARA;
        }

    }

    if(commandRx == EXIT)
    {
            stopTM2();
            stopTM3();
    }

    return 0;


}

void processApplication()
{
	unsigned long int* uartInstance = getUARTInstance();
    unsigned char userState = REPOUSO;
	unsigned char sensorFlag;
	unsigned int referenceTime,currentTime,totalTime,spentTimeVoo,spentTimeSolo = 0;
	unsigned int contatoTime[SAMPLES] = {0,0,0,0,0};
	unsigned int vooTime[SAMPLES]= {0,0,0,0,0};
	unsigned char samples = 0;
	unsigned char userSelectTapete = FALSE;

    while(samples<SAMPLES)
    {
        totalTime = getTimer3Variable();
        switch(userState)
        {
            case REPOUSO:
                sensorFlag = getTimer2Variable();
                if(sensorFlag == 0 && userSelectTapete == FALSE) //INICIO FORA DO TAPETE
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
                    //CONDI��O NA QUAL O SALTO � VALIDO
                    vooTime[samples] = spentTimeVoo;
                    contatoTime[samples] = spentTimeSolo;
                    referenceTime = currentTime;
                    samples++;
                }
                else
                {
                    userState = VOO;
                }
            break;
        }
    }
        TRANSMISSION_HW_UART(uartInstance,vooTime);
        TRANSMISSION_HW_UART(uartInstance,contatoTime);
}


