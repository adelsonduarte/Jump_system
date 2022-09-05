#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "Exportar_component.h"
#include "SubMenu.h"
#include "DisplayMessages.h"
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
    struct samples Measurement[MEASUREMENT_SIZE];
};
struct dataInsert{
    unsigned char userTime;
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
unsigned char exportStateMachine(struct Menu* subMenu)
{
    struct Menu* subMenuExport = subMenu;
    unsigned char key = 0;
    unsigned char index = 0;
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
                //funcao para habilitar comunicacao
                updateUserMsg(0,0,waitTransmissionMsg,&displayUpdateStatus);
                subMenuExport->menuState = getNextSub(EXPORTAR_UNITARIO);
                readyUserInterface(&displayUpdateStatus,cursorPosition);
            break;

            case EXPORTAR_UNITARIO:
                updateUserMsg(0,0,exportunitUserMsg,&displayUpdateStatus);
                key = getchar();
                while( getchar() != '\n' );
                if(key == AVANCAR)
                {
                    readyUserInterface(&displayUpdateStatus,cursorPosition);
                    subMenuExport->menuState = getNextSub(EXPORTAR_TODOS);
                }

                else if(key == CONFIRMAR)
                {
                    readyUserInterface(&displayUpdateStatus,cursorPosition);
                    subMenuExport->menuSelect = setSelectSub(&subMenuExport->menuState);
                    subMenuExport->menuState = getNextSub(NUM_TESTE_EXPORT);
                }
                break;

            case EXPORTAR_TODOS:
                updateUserMsg(0,0,exportallUserMsg,&displayUpdateStatus);
                key = getchar();
                while( getchar() != '\n' );
                if(key == AVANCAR)
                {
                    readyUserInterface(&displayUpdateStatus,cursorPosition);
                    subMenuExport->menuState = getNextSub(EXPORTAR_UNITARIO);
                }

                else if(key == CONFIRMAR)
                {
                    readyUserInterface(&displayUpdateStatus,cursorPosition);
                    subMenuExport->menuSelect = setSelectSub(&subMenuExport->menuState);
                    subMenuExport->menuState = getNextSub(PROCESS_TODOS);
                }
                break;


            case NUM_TESTE_EXPORT:
                updateUserMsg(0,0,consultTestUserMsg,&displayUpdateStatus);
                ptr_exportTestString = getNumTestString();
                insertUserInterface(0,0,ptr_exportTestString);
                key = getchar();
                while( getchar() != '\n' );
                if(key == INSERIR)
                {
                    setUserNumTest(&index);
                    subMenuExport->menuState = getNextSub(NUM_TESTE_EXPORT);
                }
                else if(key == AVANCAR)
                {
                    indexChange(&index,3);
                }
                else if(key == CONFIRMAR)
                {
                    readyUserInterface(&displayUpdateStatus,cursorPosition);
                    subMenuExport->menuState = getNextSub(PROCESS_UNITARIO);
                    subMenuExport->menuSelect = setSelectSub(&subMenuExport->menuState);
                }

                break;

                case PROCESS_UNITARIO:
                    updateUserMsg(0,0,exportedUserMsg,&displayUpdateStatus);
                    selectedUserTest = stringToInt(ptr_exportTestString);
                    ptr_structExportResult = getUserResultData(selectedUserTest);

                   //ESSE FOR É SÓ PARA TESTE NO CONSOLE, AO INVES DESSE MONTE DE "PRINT", COLOCAREI FUÇÃO PARA ENVIAR BT

                    for(testSamples=0;testSamples<(ptr_structExportResult->resultTestAcquiredSamples);testSamples++)
                    {
                        ptr_structExportResult = getUserResultData(selectedUserTest);
                        readyUserInterface(&displayUpdateStatus,cursorPosition);
                        updateUserMsg(0,0,"Amostra",&displayUpdateStatus);
                        readyUserInterface(&displayUpdateStatus,cursorPosition);
                        ptr_sampleString = param_1_toString(&ptr_structExportResult->Measurement[testSamples].sampleNum);
                        updateUserMsg(0,0,ptr_sampleString,&displayUpdateStatus);
                        readyUserInterface(&displayUpdateStatus,cursorPosition);

                        updateUserMsg(0,0,"Tempo de Voo",&displayUpdateStatus);
                        readyUserInterface(&displayUpdateStatus,cursorPosition);
                        ptr_vooTimeString = param_2_toString(&ptr_structExportResult->Measurement[testSamples].uiVooTime);
                        updateUserMsg(0,0,ptr_vooTimeString,&displayUpdateStatus);
                        readyUserInterface(&displayUpdateStatus,cursorPosition);

                        updateUserMsg(0,0,"Altura do salto",&displayUpdateStatus);
                        readyUserInterface(&displayUpdateStatus,cursorPosition);
                        ptr_alturaString = param_3_toString(&ptr_structExportResult->Measurement[testSamples].ucAltDistance);
                        updateUserMsg(0,0,ptr_alturaString,&displayUpdateStatus);
                        readyUserInterface(&displayUpdateStatus,cursorPosition);
                    }
                    //Acessa os dados referente ao Teste e envia apenas o selecionado por BT
                subMenuExport->menuState = getNextSub(IDDLE);
                key = MENU;
                break;

                case PROCESS_TODOS: //PAREI AQUI
                    updateUserMsg(0,0,exportedUserMsg,&displayUpdateStatus);
                    for(unsigned char i = 0; i<(TEST_SIZE);i++)
                    {
                       dataVerify =  getThereAreData(i);
                       if(dataVerify == TRUE)
                       {
//                           structToSend(i);
                            printf("Teste %d existe\n",i);
                       }
                       else printf("Teste %d nao existe\n",i);

                    }
                    subMenuExport->menuState = getNextSub(IDDLE);
                    key = MENU;
                    break;
        }
    }
}
