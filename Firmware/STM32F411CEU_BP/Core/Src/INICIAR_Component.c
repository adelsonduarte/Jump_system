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

//struct samples{
//    unsigned char sampleNum;
//    unsigned int uiVooTime;
//    unsigned int uiSoloTime;
//};
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
    struct samples sampleMeasurement[MEASUREMENT_SIZE];
};

//
struct dataInsert{
    unsigned char userTest;
    unsigned long int userTime;
    unsigned char userMass;
    unsigned char userOverMass;
    unsigned char userConsultTest;
    unsigned int userAlturaMin;
    unsigned int userAlturaMax;
    unsigned char userNumSaltos;
    unsigned long int userIntervalSaltos;
    unsigned char userCMJ;
    unsigned char userAlturaDJ;
    unsigned char userNumSeries;
    unsigned long int userIntervalSeries;
    unsigned char userCommConfig;
    unsigned char userSelectTapete;
    unsigned char userSelectSensorChannel;
};
struct Menu{
        unsigned char menuNext;
        unsigned char menuSelect;
        unsigned char menuDisplay;
        unsigned char menuState;
//        struct dataInsert menuInsert;
    };

//toda maquina de estado deve ter um loop - > LEMBRAR LABVIEW

unsigned char initStateMachine(struct Menu* subMenu)
{
    struct Menu* subMenuIniciar = subMenu;
    struct dataInsert* ptr_userConfiguration;
    struct results* ptr_result;
    struct tm myTime;
	struct tm* userTimeStruct = &myTime;
    unsigned char key = 0;
    short insertColumn = 7;


    unsigned char userTimeString[9];
    unsigned char procTimeString[9];
    unsigned char* ptr_massString;
    unsigned char* ptr_overMassString;

    unsigned char* ptr_sampleString;
    unsigned int* ptr_vooTimeString;
    unsigned int* ptr_soloTimeString;
    unsigned int* ptr_alturaString;
    unsigned int* ptr_potString;


    unsigned char displayUpdateStatus = IDDLE;

    unsigned char indexTest;
    unsigned char readingStatus = IDDLE;
    unsigned char selectedUserTest = 0;
    unsigned char testSamples = 0;

    //
//    rflashConfigData();
    ptr_userConfiguration = getUserConfigStruct();

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
                updateUserMsg(0,USERMSG1,noTransmissionMsg,&displayUpdateStatus);
                HW_PRINT_DATA(0,INSERTMSG,avancarUserMsg);
                HW_PRINT_DATA(stringLenght(avancarUserMsg),INSERTMSG,menuUserMsg);
                HW_PRINT_DATA(0,OPTIONMSG,selecionarUserMsg);
                key = getKeyPressed();
                if(key == AVANCAR)
                {
                	resetKeyPressed();
                    readyUserInterface(&displayUpdateStatus);
                    subMenuIniciar->menuState = getNextSub(COMM_ON);
                }
                else if(key == CONFIRMAR)
                {
                	resetKeyPressed();
                    stopCOMM();
                    readyUserInterface(&displayUpdateStatus);
                    ptr_userConfiguration->userCommConfig = COMM_OFF;
                    subMenuIniciar->menuState = getNextSub(TEMPO_READ);
                }
            break;

            case COMM_ON:
				updateUserMsg(0,0,yesTransmissionMsg,&displayUpdateStatus);
				HW_PRINT_DATA(0,INSERTMSG,avancarUserMsg);
				HW_PRINT_DATA(stringLenght(avancarUserMsg),INSERTMSG,menuUserMsg);
				HW_PRINT_DATA(0,OPTIONMSG,selecionarUserMsg);
				key = getKeyPressed();
                if(key == AVANCAR)
				{
                	resetKeyPressed();
                    readyUserInterface(&displayUpdateStatus);
					subMenuIniciar->menuState = getNextSub(COMM_OFF);
				}
                else if(key == CONFIRMAR)
                {
                	resetKeyPressed();
                    readyUserInterface(&displayUpdateStatus);
                    startCOMM();
                	updateUserMsg(0,0,waitTransmissionMsg,&displayUpdateStatus);
                    readyUserInterface(&displayUpdateStatus);
                     ptr_userConfiguration->userCommConfig = COMM_ON;
                    subMenuIniciar->menuState = getNextSub(TEMPO_READ);
                }
                break;

            case TEMPO_READ:
                updateUserMsg(0,USERMSG1,timeUserMsg,&displayUpdateStatus);

                userTimeStruct = getTimeStruct();
                strftime(userTimeString, sizeof(userTimeString), "%H:%M:%S", userTimeStruct);
                HW_PRINT_DATA(0,USERMSG2,userTimeString);
                HW_UPDATE_DATA(insertColumn,USERMSG2);

                HW_PRINT_DATA(0,INSERTMSG,avancarUserMsg);
                HW_PRINT_DATA(stringLenght(avancarUserMsg),INSERTMSG,menuUserMsg);
                HW_PRINT_DATA(0,OPTIONMSG,selecionarUserMsg);
                HW_PRINT_DATA(stringLenght(selecionarUserMsg),OPTIONMSG,inserirUserMsg);
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
                    readyUserInterface(&displayUpdateStatus);
					ptr_userConfiguration->userTime = milisecondsTime(userTimeStruct);
                    subMenuIniciar->menuState = getNextSub(MASSA_READ);
                }
                break;

            case MASSA_READ:
                 updateUserMsg(0,USERMSG1,massUserMsg,&displayUpdateStatus);
                 ptr_massString = getMassString();
                 HW_PRINT_DATA(0,USERMSG2,ptr_massString);
                 HW_UPDATE_DATA(insertColumn,1);
                 HW_PRINT_DATA(0,INSERTMSG,avancarUserMsg);
				 HW_PRINT_DATA(stringLenght(avancarUserMsg),INSERTMSG,menuUserMsg);
				 HW_PRINT_DATA(0,OPTIONMSG,selecionarUserMsg);
				HW_PRINT_DATA(stringLenght(selecionarUserMsg),OPTIONMSG,inserirUserMsg);
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
                    readyUserInterface(&displayUpdateStatus);
                    ptr_userConfiguration->userMass= stringToInt(ptr_massString);
                    subMenuIniciar->menuState = getNextSub(SOBREC_READ);
                }
                break;

            case SOBREC_READ:
                updateUserMsg(0,USERMSG1,overmassUserMsg,&displayUpdateStatus);
                ptr_overMassString = getOverMassString();
                HW_PRINT_DATA(0,USERMSG2,ptr_overMassString);
                HW_UPDATE_DATA(insertColumn,1);

                HW_PRINT_DATA(0,INSERTMSG,avancarUserMsg);
				 HW_PRINT_DATA(stringLenght(avancarUserMsg),INSERTMSG,menuUserMsg);
				 HW_PRINT_DATA(0,OPTIONMSG,selecionarUserMsg);
				HW_PRINT_DATA(stringLenght(selecionarUserMsg),OPTIONMSG,inserirUserMsg);

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
                    readyUserInterface(&displayUpdateStatus);
                    ptr_userConfiguration->userOverMass= stringToInt(ptr_overMassString);
                    subMenuIniciar->menuState = getNextSub(START);
                }
                break;

            case START:
                setInsertData(ptr_userConfiguration);
                updateUserMsg(0,USERMSG1,startreadUserMsg,&displayUpdateStatus);
                HW_PRINT_DATA(0,USERMSG2,userTimeString);
                HW_PRINT_DATA(0,INSERTMSG,menuUserMsg);
				HW_PRINT_DATA(0,OPTIONMSG,selecionarUserMsg);


                key = getKeyPressed();

                if(key == CONFIRMAR)
                {
                	resetKeyPressed();
                    indexTest = getResultTestNumber();
                    readyUserInterface(&displayUpdateStatus);
                    subMenuIniciar->menuState = getNextSub(READING);
                }
            break;

            case READING:
            	 updateUserMsg(0,USERMSG1,medindoUserMsg,&displayUpdateStatus);
            	 resetTimer3Variable();
				 HW_PRINT_DATA(0,OPTIONMSG,pararUserMsg);
            	 startTM2();
				 startTM3();
				 readingStatus = readingSensor();
				 key = getKeyPressed();
				 if(key == PARAR || readingStatus != IDDLE)
				 {
					 resetKeyPressed();
					 readyUserInterface(&displayUpdateStatus);
					 subMenuIniciar->menuState = getNextSub(STOP);
				 }

            break;

            case STOP:
            	key = getKeyPressed();
                updateUserMsg(0,0,stopreadUserMsg,&displayUpdateStatus);
				HW_PRINT_DATA(0,OPTIONMSG,selecionarUserMsg);

                if(key == CONFIRMAR)
                {
                	resetKeyPressed();
                    stopTM2();
                    stopTM3();
                    readyUserInterface(&displayUpdateStatus);
                    setResultTestNumber();
//                    transmissionCOMM();
                    subMenuIniciar->menuState = getNextSub(DISP_RESULTS);
                }
                break;

            case DISP_RESULTS:
                updateUserMsg(0,0,resultsUserMsg,&displayUpdateStatus);
                HW_PRINT_DATA(0,INSERTMSG,selecionarUserMsg);
				HW_PRINT_DATA(0,OPTIONMSG,pularUserMsg);
                key = getKeyPressed();

                if(key == PARAR)
                {
                	resetKeyPressed();
                    readyUserInterface(&displayUpdateStatus);
                    subMenuIniciar->menuState = getNextSub(SAVE_DATA);
                }
                else if(key == CONFIRMAR)
                {
                	resetKeyPressed();
                    readyUserInterface(&displayUpdateStatus);
                    subMenuIniciar->menuState = getNextSub(RESULTS);
                }
            break;

            case RESULTS:
            	selectedUserTest = getResultTestNumber();
            	ptr_result = getUserResultData(selectedUserTest);
				if(testSamples<(ptr_result->resultTestAcquiredSamples))
				{
//					updateUserMsg(0,USERMSG1,amostraUserMsg,&displayUpdateStatus);
					HW_PRINT_DATA(0,USERMSG1,amostraUserMsg);
					ptr_sampleString = param_1_toString(&ptr_result->sampleMeasurement[testSamples].sampleNum);
					HW_PRINT_DATA(stringLenght(amostraUserMsg),USERMSG1,ptr_sampleString);

//					HW_PRINT_DATA(0,USERMSG2,alturaSaltoUserMsg,&displayUpdateStatus);
					HW_PRINT_DATA(0,USERMSG2,alturaSaltoUserMsg);
					ptr_alturaString = param_1_toString(&ptr_result->sampleMeasurement[testSamples].alturaSalto);
					HW_PRINT_DATA(stringLenght(alturaSaltoUserMsg),USERMSG2,strcat(ptr_alturaString,"cm"));

//					HW_PRINT_DATA(strlen(alturaSaltoUserMsg)+strlen(ptr_alturaString)+1,USERMSG2,tempoVooUserMsg);
//					ptr_vooTimeString = param_2_toString(&ptr_result->sampleMeasurement[testSamples].uiVooTime);
//					HW_PRINT_DATA(strlen(alturaSaltoUserMsg)+strlen(ptr_alturaString)+strlen(tempoVooUserMsg)+1,USERMSG2 ,ptr_vooTimeString);

//					updateUserMsg(0,INSERTMSG,potenciaUserMsg,&displayUpdateStatus);
					HW_PRINT_DATA(0,INSERTMSG,potenciaUserMsg);
					ptr_potString = param_1_toString(&ptr_result->sampleMeasurement[testSamples].potenciaSalto);
					HW_PRINT_DATA(strlen(potenciaUserMsg),INSERTMSG,strcat(ptr_potString,"W"));

//					HW_PRINT_DATA(strlen(potenciaUserMsg)+strlen(ptr_potString)+1,INSERTMSG,tempoSoloUserMsg);
//					ptr_soloTimeString = param_2_toString(&ptr_result->sampleMeasurement[testSamples].uiSoloTime);
//					HW_PRINT_DATA(strlen(potenciaUserMsg)+strlen(ptr_potString)+strlen(tempoSoloUserMsg)+1,INSERTMSG , ptr_soloTimeString);

				}
				else
				{
					HW_PRINT_DATA(0, USERMSG1, "NAO HA DADOS");
					HW_PRINT_DATA(0, OPTIONMSG, pularUserMsg);
				}

				key = getKeyPressed();

				if(key == AVANCAR)
				{
					resetKeyPressed();
					readyUserInterface(&displayUpdateStatus);
					testSamples++;
					if(testSamples == ptr_result->resultTestAcquiredSamples) testSamples = 0;
					subMenuIniciar->menuState = getNextSub(RESULTS);
				}

				else if(key == PARAR)
                {
                	resetKeyPressed();
                    readyUserInterface(&displayUpdateStatus);
                    subMenuIniciar->menuState = getNextSub(SAVE_DATA);
                }

            break;

            case SAVE_DATA:
                updateUserMsg(0,0,saveUserMsg,&displayUpdateStatus);
                HW_PRINT_DATA(0,INSERTMSG,avancarUserMsg);
                HW_PRINT_DATA(0,OPTIONMSG,selecionarUserMsg);
                key = getKeyPressed();

                if(key == AVANCAR)
                {
                	resetKeyPressed();
                    readyUserInterface(&displayUpdateStatus);
                    subMenuIniciar->menuState = getNextSub(CANCEL_SAVE);
                }
                else if(key == CONFIRMAR)
                {
                	resetKeyPressed();
                	save_SD_card(ptr_result,indexTest);
                    readyUserInterface(&displayUpdateStatus);
                    updateUserMsg(0,0,savedUserMsg,&displayUpdateStatus);
                    subMenuIniciar->menuState = getNextSub(COMM_OFF);
                    testSamples = 0;
  				                      readyUserInterface(&displayUpdateStatus);
                    key = MENU;
                }
            break;

            case CANCEL_SAVE:
                updateUserMsg(0,0,cancelUserMsg,&displayUpdateStatus);
                HW_PRINT_DATA(0,INSERTMSG,avancarUserMsg);
				HW_PRINT_DATA(0,OPTIONMSG,selecionarUserMsg);
                key = getKeyPressed();

                if(key == AVANCAR)
                {
                	resetKeyPressed();
                    readyUserInterface(&displayUpdateStatus);
                    subMenuIniciar->menuState = getNextSub(SAVE_DATA);
                }
                else if(key == CONFIRMAR)
                {
                	resetKeyPressed();
                    //subMenuIniciar->menuSelect = setSelectSub(&subMenuIniciar->menuState);
                    testSamples = 0;
                    indexTest++;
                    //
                    subMenuIniciar->menuState = getNextSub(COMM_OFF);
                    readyUserInterface(&displayUpdateStatus);
                    key = MENU;
                }
            break;
        }
    }
}
