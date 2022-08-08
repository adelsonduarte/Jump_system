#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "Exportar_component.h"
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
    unsigned char userSelectSensorChannel;
};
struct Menu{
        unsigned char menuNext;
        unsigned char menuSelect;
        unsigned char menuDisplay;
        unsigned char menuState;
        struct dataInsert menuInsert;
    };

//APAGAR QUAIS DADOS? TODOS OS PARAMETROS INSERIDOS OU OS PARAMETROS LIDOS?
unsigned char eraseStateMachine(struct Menu* subMenu)
{
    struct Menu* subMenuErase = subMenu;
    unsigned char key = 0;
    unsigned char aux = 0;
    while(key != MENU)
    {
        switch(subMenuErase->menuState)
        {
            case IDDLE:
                subMenuErase->menuState = getNextSub(VERFICA_APAGAR);
            break;

            case VERFICA_APAGAR:
                printf("VERFICA_APAGAR\n");
                printf("%d\n",aux);
                key = getchar();
                while( getchar() != '\n' );
                if(key == INSERIR)
                {
                    aux++;
                    subMenuErase->menuState = getNextSub(VERFICA_APAGAR);
                }
                else if(key == CONFIRMAR)
                {
                    if(aux == CONFIRMA)
                    {
                        subMenuErase->menuSelect = setSelectSub(&subMenuErase->menuState);
                        subMenuErase->menuState = getNextSub(CONFIRMA_APAGAR);
                    }
                    else
                    {
                     subMenuErase->menuState = getNextSub(IDDLE);
                      key = MENU;
                    }
                }

            break;

            case CONFIRMA_APAGAR:
                printf("DADOS APAGADOS\n");
                //funcao para apagar os dados
                //if dados apagados = ok
                subMenuErase->menuState = getNextSub(IDDLE);
                key = MENU;
                break;
        }
    }
}
