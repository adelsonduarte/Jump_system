#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "INICIAR_Component.h"
#include "SubMenu.h"
#include "Display_module.h"
#include "DisplayMessages.h"
#include "IO_interface.h"

//Teste results
struct results{
    unsigned char sample;
    unsigned long int ulReadingTime;
    unsigned int uiVooTime;
    unsigned char ucAltDistance;
};
//
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

unsigned char initStateMachine(struct Menu* subMenu)
{
    struct Menu* subMenuIniciar = subMenu;
    unsigned char key = IDDLE;
    unsigned char displayUpdateStatus = IDDLE;
    unsigned char cursorPosition[1] = {0,0};
    unsigned char arrayTime[8] = {0,0,":",0,0,":",0,0};
    //Teste results
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
    	HAL_Delay(100);
        switch(subMenuIniciar->menuState)
        {
            case IDDLE:
                subMenuIniciar->menuState = getNextSub(COMM_OFF);
            break;
            case COMM_OFF:
            	key = getKeyPressed();
            	updateUserMsg(3,2,noTransmissionMsg,&displayUpdateStatus);
                if(key == AVANCAR)
                {
                	IOStatus(&displayUpdateStatus,&cursorPosition);
//                	if(key == IDDLE) HAL_GPIO_TogglePin(GPIOC, LED_Pin);
                    subMenuIniciar->menuState = getNextSub(COMM_ON);
                }
                else if(key == CONFIRMAR)
                {
                    //funcao para desabilitar comunicacao
                	IOStatus(&displayUpdateStatus,&cursorPosition);
                    subMenuIniciar->menuInsert.userCommConfig = COMM_OFF;
                    setInsertSub(&subMenuIniciar->menuInsert);
                    subMenuIniciar->menuSelect = setSelectSub(&subMenuIniciar->menuState);
                    subMenuIniciar->menuState = getNextSub(TEMPO_READ);
                }
            break;

            case COMM_ON:
            	key = getKeyPressed();
				updateUserMsg(3,2,yesTransmissionMsg,&displayUpdateStatus);
                if(key == AVANCAR)
				{
                	IOStatus(&displayUpdateStatus,&cursorPosition);
					subMenuIniciar->menuState = getNextSub(COMM_OFF);
				}
                else if(key == CONFIRMAR)
                {
                	IOStatus(&displayUpdateStatus,&cursorPosition);
                    //funcao para habilitar comunicacao
                	updateUserMsg(3,2,waitTransmissionMsg,&displayUpdateStatus);
                    subMenuIniciar->menuInsert.userCommConfig = COMM_ON;
                    setInsertSub(&subMenuIniciar->menuInsert);
                    subMenuIniciar->menuSelect = setSelectSub(&subMenuIniciar->menuState);
                    subMenuIniciar->menuState = getNextSub(TEMPO_READ);
                }
                break;

            case TEMPO_READ:
            	key = getKeyPressed();
//            	if(key == INSERIR) HAL_GPIO_TogglePin(GPIOC, LED_Pin);
				updateUserMsg(0,1,timeUserMsg,&displayUpdateStatus);
				insertUserInterface(cursorPosition[0],2, &arrayTime[cursorPosition[0]]);
                if(key == INSERIR)
                {
                	IOStatus(&displayUpdateStatus,&cursorPosition);
//                    subMenuIniciar->menuInsert.userTime++;
                	arrayTime[cursorPosition[0]]++;
                    subMenuIniciar->menuState = getNextSub(TEMPO_READ);
                }
                else if(key == CONFIRMAR)
                {
                	IOStatus(&displayUpdateStatus,&cursorPosition);
                    setInsertSub(&subMenuIniciar->menuInsert);
                    //Configurar TIMER
                    subMenuIniciar->menuState = getNextSub(MASSA_READ);
                    subMenuIniciar->menuSelect = setSelectSub(&subMenuIniciar->menuState);
                }
                else if(key == AVANCAR)
				{
					IOStatus(&displayUpdateStatus,&cursorPosition);
					cursorPosition[0] = cursorChangeInterface(cursorPosition[0],0);
					subMenuIniciar->menuState = getNextSub(TEMPO_READ);
					subMenuIniciar->menuSelect = setSelectSub(&subMenuIniciar->menuState);
				}
                break;

            case MASSA_READ:
            	key = getKeyPressed();
				updateUserMsg(3,2,massUserMsg,&displayUpdateStatus);
                if(key == INSERIR)
                {
                	IOStatus(&displayUpdateStatus,&cursorPosition);
                    subMenuIniciar->menuInsert.userMass++;
                    subMenuIniciar->menuState = getNextSub(MASSA_READ);
                }
                else if(key == CONFIRMAR)
                {
                	IOStatus(&displayUpdateStatus,&cursorPosition);
                    setInsertSub(&subMenuIniciar->menuInsert);
                    subMenuIniciar->menuState = getNextSub(SOBREC_READ);
                    subMenuIniciar->menuSelect = setSelectSub(&subMenuIniciar->menuState);
                }
                break;

            case SOBREC_READ:
            	key = getKeyPressed();
				updateUserMsg(3,2,overmassUserMsg,&displayUpdateStatus);
                if(key == INSERIR)
                {
                	IOStatus(&displayUpdateStatus,&cursorPosition);
                    subMenuIniciar->menuInsert.userOverMass++;
                    subMenuIniciar->menuState = getNextSub(SOBREC_READ);
                }
                else if(key == CONFIRMAR)
                {
                	IOStatus(&displayUpdateStatus,&cursorPosition);
                    setInsertSub(&subMenuIniciar->menuInsert);
                    subMenuIniciar->menuSelect = setSelectSub(&subMenuIniciar->menuState);
                    subMenuIniciar->menuState = getNextSub(START);
                }
                break;

            case START:
            	key = getKeyPressed();
				updateUserMsg(3,2,startreadUserMsg,&displayUpdateStatus);
                if(key == CONFIRMAR)
                {
                	IOStatus(&displayUpdateStatus,&cursorPosition);
                    //INICIA LEITURA (LIGA ENCODER, PONTE, O QUE FOR
                    subMenuIniciar->menuState = getNextSub(READING);
                    subMenuIniciar->menuSelect = setSelectSub(&subMenuIniciar->menuState);
                }
            break;

            case READING:
            	key = getKeyPressed();
            	//APRESENTAR OS DADOS LIDOS AQUI
                 //DISPLAY
            	updateUserMsg(3,2,testMsg,&displayUpdateStatus);
                if(key == PARAR)
                {
                	IOStatus(&displayUpdateStatus,&cursorPosition);
                	subMenuIniciar->menuState = getNextSub(STOP);
                }

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
            	key = getKeyPressed();
				updateUserMsg(3,2,stopreadUserMsg,&displayUpdateStatus);
                if(key == CONFIRMAR)
                {
                	IOStatus(&displayUpdateStatus,&cursorPosition);
                    //PARA LEITURA, DESLIGA TIMER, ENCODER, O QUE FOR
                    subMenuIniciar->menuState = getNextSub(DISP_RESULTS);
                    subMenuIniciar->menuSelect = setSelectSub(&subMenuIniciar->menuState);
                }
                break;

            case DISP_RESULTS:
            	key = getKeyPressed();
				updateUserMsg(3,2,resultsUserMsg,&displayUpdateStatus);

                if(key == PARAR)
                {
                	IOStatus(&displayUpdateStatus,&cursorPosition);
                    subMenuIniciar->menuState = getNextSub(SAVE_DATA);
                }
                else if(key == CONFIRMAR)
                {
                	IOStatus(&displayUpdateStatus,&cursorPosition);
                    subMenuIniciar->menuSelect = setSelectSub(&subMenuIniciar->menuState);
                    subMenuIniciar->menuState = getNextSub(RESULTS);
                }
            break;

            case RESULTS:
				updateUserMsg(3,2,testMsg,&displayUpdateStatus);
                //Teste results
                if(i<idx)
                {
                  printf("RESULTADO %d\n",arraySample[i]);
                printf("Altura = %d\n",arrayAltDistance[i]);
                printf("Tempo de voo = %d\n",arrayVooTime[i]);
                printf("Tempo de leitura = %d\n",arrayReadingTime[i]);
                }
                //

                subMenuIniciar->menuDisplay = getDisplaySub(&subMenuIniciar->menuDisplay);
            	key = getKeyPressed();
                if(key == AVANCAR)
                {
                	IOStatus(&displayUpdateStatus,&cursorPosition);
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
                	IOStatus(&displayUpdateStatus,&cursorPosition);
					subMenuIniciar->menuState = getNextSub(SAVE_DATA);
				}
            break;

            case SAVE_DATA:
            	key = getKeyPressed();
				updateUserMsg(3,2,saveUserMsg,&displayUpdateStatus);
                if(key == AVANCAR)
                {
                	IOStatus(&displayUpdateStatus,&cursorPosition);
                    subMenuIniciar->menuState = getNextSub(CANCEL_SAVE);
                }
                else if(key == CONFIRMAR)
                {
                	IOStatus(&displayUpdateStatus,&cursorPosition);
                    subMenuIniciar->menuSelect = setSelectSub(&subMenuIniciar->menuState);
                    updateUserMsg(3,2,savedUserMsg,&displayUpdateStatus);
                    subMenuIniciar->menuState = getNextSub(COMM_OFF);
                    key = MENU; // ta errado mas coloquei aqui pra teste
                }
            break;

            case CANCEL_SAVE:
            	key = getKeyPressed();
				updateUserMsg(3,2,cancelUserMsg,&displayUpdateStatus);
                if(key == AVANCAR)
                {
                	IOStatus(&displayUpdateStatus,&cursorPosition);
                    subMenuIniciar->menuState = getNextSub(SAVE_DATA);
                }
                else if(key == CONFIRMAR)
                {
                	IOStatus(&displayUpdateStatus,&cursorPosition);
                    subMenuIniciar->menuSelect = setSelectSub(&subMenuIniciar->menuState);
                    updateUserMsg(3,2,canceledUserMsg,&displayUpdateStatus);
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
