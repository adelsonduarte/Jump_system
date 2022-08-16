#include <stdio.h>
#include <stdlib.h>
#include "menu_module.h"
#include "main.h"
#include "INICIAR_Component.h"
#include "Consulta_component.h"
#include "Display_module.h"
#include "DisplayMessages.h"


/*Cartão de memória -> OK SD_module.c TESTAR
transmissão/recepção bluetooth -> OK DMA_exemplo TESTAR
Relé -> Rele_module.c TESTAR
Display 16x4; -> LiquidCrystal.c TESTAR*/

//Variaveis global, interrupcoes
unsigned char botaoAvancar;
unsigned char botaoConfirmar;
unsigned char botaoParar;
unsigned char botaoMenu;
unsigned char botaoInserir;


void main(void)
{
    unsigned char key = 0;

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

};
    struct Menu{
        unsigned char menuNext;
        unsigned char menuSelect;
        unsigned char menuDisplay;
        unsigned char menuState;
        struct dataInsert menuInsert;
    };

    unsigned char displayUpdateStatus = IDDLE;
    unsigned char cursorPosition[2] = {0,0};
    struct Menu menuTesteMain = {IDDLE,IDDLE,IDDLE,IDDLE};
    struct Menu menuTesteSub = {IDDLE,IDDLE,IDDLE,IDDLE};
    unsigned char* mainMenuArray;
    unsigned char* subMenuArray;

    startUserInterface(appNameMsg,companyNameMsg,appVersionMsg);
    while(1)
    {
        switch(menuTesteMain.menuState)
        {
            case IDDLE:
                key = getchar();
                while( getchar() != '\n' );
                if(key == AVANCAR)
                {
                    readyUserInterface(&displayUpdateStatus,cursorPosition);
                    menuTesteMain.menuState = getNextMain(START_TEST);
                }
            break;

            case START_TEST:
                updateUserMsg(0,0,startUserMsg,&displayUpdateStatus);
                key = getchar();
                while( getchar() != '\n' );
                if(key == AVANCAR)
                {
                    readyUserInterface(&displayUpdateStatus,cursorPosition);
                    menuTesteMain.menuState = getNextMain(CONSULT_DATA);
                }
                else if(key == CONFIRMAR)
                {
                    readyUserInterface(&displayUpdateStatus,cursorPosition);
                    menuTesteMain.menuState = setSelectMain(&menuTesteMain.menuState);
                    menuTesteMain.menuSelect = menuTesteMain.menuState;
                    initStateMachine(&menuTesteSub);
                    menuTesteSub.menuState = IDDLE;
                    menuTesteSub.menuSelect = IDDLE;
                }
            break;

            case CONSULT_DATA:
                updateUserMsg(0,0,consultUserMsg,&displayUpdateStatus);
                key = getchar();
                while( getchar() != '\n' );
                if(key == AVANCAR)
                {
                    readyUserInterface(&displayUpdateStatus,cursorPosition);
                    menuTesteMain.menuState = getNextMain(CONFIG_SENSOR);
                }

                else if(key == CONFIRMAR)
                {
                    readyUserInterface(&displayUpdateStatus,cursorPosition);
                   menuTesteMain.menuState = setSelectMain(&menuTesteMain.menuState);
                   consultStateMachine(&menuTesteSub);
                   menuTesteMain.menuState = getNextMain(START_TEST);
                   menuTesteSub.menuState = IDDLE;
                   menuTesteSub.menuSelect = IDDLE;
                }
            break;

            case CONFIG_SENSOR:
                updateUserMsg(0,0,configUserMsg,&displayUpdateStatus);
                key = getchar();
                while( getchar() != '\n' );
                if(key == AVANCAR)
                {
                    readyUserInterface(&displayUpdateStatus,cursorPosition);
                    menuTesteMain.menuState = getNextMain(EXPORT_DATA);
                }
                else if(key == CONFIRMAR)
                {
                    readyUserInterface(&displayUpdateStatus,cursorPosition);
                    menuTesteMain.menuState = setSelectMain(&menuTesteMain.menuState);
                    configStateMachine(&menuTesteSub);
                    menuTesteSub.menuState = IDDLE;
                    menuTesteSub.menuSelect = IDDLE;
                    menuTesteMain.menuState = getNextMain(START_TEST);
                }
            break;

            case EXPORT_DATA:
                updateUserMsg(0,0,exportUserMsg,&displayUpdateStatus);
                key = getchar();
                while( getchar() != '\n' );
                if(key == AVANCAR)
                {
                    readyUserInterface(&displayUpdateStatus,cursorPosition);
                    menuTesteMain.menuState = getNextMain(ERASE_DATA);
                }
                else if(key == CONFIRMAR)
                {
                    readyUserInterface(&displayUpdateStatus,cursorPosition);
                    menuTesteMain.menuState = setSelectMain(&menuTesteMain.menuState);
                    exportStateMachine(&menuTesteSub);
                    menuTesteSub.menuState = IDDLE;
                    menuTesteSub.menuSelect = IDDLE;
                    menuTesteMain.menuState = getNextMain(START_TEST);
                }
            break;

            case ERASE_DATA:
                updateUserMsg(0,0,eraseUserMsg,&displayUpdateStatus);
                key = getchar();
                while( getchar() != '\n' );
                if(key == AVANCAR)
                {
                    readyUserInterface(&displayUpdateStatus,cursorPosition);
                    menuTesteMain.menuState = getNextMain(TESTE);
                }

                else if(key == CONFIRMAR)
                {
                    readyUserInterface(&displayUpdateStatus,cursorPosition);
                    menuTesteMain.menuState = setSelectMain(&menuTesteMain.menuState);
                    eraseStateMachine(&menuTesteSub);
                    menuTesteSub.menuState = IDDLE;
                    menuTesteSub.menuSelect = IDDLE;
                    menuTesteMain.menuState = getNextMain(START_TEST);
                }
            break;

            //Alterar a linha 112 (START_TEST ->TESTE)para que o case TESTE funcione
            case TESTE:
                printf("ESTADO DE TESTE - ACESSO AS VARIAVEIS PRIVADAS STRUCT MENU\n");
                key = getchar();
                while( getchar() != '\n' );
                if(key == AVANCAR) menuTesteMain.menuState = getNextMain(START_TEST);
                else if(key == CONFIRMAR)
                {
                     mainMenuArray = getDataMainMenuTest();
                     subMenuArray = getDataSubMenuTest();
                     for(unsigned char i =0;i<MAINMENU_SIZE;i++)
                    {
                        printf("Private MAIN menu\n");
                        printf("%d\n",mainMenuArray[i]);
                    }
                        printf("\n\n");
                    for(unsigned char i =0;i<SUBMENU_SIZE;i++)
                    {
                        printf("Private SUB menu\n");
                        printf("%d\n",subMenuArray[i]);
                    }
                }

            break;
        }
    }
}
