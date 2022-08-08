#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "INICIAR_Component.h"
#include "SubMenu.h"

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
    unsigned char key = 0;
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
        switch(subMenuIniciar->menuState)
        {
            case IDDLE:
                subMenuIniciar->menuState = getNextSub(COMM_OFF);
            break;
            case COMM_OFF:
                printf("COMM_OFF\n");
                key = getchar();
                while( getchar() != '\n' );
                if(key == AVANCAR)
                {
                    subMenuIniciar->menuState = getNextSub(COMM_ON);
                }
                else if(key == CONFIRMAR)
                {
                    //funcao para desabilitar comunicacao
                    subMenuIniciar->menuInsert.userCommConfig = COMM_OFF;
                    setInsertSub(&subMenuIniciar->menuInsert);
                    subMenuIniciar->menuSelect = setSelectSub(&subMenuIniciar->menuState);
                    subMenuIniciar->menuState = getNextSub(TEMPO_READ);
                }
            break;

            case COMM_ON:
                printf("COMM_ON\n");
                key = getchar();
                while( getchar() != '\n' );
                if(key == AVANCAR) subMenuIniciar->menuState = getNextSub(COMM_OFF);
                else if(key == CONFIRMAR)
                {

                    //funcao para habilitar comunicacao
                    // display PAREANDO e um loop pra contar tempo
                    subMenuIniciar->menuInsert.userCommConfig = COMM_ON;
                    setInsertSub(&subMenuIniciar->menuInsert);
                    subMenuIniciar->menuSelect = setSelectSub(&subMenuIniciar->menuState);
                    subMenuIniciar->menuState = getNextSub(TEMPO_READ);
                }
                break;

            case TEMPO_READ:
                printf("TEMPO LEITURA: %d\n",subMenuIniciar->menuInsert.userTime);
                key = getchar();
                while( getchar() != '\n' );
                if(key == INSERIR)
                {
                    subMenuIniciar->menuInsert.userTime++;
                    subMenuIniciar->menuState = getNextSub(TEMPO_READ);
                }
                else if(key == CONFIRMAR)
                {
                    printf("TEMPO DE LEITURA = %d\n",subMenuIniciar->menuInsert.userTime);
                    setInsertSub(&subMenuIniciar->menuInsert);
                    //Configurar TIMER
                    subMenuIniciar->menuState = getNextSub(MASSA_READ);
                    subMenuIniciar->menuSelect = setSelectSub(&subMenuIniciar->menuState);
                }
                break;

            case MASSA_READ:
                 printf("MASSA CORPORAL: %d\n",subMenuIniciar->menuInsert.userMass);
                key = getchar();
                while( getchar() != '\n' );
                if(key == INSERIR)
                {
                    subMenuIniciar->menuInsert.userMass++;
                    subMenuIniciar->menuState = getNextSub(MASSA_READ);
                }
                else if(key == CONFIRMAR)
                {
                    printf("MASSA CORPORAL = %d\n",subMenuIniciar->menuInsert.userMass);
                    setInsertSub(&subMenuIniciar->menuInsert);
                    subMenuIniciar->menuState = getNextSub(SOBREC_READ);
                    subMenuIniciar->menuSelect = setSelectSub(&subMenuIniciar->menuState);
                }
                break;

            case SOBREC_READ:
                printf("SOBRECARGA: %d\n",subMenuIniciar->menuInsert.userOverMass);
                key = getchar();
                while( getchar() != '\n' );
                if(key == INSERIR)
                {
                    subMenuIniciar->menuInsert.userOverMass++;
                    subMenuIniciar->menuState = getNextSub(SOBREC_READ);
                }
                else if(key == CONFIRMAR)
                {
                    printf("SOBRECARGA = %d\n",subMenuIniciar->menuInsert.userOverMass);
                    setInsertSub(&subMenuIniciar->menuInsert);
                    subMenuIniciar->menuSelect = setSelectSub(&subMenuIniciar->menuState);
                    subMenuIniciar->menuState = getNextSub(START);
                }
                break;

            case START:
                 printf("INICIAR LEITURA\n");
                 printf("T = %d\n",subMenuIniciar->menuInsert.userTime);
                key = getchar();
                while( getchar() != '\n' );
                if(key == CONFIRMAR)
                {
                    //INICIA LEITURA (LIGA ENCODER, PONTE, O QUE FOR
                    subMenuIniciar->menuState = getNextSub(READING);
                    subMenuIniciar->menuSelect = setSelectSub(&subMenuIniciar->menuState);
                }
            break;

            case READING:
                 printf("READING->->-> LOOP DE LEITURA DEVE FICAR AQUI\n");
                 //DISPLAY
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
                printf("CONFIRMA PARADA?\n");
                key = getchar();
                while( getchar() != '\n' );
                if(key == CONFIRMAR)
                {
                    //PARA LEITURA, DESLIGA TIMER, ENCODER, O QUE FOR
                    subMenuIniciar->menuState = getNextSub(DISP_RESULTS);
                    subMenuIniciar->menuSelect = setSelectSub(&subMenuIniciar->menuState);


                }
                break;

            case DISP_RESULTS:
                printf("VER RESULTADOS DOS ESTÁGIOS\n");
                subMenuIniciar->menuDisplay = getDisplaySub(&subMenuIniciar->menuDisplay);
                key = getchar();
                while( getchar() != '\n' );
                if(key == PARAR)
                {
                    subMenuIniciar->menuState = getNextSub(SAVE_DATA);
                }
                else if(key == CONFIRMAR)
                {
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
                else if(key == PARAR) subMenuIniciar->menuState = getNextSub(SAVE_DATA);
            break;

            case SAVE_DATA:
                printf("SALVAR\n");
                key = getchar();
                while( getchar() != '\n' );
                if(key == AVANCAR)
                {
                    subMenuIniciar->menuState = getNextSub(CANCEL_SAVE);
                }
                else if(key == CONFIRMAR)
                {
                    subMenuIniciar->menuSelect = setSelectSub(&subMenuIniciar->menuState);
                    //display
                    printf("Salvando->->->\n");
                    subMenuIniciar->menuState = getNextSub(COMM_OFF);
                    key = MENU; // ta errado mas coloquei aqui pra teste
                }
            break;

            case CANCEL_SAVE:
                printf("CANCEL_SAVE\n");
                key = getchar();
                while( getchar() != '\n' );
                if(key == AVANCAR)
                {
                    subMenuIniciar->menuState = getNextSub(SAVE_DATA);
                }
                else if(key == CONFIRMAR)
                {
                    subMenuIniciar->menuSelect = setSelectSub(&subMenuIniciar->menuState);
                    //display
                    printf("Cancelando->->->\n");
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
