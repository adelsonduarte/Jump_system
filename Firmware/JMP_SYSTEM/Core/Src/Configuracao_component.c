#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "Configuracao_component.h"
#include "SubMenu.h"
#include "DisplayMessages.h"
#include "DataProcessing.h"
#include "Display_module.h"
#include "Data.h"
#include "time.h"



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
//verificar se vou usar o codigo abaixo


unsigned char configStateMachine(struct Menu* subMenu)
{
    unsigned char* ptr_altMinString;
    unsigned char* ptr_altMaxString;
    unsigned char* ptr_numSaltosString;
    unsigned char* ptr_intervalNumSaltosString;
    unsigned char* ptr_jumpSelectString;
    unsigned char* ptr_altDJString;
    unsigned char* ptr_numSeriesString;
    unsigned char* ptr_intervalSeriesString;

    unsigned char userIntervalSaltosTimeString[9];
    struct tm myTime;
	struct tm* configIntervalTimeStruct = &myTime;

    struct Menu* subMenuTesteConfigurar = subMenu;
    unsigned char cursorPosition[2] = {0,0};
    //verificar se vou usar
    struct dataInsert measurementSensor1;
    struct dataInsert measurementSensor2;
    //
    struct dataInsert* ptr_userConfiguration = getUserConfigStruct();
    resetConfigStruct(ptr_userConfiguration);

    //
    unsigned char key = 0;
    unsigned char displayUpdateStatus = IDDLE;
    short index = 2;
    while(key != MENU)
    {
        switch(subMenuTesteConfigurar->menuState)
        {
        case IDDLE:
            subMenuTesteConfigurar->menuState = getNextSub(CONFIG_SENSOR_1);

            break;
            case CONFIG_SENSOR_1:
                updateUserMsg(0,0,sensor1UserMsg,&displayUpdateStatus);
                key = getKeyPressed();

                if(key == AVANCAR)
                {
                	resetKeyPressed();
                    readyUserInterface(&displayUpdateStatus,cursorPosition);
                    subMenuTesteConfigurar->menuState = getNextSub(CONFIG_SENSOR_2);
                }
                else if(key == CONFIRMAR)
                {
                	resetKeyPressed();
                    readyUserInterface(&displayUpdateStatus,cursorPosition);
                    ptr_userConfiguration->userSelectSensorChannel = 1;
                    subMenuTesteConfigurar->menuSelect = setSelectSub(&subMenuTesteConfigurar->menuState);
                    subMenuTesteConfigurar->menuState = getNextSub(SENSOR_ALTMIN);
                }

                break;

            case CONFIG_SENSOR_2:
                updateUserMsg(0,0,sensor2UserMsg,&displayUpdateStatus);
                key = getKeyPressed();

                if(key == AVANCAR)
                {
                	resetKeyPressed();
                    readyUserInterface(&displayUpdateStatus,cursorPosition);
                    subMenuTesteConfigurar->menuState = getNextSub(CONFIG_SENSOR_1);
                }
                else if(key == CONFIRMAR)
                {
                	resetKeyPressed();
                    readyUserInterface(&displayUpdateStatus,cursorPosition);
                    ptr_userConfiguration->userSelectSensorChannel = 2;
                    subMenuTesteConfigurar->menuSelect = setSelectSub(&subMenuTesteConfigurar->menuState);
                    subMenuTesteConfigurar->menuState = getNextSub(SENSOR_ALTMIN);
                }
                break;

            case SENSOR_ALTMIN:
                updateUserMsg(0,0,altminUserMsg,&displayUpdateStatus);
                ptr_altMinString = getAltMinString();
                printDataDisplay(0,1,ptr_altMinString);
                updateDataDisplay(index,1);
                key = getKeyPressed();

                if(key == INSERIR)
                {
                	resetKeyPressed();
                    setUserAltMin(&index);
                    subMenuTesteConfigurar->menuState = getNextSub(SENSOR_ALTMIN);
                }
                else if(key == AVANCAR)
                {
                	resetKeyPressed();
                    indexChange(&index,2);
                }
                else if(key == CONFIRMAR)
                {
                	resetKeyPressed();
                    index = 2;
                    readyUserInterface(&displayUpdateStatus,cursorPosition);
                    subMenuTesteConfigurar->menuState = getNextSub(SENSOR_ALTMAX);
                    subMenuTesteConfigurar->menuSelect = setSelectSub(&subMenuTesteConfigurar->menuState);
                }
                break;

            case SENSOR_ALTMAX:
                updateUserMsg(0,0,altmaxUserMsg,&displayUpdateStatus);
                ptr_altMaxString = getAltMaxString();
                printDataDisplay(0,1,ptr_altMaxString);
                updateDataDisplay(index,1);
                key = getKeyPressed();

                if(key == INSERIR)
                {
                	resetKeyPressed();
                    setUserAltMax(&index);
                    subMenuTesteConfigurar->menuState = getNextSub(SENSOR_ALTMAX);
                }
                else if(key == AVANCAR)
                {
                	resetKeyPressed();
                    indexChange(&index,2);
                }
                else if(key == CONFIRMAR)
                {
                	resetKeyPressed();
                    index = 2;
                    readyUserInterface(&displayUpdateStatus,cursorPosition);
                    subMenuTesteConfigurar->menuState = getNextSub(SENSOR_SALTOS);
                    subMenuTesteConfigurar->menuSelect = setSelectSub(&subMenuTesteConfigurar->menuState);
                }

                break;

            case SENSOR_SALTOS:
                updateUserMsg(0,0,numsaltosUserMsg,&displayUpdateStatus);
                ptr_numSaltosString = getNumSaltosString();
                printDataDisplay(0,1,ptr_numSaltosString);
                updateDataDisplay(index,1);
                key = getKeyPressed();

                if(key == INSERIR)
                {
                	resetKeyPressed();
                    setUserNumSaltos(&index);
                    subMenuTesteConfigurar->menuState = getNextSub(SENSOR_SALTOS);
                }
                else if(key == AVANCAR)
                {
                	resetKeyPressed();
                    indexChange(&index,2);
                }
                else if(key == CONFIRMAR)
                {
                	resetKeyPressed();
                    index = 4;
                    readyUserInterface(&displayUpdateStatus,cursorPosition);
                    subMenuTesteConfigurar->menuState = getNextSub(SENSOR_INT_SALTOS);
                    subMenuTesteConfigurar->menuSelect = setSelectSub(&subMenuTesteConfigurar->menuState);
                }
                break;

            case SENSOR_INT_SALTOS:
                updateUserMsg(0,0,intersaltosUserMsg,&displayUpdateStatus);
                configIntervalTimeStruct = getIntervalTimeStruct();
                strftime(userIntervalSaltosTimeString, sizeof(userIntervalSaltosTimeString), "%M:%S", configIntervalTimeStruct);
                printDataDisplay(0,1,userIntervalSaltosTimeString);
                updateDataDisplay(index,1);
                key = getKeyPressed();

                if(key == INSERIR)
                {
                	resetKeyPressed();
                	setIntervalSaltosTime(&index);
                    subMenuTesteConfigurar->menuState = getNextSub(SENSOR_INT_SALTOS);
                }
                else if(key == AVANCAR)
				{
					resetKeyPressed();
					indexColumn(&index,4);
				}
                else if(key == CONFIRMAR)
                {
                	resetKeyPressed();
                    index = 0;
                    readyUserInterface(&displayUpdateStatus,cursorPosition);
                    subMenuTesteConfigurar->menuState = getNextSub(SENSOR_JMP_SELECT);
                    subMenuTesteConfigurar->menuSelect = setSelectSub(&subMenuTesteConfigurar->menuState);
                }

                break;

            case SENSOR_JMP_SELECT:
                updateUserMsg(0,0,tiposaltoUserMsg,&displayUpdateStatus);
                ptr_jumpSelectString = getTypeJumpString();
                printDataDisplay(0,1,ptr_jumpSelectString);
                updateDataDisplay(index,1);
                key = getKeyPressed();

                if(key == INSERIR)
                {
                	resetKeyPressed();
                    setUserTypeJump(&index);
                    subMenuTesteConfigurar->menuState = getNextSub(SENSOR_JMP_SELECT);

                }
                else if(key == CONFIRMAR)
                {
                	resetKeyPressed();
                    if(*ptr_jumpSelectString == '3')
                    {
                    	index = 1;
                        subMenuTesteConfigurar->menuState = getNextSub(SENSOR_ALTDJ);
                        subMenuTesteConfigurar->menuSelect = setSelectSub(&subMenuTesteConfigurar->menuState);
                    }
                    else
                    {
                    	index = 2;
                        subMenuTesteConfigurar->menuState = getNextSub(SENSOR_SERIES);
                        subMenuTesteConfigurar->menuSelect = setSelectSub(&subMenuTesteConfigurar->menuState);
                    }
                    //TESTE trocar a variavel por uma local e o resultado enviar para ptr_userConfiguration->userCMJ.
                    readyUserInterface(&displayUpdateStatus,cursorPosition);

                }

                break;

            case SENSOR_ALTDJ:
                updateUserMsg(0,0,altdjUserMsg,&displayUpdateStatus);
                ptr_altDJString = getAltDJString();
                printDataDisplay(0,1,ptr_altDJString);
                updateDataDisplay(index,1);
                key = getKeyPressed();

                if(key == INSERIR)
                {
                	resetKeyPressed();
                    setUserAltDJ(&index);
                    subMenuTesteConfigurar->menuState = getNextSub(SENSOR_ALTDJ);
                }
                else if(key == CONFIRMAR)
                {
                	resetKeyPressed();
                    index = 2;
                    readyUserInterface(&displayUpdateStatus,cursorPosition);
                    subMenuTesteConfigurar->menuState = getNextSub(SENSOR_SERIES);
                    subMenuTesteConfigurar->menuSelect = setSelectSub(&subMenuTesteConfigurar->menuState);
                }

                break;

            case SENSOR_SERIES:
                updateUserMsg(0,0,numserieUserMsg,&displayUpdateStatus);
                ptr_numSeriesString = getNumSeriesString();
                printDataDisplay(0,1,ptr_numSeriesString);
                updateDataDisplay(index,1);
                key = getKeyPressed();

                if(key == INSERIR)
                {
                	resetKeyPressed();
                    setUserNumSeries(&index);
                    subMenuTesteConfigurar->menuState = getNextSub(SENSOR_SERIES);
                }
                else if(key == AVANCAR)
				{
					resetKeyPressed();
					indexColumn(&index,2);
				}
                else if(key == CONFIRMAR)
                {
                	resetKeyPressed();
                    index = 2;
                    readyUserInterface(&displayUpdateStatus,cursorPosition);
                    subMenuTesteConfigurar->menuState = getNextSub(SENSOR_INT_SERIES);
                    subMenuTesteConfigurar->menuSelect = setSelectSub(&subMenuTesteConfigurar->menuState);
                }

                break;

            case SENSOR_INT_SERIES:
                updateUserMsg(0,0,interseriesUserMsg,&displayUpdateStatus);
                ptr_intervalSeriesString = getIntervalSeriesString();
                printDataDisplay(0,1,ptr_intervalSeriesString);
                updateDataDisplay(index,1);
                key = getKeyPressed();

                if(key == INSERIR)
                {
                	resetKeyPressed();
                    setUserIntervalSeries(&index);
                    subMenuTesteConfigurar->menuState = getNextSub(SENSOR_INT_SERIES);
                }
                else if(key == AVANCAR)
				{
					resetKeyPressed();
					indexColumn(&index,2);
				}
                else if(key == CONFIRMAR)
                {
                	resetKeyPressed();
                    index = 2;
                    readyUserInterface(&displayUpdateStatus,cursorPosition);
                    subMenuTesteConfigurar->menuState = getNextSub(TAPETE_ON);
                    subMenuTesteConfigurar->menuSelect = setSelectSub(&subMenuTesteConfigurar->menuState);
                }

            break;

            case TAPETE_ON:
                updateUserMsg(0,0,intapeteUserMsg,&displayUpdateStatus);
                key = getKeyPressed();

                if(key == AVANCAR)
                {
                	resetKeyPressed();
                	readyUserInterface(&displayUpdateStatus,cursorPosition);
                    subMenuTesteConfigurar->menuState = getNextSub(TAPETE_OFF);
                }
                else if(key == CONFIRMAR)
                {
                	resetKeyPressed();
                    readyUserInterface(&displayUpdateStatus,cursorPosition);
                    subMenuTesteConfigurar->menuSelect = setSelectSub(&subMenuTesteConfigurar->menuState);
                    ptr_userConfiguration->userSelectTapete = TRUE;
                    subMenuTesteConfigurar->menuState = getNextSub(SAVE_CONFIGS);
                }
                break;

            case TAPETE_OFF:
                updateUserMsg(0,0,outtapeteUserMsg,&displayUpdateStatus);
                key = getKeyPressed();

                if(key == AVANCAR)
                {
                	resetKeyPressed();
                	readyUserInterface(&displayUpdateStatus,cursorPosition);
                    subMenuTesteConfigurar->menuState = getNextSub(TAPETE_ON);
                }
                else if(key == CONFIRMAR)
                {
                	resetKeyPressed();
                    readyUserInterface(&displayUpdateStatus,cursorPosition);
                    subMenuTesteConfigurar->menuSelect = setSelectSub(&subMenuTesteConfigurar->menuState);
                    ptr_userConfiguration->userSelectTapete = FALSE;
                    subMenuTesteConfigurar->menuState = getNextSub(SAVE_CONFIGS);
                }
                break;

            case SAVE_CONFIGS:
                subMenuTesteConfigurar->menuState = getNextSub(CONFIG_SENSOR_1);
                setInsertData(ptr_userConfiguration);
                readyUserInterface(&displayUpdateStatus,cursorPosition);
                key = MENU;
                break;
        }
    }
}


