#include <stdio.h>
#include <stdlib.h>
#include "menu_module.h"
#include "main.h"


unsigned char menuStateMachine(unsigned char* currentStateMenu)
{
    struct menuStruct selectMenu;
    struct menuStruct* ptr_selectMenu = &selectMenu;
    ptr_selectMenu->menuMainSelect = START_TEST;
    ptr_selectMenu->menuSubSelect = IDDLE;
//    static unsigned char key = 0;

    while(ptr_selectMenu->menuSubSelect == IDDLE)
    {
        switch(ptr_selectMenu->menuMainSelect)
        {
            case START_TEST:
                //display
                printf("INICIAR\n");
                *ptr_key = getchar();
                while(getchar() != '\n' );
                if(*ptr_key == AVANCAR)
                {
                  ptr_selectMenu->menuMainSelect = CONSULT_DATA;
                }
                else if(*ptr_key==CONFIRMAR)
                {
                    ptr_selectMenu->menuMainSelect = START_TEST;
                    ptr_selectMenu->menuSubSelect = START_TEST;
                }
                else
                {
                   ptr_selectMenu->menuMainSelect = START_TEST;
                }

            break;

            case CONSULT_DATA:
                //display
                printf("Consulta\n");
                *ptr_key = getchar();
                while( getchar() != '\n' );
                if(*ptr_key==AVANCAR)
                {
                    ptr_selectMenu->menuMainSelect = CONFIG_SENSOR;
                }
                else if(*ptr_key==CONFIRMAR)
                {
                    ptr_selectMenu->menuMainSelect = START_TEST;
                    ptr_selectMenu->menuSubSelect = COMMCONFIG;
                }
                else ptr_selectMenu->menuMainSelect = CONSULT_DATA;
            break;

            case CONFIG_SENSOR:
                //display
                printf("Configuracao\n");
                *ptr_key = getchar();
                while( getchar() != '\n' );
                if(*ptr_key==AVANCAR)
                {
                    ptr_selectMenu->menuMainSelect = EXPORT_DATA;
                }
                else if(*ptr_key==CONFIRMAR)
                {
                  ptr_selectMenu->menuMainSelect = START_TEST;
                  ptr_selectMenu->menuSubSelect = COMMCONFIG;
                }
                else ptr_selectMenu->menuMainSelect = CONFIG_SENSOR;
            break;
            case EXPORT_DATA:
                //display
                printf("Exportacao\n");
                *ptr_key = getchar();
                while( getchar() != '\n' );
                if(*ptr_key==AVANCAR)
                {
                    ptr_selectMenu->menuMainSelect = ERASE_DATA;
                }
                else if(*ptr_key==CONFIRMAR)
                {
                  ptr_selectMenu->menuMainSelect = START_TEST;
                  ptr_selectMenu->menuSubSelect = COMMCONFIG;
                }
                else ptr_selectMenu->menuMainSelect = EXPORT_DATA;
            break;
            case ERASE_DATA:
                printf("Apaga dados\n");
                *ptr_key = getchar();
                while( getchar() != '\n' );
                if(*ptr_key==AVANCAR || key==MENU)
                {
                   ptr_selectMenu->menuMainSelect = START_TEST;
                }
                else if(*ptr_key==CONFIRMAR)
                {
                  ptr_selectMenu->menuMainSelect = START_TEST;
                  ptr_selectMenu->menuSubSelect = ERASE_DATA;
                }
                else ptr_selectMenu->menuMainSelect = ERASE_DATA;
            break;

            default:
                {
                    ptr_selectMenu->menuMainSelect = START_TEST;
                    ptr_selectMenu->menuSubSelect = IDDLE;
                }
        }

    }
    return ptr_selectMenu->menuSubSelect;
}
