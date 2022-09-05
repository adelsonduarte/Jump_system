#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "INICIAR_Component.h"
#include "SubMenu.h"
#include "time.h"
#include "Display_module.h"
#include "DisplayMessages.h"
#include "SD_module.h"

//Teste results

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
    struct samples sampleMeasurement[MEASUREMENT_SIZE];
};

//
struct dataInsert{
    unsigned char userTest;
    unsigned long int userTime;
    unsigned char userMass;
    unsigned char userOverMass;
    unsigned char userConsultTest;
    unsigned char userAlturaMin;
    unsigned char userAlturaMax;
    unsigned char userNumSaltos;
    unsigned char userIntervalSaltos;
    unsigned char userCMJ;
    unsigned char userAlturaDJ;
    unsigned char userNumSeries;
    unsigned char userIntervalSeries;
    unsigned char userCommConfig;
    unsigned char userSelectTapete;
    unsigned char userSelectSensorChannel;
};
struct Menu{
        unsigned char menuNext;
        unsigned char menuSelect;
        unsigned char menuDisplay;
        unsigned char menuState;
        struct dataInsert menuInsert;
    };

//toda maquina de estado deve ter um loop - > LEMBRAR LABVIEW

unsigned char initStateMachine(struct Menu* subMenu)
{
    struct Menu* subMenuIniciar = subMenu;
    struct dataInsert* ptr_userConfiguration = getUserConfigStruct();
    unsigned char key = 0;
    unsigned char index = 0;

    struct tm myTime;
    struct tm* userTimeStruct = &myTime;
    unsigned char userTimeString[9];
    unsigned char procTimeString[9];
    unsigned char* ptr_massString;
    unsigned char* ptr_overMassString;

    unsigned char displayUpdateStatus = IDDLE;
    unsigned char cursorPosition[2] = {0,0};

    //Teste results
    unsigned char* ptr_Sample;
    unsigned char* ptr_ulReadingTime;
    unsigned char* ptr_uiVooTime;
    unsigned char* ptr_ucAltDistance;
    struct results result[TEST_SIZE]; //verificar se vou usar o endereço de data.c assim como fiz com a estrutura de configuracao
    unsigned char i = 0;
    unsigned char sampleCount=0;
    unsigned char indexTest;
    static unsigned char arraySample[9];
    static unsigned long int arrayReadingTime[9];
    static unsigned int arrayVooTime[9];
    static unsigned char arrayAltDistance[9];
    //
    resetResultStruct(&result[0]);
    resetResultStruct(&result[1]);
    resetResultStruct(&result[2]);
    resetResultStruct(&result[3]);
    resetResultStruct(&result[4]);
    while(key != MENU)
    {
        switch(subMenuIniciar->menuState)
        {
            case IDDLE:
                subMenuIniciar->menuState = getNextSub(COMM_OFF);
                //RESET
            break;

            case COMM_OFF:
                updateUserMsg(3,2,noTransmissionMsg,&displayUpdateStatus);
                key = getchar();
                while( getchar() != '\n' );
                if(key == AVANCAR)
                {
                    readyUserInterface(&displayUpdateStatus,cursorPosition);
                    subMenuIniciar->menuState = getNextSub(COMM_ON);
                }
                else if(key == CONFIRMAR)
                {
                    //funcao para desabilitar comunicacao
                    readyUserInterface(&displayUpdateStatus,cursorPosition);
                    ptr_userConfiguration->userCommConfig = COMM_OFF;
                    subMenuIniciar->menuSelect = setSelectSub(&subMenuIniciar->menuState);
                    subMenuIniciar->menuState = getNextSub(TEMPO_READ);
                }
            break;

            case COMM_ON:
				updateUserMsg(3,2,yesTransmissionMsg,&displayUpdateStatus);
				key = getchar();
                while( getchar() != '\n' );
                if(key == AVANCAR)
				{
                	readyUserInterface(&displayUpdateStatus,cursorPosition);
					subMenuIniciar->menuState = getNextSub(COMM_OFF);
				}
                else if(key == CONFIRMAR)
                {
                	readyUserInterface(&displayUpdateStatus,cursorPosition);
                    //funcao para habilitar comunicacao
                	updateUserMsg(3,2,waitTransmissionMsg,&displayUpdateStatus);

                     ptr_userConfiguration->userCommConfig = COMM_ON;
                    subMenuIniciar->menuSelect = setSelectSub(&subMenuIniciar->menuState);
                    subMenuIniciar->menuState = getNextSub(TEMPO_READ);
                }
                break;

            case TEMPO_READ:
                updateUserMsg(3,2,timeUserMsg,&displayUpdateStatus);
                userTimeStruct = getTimeStruct();
                strftime(userTimeString, sizeof(userTimeString), "%H:%M:%S", userTimeStruct);
                insertUserInterface(0,0,userTimeString);
                key = getchar();
                while( getchar() != '\n' );
                if(key == INSERIR)
                {
//                    ptr_userTimeString = setUserTime(&index);
                    setUserTime(&index);
                    subMenuIniciar->menuState = getNextSub(TEMPO_READ);
                }
                else if (key == AVANCAR)
                {
                    indexTime(&index);
                }
                else if(key == CONFIRMAR)
                {
                    index = 0;
                    readyUserInterface(&displayUpdateStatus,cursorPosition);
                    strftime(procTimeString, sizeof(procTimeString), "%H%M%S", userTimeStruct);
                    puts(procTimeString);
                    ptr_userConfiguration->userTime = stringToLong(procTimeString);
                    //Configurar TIMER
                    subMenuIniciar->menuState = getNextSub(MASSA_READ);
                    subMenuIniciar->menuSelect = setSelectSub(&subMenuIniciar->menuState);
                }
                break;

            case MASSA_READ:
                 updateUserMsg(3,2,massUserMsg,&displayUpdateStatus);
                 ptr_massString = getMassString();
                 insertUserInterface(0,0,ptr_massString);
                key = getchar();
                while( getchar() != '\n' );
                if(key == INSERIR)
                {
                    setUserMass(&index);
                    subMenuIniciar->menuState = getNextSub(MASSA_READ);
                }
                else if(key == AVANCAR)
                {
                    indexMass(&index);
                }
                else if(key == CONFIRMAR)
                {
                    index = 0;
                    readyUserInterface(&displayUpdateStatus,cursorPosition);
                    ptr_userConfiguration->userMass= stringToInt(ptr_massString);
                    subMenuIniciar->menuState = getNextSub(SOBREC_READ);
                    subMenuIniciar->menuSelect = setSelectSub(&subMenuIniciar->menuState);
                }
                break;

            case SOBREC_READ:
                updateUserMsg(3,2,overmassUserMsg,&displayUpdateStatus);
                ptr_overMassString = getOverMassString();
                insertUserInterface(0,0,ptr_overMassString);
                key = getchar();
                while( getchar() != '\n' );
                if(key == INSERIR)
                {
                    setUserOverMass(&index);
                    subMenuIniciar->menuState = getNextSub(SOBREC_READ);
                }
                else if(key == AVANCAR)
                {
                    indexMass(&index);
                }
                else if(key == CONFIRMAR)
                {
                    index = 0;
                    readyUserInterface(&displayUpdateStatus,cursorPosition);
                    ptr_userConfiguration->userOverMass= stringToInt(ptr_overMassString);
                    subMenuIniciar->menuSelect = setSelectSub(&subMenuIniciar->menuState);
                    subMenuIniciar->menuState = getNextSub(START);
                }
                break;

            case START:
                setInsertData(ptr_userConfiguration);
                updateUserMsg(3,2,startreadUserMsg,&displayUpdateStatus);
                insertUserInterface(0,0,userTimeString);
                key = getchar();
                while( getchar() != '\n' );
                if(key == CONFIRMAR)
                {
//                    setTest(&result[indexTest].resultTestNum); //verificar talvez nao seja util
                    //INICIA LEITURA (LIGA ENCODER, PONTE, O QUE FOR //I0_INTERFACE

                    indexTest = getResultTestNumber();
                    readyUserInterface(&displayUpdateStatus,cursorPosition);
                    subMenuIniciar->menuState = getNextSub(READING);
                    subMenuIniciar->menuSelect = setSelectSub(&subMenuIniciar->menuState);
                }
            break;

            case READING:
                 printf("READING->->-> LOOP DE LEITURA DEVE FICAR AQUI\n");
                 /*DISPLAY
                 BASICAMENTE, CHAMAR FUNÇÕES PARA ACESSAR O MAIN  E AS VARIAVEIS DE TEMPO E LEITURA DO SENSOR
                 ATUALIZAR SOMENTE QUANDO TIVER NOVO DADO DA INTERRUPÇÃO
                 CALCULA O PARAMETRO PASSADO PELO ALEX DE CADA AMOSTRA :Altura do Salto em Centímetros = ((Tempo Voo^2) *  (9,81/8)) * 10
                 processResult : calcula o parametro acima
                 APRESENTAR O RESULTADO PARA O USUÁRIO
                 O LOOP DE READING DEVE PARAR QUANDO:
                 1 - DER O TEMPO CONFIGURADO
                 2 - DER O NUMERO DE SALTOS CONFIGURADO
                 3 - PRESSIONAR O BOTAO PARAR

                 */
                key = getchar();
                while( getchar() != '\n' );
                if(key == PARAR) subMenuIniciar->menuState = getNextSub(STOP);
                //Teste results
                else if(key==AMOSTRA)
                {
                    result[indexTest].sampleMeasurement[sampleCount].sampleNum = sampleCount+1;
                    result[indexTest].sampleMeasurement[sampleCount].ucAltDistance+=5;
                    result[indexTest].sampleMeasurement[sampleCount].uiVooTime+=10;
                    result[indexTest].sampleMeasurement[sampleCount].ulReadingTime+= 100;
                    arraySample[sampleCount] = result[indexTest].sampleMeasurement[sampleCount].sampleNum;
                    arrayAltDistance[sampleCount] = result[indexTest].sampleMeasurement[sampleCount].ucAltDistance;
                    arrayVooTime[sampleCount] = result[indexTest].sampleMeasurement[sampleCount].uiVooTime;
                    arrayReadingTime[sampleCount] = result[indexTest].sampleMeasurement[sampleCount].ulReadingTime;
                    printf("result[%d].sampleMeasurement[%d].sampleNum = %d\n",indexTest,sampleCount,result[indexTest].sampleMeasurement[sampleCount].sampleNum);
                    printf("result[%d].sampleMeasurement[%d].ulReadingTime  = %d\n",indexTest,sampleCount,result[indexTest].sampleMeasurement[sampleCount].ulReadingTime);
                    printf("result[%d].sampleMeasurement[%d].uiVooTime = %d\n",indexTest,sampleCount,result[indexTest].sampleMeasurement[sampleCount].uiVooTime);
                    printf("result[%d].sampleMeasurement[%d].ucAltDistance = %d\n",indexTest,sampleCount,result[indexTest].sampleMeasurement[sampleCount].ucAltDistance);
                    sampleCount++;
                }
                //
            break;

            case STOP:
                updateUserMsg(3,2,stopreadUserMsg,&displayUpdateStatus);
                key = getchar();
                while( getchar() != '\n' );
                if(key == CONFIRMAR)
                {
                    readyUserInterface(&displayUpdateStatus,cursorPosition);
                    //PARA LEITURA, DESLIGA TIMER, ENCODER, O QUE FOR I0_INTERFACE
                    setUserResultData(&result[indexTest],indexTest,sampleCount);
                    setResultTestNumber();
                    subMenuIniciar->menuState = getNextSub(DISP_RESULTS);
                    subMenuIniciar->menuSelect = setSelectSub(&subMenuIniciar->menuState);

                }
                break;

            case DISP_RESULTS:
                updateUserMsg(3,2,resultsUserMsg,&displayUpdateStatus);
                key = getchar();
                while( getchar() != '\n' );
                if(key == PARAR)
                {
                    readyUserInterface(&displayUpdateStatus,cursorPosition);
                    subMenuIniciar->menuState = getNextSub(SAVE_DATA);
                }
                else if(key == CONFIRMAR)
                {
                    readyUserInterface(&displayUpdateStatus,cursorPosition);
                    subMenuIniciar->menuSelect = setSelectSub(&subMenuIniciar->menuState);
                    subMenuIniciar->menuState = getNextSub(RESULTS);
                }
            break;

            case RESULTS:
                //Teste results
                if(i<sampleCount)
                {
                insertUserInterface(0,0,"SALTO");
                ptr_Sample = param_1_toString(&arraySample[i]);
                ptr_uiVooTime = param_2_toString(&arrayVooTime[i]);
                ptr_ucAltDistance = param_3_toString(&arrayAltDistance[i]);
                insertUserInterface(0,0,ptr_Sample);
                insertUserInterface(0,0,ptr_ucAltDistance);
                insertUserInterface(0,0,ptr_uiVooTime);
                }

                //
                subMenuIniciar->menuDisplay = getDisplaySub(&subMenuIniciar->menuDisplay);
                key = getchar();
                while( getchar() != '\n' );
                if(key == AVANCAR)
                {
                    //Teste results
                    i++;
                    if(i==sampleCount)
                    {
                        i=0;
                    }
                    //
                    subMenuIniciar->menuState = getNextSub(RESULTS);
                }
                else if(key == PARAR)
                {
                    readyUserInterface(&displayUpdateStatus,cursorPosition);
                    subMenuIniciar->menuState = getNextSub(SAVE_DATA);
                }

            break;

            case SAVE_DATA:
                updateUserMsg(3,2,saveUserMsg,&displayUpdateStatus);
                key = getchar();
                while( getchar() != '\n' );
                if(key == AVANCAR)
                {
                    readyUserInterface(&displayUpdateStatus,cursorPosition);
                    updateUserMsg(3,2,cancelUserMsg,&displayUpdateStatus);
                    subMenuIniciar->menuState = getNextSub(CANCEL_SAVE);
                }
                else if(key == CONFIRMAR)
                {
                    save_data();
                    readyUserInterface(&displayUpdateStatus,cursorPosition);
                    updateUserMsg(3,2,savedUserMsg,&displayUpdateStatus);
                    subMenuIniciar->menuSelect = setSelectSub(&subMenuIniciar->menuState);
                    //display
                    subMenuIniciar->menuState = getNextSub(COMM_OFF);
                    sampleCount = 0;
                    i=0;
                    key = MENU; // ta errado mas coloquei aqui pra teste
                }
            break;

            case CANCEL_SAVE:
                updateUserMsg(3,2,cancelUserMsg,&displayUpdateStatus);
                key = getchar();
                while( getchar() != '\n' );
                if(key == AVANCAR)
                {
                    readyUserInterface(&displayUpdateStatus,cursorPosition);
                    subMenuIniciar->menuState = getNextSub(SAVE_DATA);
                }
                else if(key == CONFIRMAR)
                {
                    readyUserInterface(&displayUpdateStatus,cursorPosition);
                    updateUserMsg(3,2,canceledUserMsg,&displayUpdateStatus);
                    subMenuIniciar->menuSelect = setSelectSub(&subMenuIniciar->menuState);
                    //display
                    ////Teste results
//                    result[indexTest].sample=0;
//                    result[indexTest].ucAltDistance=0;
//                    result[indexTest].uiVooTime =0;
//                    result[indexTest].ulReadingTime = 0;
                    sampleCount = 0;
                    i=0;
                    indexTest++;
                    //
                    subMenuIniciar->menuState = getNextSub(COMM_OFF);
                    key = MENU; // ta errado mas coloquei aqui pra teste
                }
            break;
        }
    }
}
