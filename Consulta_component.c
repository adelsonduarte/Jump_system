#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "Consulta_component.h"
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

//toda maquina de estado deve ter um loop - > LEMBRAR LABVIEW

unsigned char consultStateMachine(struct Menu* subMenu)
{
    struct Menu* subMenuTesteConsultar = subMenu;
    unsigned char key = 0;
    static unsigned char results = 0;
//    struct Menu subMenuTesteConsultar = {COMM_OFF,COMM_OFF,COMM_OFF,COMM_OFF};
    while(key != MENU)
    {
        switch(subMenuTesteConsultar->menuState)
        {
            case IDDLE:
                subMenuTesteConsultar->menuState = getNextSub(CONSULTA_TESTE);
            break;
            case CONSULTA_TESTE:
                printf("CONSULTA_TESTE: %d\n",subMenuTesteConsultar->menuInsert.userConsultTest);
                key = getchar();
                while( getchar() != '\n' );
                if(key == INSERIR)
                {
                    subMenuTesteConsultar->menuInsert.userConsultTest++;
                    subMenuTesteConsultar->menuState = getNextSub(CONSULTA_TESTE);
                }
                else if(key == CONFIRMAR)
                {
                    printf("CONSULTA_TESTE: %d\n",subMenuTesteConsultar->menuInsert.userConsultTest);
                    setInsertSub(&subMenuTesteConsultar->menuInsert);
                    subMenuTesteConsultar->menuState = getNextSub(RESULT_TESTE);
                    subMenuTesteConsultar->menuSelect = setSelectSub(&subMenuTesteConsultar->menuState);
                }
            break;

            case RESULT_TESTE:
                printf("TESTE %d DADO %d\n",subMenuTesteConsultar->menuInsert.userConsultTest,results);
//                subMenuTesteConsultar->menuDisplay = getDisplaySub(&subMenuTesteConsultar->menuDisplay);
                key = getchar();
                while( getchar() != '\n' );
                if(key == AVANCAR)
                {
                    results++;
                    subMenuTesteConsultar->menuState = getNextSub(RESULT_TESTE);
                }
                else if(key == PARAR)
                {
                    subMenuTesteConsultar->menuState = getNextSub(EXPORTAR);
                }
                break;

            case EXPORTAR:
                printf("EXPORTAR\n");
                key = getchar();
                while( getchar() != '\n' );
                if(key == PARAR)
                {
                    key = MENU; // ta errado mas coloquei aqui pra teste
                    subMenuTesteConsultar->menuState = getNextSub(CONSULTA_TESTE);
                }
                else if(key == CONFIRMAR)
                {
                    //display
                    subMenuTesteConsultar->menuSelect = setSelectSub(&subMenuTesteConsultar->menuState);
                    printf("Exportando...\n");
                    subMenuTesteConsultar->menuState = getNextSub(CONSULTA_TESTE);
                    key = MENU; // ta errado mas coloquei aqui pra teste
                }
                break;
        }
    }
}
