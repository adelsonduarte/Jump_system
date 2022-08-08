#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "Configuracao_component.h"
#include "SubMenu.h"

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
    unsigned char userSelectSensorChannel
};
struct Menu{
        unsigned char menuNext;
        unsigned char menuSelect;
        unsigned char menuDisplay;
        unsigned char menuState;
        struct dataInsert menuInsert;
    };

//toda maquina de estado deve ter um loop - > LEMBRAR LABVIEW

unsigned char configStateMachine(struct Menu* subMenu) //
{
    struct Menu* subMenuTesteConfigurar = subMenu;
    //verificar se vou usar
    struct dataInsert measurementSensor1;
    struct dataInsert measurementSensor2;
    //
    unsigned char key = 0;
    while(key != MENU)
    {
        switch(subMenuTesteConfigurar->menuState)
        {
        case IDDLE:
            subMenuTesteConfigurar->menuState = getNextSub(CONFIG_SENSOR_1);

            break;
            case CONFIG_SENSOR_1:
                printf("CONFIG_SENSOR_1\n");
                key = getchar();
                while( getchar() != '\n' );
                if(key == AVANCAR)
                {
                    subMenuTesteConfigurar->menuState = getNextSub(CONFIG_SENSOR_2);
                }
                else if(key == CONFIRMAR)
                {
                    subMenuTesteConfigurar->menuInsert.userSelectSensorChannel = 1;
                    subMenuTesteConfigurar->menuSelect = setSelectSub(&subMenuTesteConfigurar->menuState);
                    subMenuTesteConfigurar->menuState = getNextSub(SENSOR_ALTMIN);
                }

                break;

            case CONFIG_SENSOR_2:
                printf("CONFIG_SENSOR_2\n");
                key = getchar();
                while( getchar() != '\n' );
                if(key == AVANCAR)
                {
                    subMenuTesteConfigurar->menuState = getNextSub(CONFIG_SENSOR_1);
                }
                else if(key == CONFIRMAR)
                {
                    subMenuTesteConfigurar->menuInsert.userSelectSensorChannel = 2;
                    subMenuTesteConfigurar->menuSelect = setSelectSub(&subMenuTesteConfigurar->menuState);
                    subMenuTesteConfigurar->menuState = getNextSub(SENSOR_ALTMIN);
                }
                break;

            case SENSOR_ALTMIN:
                printf("SENSOR_ALTMIN: %d\n",subMenuTesteConfigurar->menuInsert.userAlturaMin);
                key = getchar();
                while( getchar() != '\n' );
                if(key == INSERIR)
                {
                    subMenuTesteConfigurar->menuInsert.userAlturaMin++;
                    subMenuTesteConfigurar->menuState = getNextSub(SENSOR_ALTMIN);
                }
                else if(key == CONFIRMAR)
                {
                    printf("SENSOR_ALTMIN = %d\n",subMenuTesteConfigurar->menuInsert.userAlturaMin);
                    setInsertSub(&subMenuTesteConfigurar->menuInsert);
                    subMenuTesteConfigurar->menuState = getNextSub(SENSOR_ALTMAX);
                    subMenuTesteConfigurar->menuSelect = setSelectSub(&subMenuTesteConfigurar->menuState);
                }
                break;

            case SENSOR_ALTMAX:
                printf("SENSOR_ALTMAX: %d\n",subMenuTesteConfigurar->menuInsert.userAlturaMax);
                key = getchar();
                while( getchar() != '\n' );
                if(key == INSERIR)
                {
                    subMenuTesteConfigurar->menuInsert.userAlturaMax++;
                    subMenuTesteConfigurar->menuState = getNextSub(SENSOR_ALTMAX);
                }
                else if(key == CONFIRMAR)
                {
                    printf("SENSOR_ALTMAX = %d\n",subMenuTesteConfigurar->menuInsert.userAlturaMax);
                    setInsertSub(&subMenuTesteConfigurar->menuInsert);
                    subMenuTesteConfigurar->menuState = getNextSub(SENSOR_SALTOS);
                    subMenuTesteConfigurar->menuSelect = setSelectSub(&subMenuTesteConfigurar->menuState);
                }

                break;

            case SENSOR_SALTOS:
                printf("SENSOR_SALTOS: %d\n",subMenuTesteConfigurar->menuInsert.userNumSaltos);
                key = getchar();
                while( getchar() != '\n' );
                if(key == INSERIR)
                {
                    subMenuTesteConfigurar->menuInsert.userNumSaltos++;
                    subMenuTesteConfigurar->menuState = getNextSub(SENSOR_SALTOS);
                }
                else if(key == CONFIRMAR)
                {
                    printf("SENSOR_SALTOS = %d\n",subMenuTesteConfigurar->menuInsert.userNumSaltos);
                    setInsertSub(&subMenuTesteConfigurar->menuInsert);
                    subMenuTesteConfigurar->menuState = getNextSub(SENSOR_INT_SALTOS);
                    subMenuTesteConfigurar->menuSelect = setSelectSub(&subMenuTesteConfigurar->menuState);
                }
                break;

            case SENSOR_INT_SALTOS:
                printf("SENSOR_INT_SALTOS: %d\n",subMenuTesteConfigurar->menuInsert.userIntervalSaltos);
                key = getchar();
                while( getchar() != '\n' );
                if(key == INSERIR)
                {
                    subMenuTesteConfigurar->menuInsert.userIntervalSaltos++;
                    subMenuTesteConfigurar->menuState = getNextSub(SENSOR_INT_SALTOS);
                }
                else if(key == CONFIRMAR)
                {
                    printf("SENSOR_INT_SALTOS = %d\n",subMenuTesteConfigurar->menuInsert.userIntervalSaltos);
                    setInsertSub(&subMenuTesteConfigurar->menuInsert);
                    subMenuTesteConfigurar->menuState = getNextSub(SENSOR_JMP_SELECT);
                    subMenuTesteConfigurar->menuSelect = setSelectSub(&subMenuTesteConfigurar->menuState);
                }

                break;

            case SENSOR_JMP_SELECT:
                printf("SENSOR_JMP_SELECT: %d\n",subMenuTesteConfigurar->menuInsert.userCMJ);
                key = getchar();
                while( getchar() != '\n' );
                if(key == INSERIR)
                {
                    subMenuTesteConfigurar->menuInsert.userCMJ++;
                    subMenuTesteConfigurar->menuState = getNextSub(SENSOR_JMP_SELECT);

                }
                else if(key == CONFIRMAR)
                {
                    if(subMenuTesteConfigurar->menuInsert.userCMJ == 3)
                    {
                        printf("SENSOR_JMP_SELECT = %d\n",subMenuTesteConfigurar->menuInsert.userCMJ);
                        setInsertSub(&subMenuTesteConfigurar->menuInsert);
                        subMenuTesteConfigurar->menuState = getNextSub(SENSOR_ALTDJ);
                        subMenuTesteConfigurar->menuSelect = setSelectSub(&subMenuTesteConfigurar->menuState);
                    }
                    else
                    {
                        printf("SENSOR_JMP_SELECT ou = %d\n",subMenuTesteConfigurar->menuInsert.userCMJ);
                        setInsertSub(&subMenuTesteConfigurar->menuInsert);
                        subMenuTesteConfigurar->menuState = getNextSub(SENSOR_SERIES);
                        subMenuTesteConfigurar->menuSelect = setSelectSub(&subMenuTesteConfigurar->menuState);
                    }
                    //TESTE trocar a variavel por uma local e o resultado enviar para subMenuTesteConfigurar->menuInsert.userCMJ.
                    subMenuTesteConfigurar->menuInsert.userCMJ=0;

                }

                break;

            case SENSOR_ALTDJ:
                printf("SENSOR_ALTDJ: %d\n",subMenuTesteConfigurar->menuInsert.userAlturaDJ);
                key = getchar();
                while( getchar() != '\n' );
                if(key == INSERIR)
                {
                    subMenuTesteConfigurar->menuInsert.userAlturaDJ++;
                    subMenuTesteConfigurar->menuState = getNextSub(SENSOR_ALTDJ);
                }
                else if(key == CONFIRMAR)
                {
                    printf("SENSOR_ALTDJ = %d\n",subMenuTesteConfigurar->menuInsert.userAlturaDJ);
                    setInsertSub(&subMenuTesteConfigurar->menuInsert);
                    subMenuTesteConfigurar->menuState = getNextSub(SENSOR_SERIES);
                    subMenuTesteConfigurar->menuSelect = setSelectSub(&subMenuTesteConfigurar->menuState);
                }

                break;

            case SENSOR_SERIES:
                printf("SENSOR_SERIES: %d\n",subMenuTesteConfigurar->menuInsert.userNumSeries);
                key = getchar();
                while( getchar() != '\n' );
                if(key == INSERIR)
                {
                    subMenuTesteConfigurar->menuInsert.userNumSeries++;
                    subMenuTesteConfigurar->menuState = getNextSub(SENSOR_SERIES);
                }
                else if(key == CONFIRMAR)
                {
                    printf("SENSOR_SERIES = %d\n",subMenuTesteConfigurar->menuInsert.userNumSeries);
                    setInsertSub(&subMenuTesteConfigurar->menuInsert);
                    subMenuTesteConfigurar->menuState = getNextSub(SENSOR_INT_SERIES);
                    subMenuTesteConfigurar->menuSelect = setSelectSub(&subMenuTesteConfigurar->menuState);
                }

                break;

            case SENSOR_INT_SERIES:
                printf("SENSOR_INT_SERIES: %d\n",subMenuTesteConfigurar->menuInsert.userIntervalSeries);
                key = getchar();
                while( getchar() != '\n' );
                if(key == INSERIR)
                {
                    subMenuTesteConfigurar->menuInsert.userIntervalSeries++;
                    subMenuTesteConfigurar->menuState = getNextSub(SENSOR_INT_SERIES);
                }
                else if(key == CONFIRMAR)
                {
                    printf("SENSOR_INT_SERIES = %d\n",subMenuTesteConfigurar->menuInsert.userIntervalSeries);
                    setInsertSub(&subMenuTesteConfigurar->menuInsert);
                    subMenuTesteConfigurar->menuState = getNextSub(TAPETE_ON);
                    subMenuTesteConfigurar->menuSelect = setSelectSub(&subMenuTesteConfigurar->menuState);
                }

            break;

            case TAPETE_ON:
                printf("TAPETE_ON?\n");
                key = getchar();
                while( getchar() != '\n' );
                if(key == AVANCAR)
                {
                    subMenuTesteConfigurar->menuState = getNextSub(TAPETE_OFF);
                }
                else if(key == CONFIRMAR)
                {
                    subMenuTesteConfigurar->menuSelect = setSelectSub(&subMenuTesteConfigurar->menuState);
                    subMenuTesteConfigurar->menuInsert.userSelectTapete = TRUE;
                    setInsertSub(&subMenuTesteConfigurar->menuInsert);
                    subMenuTesteConfigurar->menuState = getNextSub(CONFIG_SENSOR_1);
                    key = MENU;
                }
                break;

            case TAPETE_OFF:
                printf("TAPETE_OFF?\n");
                key = getchar();
                while( getchar() != '\n' );
                if(key == AVANCAR)
                {
                    subMenuTesteConfigurar->menuState = getNextSub(TAPETE_ON);
                }
                else if(key == CONFIRMAR)
                {
                    subMenuTesteConfigurar->menuSelect = setSelectSub(&subMenuTesteConfigurar->menuState);
                    subMenuTesteConfigurar->menuInsert.userSelectTapete = FALSE;
                    setInsertSub(&subMenuTesteConfigurar->menuInsert);
                    subMenuTesteConfigurar->menuState = getNextSub(CONFIG_SENSOR_1);
                    key = MENU;
                }
                break;
        }
    }
}
