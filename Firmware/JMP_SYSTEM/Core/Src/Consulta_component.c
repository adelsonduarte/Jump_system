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

unsigned char consultStateMachine(struct Menu* subMenu)
{
    struct Menu* subMenuTesteConsultar = subMenu;
    unsigned char* ptr_consultTestString;
    unsigned char* ptr_sampleString;
    unsigned char* ptr_vooTimeString;
    unsigned char* ptr_alturaString;
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
                updateUserMsg(0,0,consultTestUserMsg,&displayUpdateStatus);
                ptr_consultTestString = getNumTestString();
                printDataDisplay(0,1,ptr_consultTestString);
                updateDataDisplay(index,1);
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
            	updateUserMsg(0,0,consultTestUserMsg,&displayUpdateStatus);
                selectedUserTest = stringToInt(ptr_consultTestString);
//                ptr_structConsultResult = load_data(selectedUserTest); //APENAS PARA APLICAÇÃO COM SD
                ptr_structConsultResult = getUserResultData(selectedUserTest);
//                if(testSamples<(ptr_structConsultResult->resultTestAcquiredSamples))
//                {
//                	resetKeyPressed();
//                    updateUserMsg(0,0,"Amostra",&displayUpdateStatus);
//                    readyUserInterface(&displayUpdateStatus,cursorPosition);
//                    ptr_sampleString = param_1_toString(&ptr_structConsultResult->Measurement[testSamples].sampleNum);
//                    updateUserMsg(0,1,ptr_sampleString,&displayUpdateStatus);
//                    readyUserInterface(&displayUpdateStatus,cursorPosition);
//
//                    updateUserMsg(0,0,"Tempo de Voo",&displayUpdateStatus);
//                    readyUserInterface(&displayUpdateStatus,cursorPosition);
//                    ptr_vooTimeString = param_2_toString(&ptr_structConsultResult->Measurement[testSamples].uiVooTime);
//                    updateUserMsg(0,1,ptr_vooTimeString,&displayUpdateStatus);
//                    readyUserInterface(&displayUpdateStatus,cursorPosition);
//
//                    updateUserMsg(0,0,"Altura do salto",&displayUpdateStatus);
//                    readyUserInterface(&displayUpdateStatus,cursorPosition);
//                    ptr_alturaString = param_3_toString(&ptr_structConsultResult->Measurement[testSamples].uiSoloTime);
//                    updateUserMsg(0,1,ptr_alturaString,&displayUpdateStatus);
//                    readyUserInterface(&displayUpdateStatus,cursorPosition);
//                }
//                else  printDataDisplay(0,0,"VAZIO");

                key = getKeyPressed();

                if(key == AVANCAR)
                {
                	resetKeyPressed();
                    if(testSamples<(ptr_structConsultResult->resultTestAcquiredSamples))
                    {
                        updateUserMsg(0,0,"Amostra",&displayUpdateStatus);
                        readyUserInterface(&displayUpdateStatus,cursorPosition);
                        ptr_sampleString = param_1_toString(&ptr_structConsultResult->Measurement[testSamples].sampleNum);
                        updateUserMsg(9,0,ptr_sampleString,&displayUpdateStatus);
                        readyUserInterface(&displayUpdateStatus,cursorPosition);

                        updateUserMsg(0,1,"Tempo de Voo",&displayUpdateStatus);
                        readyUserInterface(&displayUpdateStatus,cursorPosition);
                        ptr_vooTimeString = param_2_toString(&ptr_structConsultResult->Measurement[testSamples].uiVooTime);
                        updateUserMsg(9,1,ptr_vooTimeString,&displayUpdateStatus);
                        readyUserInterface(&displayUpdateStatus,cursorPosition);

                        updateUserMsg(0,2,"Altura do salto",&displayUpdateStatus);
                        readyUserInterface(&displayUpdateStatus,cursorPosition);
                        ptr_alturaString = param_3_toString(&ptr_structConsultResult->Measurement[testSamples].uiSoloTime);
                        updateUserMsg(9,2,ptr_alturaString,&displayUpdateStatus);
                        readyUserInterface(&displayUpdateStatus,cursorPosition);
                    }
                    else  printDataDisplay(0,0,"VAZIO");
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
                updateUserMsg(0,0,consultExportUserMsg,&displayUpdateStatus);
                key = getKeyPressed();

                if(key == PARAR)
                {
                	resetKeyPressed();
                	readyUserInterface(&displayUpdateStatus,cursorPosition);
                    key = MENU; // ta errado mas coloquei aqui pra teste
                    subMenuTesteConsultar->menuState = getNextSub(CONSULTA_TESTE);
                }
                else if(key == CONFIRMAR)
                {
                    //display
                	resetKeyPressed();
                    updateUserMsg(0,0,exportedUserMsg,&displayUpdateStatus);
                    subMenuTesteConsultar->menuSelect = setSelectSub(&subMenuTesteConsultar->menuState);
                    subMenuTesteConsultar->menuState = getNextSub(CONSULTA_TESTE);
                    readyUserInterface(&displayUpdateStatus,cursorPosition);
                    key = MENU; // ta errado mas coloquei aqui pra teste
                }
                break;
        }
    }
}
