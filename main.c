#include <stdio.h>
#include <stdlib.h>
#include "menu_module.h"
#include "main.h"
#include "INICIAR_Component.h"
#include "Consulta_component.h"


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


    struct Menu menuTesteMain = {IDDLE,IDDLE,IDDLE,IDDLE};
    struct Menu menuTesteSub = {IDDLE,IDDLE,IDDLE,IDDLE};
    unsigned char* mainMenuArray;
    unsigned char* subMenuArray;
    //Esse while é só pra teste. Na aplicação real teremos interrupção para chamar o menu_module.c
    while(1)
    {
        switch(menuTesteMain.menuState)
        {
            case IDDLE:
                printf("05.Jump System NG\nCEFISE Versao 0.1 0.1\n");
                key = getchar();
                while( getchar() != '\n' );
                if(key == AVANCAR) menuTesteMain.menuState = getNextMain(START_TEST);
                else if(key == CONFIRMAR)  menuTesteMain.menuState = setSelectMain(&menuTesteMain.menuState);
            break;
            case START_TEST:
                printf("chama .c com a maquina de estado do START_TEST\n");
                key = getchar();
                while( getchar() != '\n' );
                if(key == AVANCAR) menuTesteMain.menuState = getNextMain(CONSULT_DATA);
                else if(key == CONFIRMAR)
                {
                    menuTesteMain.menuState = setSelectMain(&menuTesteMain.menuState);
                    menuTesteMain.menuSelect = menuTesteMain.menuState;
                    initStateMachine(&menuTesteSub);
                    menuTesteSub.menuState = IDDLE;
                    menuTesteSub.menuSelect = IDDLE;
                }
            break;

            case CONSULT_DATA:
                printf("chama .c com a maquina de estado do CONSULT_DATA\n");
                key = getchar();
                while( getchar() != '\n' );
                if(key == AVANCAR) menuTesteMain.menuState = getNextMain(CONFIG_SENSOR);
                else if(key == CONFIRMAR)
                {
                   menuTesteMain.menuState = setSelectMain(&menuTesteMain.menuState);
                   consultStateMachine(&menuTesteSub);
                   menuTesteMain.menuState = getNextMain(START_TEST);
                   menuTesteSub.menuState = IDDLE;
                   menuTesteSub.menuSelect = IDDLE;
                }
            break;

            case CONFIG_SENSOR:
                printf("chama .c com a maquina de estado do CONFIG_SENSOR\n");
                key = getchar();
                while( getchar() != '\n' );
                if(key == AVANCAR) menuTesteMain.menuState = getNextMain(EXPORT_DATA);
                else if(key == CONFIRMAR)
                {
                    menuTesteMain.menuState = setSelectMain(&menuTesteMain.menuState);
                    configStateMachine(&menuTesteSub);
                    menuTesteSub.menuState = IDDLE;
                    menuTesteSub.menuSelect = IDDLE;
                    menuTesteMain.menuState = getNextMain(START_TEST);
                }
            break;

            case EXPORT_DATA:
                printf("chama .c com a maquina de estado do EXPORT_DATA\n");
                key = getchar();
                while( getchar() != '\n' );
                if(key == AVANCAR) menuTesteMain.menuState = getNextMain(ERASE_DATA);
                else if(key == CONFIRMAR)
                {
                    menuTesteMain.menuState = setSelectMain(&menuTesteMain.menuState);
                    exportStateMachine(&menuTesteSub);
                    menuTesteSub.menuState = IDDLE;
                    menuTesteSub.menuSelect = IDDLE;
                    menuTesteMain.menuState = getNextMain(START_TEST);
                }
            break;

            case ERASE_DATA:
                printf("chama .c com a maquina de estado do ERASE_DATA\n");
                key = getchar();
                while( getchar() != '\n' );
                if(key == AVANCAR) menuTesteMain.menuState = getNextMain(TESTE);
                else if(key == CONFIRMAR)
                {
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
