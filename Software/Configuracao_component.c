#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "Configuracao_component.h"
#include "SubMenu.h"
#include "DisplayMessages.h"
#include "DataProcessing.h"

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
    unsigned char index = 0;
    while(key != MENU)
    {
        switch(subMenuTesteConfigurar->menuState)
        {
        case IDDLE:
            subMenuTesteConfigurar->menuState = getNextSub(CONFIG_SENSOR_1);

            break;
            case CONFIG_SENSOR_1:
                updateUserMsg(0,0,sensor1UserMsg,&displayUpdateStatus);
                key = getchar();
                while( getchar() != '\n' );
                if(key == AVANCAR)
                {
                    readyUserInterface(&displayUpdateStatus,cursorPosition);
                    subMenuTesteConfigurar->menuState = getNextSub(CONFIG_SENSOR_2);
                }
                else if(key == CONFIRMAR)
                {
                    readyUserInterface(&displayUpdateStatus,cursorPosition);
                    ptr_userConfiguration->userSelectSensorChannel = 1;
                    subMenuTesteConfigurar->menuSelect = setSelectSub(&subMenuTesteConfigurar->menuState);
                    subMenuTesteConfigurar->menuState = getNextSub(SENSOR_ALTMIN);
                }

                break;

            case CONFIG_SENSOR_2:
                updateUserMsg(0,0,sensor2UserMsg,&displayUpdateStatus);
                key = getchar();
                while( getchar() != '\n' );
                if(key == AVANCAR)
                {
                    readyUserInterface(&displayUpdateStatus,cursorPosition);
                    subMenuTesteConfigurar->menuState = getNextSub(CONFIG_SENSOR_1);
                }
                else if(key == CONFIRMAR)
                {
                    readyUserInterface(&displayUpdateStatus,cursorPosition);
                    ptr_userConfiguration->userSelectSensorChannel = 2;
                    subMenuTesteConfigurar->menuSelect = setSelectSub(&subMenuTesteConfigurar->menuState);
                    subMenuTesteConfigurar->menuState = getNextSub(SENSOR_ALTMIN);
                }
                break;

            case SENSOR_ALTMIN:
                updateUserMsg(0,0,altminUserMsg,&displayUpdateStatus);
                ptr_altMinString = getAltMinString();
                insertUserInterface(0,0,ptr_altMinString);
                key = getchar();
                while( getchar() != '\n' );
                if(key == INSERIR)
                {
                    setUserAltMin(&index);
                    subMenuTesteConfigurar->menuState = getNextSub(SENSOR_ALTMIN);
                }
                else if(key == AVANCAR)
                {
                    indexChange(&index,2);
                }
                else if(key == CONFIRMAR)
                {
                    index = 0;
                    readyUserInterface(&displayUpdateStatus,cursorPosition);
                    subMenuTesteConfigurar->menuState = getNextSub(SENSOR_ALTMAX);
                    subMenuTesteConfigurar->menuSelect = setSelectSub(&subMenuTesteConfigurar->menuState);
                }
                break;

            case SENSOR_ALTMAX:
                updateUserMsg(0,0,altmaxUserMsg,&displayUpdateStatus);
                ptr_altMaxString = getAltMaxString();
                insertUserInterface(0,0,ptr_altMaxString);
                key = getchar();
                while( getchar() != '\n' );
                if(key == INSERIR)
                {
                    setUserAltMax(&index);
                    subMenuTesteConfigurar->menuState = getNextSub(SENSOR_ALTMAX);
                }
                else if(key == AVANCAR)
                {
                    indexChange(&index,2);
                }
                else if(key == CONFIRMAR)
                {
                    index = 0;
                    readyUserInterface(&displayUpdateStatus,cursorPosition);
                    subMenuTesteConfigurar->menuState = getNextSub(SENSOR_SALTOS);
                    subMenuTesteConfigurar->menuSelect = setSelectSub(&subMenuTesteConfigurar->menuState);
                }

                break;

            case SENSOR_SALTOS:
                updateUserMsg(0,0,numsaltosUserMsg,&displayUpdateStatus);
                ptr_numSaltosString = getNumSaltosString();
                insertUserInterface(0,0,ptr_numSaltosString);
                key = getchar();
                while( getchar() != '\n' );
                if(key == INSERIR)
                {
                    setUserNumSaltos(&index);
                    subMenuTesteConfigurar->menuState = getNextSub(SENSOR_SALTOS);
                }
                else if(key == AVANCAR)
                {
                    indexChange(&index,2);
                }
                else if(key == CONFIRMAR)
                {
                    index = 0;
                    readyUserInterface(&displayUpdateStatus,cursorPosition);
                    subMenuTesteConfigurar->menuState = getNextSub(SENSOR_INT_SALTOS);
                    subMenuTesteConfigurar->menuSelect = setSelectSub(&subMenuTesteConfigurar->menuState);
                }
                break;

            case SENSOR_INT_SALTOS: //VERIFICAR AINDA resolucao de 1s 00min:00segundos
                updateUserMsg(0,0,intersaltosUserMsg,&displayUpdateStatus);
                ptr_intervalNumSaltosString = getIntervalSaltosString();
                insertUserInterface(0,0,ptr_intervalNumSaltosString);
                key = getchar();
                while( getchar() != '\n' );
                if(key == INSERIR)
                {
                     setUserIntervalSaltos(&index);
                    subMenuTesteConfigurar->menuState = getNextSub(SENSOR_INT_SALTOS);
                }
                else if(key == CONFIRMAR)
                {
                    index = 0;
                    readyUserInterface(&displayUpdateStatus,cursorPosition);
                    subMenuTesteConfigurar->menuState = getNextSub(SENSOR_JMP_SELECT);
                    subMenuTesteConfigurar->menuSelect = setSelectSub(&subMenuTesteConfigurar->menuState);
                }

                break;

            case SENSOR_JMP_SELECT:
                updateUserMsg(0,0,tiposaltoUserMsg,&displayUpdateStatus);
                ptr_jumpSelectString = getTypeJumpString();
                insertUserInterface(0,0,ptr_jumpSelectString);
                key = getchar();
                while( getchar() != '\n' );
                if(key == INSERIR)
                {
                    setUserTypeJump(&index);
                    subMenuTesteConfigurar->menuState = getNextSub(SENSOR_JMP_SELECT);

                }
                else if(key == CONFIRMAR)
                {
                    if(*ptr_jumpSelectString == '3')
                    {
                        subMenuTesteConfigurar->menuState = getNextSub(SENSOR_ALTDJ);
                        subMenuTesteConfigurar->menuSelect = setSelectSub(&subMenuTesteConfigurar->menuState);
                    }
                    else
                    {
                        subMenuTesteConfigurar->menuState = getNextSub(SENSOR_SERIES);
                        subMenuTesteConfigurar->menuSelect = setSelectSub(&subMenuTesteConfigurar->menuState);
                    }
                    //TESTE trocar a variavel por uma local e o resultado enviar para ptr_userConfiguration->userCMJ.
                    readyUserInterface(&displayUpdateStatus,cursorPosition);
                    index = 0;
                }

                break;

            case SENSOR_ALTDJ:
                updateUserMsg(0,0,altdjUserMsg,&displayUpdateStatus);
                ptr_altDJString = getAltDJString();
                insertUserInterface(0,0,ptr_altDJString);
                key = getchar();
                while( getchar() != '\n' );
                if(key == INSERIR)
                {
                    setUserAltDJ(&index);
                    subMenuTesteConfigurar->menuState = getNextSub(SENSOR_ALTDJ);
                }
                else if(key == CONFIRMAR)
                {
                    index = 0;
                    subMenuTesteConfigurar->menuState = getNextSub(SENSOR_SERIES);
                    subMenuTesteConfigurar->menuSelect = setSelectSub(&subMenuTesteConfigurar->menuState);
                }

                break;

            case SENSOR_SERIES:
                updateUserMsg(0,0,numserieUserMsg,&displayUpdateStatus);
                ptr_numSeriesString = getNumSeriesString();
                insertUserInterface(0,0,ptr_numSeriesString);
                key = getchar();
                while( getchar() != '\n' );
                if(key == INSERIR)
                {
                    setUserNumSeries(&index);
                    subMenuTesteConfigurar->menuState = getNextSub(SENSOR_SERIES);
                }
                else if(key == CONFIRMAR)
                {
                    index = 0;
                    subMenuTesteConfigurar->menuState = getNextSub(SENSOR_INT_SERIES);
                    subMenuTesteConfigurar->menuSelect = setSelectSub(&subMenuTesteConfigurar->menuState);
                }

                break;

            case SENSOR_INT_SERIES:
                updateUserMsg(0,0,interseriesUserMsg,&displayUpdateStatus);
                ptr_intervalSeriesString = getIntervalSeriesString();
                insertUserInterface(0,0,ptr_intervalSeriesString);
                key = getchar();
                while( getchar() != '\n' );
                if(key == INSERIR)
                {
                    setUserIntervalSeries(&index);
                    subMenuTesteConfigurar->menuState = getNextSub(SENSOR_INT_SERIES);
                }
                else if(key == CONFIRMAR)
                {
                    index = 0;
                    subMenuTesteConfigurar->menuState = getNextSub(TAPETE_ON);
                    subMenuTesteConfigurar->menuSelect = setSelectSub(&subMenuTesteConfigurar->menuState);
                }

            break;

            case TAPETE_ON:
                updateUserMsg(0,0,intapeteUserMsg,&displayUpdateStatus);
                key = getchar();
                while( getchar() != '\n' );
                if(key == AVANCAR)
                {
                    subMenuTesteConfigurar->menuState = getNextSub(TAPETE_OFF);
                }
                else if(key == CONFIRMAR)
                {
                    subMenuTesteConfigurar->menuSelect = setSelectSub(&subMenuTesteConfigurar->menuState);
                    ptr_userConfiguration->userSelectTapete = TRUE;
                    subMenuTesteConfigurar->menuState = getNextSub(SAVE_CONFIGS);
                }
                break;

            case TAPETE_OFF:
                updateUserMsg(0,0,outtapeteUserMsg,&displayUpdateStatus);
                key = getchar();
                while( getchar() != '\n' );
                if(key == AVANCAR)
                {
                    subMenuTesteConfigurar->menuState = getNextSub(TAPETE_ON);
                }
                else if(key == CONFIRMAR)
                {
                    subMenuTesteConfigurar->menuSelect = setSelectSub(&subMenuTesteConfigurar->menuState);
                    ptr_userConfiguration->userSelectTapete = FALSE;
                    subMenuTesteConfigurar->menuState = getNextSub(SAVE_CONFIGS);
                }
                break;

            case SAVE_CONFIGS:
                subMenuTesteConfigurar->menuState = getNextSub(CONFIG_SENSOR_1);
                setInsertData(ptr_userConfiguration);
                key = MENU;
                break;
        }
    }
}



//                printf("ptr_userConfiguration->userTime = %ld\n",ptr_userConfiguration->userTime);
//                printf("ptr_userConfiguration->userMass = %d\n",ptr_userConfiguration->userMass);
//                printf("ptr_userConfiguration->userOverMass = %d\n",ptr_userConfiguration->userOverMass);
//                printf("ptr_userConfiguration->userConsultTest = %d\n",ptr_userConfiguration->userConsultTest);
//                printf("ptr_userConfiguration->userAlturaMin = %d\n",ptr_userConfiguration->userAlturaMin);
//                printf("ptr_userConfiguration->userAlturaMax = %d\n",ptr_userConfiguration->userAlturaMax);
//                printf("ptr_userConfiguration->userNumSaltos = %d\n",ptr_userConfiguration->userNumSaltos);
//                printf("ptr_userConfiguration->userIntervalSaltos = %d\n",ptr_userConfiguration->userIntervalSaltos);
//                printf("ptr_userConfiguration->userCMJ = %d\n",ptr_userConfiguration->userCMJ);
//                printf("ptr_userConfiguration->userAlturaDJ = %ld\n",ptr_userConfiguration->userAlturaDJ);
//                printf("ptr_userConfiguration->userNumSeries = %d\n",ptr_userConfiguration->userNumSeries);
//                printf("ptr_userConfiguration->userIntervalSeries = %d\n",ptr_userConfiguration->userIntervalSeries);
//                printf("ptr_userConfiguration->userCommConfig = %d\n",ptr_userConfiguration->userCommConfig);
//                printf("ptr_userConfiguration->userSelectTapete = %d\n",ptr_userConfiguration->userSelectTapete);
//                printf("ptr_userConfiguration->userSelectSensorChannel = %d\n",ptr_userConfiguration->userSelectSensorChannel);
//                printf("endereco = %d\n",ptr_userConfiguration);

