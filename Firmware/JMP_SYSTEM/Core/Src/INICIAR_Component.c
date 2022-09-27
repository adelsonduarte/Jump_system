#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "INICIAR_Component.h"
#include "SubMenu.h"
#include "time.h"
#include "Display_module.h"
#include "DisplayMessages.h"
#include "SD_module.h"
#include "Data.h"
#include "IO_interface.h"
#include "SENSORHW.h"

//Teste results

struct samples{
    unsigned char sampleNum;
    unsigned int uiVooTime;
    unsigned int uiSoloTime;
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
    short insertColumn = 7;

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
    struct results result[TEST_SIZE]; //verificar se vou usar o endere�o de data.c assim como fiz com a estrutura de configuracao
    unsigned char i = 0;
    unsigned char sampleCount=0;
    unsigned char indexTest;

    //
    resetResultStruct(&result[0]);
    resetResultStruct(&result[1]);
    resetResultStruct(&result[2]);
    resetResultStruct(&result[3]);
    resetResultStruct(&result[4]);


    unsigned char startTapete,readingState;


    while(key != MENU)
    {
        switch(subMenuIniciar->menuState)
        {
            case IDDLE:
                subMenuIniciar->menuState = getNextSub(COMM_OFF);
                //RESET
            break;

            case COMM_OFF:
                updateUserMsg(0,0,noTransmissionMsg,&displayUpdateStatus);
                key = getKeyPressed();
                if(key == AVANCAR)
                {
                	resetKeyPressed();
                    readyUserInterface(&displayUpdateStatus,cursorPosition);
                    subMenuIniciar->menuState = getNextSub(COMM_ON);
                }
                else if(key == CONFIRMAR)
                {
                	resetKeyPressed();
                    stopCOMM();
                    readyUserInterface(&displayUpdateStatus,cursorPosition);
                    ptr_userConfiguration->userCommConfig = COMM_OFF;
                    subMenuIniciar->menuSelect = setSelectSub(&subMenuIniciar->menuState);
                    subMenuIniciar->menuState = getNextSub(TEMPO_READ);
                }
            break;

            case COMM_ON:
				updateUserMsg(0,0,yesTransmissionMsg,&displayUpdateStatus);
				key = getKeyPressed();
                if(key == AVANCAR)
				{
                	resetKeyPressed();
                	readyUserInterface(&displayUpdateStatus,cursorPosition);
					subMenuIniciar->menuState = getNextSub(COMM_OFF);
				}
                else if(key == CONFIRMAR)
                {
                	resetKeyPressed();
                	readyUserInterface(&displayUpdateStatus,cursorPosition);
                    startCOMM();
                	updateUserMsg(0,0,waitTransmissionMsg,&displayUpdateStatus);
                	readyUserInterface(&displayUpdateStatus,cursorPosition);
                     ptr_userConfiguration->userCommConfig = COMM_ON;
                    subMenuIniciar->menuSelect = setSelectSub(&subMenuIniciar->menuState);
                    subMenuIniciar->menuState = getNextSub(TEMPO_READ);
                }
                break;

            case TEMPO_READ:
                updateUserMsg(0,0,timeUserMsg,&displayUpdateStatus);
                userTimeStruct = getTimeStruct();
                strftime(userTimeString, sizeof(userTimeString), "%H:%M:%S", userTimeStruct);
                printDataDisplay(0,1,userTimeString);
                updateDataDisplay(insertColumn,1);
                key = getKeyPressed();

                if(key == INSERIR)
                {
                	resetKeyPressed();
                    setUserTime(&insertColumn);
                    subMenuIniciar->menuState = getNextSub(TEMPO_READ);
                }
                else if (key == AVANCAR)
                {
                	resetKeyPressed();
                    indexColumn(&insertColumn,7);
                }
                else if(key == CONFIRMAR)
                {
                	resetKeyPressed();
                	insertColumn = 4; //colocar um define talvez -> definicao de caracteres no display massa e overmass
                    readyUserInterface(&displayUpdateStatus,cursorPosition);
                    strftime(procTimeString, sizeof(procTimeString), "%H%M%S", userTimeStruct);
                    ptr_userConfiguration->userTime = stringToLong(procTimeString);
                    //Configurar TIMER
                    subMenuIniciar->menuState = getNextSub(MASSA_READ);
                    subMenuIniciar->menuSelect = setSelectSub(&subMenuIniciar->menuState);
                }
                break;

            case MASSA_READ:
                 updateUserMsg(0,0,massUserMsg,&displayUpdateStatus);
                 ptr_massString = getMassString();
                 printDataDisplay(0,1,ptr_massString);
                 updateDataDisplay(insertColumn,1);
                key = getKeyPressed();
                if(key == INSERIR)
                {
                	resetKeyPressed();
                    setUserMass(&insertColumn); //criar variavel adicional para separar insertcolumn
                    subMenuIniciar->menuState = getNextSub(MASSA_READ);
                }
                else if(key == AVANCAR)
                {
                	resetKeyPressed();
                    indexMass(&insertColumn);
                }
                else if(key == CONFIRMAR)
                {
                	resetKeyPressed();
                	insertColumn = 4;
                    readyUserInterface(&displayUpdateStatus,cursorPosition);
                    ptr_userConfiguration->userMass= stringToInt(ptr_massString);
                    subMenuIniciar->menuState = getNextSub(SOBREC_READ);
                    subMenuIniciar->menuSelect = setSelectSub(&subMenuIniciar->menuState);
                }
                break;

            case SOBREC_READ:
                updateUserMsg(0,0,overmassUserMsg,&displayUpdateStatus);
                ptr_overMassString = getOverMassString();
                printDataDisplay(0,1,ptr_overMassString);
                updateDataDisplay(insertColumn,1);
                key = getKeyPressed();

                if(key == INSERIR)
                {
                	resetKeyPressed();
                    setUserOverMass(&insertColumn);
                    subMenuIniciar->menuState = getNextSub(SOBREC_READ);
                }
                else if(key == AVANCAR)
                {
                	resetKeyPressed();
                    indexMass(&insertColumn);
                }
                else if(key == CONFIRMAR)
                {
                	resetKeyPressed();
                	insertColumn = 7; //definicao de caracteres para TIME
                    readyUserInterface(&displayUpdateStatus,cursorPosition);
                    ptr_userConfiguration->userOverMass= stringToInt(ptr_overMassString);
                    subMenuIniciar->menuSelect = setSelectSub(&subMenuIniciar->menuState);
                    subMenuIniciar->menuState = getNextSub(START);
                }
                break;

            case START:
                setInsertData(ptr_userConfiguration);
                updateUserMsg(0,0,startreadUserMsg,&displayUpdateStatus);
                printDataDisplay(0,1,userTimeString);
                key = getKeyPressed();

                if(key == CONFIRMAR)
                {
                	resetKeyPressed();
                	startTapete = getUserSelectTapete();
                	if(startTapete == TRUE) readingState = DENTRO;
                	else readingState = FORA;

                    indexTest = getResultTestNumber();
                    readyUserInterface(&displayUpdateStatus,cursorPosition);
                    subMenuIniciar->menuState = getNextSub(READING);
                    subMenuIniciar->menuSelect = setSelectSub(&subMenuIniciar->menuState);
                }
            break;

            case READING:
            	 updateUserMsg(0,0,"READING...",&displayUpdateStatus);
            	 startTM2();
				 startTM3();
//
//            	 while(key != PARAR)
//            	 {
            		 switch(readingState)
					 {
						 case FORA:
							startReadingOutsideSensor();
						 break;
						 case DENTRO:
							startReadingInsideSensor();
						 break;
					 }
            		 key = getKeyPressed();


//					 timer3Data = getTimer3Variable();
//					 sprintf(timer3DataString,"%d",timer3Data);
//					 sprintf(timer2DataString,"%d",sensorFlag);
//					 printDataDisplay(0,2,timer3DataString);
//					 printDataDisplay(0,3,timer2DataString);
//					 key = getKeyPressed();
//            	 }

	//                 printf("READING->->-> LOOP DE LEITURA DEVE FICAR AQUI\n");
				 /*DISPLAY
				 BASICAMENTE, CHAMAR FUN��ES PARA ACESSAR O MAIN  E AS VARIAVEIS DE TEMPO E LEITURA DO SENSOR
				 ATUALIZAR SOMENTE QUANDO TIVER NOVO DADO DA INTERRUP��O
				 CALCULA O PARAMETRO PASSADO PELO ALEX DE CADA AMOSTRA :Altura do Salto em Cent�metros = ((Tempo Voo^2) *  (9,81/8)) * 10
				 processResult : calcula o parametro acima
				 APRESENTAR O RESULTADO PARA O USU�RIO
				 O LOOP DE READING DEVE PARAR QUANDO:
				 1 - DER O TEMPO CONFIGURADO
				 2 - DER O NUMERO DE SALTOS CONFIGURADO
				 3 - PRESSIONAR O BOTAO PARAR

				 */


				if(key == PARAR)
				{
					resetKeyPressed();
					readyUserInterface(&displayUpdateStatus,cursorPosition);
					subMenuIniciar->menuState = getNextSub(STOP);
				}
            break;

            case STOP:
                updateUserMsg(0,0,stopreadUserMsg,&displayUpdateStatus);
                key = getKeyPressed();

                if(key == CONFIRMAR)
                {
//                	transmissionCOMM(&timer3Data);
//                	transmissionCOMM();
                	resetKeyPressed();
                    stopTM2();
                    stopTM3();
                    readyUserInterface(&displayUpdateStatus,cursorPosition);
                    //PARA LEITURA, DESLIGA TIMER, ENCODER, O QUE FOR I0_INTERFACE
//                    setUserResultData(&result[indexTest],indexTest,sampleCount);
                    setResultTestNumber();
                    subMenuIniciar->menuState = getNextSub(DISP_RESULTS);
                    subMenuIniciar->menuSelect = setSelectSub(&subMenuIniciar->menuState);

                }
                break;

            case DISP_RESULTS:
                updateUserMsg(0,0,resultsUserMsg,&displayUpdateStatus);
                key = getKeyPressed();

                if(key == PARAR)
                {
                	resetKeyPressed();
                    readyUserInterface(&displayUpdateStatus,cursorPosition);
                    subMenuIniciar->menuState = getNextSub(SAVE_DATA);
                }
                else if(key == CONFIRMAR)
                {
                	resetKeyPressed();
                    readyUserInterface(&displayUpdateStatus,cursorPosition);
                    subMenuIniciar->menuSelect = setSelectSub(&subMenuIniciar->menuState);
                    subMenuIniciar->menuState = getNextSub(RESULTS);
                }
            break;

            case RESULTS:
                //Teste results
//                if(i<sampleCount)
//                {
//                printDataDisplay(0,0,"SALTO");
//                ptr_Sample = param_1_toString(&arraySample[i]);
//                ptr_uiVooTime = param_2_toString(&arrayVooTime[i]);
//                ptr_ucAltDistance = param_3_toString(&arrayAltDistance[i]);
//                printDataDisplay(0,0,ptr_Sample);
//                printDataDisplay(0,0,ptr_ucAltDistance);
//                printDataDisplay(0,0,ptr_uiVooTime);
//                }
//
//                //
//                subMenuIniciar->menuDisplay = getDisplaySub(&subMenuIniciar->menuDisplay);
//                key = getKeyPressed();
//
//                if(key == AVANCAR)
//                {
//                    //Teste results
//                    i++;
//                    if(i==sampleCount)
//                    {
//                        i=0;
//                    }
//                    //
//                    subMenuIniciar->menuState = getNextSub(RESULTS);
//                }
                if(key == PARAR)
                {
                	resetKeyPressed();
                    readyUserInterface(&displayUpdateStatus,cursorPosition);
                    subMenuIniciar->menuState = getNextSub(SAVE_DATA);
                }

            break;

            case SAVE_DATA:
                updateUserMsg(0,0,saveUserMsg,&displayUpdateStatus);
                key = getKeyPressed();

                if(key == AVANCAR)
                {
                	resetKeyPressed();
                    readyUserInterface(&displayUpdateStatus,cursorPosition);
                    updateUserMsg(0,0,cancelUserMsg,&displayUpdateStatus);
                    subMenuIniciar->menuState = getNextSub(CANCEL_SAVE);
                }
                else if(key == CONFIRMAR)
                {
                	resetKeyPressed();
                    save_data(indexTest);
                    readyUserInterface(&displayUpdateStatus,cursorPosition);
                    updateUserMsg(0,0,savedUserMsg,&displayUpdateStatus);
                    subMenuIniciar->menuSelect = setSelectSub(&subMenuIniciar->menuState);
                    //display
                    subMenuIniciar->menuState = getNextSub(COMM_OFF);
                    sampleCount = 0;
                    i=0;
  				  readyUserInterface(&displayUpdateStatus,cursorPosition);
                    key = MENU; // ta errado mas coloquei aqui pra teste
                }
            break;

            case CANCEL_SAVE:
                updateUserMsg(0,0,cancelUserMsg,&displayUpdateStatus);
                key = getKeyPressed();

                if(key == AVANCAR)
                {
                	resetKeyPressed();
                    readyUserInterface(&displayUpdateStatus,cursorPosition);
                    subMenuIniciar->menuState = getNextSub(SAVE_DATA);
                }
                else if(key == CONFIRMAR)
                {
                	resetKeyPressed();
                    readyUserInterface(&displayUpdateStatus,cursorPosition);
                    updateUserMsg(0,0,canceledUserMsg,&displayUpdateStatus);
                    subMenuIniciar->menuSelect = setSelectSub(&subMenuIniciar->menuState);
                    sampleCount = 0;
                    i=0;
                    indexTest++;
                    //
                    subMenuIniciar->menuState = getNextSub(COMM_OFF);
  				  readyUserInterface(&displayUpdateStatus,cursorPosition);
                    key = MENU; // ta errado mas coloquei aqui pra teste
                }
            break;
        }
    }
    readyUserInterface(&displayUpdateStatus,cursorPosition);
}
