#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "Exportar_component.h"
#include "SubMenu.h"
#include "DisplayMessages.h"
#include "Display_module.h"
#include "Data.h"
#include "DataProcessing.h"

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

//toda maquina de estado deve ter um loop - > LEMBRAR LABVIEW
unsigned char exportStateMachine(struct Menu* subMenu)
{
    struct Menu* subMenuExport = subMenu;
    unsigned char key = 0;
    short index = 2;
    unsigned char indexTest = 0;
    unsigned char testSamples = 0;
    unsigned char selectedUserTest=0;
    unsigned char* ptr_exportTestString;
    unsigned char* ptr_sampleString;
    unsigned char* ptr_vooTimeString;
    unsigned char* ptr_alturaString;
    struct results* ptr_structExportResult;
    unsigned char dataVerify;
    unsigned char cursorPosition[2] = {0,0};
    unsigned char displayUpdateStatus = IDDLE;
    while(key != MENU)
    {
        switch(subMenuExport->menuState)
        {
            case IDDLE:
                subMenuExport->menuState = getNextSub(VERIFICA_COMM);
            break;

            case VERIFICA_COMM:
            	startCOMM(); //verificar se nao preciso deixar uma flag de comm no data.c para acessar o valor dela
            	// e comparar para verificar se a comm já está ligada antes de liga-la novamente.
                updateUserMsg(0,0,waitTransmissionMsg,&displayUpdateStatus);
                subMenuExport->menuState = getNextSub(EXPORTAR_UNITARIO);
                readyUserInterface(&displayUpdateStatus,cursorPosition);
            break;

            case EXPORTAR_UNITARIO:
                updateUserMsg(0,USERMSG1,exportunitUserMsg,&displayUpdateStatus);
                printDataDisplay(0,INSERTMSG,avancarUserMsg);
				printDataDisplay(strlen(avancarUserMsg),INSERTMSG,menuUserMsg);
				printDataDisplay(0,OPTIONMSG,selecionarUserMsg);

                key = getKeyPressed();

                if(key == AVANCAR)
                {
                	resetKeyPressed();
                    readyUserInterface(&displayUpdateStatus,cursorPosition);
                    subMenuExport->menuState = getNextSub(EXPORTAR_TODOS);
                }

                else if(key == CONFIRMAR)
                {
                	resetKeyPressed();
                    readyUserInterface(&displayUpdateStatus,cursorPosition);
                    subMenuExport->menuSelect = setSelectSub(&subMenuExport->menuState);
                    subMenuExport->menuState = getNextSub(NUM_TESTE_EXPORT);
                }
                break;

            case EXPORTAR_TODOS:
                updateUserMsg(0,0,exportallUserMsg,&displayUpdateStatus);
                printDataDisplay(0,INSERTMSG,avancarUserMsg);
				printDataDisplay(strlen(avancarUserMsg),INSERTMSG,menuUserMsg);
				printDataDisplay(0,OPTIONMSG,selecionarUserMsg);
                key = getKeyPressed();

                if(key == AVANCAR)
                {
                	resetKeyPressed();
                    readyUserInterface(&displayUpdateStatus,cursorPosition);
                    subMenuExport->menuState = getNextSub(EXPORTAR_UNITARIO);
                }

                else if(key == CONFIRMAR)
                {
                	resetKeyPressed();
                    readyUserInterface(&displayUpdateStatus,cursorPosition);
                    subMenuExport->menuSelect = setSelectSub(&subMenuExport->menuState);
                    subMenuExport->menuState = getNextSub(PROCESS_TODOS);
                }
                break;


            case NUM_TESTE_EXPORT:
                updateUserMsg(0,USERMSG1,consultTestUserMsg,&displayUpdateStatus);
                ptr_exportTestString = getNumTestString();
                printDataDisplay(0,USERMSG2,ptr_exportTestString);
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
                    subMenuExport->menuState = getNextSub(NUM_TESTE_EXPORT);
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
                    subMenuExport->menuState = getNextSub(PROCESS_UNITARIO);
                    subMenuExport->menuSelect = setSelectSub(&subMenuExport->menuState);
                }

                break;

                case PROCESS_UNITARIO:
                    updateUserMsg(0,0,exportedUserMsg,&displayUpdateStatus);
                    selectedUserTest = stringToInt(ptr_exportTestString);
                    ptr_structExportResult = getUserResultData(selectedUserTest);
                    /*Question: I need to export to spi(sdcard) or to uart(bluetooth) block?
                     *
                     */
                   //ESSE FOR � S� PARA TESTE NO CONSOLE, AO INVES DESSE MONTE DE "PRINT", COLOCAREI FU��O PARA ENVIAR BT
//                    transmissionCOMM();
                    //Acessa os dados referente ao Teste e envia apenas o selecionado por BT
                subMenuExport->menuState = getNextSub(IDDLE);
                key = MENU;
                break;

                case PROCESS_TODOS: //
                    updateUserMsg(0,0,exportedUserMsg,&displayUpdateStatus);

                    subMenuExport->menuState = getNextSub(IDDLE);
  				  readyUserInterface(&displayUpdateStatus,cursorPosition);
                    key = MENU;
                    break;
        }
    }

}
