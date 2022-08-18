#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "INICIAR_Component.h"
#include "SubMenu.h"
#include "time.h"
#include "Display_module.h"
#include "DisplayMessages.h"

//Teste results
struct results{
    unsigned char sample;
    unsigned long int ulReadingTime;
    unsigned int uiVooTime;
    unsigned char ucAltDistance;
};

//
struct dataInsert{
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
    unsigned char key = 0;
    unsigned char index = 0;

    struct tm myTime;
    struct tm* userTimeStruct = &myTime;
    unsigned char userTimeString[9];
    unsigned char procTimeString[9];
//    unsigned char* ptr_userTimeString;
    unsigned char* ptr_massArray;
    unsigned char* ptr_massString;
    unsigned char* ptr_overMassArray;
    unsigned char* ptr_overMassString;


    unsigned char displayUpdateStatus = IDDLE;
    unsigned char cursorPosition[2] = {0,0};

    //Teste results
    unsigned char* ptr_Sample;
    unsigned char* ptr_ulReadingTime;
    unsigned char* ptr_uiVooTime;
    unsigned char* ptr_ucAltDistance;
    struct results result ={0,0,0,0};
    unsigned char i = 0;
    unsigned char idx=0;
    static unsigned char arraySample[9];
    static unsigned long int arrayReadingTime[9];
    static unsigned int arrayVooTime[9];
    static unsigned char arrayAltDistance[9];
    //
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
                    subMenuIniciar->menuInsert.userCommConfig = COMM_OFF;
                    setInsertSub(&subMenuIniciar->menuInsert);
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

                    subMenuIniciar->menuInsert.userCommConfig = COMM_ON;
                    setInsertSub(&subMenuIniciar->menuInsert);
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
                    subMenuIniciar->menuInsert.userTime = stringToLong(procTimeString);
//                    setInsertSub(&subMenuIniciar->menuInsert);
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
                    ptr_massString = setUserMass(&index);
//                    insertUserInterface(0,0,ptr_massString);
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
                    subMenuIniciar->menuInsert.userMass= stringToInt(ptr_massString);
                    printf("subMenuIniciar->menuInsert.userMass = %d\n",subMenuIniciar->menuInsert.userMass);
//                    setInsertSub(&subMenuIniciar->menuInsert);
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
                    ptr_overMassString = setUserOverMass(&index);
//                    subMenuIniciar->menuInsert.userOverMass++;
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
                    subMenuIniciar->menuInsert.userOverMass= stringToInt(ptr_overMassString);
//                    setInsertSub(&subMenuIniciar->menuInsert);
                    subMenuIniciar->menuSelect = setSelectSub(&subMenuIniciar->menuState);
                    subMenuIniciar->menuState = getNextSub(START);
                }
                break;

            case START:
                 updateUserMsg(3,2,startreadUserMsg,&displayUpdateStatus);
                 insertUserInterface(0,0,userTimeString);
                key = getchar();
                while( getchar() != '\n' );
                if(key == CONFIRMAR)
                {
                    //INICIA LEITURA (LIGA ENCODER, PONTE, O QUE FOR //I0_INTERFACE
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
                    result.sample++;
                    result.ucAltDistance+=5;
                    result.uiVooTime +=10;
                    result.ulReadingTime += 100;
                    arraySample[idx] = result.sample;
                    arrayAltDistance[idx] = result.ucAltDistance;
                    arrayVooTime[idx] = result.uiVooTime;
                    arrayReadingTime[idx] = result.ulReadingTime;
                    idx++;
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
                    //PAREI AQUI
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
                if(i<idx)
                {
                printf("RESULTADO %d\n",arraySample[i]);
                printf("Altura = %d\n",arrayAltDistance[i]);
                printf("Tempo de voo = %d\n",arrayVooTime[i]);
                printf("Tempo de leitura = %d\n",arrayReadingTime[i]);
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
                    if(i==idx)
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
                    readyUserInterface(&displayUpdateStatus,cursorPosition);
                    updateUserMsg(3,2,savedUserMsg,&displayUpdateStatus);
                    subMenuIniciar->menuSelect = setSelectSub(&subMenuIniciar->menuState);
                    //display
                    subMenuIniciar->menuState = getNextSub(COMM_OFF);
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
                    result.sample=0;
                    result.ucAltDistance=0;
                    result.uiVooTime =0;
                    result.ulReadingTime = 0;
                    idx = 0;
                    i=0;
                    //
                    subMenuIniciar->menuState = getNextSub(COMM_OFF);
                    key = MENU; // ta errado mas coloquei aqui pra teste
                }
            break;
        }
    }
}
