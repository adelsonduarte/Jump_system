#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "Consulta_component.h"
#include "SubMenu.h"
#include "DisplayMessages.h"
#include "Display_module.h"
#include "DataProcessing.h"
#include "Data.h"

struct samples{
    unsigned char sampleNum;
    unsigned int uiVooTime;
    unsigned int uiSoloTime;
};

struct results{
    unsigned char resultTestNum;
    unsigned char resultTestAcquiredSamples;
    unsigned char thereAreData;
    unsigned char timeout;
    struct samples Measurement[MEASUREMENT_SIZE];
};

struct dataInsert{
    unsigned char userTime;
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
struct Menu{
        unsigned char menuNext;
        unsigned char menuSelect;
        unsigned char menuDisplay;
        unsigned char menuState;
        struct dataInsert menuInsert;
    };

unsigned char consultStateMachine(struct Menu* subMenu)
{
    struct Menu* subMenuTesteConsultar = subMenu;
    unsigned char* ptr_consultTestString;
    unsigned char* ptr_sampleString;
    unsigned char* ptr_vooTimeString;
    unsigned char* ptr_alturaString;
    unsigned char* ptr_potString;
    struct results* ptr_structConsultResult;
    unsigned char selectedUserTest = 0;
    unsigned char testSamples=0;
    unsigned char cursorPosition[2] = {0,0};
    short index = 2; //(000 MENU)
    unsigned char key = 0;
    static unsigned char results = 0;
    unsigned char displayUpdateStatus = IDDLE;

    while(key != MENU)
    {
        switch(subMenuTesteConsultar->menuState)
        {
            case IDDLE:
                subMenuTesteConsultar->menuState = getNextSub(CONSULTA_TESTE);
            break;

            case CONSULTA_TESTE:
                updateUserMsg(0,USERMSG1,consultTestUserMsg,&displayUpdateStatus);
                ptr_consultTestString = getNumTestString();
                printDataDisplay(0,USERMSG2,ptr_consultTestString);
                updateDataDisplay(index,USERMSG2);

                printDataDisplay(0,INSERTMSG,avancarUserMsg);
				printDataDisplay(strlen(avancarUserMsg),INSERTMSG,menuUserMsg);
				printDataDisplay(0,OPTIONMSG,selecionarUserMsg);
				printDataDisplay(strlen(selecionarUserMsg),OPTIONMSG,inserirUserMsg);
                key = getKeyPressed();
                if(key == INSERIR)
                {
                	resetKeyPressed();
                    setUserNumTest(&index);
                    subMenuTesteConsultar->menuState = getNextSub(CONSULTA_TESTE);
                }
                else if(key == AVANCAR)
                {
                	resetKeyPressed();
                    indexChange(&index,2);
                }
                else if(key == CONFIRMAR)
                {
                	resetKeyPressed();
                    readyUserInterface(&displayUpdateStatus,cursorPosition);
                    subMenuTesteConsultar->menuState = getNextSub(RESULT_TESTE);
                    subMenuTesteConsultar->menuSelect = setSelectSub(&subMenuTesteConsultar->menuState);
                }
            break;

            case RESULT_TESTE:
                selectedUserTest = stringToInt(ptr_consultTestString);
                printDataDisplay(0,OPTIONMSG,avancarUserMsg);
                printDataDisplay(strlen(avancarUserMsg),OPTIONMSG,pararUserMsg);
//                ptr_structConsultResult = load_data(selectedUserTest); //APENAS PARA APLICAÇÃO COM SD
                ptr_structConsultResult = getUserResultData(selectedUserTest);
                if(testSamples<(ptr_structConsultResult->resultTestAcquiredSamples))
                {
                	printDataDisplay(0,USERMSG1,amostraUserMsg);
					ptr_sampleString = param_1_toString(&ptr_structConsultResult->Measurement[testSamples].sampleNum);
					printDataDisplay(strlen(amostraUserMsg),USERMSG1 , ptr_sampleString);

					printDataDisplay(0,USERMSG2,tempoVooUserMsg);
					ptr_vooTimeString = param_2_toString(&ptr_structConsultResult->Measurement[testSamples].uiVooTime);
					printDataDisplay(strlen(tempoVooUserMsg),USERMSG2 ,ptr_vooTimeString);


					printDataDisplay(0,INSERTMSG,tempoSoloUserMsg);
					ptr_alturaString = param_2_toString(&ptr_structConsultResult->Measurement[testSamples].uiSoloTime);
					printDataDisplay(strlen(tempoSoloUserMsg),INSERTMSG , ptr_alturaString);

//                  ptr_potString; = param_3_toString(&ptr_structExportResult->Measurement[testSamples].uiSoloTime);
//					printDataDisplay(0, INSERTMSG, ptr_potString);

                }
                else  printDataDisplay(0,0,"VAZIO");

                key = getKeyPressed();

                if(key == AVANCAR)
                {
                	resetKeyPressed();
                	readyUserInterface(&displayUpdateStatus,cursorPosition);
                    testSamples++;
                    if(testSamples == ptr_structConsultResult->resultTestAcquiredSamples) testSamples = 0;
                    subMenuTesteConsultar->menuState = getNextSub(RESULT_TESTE);
                }
                else if(key == PARAR)
                {
                	resetKeyPressed();
                    readyUserInterface(&displayUpdateStatus,cursorPosition);
                    subMenuTesteConsultar->menuState = getNextSub(EXPORTAR);
                }
                break;

            case EXPORTAR:
                updateUserMsg(0,USERMSG1,consultExportUserMsg,&displayUpdateStatus);
                printDataDisplay(0,INSERTMSG,selecionarUserMsg);
                printDataDisplay(0,OPTIONMSG,pararUserMsg);
                key = getKeyPressed();

                if(key == PARAR)
                {
                	resetKeyPressed();
                	readyUserInterface(&displayUpdateStatus,cursorPosition);
                    key = MENU;
                    subMenuTesteConsultar->menuState = getNextSub(CONSULTA_TESTE);
                }
                else if(key == CONFIRMAR)
                {
                    //display
                	resetKeyPressed();
                    updateUserMsg(0,0,exportedUserMsg,&displayUpdateStatus);
                    subMenuTesteConsultar->menuSelect = setSelectSub(&subMenuTesteConsultar->menuState);
                    subMenuTesteConsultar->menuState = getNextSub(CONSULTA_TESTE);
                    key = MENU;
                }
                break;
        }
    }
}
