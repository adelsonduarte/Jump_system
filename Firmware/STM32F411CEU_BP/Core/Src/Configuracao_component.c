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

unsigned char configStateMachine(struct Menu* subMenu)
{
    unsigned char* ptr_altMinString;
    unsigned char* ptr_altMaxString;
    unsigned char* ptr_numSaltosString;
//    unsigned char* ptr_intervalNumSaltosString;
    unsigned char* ptr_jumpSelectString;
    unsigned char* ptr_altDJString;
    unsigned char* ptr_numSeriesString;
//    unsigned char* ptr_intervalSeriesString;

    unsigned char userIntervalTimeString[9];
	struct tm* configIntervalTimeStruct;

	struct tm* configIntervalSeriesTimeStruct;



    struct Menu* subMenuTesteConfigurar = subMenu;
    //
    struct dataInsert* ptr_userConfiguration = getUserConfigStruct();
    resetConfigStruct(ptr_userConfiguration);

    //
    unsigned char key = 0;
    unsigned char displayUpdateStatus = IDDLE;
    short index = 2;
    unsigned int altMin = 0;
    unsigned int altMax = 0;
    unsigned int tmin = 0;
    unsigned int tmax = 0;


    while(key != MENU)
    {
        switch(subMenuTesteConfigurar->menuState)
        {
        case IDDLE:
            subMenuTesteConfigurar->menuState = getNextSub(CONFIG_SENSOR_1);

            break;
            case CONFIG_SENSOR_1:
                updateUserMsg(0,USERMSG1,sensor1UserMsg,&displayUpdateStatus);
                HW_PRINT_DATA(0,INSERTMSG,avancarUserMsg);
                HW_PRINT_DATA(stringLenght(avancarUserMsg),INSERTMSG,menuUserMsg);
                HW_PRINT_DATA(0,OPTIONMSG,selecionarUserMsg);
                key = getKeyPressed();

                if(key == AVANCAR)
                {
                	resetKeyPressed();
                    readyUserInterface(&displayUpdateStatus);
                    subMenuTesteConfigurar->menuState = getNextSub(CONFIG_SENSOR_2);
                }
                else if(key == CONFIRMAR)
                {
                	resetKeyPressed();
                    readyUserInterface(&displayUpdateStatus);
                    ptr_userConfiguration->userSelectSensorChannel = 1;
                    subMenuTesteConfigurar->menuState = getNextSub(SENSOR_ALTMIN);
                }

                break;

            case CONFIG_SENSOR_2:
                updateUserMsg(0,0,sensor2UserMsg,&displayUpdateStatus);
                HW_PRINT_DATA(0,INSERTMSG,avancarUserMsg);
                HW_PRINT_DATA(stringLenght(avancarUserMsg),INSERTMSG,menuUserMsg);
                HW_PRINT_DATA(0,OPTIONMSG,selecionarUserMsg);
                key = getKeyPressed();

                if(key == AVANCAR)
                {
                	resetKeyPressed();
                    readyUserInterface(&displayUpdateStatus);
                    subMenuTesteConfigurar->menuState = getNextSub(CONFIG_SENSOR_1);
                }
                else if(key == CONFIRMAR)
                {
                	resetKeyPressed();
                    readyUserInterface(&displayUpdateStatus);
                    ptr_userConfiguration->userSelectSensorChannel = 2;
                    subMenuTesteConfigurar->menuState = getNextSub(SENSOR_ALTMIN);
                }
                break;

            case SENSOR_ALTMIN:
                updateUserMsg(0,USERMSG1,altminUserMsg,&displayUpdateStatus);
                ptr_altMinString = getAltMinString();
                HW_PRINT_DATA(0,USERMSG2,ptr_altMinString);
                HW_UPDATE_DATA(index,USERMSG2);

				HW_PRINT_DATA(0,INSERTMSG,avancarUserMsg);
				HW_PRINT_DATA(stringLenght(avancarUserMsg),INSERTMSG,menuUserMsg);
				HW_PRINT_DATA(0,OPTIONMSG,selecionarUserMsg);
				HW_PRINT_DATA(stringLenght(selecionarUserMsg),OPTIONMSG,inserirUserMsg);
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
                    altMin = stringToInt(getAltMinString());
                    tmin = alturaToTempo(altMin);
                    ptr_userConfiguration->userAlturaMin = tmin;
                    readyUserInterface(&displayUpdateStatus);
                    subMenuTesteConfigurar->menuState = getNextSub(SENSOR_ALTMAX);
                }
                break;

            case SENSOR_ALTMAX:
                updateUserMsg(0,USERMSG1,altmaxUserMsg,&displayUpdateStatus);
                ptr_altMaxString = getAltMaxString();
                HW_PRINT_DATA(0,USERMSG2,ptr_altMaxString);
                HW_UPDATE_DATA(index,USERMSG2);

                HW_PRINT_DATA(0,INSERTMSG,avancarUserMsg);
				HW_PRINT_DATA(stringLenght(avancarUserMsg),INSERTMSG,menuUserMsg);
				HW_PRINT_DATA(0,OPTIONMSG,selecionarUserMsg);
				HW_PRINT_DATA(stringLenght(selecionarUserMsg),OPTIONMSG,inserirUserMsg);
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
                    altMax = stringToInt(getAltMaxString());
                    tmax = alturaToTempo(altMax);
                    ptr_userConfiguration->userAlturaMax = tmax;
                    readyUserInterface(&displayUpdateStatus);
                    subMenuTesteConfigurar->menuState = getNextSub(SENSOR_SALTOS);
                }

                break;

            case SENSOR_SALTOS:
                updateUserMsg(0,USERMSG1,numsaltosUserMsg,&displayUpdateStatus);
                ptr_numSaltosString = getNumSaltosString();
                HW_PRINT_DATA(0,USERMSG2,ptr_numSaltosString);
                HW_UPDATE_DATA(index,USERMSG2);

                HW_PRINT_DATA(0,INSERTMSG,avancarUserMsg);
				HW_PRINT_DATA(stringLenght(avancarUserMsg),INSERTMSG,menuUserMsg);
				HW_PRINT_DATA(0,OPTIONMSG,selecionarUserMsg);
				HW_PRINT_DATA(stringLenght(selecionarUserMsg),OPTIONMSG,inserirUserMsg);
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
                    ptr_userConfiguration->userNumSaltos = stringToInt(getNumSaltosString());
                    readyUserInterface(&displayUpdateStatus);
                    subMenuTesteConfigurar->menuState = getNextSub(SENSOR_INT_SALTOS);
                }
                break;

            case SENSOR_INT_SALTOS:
                updateUserMsg(0,USERMSG1,intersaltosUserMsg,&displayUpdateStatus);
                configIntervalTimeStruct = getIntervalSaltosTimeStruct();
                strftime(userIntervalTimeString, sizeof(userIntervalTimeString), "%M:%S", configIntervalTimeStruct);
                HW_PRINT_DATA(0,USERMSG2,userIntervalTimeString);
                HW_UPDATE_DATA(index,USERMSG2);

                HW_PRINT_DATA(0,INSERTMSG,avancarUserMsg);
				HW_PRINT_DATA(stringLenght(avancarUserMsg),INSERTMSG,menuUserMsg);
				HW_PRINT_DATA(0,OPTIONMSG,selecionarUserMsg);
				HW_PRINT_DATA(stringLenght(selecionarUserMsg),OPTIONMSG,inserirUserMsg);
                key = getKeyPressed();

                if(key == INSERIR)
                {
                	resetKeyPressed();
                	setUserIntervalSaltosTime(&index);
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
                    ptr_userConfiguration->userIntervalSaltos = milisecondsTime(configIntervalTimeStruct);
                    readyUserInterface(&displayUpdateStatus);
                    subMenuTesteConfigurar->menuState = getNextSub(SENSOR_JMP_SELECT);
                }

                break;

            case SENSOR_JMP_SELECT:
                updateUserMsg(0,USERMSG1,tiposaltoUserMsg,&displayUpdateStatus);
                ptr_jumpSelectString = getTypeJumpString();
                HW_PRINT_DATA(0,USERMSG2,ptr_jumpSelectString);
                HW_UPDATE_DATA(index,USERMSG2);
				HW_PRINT_DATA(0,OPTIONMSG,selecionarUserMsg);
				HW_PRINT_DATA(stringLenght(selecionarUserMsg),OPTIONMSG,inserirUserMsg);
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
                    }
                    else
                    {
                    	index = 2;
                        subMenuTesteConfigurar->menuState = getNextSub(SENSOR_SERIES);
                    }
                    //TESTE trocar a variavel por uma local e o resultado enviar para ptr_userConfiguration->userCMJ.
                    readyUserInterface(&displayUpdateStatus);

                }

                break;

            case SENSOR_ALTDJ:
                updateUserMsg(0,USERMSG1,altdjUserMsg,&displayUpdateStatus);
                ptr_altDJString = getAltDJString();
                HW_PRINT_DATA(0,USERMSG2,ptr_altDJString);
                HW_UPDATE_DATA(index,USERMSG2);

                HW_PRINT_DATA(0,INSERTMSG,avancarUserMsg);
				HW_PRINT_DATA(stringLenght(avancarUserMsg),INSERTMSG,menuUserMsg);
				HW_PRINT_DATA(0,OPTIONMSG,selecionarUserMsg);
				HW_PRINT_DATA(stringLenght(selecionarUserMsg),OPTIONMSG,inserirUserMsg);
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
                    readyUserInterface(&displayUpdateStatus);
                    ptr_userConfiguration->userAlturaDJ = stringToInt(getAltDJString());
                    subMenuTesteConfigurar->menuState = getNextSub(SENSOR_SERIES);
                }
                else if(key == AVANCAR)
				{
					resetKeyPressed();
					indexColumn(&index,2);
				}

                break;

            case SENSOR_SERIES:
                updateUserMsg(0,USERMSG1,numserieUserMsg,&displayUpdateStatus);
                ptr_numSeriesString = getNumSeriesString();
                HW_PRINT_DATA(0,USERMSG2,ptr_numSeriesString);
                HW_UPDATE_DATA(index,USERMSG2);
                HW_PRINT_DATA(0,INSERTMSG,avancarUserMsg);
				HW_PRINT_DATA(stringLenght(avancarUserMsg),INSERTMSG,menuUserMsg);
				HW_PRINT_DATA(0,OPTIONMSG,selecionarUserMsg);
				HW_PRINT_DATA(stringLenght(selecionarUserMsg),OPTIONMSG,inserirUserMsg);
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
                    index = 4;
                    readyUserInterface(&displayUpdateStatus);
                    ptr_userConfiguration->userNumSeries = stringToInt(getNumSeriesString());
                    subMenuTesteConfigurar->menuState = getNextSub(SENSOR_INT_SERIES);
                }

                break;

            case SENSOR_INT_SERIES:
                updateUserMsg(0,USERMSG1,interseriesUserMsg,&displayUpdateStatus);
                configIntervalSeriesTimeStruct = getintervalSeriesTimeStruct();
				strftime(userIntervalTimeString, sizeof(userIntervalTimeString), "%M:%S", configIntervalSeriesTimeStruct);
				HW_PRINT_DATA(0,USERMSG2,userIntervalTimeString);
                HW_UPDATE_DATA(index,USERMSG2);

                HW_PRINT_DATA(0,INSERTMSG,avancarUserMsg);
				HW_PRINT_DATA(stringLenght(avancarUserMsg),INSERTMSG,menuUserMsg);
				HW_PRINT_DATA(0,OPTIONMSG,selecionarUserMsg);
				HW_PRINT_DATA(stringLenght(selecionarUserMsg),OPTIONMSG,inserirUserMsg);
                key = getKeyPressed();

                if(key == INSERIR)
                {
                	resetKeyPressed();
                	setUserIntervalSeriesTime(&index);
                    subMenuTesteConfigurar->menuState = getNextSub(SENSOR_INT_SERIES);
                }
                else if(key == AVANCAR)
				{
					resetKeyPressed();
					indexColumn(&index,4);
				}
                else if(key == CONFIRMAR)
                {
                	resetKeyPressed();
                    index = 2;
                    ptr_userConfiguration->userIntervalSeries = milisecondsTime(configIntervalSeriesTimeStruct);
                    readyUserInterface(&displayUpdateStatus);
                    subMenuTesteConfigurar->menuState = getNextSub(TAPETE_ON);
                }

            break;

            case TAPETE_ON:
                updateUserMsg(0,USERMSG1,intapeteUserMsg,&displayUpdateStatus);
                HW_PRINT_DATA(0,INSERTMSG,avancarUserMsg);
				HW_PRINT_DATA(stringLenght(avancarUserMsg),INSERTMSG,menuUserMsg);
				HW_PRINT_DATA(0,OPTIONMSG,selecionarUserMsg);
                key = getKeyPressed();

                if(key == AVANCAR)
                {
                	resetKeyPressed();
                	readyUserInterface(&displayUpdateStatus);
                    subMenuTesteConfigurar->menuState = getNextSub(TAPETE_OFF);
                }
                else if(key == CONFIRMAR)
                {
                	resetKeyPressed();
                    readyUserInterface(&displayUpdateStatus);
                    ptr_userConfiguration->userSelectTapete = TRUE;
                    subMenuTesteConfigurar->menuState = getNextSub(SAVE_CONFIGS);
                }
                break;

            case TAPETE_OFF:
                updateUserMsg(0,USERMSG1,outtapeteUserMsg,&displayUpdateStatus);
                HW_PRINT_DATA(0,INSERTMSG,avancarUserMsg);
				HW_PRINT_DATA(stringLenght(avancarUserMsg),INSERTMSG,menuUserMsg);
				HW_PRINT_DATA(0,OPTIONMSG,selecionarUserMsg);
                key = getKeyPressed();

                if(key == AVANCAR)
                {
                	resetKeyPressed();
                    readyUserInterface(&displayUpdateStatus);
                    subMenuTesteConfigurar->menuState = getNextSub(TAPETE_ON);
                }
                else if(key == CONFIRMAR)
                {
                	resetKeyPressed();
                    readyUserInterface(&displayUpdateStatus);
                    ptr_userConfiguration->userSelectTapete = FALSE;
                    subMenuTesteConfigurar->menuState = getNextSub(SAVE_CONFIGS);
                }
                break;

            case SAVE_CONFIGS:
                subMenuTesteConfigurar->menuState = getNextSub(CONFIG_SENSOR_1);
                setInsertData(ptr_userConfiguration);
//                wflashConfigData(ptr_userConfiguration);
                readyUserInterface(&displayUpdateStatus);
                key = MENU;
                break;
        }
    }
}

